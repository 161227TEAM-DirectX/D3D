#pragma once
#include "iGameNode.h"
#include "terrain.h"
//#include "dijkstra.h"
#include "monster.h"
#include "bossMonster.h"
#include "xPlayer.h"
#include "Environment.h"

class terrainPickingTest : public iGameNode
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
	xPlayer*			_player;
	monster*			player;
	bossMonster*		boss;
	baseObject*			enemy;
	terrain*			_terrain;			//����Ŭ����
	terrain*			_terrainShadow;		//���� �׸���
//	dx::transform*		_trans;				//Ʈ������
//	lightDirection*		_dirLight;			//�𷺼Ƕ���Ʈ
	D3DXVECTOR3			_hitPos;			//��Ʈ ������
	SELECTFUNC			lButtonState;
//	vector<light*>		_lights;
	vector<baseObject*>	mon;
	
	vector<baseObject*> testObject;

	vector<baseObject*>		_renderObjects;		//���� ��ġ�� ���� ������Ʈ �迭
	vector<baseObject*>		_cullObjects;		//�ø��� ������Ʈ

	camera*				_mainCamera;
	camera*				_directionLightCamera;
	lightDirection*		_sceneBaseDirectionLight;
	float				_shadowDistance;

	Environment*		_env;

	int sour;
	int dest;

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

	void InitMonster(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);

	terrainPickingTest() {}
	~terrainPickingTest() {}
};