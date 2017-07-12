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

	//�����(tempSour)���� ������(tempDest)���� ���͸� ���Ѵ�.
	D3DXVECTOR3 path = vecNode[tempDest]->getPosition() - vecNode[tempSour]->getPosition();
	float cost = D3DXVec3Length(&path);

	adj[tempSour].push_back(make_pair(tempDest, cost));
	adj[tempDest].push_back(make_pair(tempSour, cost));

	sour = -1; dest = -1;
}

void dijkstra::FindPath(D3DXVECTOR3 vSt, D3DXVECTOR3 vDst/*, vector<baseObject*>& object*/)
{
	bool isCollision = false;
	vector<float> dist(vecNode.size(), FLT_MAX);	//��� ������ dist(�Ÿ���)�� ������ ���� �ӽ� ����
	vector<int> swap;
	path.swap(swap);
	//path.clear();
	map<int, pair<float, int>> mapSwap;
	tempPath.swap(mapSwap);
	//tempPath.clear();
	

	//����ó�� ��尡 ���ٸ� ���� ã�� ����.
	if (vecNode.size() <= 0) return;

	for (int i = 0; i < vecNode.size(); i++)
	{
		//���� �ڽ�Ʈ�� ���Ѵ�� ����
		vecNode[i]->setCost(FLT_MAX);
		//���� �湮������ �ʱ�ȭ
		vecNode[i]->setVisited(false);
		//Via(�������)�� �ʱ�ȭ
		vecNode[i]->setVia(-1);
	}

	int startIndex = -1;		//���� ���
	int DestIndex = -1;			//������ ���

	float fDistance = FLT_MAX;
	//��� ������ ���� ���� �����ڿ��� ���� ����� ���� ��带 ã�´�.
	for (size_t  i = 0; i < vecNode.size(); i++)
	{
		isCollision = false;
		//�� ����(������ġ(�ɸ�����ġ), i��° ���� ��ġ)������ ���͸� ���Ѵ�.
		D3DXVECTOR3 v = vecNode[i]->getPosition() - vSt;
		float tempDistance = D3DXVec3Length(&v);

		if (fDistance > tempDistance)
		{
			fDistance = tempDistance;
			startIndex = i;
		}
	}

	fDistance = FLT_MAX;
	//��� ������ ���� ���� ���������� ���� ����� ��带 ã�´�.
	for (size_t i = 0; i < vecNode.size(); i++)
	{
		isCollision = false;
		//��������� ��带 �ٶ󺸴� ���⺤�͸� �����´�.(�� �� ������ ���͸� �����´�)
		D3DXVECTOR3 v = vecNode[i]->getPosition() - vDst;
		//�� �� ������ �Ÿ��� ���Ѵ�.
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

	//�켱���� ť�� ��� ������ ����(������ cost = FLT_MAX, via = -1, visited = false) 
	//�� startIndex�� visited����� ���� ������ ��� ����.
	for (size_t i = 0; i < vecNode.size(); i++)
	{
		pq.push(vecNode[i]);
	}

	tempPath.insert(make_pair(startIndex, make_pair(0, -1)));

	while (!pq.empty())
	{
		//��尡 ������ �ִ� ��庤�Ϳ����� �ε��� ���� �����´�.
		int index = pq.top()->getSelfIndex();
		//��尡 ������ �ִ� �ڽ�Ʈ��(�̵����)�� �����´�.
		float cost = pq.top()->getCost();
		//����
		pq.pop();

		//�Ÿ����� Ȯ���ϰ� cost�� �� ũ�ٸ� �Ѿ��.
		//�ֳ��ϸ� �̹� ����ȭ�� �̵� ��ΰ� �ִٴ� �ǹ��̱� ������ �� �ٽ� ����� �� �ʿ�� ����.
		if (dist[index] < cost) continue;

		//cost���� �� ũ�ٸ� ��θ� ã�ƾ� �Ѵٴ� �Ҹ��̴�.
		//�̸� ���� ���� index�� ������ �ִ� ���� ��带 �ľ��Ͽ� ������ cost�� �����Ѵ�.
		for (int i = 0; i < adj[index].size(); i++)
		{
			//��������� first�� �ε������̴�.
			int n = adj[index][i].first;
			//��������� second�� ��ΰ��̴�.
			float v = adj[index][i].second;

			//�����ε��������� ���� ��κ��� ��������� ��ΰ� �� ª�ٸ� �����϶�.
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

	//������������ ��� ��带 Ȯ���ϸ� ��ֹ��� �ִ��� �ľ� �� ��ֹ��� ���ٸ� �������� �� ���� ���� ���
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

	//���������� ��� ��带 �˻�
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

	//���� ��ġ���� ������ ���� �浹���� �ʰ� �ִܰŸ��� ��� �׳� �ٷ� �̵��Ѵ�.
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

	//���� ���� �� ũ��
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

	//������������ ��� ��带 Ȯ���ϸ� ��ֹ��� �ִ��� �ľ� �� ��ֹ��� ���ٸ� �������� �� ���� ���� ���
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

	//���������� ��� ��带 �˻�
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

	//���� ��ġ���� ������ ���� �浹���� �ʰ� �ִܰŸ��� ��� �׳� �ٷ� �̵��Ѵ�.
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

	//���� ���� �� ũ��
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