#pragma once
#include "iGameNode.h"
//class terrain;
class bossMonster;

class stageThree : public iGameNode
{
private:
	bossMonster* boss;
	xPlayer* player;
	camera* _mainCamera;
	camera* _directionLightCamera;
	lightDirection* sceneBaseDirectionLight;

	terrain*			_terrain;			//����Ŭ����
	terrain*			_terrainShadow;		//���� �׸���
private:
	vector<baseObject*> _renderObject;
	vector<baseObject*>	_cullObject;

private:
	float _shadowDistance;
	bool start;

public:
	stageThree();
	~stageThree();

	HRESULT init();
	void release();
	void update();
	void render();

	//�׸��ڸ� ���� �ʱ�ȭ �۾� ����
	void shadowInit(void);
	//�׸��� ������Ʈ
	void shadowUpdate(void);
	//�׸��� ����
	void shadowRender(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);
};

