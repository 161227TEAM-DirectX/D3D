#include "stdafx.h"
#include "terrain.h"
#include "dijkstra.h"
#include "Node.h"
#include "Action.h"
#include "ActionSeq.h"
#include "ActionMove.h"
#include "ActionReMove.h"

dijkstra::dijkstra()
{

}


dijkstra::~dijkstra()
{
	for (int i = 0; i < vecNode.size(); i++)
	{
		SAFE_DELETE(vecNode[i]);
	}
}

void dijkstra::render(void)
{
	D3DXMATRIXA16 matT;
	D3DXMATRIX oldMat;

	_device->GetTransform(D3DTS_WORLD, &oldMat);
	_device->SetTransform(D3DTS_WORLD, &matT);

	for (int i = 0; i < adj.size(); i++)
	{
		for (int j = 0; j < adj[i].size(); j++)
		{
			GIZMOMANAGER->Line(vecNode[i]->getPosition(), vecNode[adj[i][j].first]->getPosition(), D3DCOLOR_XRGB(255,0,255));
		}
	}

	_device->SetTransform(D3DTS_WORLD, &oldMat);
}

void dijkstra::addNode(D3DXVECTOR3 pos)
{
	Node* temp = nullptr;

	temp = new Node;
	//pos.y = 0.0f;
	temp->setPosition(pos);
	temp->setMesh(0.2f);

	if (vecNode.empty())temp->setSelfIndex(0);
	else temp->setSelfIndex(vecNode.size());

	vecNode.push_back(temp);
	adj.resize(vecNode.size());
}

void dijkstra::connectNode(int& sour, int& dest)
{
	int tempSour = sour;
	int tempDest = dest;

	//출발지(tempSour)에서 목적지(tempDest)로의 벡터를 구한다.
	D3DXVECTOR3 path = vecNode[tempDest]->getPosition() - vecNode[tempSour]->getPosition();
	float cost = D3DXVec3Length(&path);

	adj[tempSour].push_back(make_pair(tempDest, cost));
	adj[tempDest].push_back(make_pair(tempSour, cost));

	sour = -1; dest = -1;
}

