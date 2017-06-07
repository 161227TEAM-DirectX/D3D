#pragma once
#include "gameNode.h"
#include "terrain.h"
//#include "dijkstra.h"
#include "monster.h"

class terrainPickingTest : public gameNode
{
private:
	enum SELECTFUNC
	{
		SELECT_NODE = 1,
		SELECT_LINE,
		SELECT_MOVING,
		SELECT_OBJECT,
		SELECT_NONE
	};

private:
//	dijkstra*			tempDijkstra;
	monster*			player;
	baseObject*			enemy;
	terrain*			_terrain;	//����Ŭ����
	dx::transform*		_trans;		//Ʈ������
	lightDirection*		_dirLight;	//�𷺼Ƕ���Ʈ
	D3DXVECTOR3			_hitPos;	//��Ʈ ������
	SELECTFUNC			lButtonState;
	vector<light*>		_lights;
	vector<baseObject*> testObject;

	int sour;					//��� ����� ��� ��� �ε�����
	int dest;					//��� ����� ������ ��� �ε�����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//lButtonState�� ���� �Լ�
	void lButtonStateChange(void);

	//lButtonState�� ���� �ٸ� ����� ��Ŭ�� ��� ����
	void selectLButton(void);

	//��ŷ�� ��ġ�� ������Ʈ�� �߰��մϴ�.
	void addObject(void);

	terrainPickingTest() {}
	~terrainPickingTest() {}
};

