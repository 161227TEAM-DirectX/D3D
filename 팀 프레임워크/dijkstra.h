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
	vector<Node*>			vecNode;						//��带 ������ �ִ� ����
	vector<vector<pair<int, float>>> adj;					//�� ����� ���� ��带 ������ �ִ� ����2��
	priority_queue<Node*, vector<Node*>, comp>	pq;			//����� �� �켱���� ť
	map<int, pair<float, int>> tempPath;					//�� ��忡�� �� �ִܰŸ��� ������ �ִ� ��
	vector<int>					path;						//���� ���
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