void dijkstra::FindPath(D3DXVECTOR3 vSt, D3DXVECTOR3 vDst/*, vector<baseObject*>& object*/)
{
	bool isCollision = false;
	vector<float> dist(vecNode.size(), FLT_MAX);	//모든 벡터의 dist(거리값)을 가지고 있을 임시 벡터
	vector<int> swap;
	path.swap(swap);
	//path.clear();
	map<int, pair<float, int>> mapSwap;
	tempPath.swap(mapSwap);
	//tempPath.clear();
	

	//오류처리 노드가 없다면 길을 찾지 마라.
	if (vecNode.size() <= 0) return;

	for (int i = 0; i < vecNode.size(); i++)
	{
		//정점 코스트를 무한대로 설정
		vecNode[i]->setCost(FLT_MAX);
		//정점 방문변수를 초기화
		vecNode[i]->setVisited(false);
		//Via(이전노드)를 초기화
		vecNode[i]->setVia(-1);
	}

	int startIndex = -1;		//시작 노드
	int DestIndex = -1;			//목적지 노드

	float fDistance = FLT_MAX;
	//모든 정점을 돌며 현재 주전자에서 가장 가까운 시작 노드를 찾는다.
	for (size_t  i = 0; i < vecNode.size(); i++)
	{
		isCollision = false;
		//두 정점(시작위치(케릭터위치), i번째 벡터 위치)사이의 벡터를 구한다.
		D3DXVECTOR3 v = vecNode[i]->getPosition() - vSt;
		float tempDistance = D3DXVec3Length(&v);

		if (fDistance > tempDistance)
		{
			fDistance = tempDistance;
			startIndex = i;
		}
	}

	fDistance = FLT_MAX;
	//모든 정점을 돌며 현재 목적지에서 가장 가까운 노드를 찾는다.
	for (size_t i = 0; i < vecNode.size(); i++)
	{
		isCollision = false;
		//출발지에서 노드를 바라보는 방향벡터를 가져온다.(두 점 사이의 벡터를 가져온다)
		D3DXVECTOR3 v = vecNode[i]->getPosition() - vDst;
		//두 점 사이의 거리를 구한다.
		float tempDistance = D3DXVec3Length(&v);

		if (fDistance > tempDistance)
		{
			fDistance = tempDistance;
			DestIndex = i;
		}
	}

	dist[startIndex] = 0.0f;
	vecNode[startIndex]->setCost(0);
	vecNode[startIndex]->setVia(startIndex);

	//우선순위 큐에 모든 정점을 저장(정점은 cost = FLT_MAX, via = -1, visited = false) 
	//단 startIndex는 visited빼고는 위에 설정한 대로 간다.
	for (size_t i = 0; i < vecNode.size(); i++)
	{
		pq.push(vecNode[i]);
	}

	tempPath.insert(make_pair(startIndex, make_pair(0, -1)));

	while (!pq.empty())
	{
		//노드가 가지고 있는 노드벡터에서의 인덱스 값을 가져온다.
		int index = pq.top()->getSelfIndex();
		//노드가 가지고 있는 코스트값(이동비용)을 가져온다.
		float cost = pq.top()->getCost();
		//제거
		pq.pop();

		//거리값을 확인하고 cost가 더 크다면 넘어간다.
		//왜냐하면 이미 최적화된 이동 경로가 있다는 의미이기 때문에 또 다시 계산을 할 필요는 없다.
		if (dist[index] < cost) continue;

		//cost값이 더 크다면 경로를 찾아야 한다는 소리이다.
		//이를 위해 현색 index가 가지고 있는 인접 노드를 파악하여 노드들의 cost를 수정한다.
		for (int i = 0; i < adj[index].size(); i++)
		{
			//인접노드의 first는 인덱스값이다.
			int n = adj[index][i].first;
			//인접노드의 second는 경로값이다.
			float v = adj[index][i].second;

			//현재인덱스까지의 누적 경로보다 인접경로의 경로가 더 짧다면 실행하라.
			if (dist[n] > dist[index] + v)
			{
				dist[n] = dist[index] + v;
				Node* temp = new Node(n, dist[n], index, *vecNode[n]);
				pq.push(temp);
				tempPath[n] = make_pair(dist[n], index);
			}
		}
	}

	int next = DestIndex;
	while (next != -1)
	{
		path.push_back(next);
		next = tempPath[next].second;
	}
}

