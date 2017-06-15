#pragma once
#include "Node.h"

class Action;
class terrain;
class ActionSeq;
//const float MOVETIME = 1.5f;

class dijkstra
{
private:
	struct comp
	{
		bool operator()(Node* E1, Node* E2) {
			return E1->getCost() > E2->getCost();
		}
	};

private:
	vector<Node*>			vecNode;						//노드를 가지고 있는 벡터
	vector<vector<pair<int, float>>> adj;					//각 노드의 인접 노드를 가지고 있는 벡터2중
	priority_queue<Node*, vector<Node*>, comp>	pq;			//계산을 할 우선순위 큐
	map<int, pair<float, int>> tempPath;					//각 노드에서 갈 최단거리를 가지고 있는 맵
	vector<int>					path;						//최종 경로
public:
	dijkstra();
	~dijkstra();

	void render(void);

	void addNode(D3DXVECTOR3 pos);

	const vector<Node*>& getVecNode(void) { return vecNode; }
	Node* getVecNode(int i) { return vecNode[i]; }

	const vector<vector<pair<int, float>>>& getadjNode(void) { return adj; }

	const vector<int>& getPath(void) { return path; }

public:
	void connectNode(int& sour, int& dest);
	void FindPath(D3DXVECTOR3 vSt, D3DXVECTOR3 vDst/*, vector<baseObject*>& object*/);
	ActionSeq* OptimizedAction(baseObject& player, baseObject& enemy, terrain& rand, vector<baseObject*>& object, D3DXVECTOR3 vStart, D3DXVECTOR3 vDest);
	ActionSeq* OptimizedAction(baseObject& player, terrain& rand, vector<baseObject*>& object, D3DXVECTOR3 vStart, D3DXVECTOR3 vDest);
};