ActionSeq* dijkstra::OptimizedAction(baseObject& player, baseObject& playerObject, terrain& rand, vector<baseObject*>& object, D3DXVECTOR3 vStart, D3DXVECTOR3 vDest)
{
	bool collision = false;
	int startNodeIndex = -1;

	if (path.size() <= 0)
	{
		ActionSeq* actionSeq = new ActionSeq;

		ActionMove* aM = new ActionMove;

		aM->setFrom(vStart);
		aM->setTo(vDest);
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		aM->setPlayerObject(playerObject);
		actionSeq->AddAction(aM);
		aM = nullptr;

		return actionSeq;
	}

	//시작지점에서 모든 노드를 확인하며 장애물이 있는지 파악 후 장애물이 없다면 직행으로 그 노드로 가는 방법
	//
	for (int i = path.size() - 1; i >= 0; --i)
	{
		if (collision) break;
	//	float fDist = FLT_MAX;
		D3DXVECTOR3 hitpos;
		Ray picker(vStart, vecNode[path[i]]->getPosition() - vStart);

		if (object.size() == 0)
		{
			startNodeIndex = 0;
			break;
		}

		for (int j = 0; j < object.size(); j++)
		{
			if (PHYSICSMANAGER->isRayHitBound(&picker, &object[j]->_boundBox, object[j]->_transform, &hitpos, nullptr))
			{
				collision = true;
				if (startNodeIndex == -1 || startNodeIndex == (path.size()-1)) break;
				else
				{
					startNodeIndex++;
					break;
				}
			}
			else startNodeIndex = i;
		}	
	}

	int destNodeIndex = -1;
	collision = false;

	//목적지에서 모든 노드를 검사
	for (int i = 0; i < path.size(); ++i)
	{
		if (collision) break;
	//	float fDist = FLT_MAX;
		D3DXVECTOR3 hitpos;
		Ray picker = { vDest, vecNode[path[i]]->getPosition() - vDest };

		if (object.size() == 0)
		{
			destNodeIndex = path.size() - 1;
			break;
		}

		for (int j = 0; j < object.size(); j++)
		{
			if (PHYSICSMANAGER->isRayHitBound(&picker, &object[j]->_boundBox, object[j]->_transform, &hitpos, nullptr))
			{
				collision = true;
				if (destNodeIndex == -1 || destNodeIndex == 0) break;
				else
				{
					destNodeIndex--;
					break;
				}
			}
			else
			{
				destNodeIndex = i;
			}
		}
	}

	if (destNodeIndex < 0 || startNodeIndex < 0) return nullptr;

	//현재 위치에서 목적지 까지 충돌되지 않고 최단거리일 경우 그냥 바로 이동한다.
	float nodeDistance = D3DXVec3Length(&(vStart - vecNode[path[startNodeIndex]]->getPosition()));
	float destDistance = D3DXVec3Length(&(vStart - vDest));

	if (nodeDistance > destDistance)
	{
		bool collision = false;
		Ray picker = { vStart, vStart - vDest };
		D3DXVECTOR3 hitpos;

		for (int j = 0; j < object.size(); j++)
		{
			if (PHYSICSMANAGER->isRayHitBound(&picker, &object[j]->_boundBox, object[j]->_transform, &hitpos, nullptr))
			{
				collision = true;
			}
		}

		if (!collision)
		{
			ActionSeq* actionSeq = new ActionSeq;

			ActionMove* aM = new ActionMove;

			aM->setFrom(vStart);
			aM->setTo(vDest);
			aM->setOwner(player);
			aM->setRand(rand);
			aM->setObject(object);
			aM->setPlayerObject(playerObject);
			actionSeq->AddAction(aM);
			aM = nullptr;

			return actionSeq;
		}
	}

	ActionSeq* actionSeq = nullptr;

	//시작 값이 더 크면
	if (destNodeIndex < startNodeIndex)
	{
		actionSeq = new ActionSeq;

		ActionMove* aM = new ActionMove;

		aM->setFrom(vStart);
		aM->setTo(vecNode[path[startNodeIndex]]->getPosition());
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		aM->setPlayerObject(playerObject);
		actionSeq->AddAction(aM);
		aM = nullptr;

		for (int i = startNodeIndex; i > destNodeIndex; --i)
		{
			aM = new ActionMove;
			aM->setFrom(vecNode[path[i]]->getPosition());
			aM->setTo(vecNode[path[i - 1]]->getPosition());
			aM->setObject(object);
			aM->setOwner(player);
			aM->setRand(rand);
			aM->setPlayerObject(playerObject);
			actionSeq->AddAction(aM);
			aM = nullptr;
		}

		aM = new ActionMove;
		aM->setFrom(vecNode[path[destNodeIndex]]->getPosition());
		aM->setTo(vDest);
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		aM->setPlayerObject(playerObject);
		actionSeq->AddAction(aM);
		aM = nullptr;
	}
	else if(destNodeIndex == startNodeIndex)
	{
		actionSeq = new ActionSeq;

		ActionMove* aM = nullptr;

		aM = new ActionMove;

		aM->setFrom(vStart);
		aM->setTo(vecNode[path[startNodeIndex]]->getPosition());
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		aM->setPlayerObject(playerObject);
		actionSeq->AddAction(aM);
		aM = nullptr;

		aM = new ActionMove;
		aM->setFrom(vecNode[path[destNodeIndex]]->getPosition());
		aM->setTo(vDest);
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		aM->setPlayerObject(playerObject);
		actionSeq->AddAction(aM);
		aM = nullptr;
	}
	else
	{
		actionSeq = new ActionSeq;

		ActionMove* aM = new ActionMove;

		aM->setFrom(vStart);
		aM->setTo(vecNode[path[path.size()-1]]->getPosition());
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		aM->setPlayerObject(playerObject);
		actionSeq->AddAction(aM);
		aM = nullptr;

		for (int i = path.size() - 1; i > 0; --i)
		{
			aM = new ActionMove;
			aM->setFrom(vecNode[path[i]]->getPosition());
			aM->setTo(vecNode[path[i - 1]]->getPosition());
			aM->setObject(object);
			aM->setOwner(player);
			aM->setRand(rand);
			aM->setPlayerObject(playerObject);
			actionSeq->AddAction(aM);
			aM = nullptr;
		}

		aM = new ActionMove;
		aM->setFrom(vecNode[path[0]]->getPosition());
		aM->setTo(vDest);
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		aM->setPlayerObject(playerObject);
		actionSeq->AddAction(aM);
		aM = nullptr;
	}

	return actionSeq;
}

ActionSeq * dijkstra::OptimizedAction(baseObject & player, terrain & rand, vector<baseObject*>& object, D3DXVECTOR3 vStart, D3DXVECTOR3 vDest)
{
	bool collision = false;
	int startNodeIndex = -1;

	if (path.size() <= 0)
	{
		ActionSeq* actionSeq = new ActionSeq;

		ActionReMove* aM = new ActionReMove;

		aM->setFrom(vStart);
		aM->setTo(vDest);
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		actionSeq->AddAction(aM);
		aM = nullptr;

		return actionSeq;
	}

	//시작지점에서 모든 노드를 확인하며 장애물이 있는지 파악 후 장애물이 없다면 직행으로 그 노드로 가는 방법
	//
	for (int i = path.size() - 1; i >= 0; --i)
	{
		if (collision) break;
		//	float fDist = FLT_MAX;
		D3DXVECTOR3 hitpos;
		Ray picker(vStart, vecNode[path[i]]->getPosition() - vStart);

		if (object.size() == 0)
		{
			startNodeIndex = 0;
			break;
		}

		for (int j = 0; j < object.size(); j++)
		{
			if (PHYSICSMANAGER->isRayHitBound(&picker, &object[j]->_boundBox, object[j]->_transform, &hitpos, nullptr))
			{
				collision = true;
				if (startNodeIndex == -1 || startNodeIndex == (path.size() - 1)) break;
				else
				{
					startNodeIndex++;
					break;
				}
			}
			else startNodeIndex = i;
		}
	}

	int destNodeIndex = -1;
	collision = false;

	//목적지에서 모든 노드를 검사
	for (int i = 0; i < path.size(); ++i)
	{
		if (collision) break;
		//	float fDist = FLT_MAX;
		D3DXVECTOR3 hitpos;
		Ray picker = { vDest, vecNode[path[i]]->getPosition() - vDest };

		if (object.size() == 0)
		{
			destNodeIndex = path.size() - 1;
			break;
		}

		for (int j = 0; j < object.size(); j++)
		{
			if (PHYSICSMANAGER->isRayHitBound(&picker, &object[j]->_boundBox, object[j]->_transform, &hitpos, nullptr))
			{
				collision = true;
				if (destNodeIndex == -1 || destNodeIndex == 0) break;
				else
				{
					destNodeIndex--;
					break;
				}
			}
			else
			{
				destNodeIndex = i;
			}
		}
	}

	if (destNodeIndex < 0 || startNodeIndex < 0) return nullptr;

	//현재 위치에서 목적지 까지 충돌되지 않고 최단거리일 경우 그냥 바로 이동한다.
	float nodeDistance = D3DXVec3Length(&(vStart - vecNode[path[startNodeIndex]]->getPosition()));
	float destDistance = D3DXVec3Length(&(vStart - vDest));

	if (nodeDistance > destDistance)
	{
		bool collision = false;
		Ray picker = { vStart, vStart - vDest };
		D3DXVECTOR3 hitpos;

		for (int j = 0; j < object.size(); j++)
		{
			if (PHYSICSMANAGER->isRayHitBound(&picker, &object[j]->_boundBox, object[j]->_transform, &hitpos, nullptr))
			{
				collision = true;
			}
		}

		if (!collision)
		{
			ActionSeq* actionSeq = new ActionSeq;

			ActionReMove* aM = new ActionReMove;

			aM->setFrom(vStart);
			aM->setTo(vDest);
			aM->setOwner(player);
			aM->setRand(rand);
			aM->setObject(object);
			actionSeq->AddAction(aM);
			aM = nullptr;

			return actionSeq;
		}
	}

	ActionSeq* actionSeq = nullptr;

	//시작 값이 더 크면
	if (destNodeIndex < startNodeIndex)
	{
		actionSeq = new ActionSeq;

		ActionReMove* aM = new ActionReMove;

		aM->setFrom(vStart);
		aM->setTo(vecNode[path[startNodeIndex]]->getPosition());
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		actionSeq->AddAction(aM);
		aM = nullptr;

		for (int i = startNodeIndex; i > destNodeIndex; --i)
		{
			aM = new ActionReMove;
			aM->setFrom(vecNode[path[i]]->getPosition());
			aM->setTo(vecNode[path[i - 1]]->getPosition());
			aM->setObject(object);
			aM->setOwner(player);
			aM->setRand(rand);
			actionSeq->AddAction(aM);
			aM = nullptr;
		}

		aM = new ActionReMove;
		aM->setFrom(vecNode[path[destNodeIndex]]->getPosition());
		aM->setTo(vDest);
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		actionSeq->AddAction(aM);
		aM = nullptr;
	}
	else if (destNodeIndex == startNodeIndex)
	{
		actionSeq = new ActionSeq;

		ActionReMove* aM = nullptr;

		aM = new ActionReMove;

		aM->setFrom(vStart);
		aM->setTo(vecNode[path[startNodeIndex]]->getPosition());
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		actionSeq->AddAction(aM);
		aM = nullptr;

		aM = new ActionReMove;
		aM->setFrom(vecNode[path[destNodeIndex]]->getPosition());
		aM->setTo(vDest);
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		actionSeq->AddAction(aM);
		aM = nullptr;
	}
	else
	{
		actionSeq = new ActionSeq;

		ActionReMove* aM = new ActionReMove;

		aM->setFrom(vStart);
		aM->setTo(vecNode[path[path.size() - 1]]->getPosition());
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		actionSeq->AddAction(aM);
		aM = nullptr;

		for (int i = path.size() - 1; i > 0; --i)
		{
			aM = new ActionReMove;
			aM->setFrom(vecNode[path[i]]->getPosition());
			aM->setTo(vecNode[path[i - 1]]->getPosition());
			aM->setObject(object);
			aM->setOwner(player);
			aM->setRand(rand);
			actionSeq->AddAction(aM);
			aM = nullptr;
		}

		aM = new ActionReMove;
		aM->setFrom(vecNode[path[0]]->getPosition());
		aM->setTo(vDest);
		aM->setOwner(player);
		aM->setRand(rand);
		aM->setObject(object);
		actionSeq->AddAction(aM);
		aM = nullptr;
	}

	return actionSeq;
}