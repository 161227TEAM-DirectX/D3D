#pragma once
#include "iGameNode.h"
//class terrain;
class bossMonster;
class Environment;
class WaterTerrain;

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

	Environment*		env;
	WaterTerrain*		water;
private:
	vector<baseObject*> _renderObject;
	vector<baseObject*>	_cullObject;

private:
	float _shadowDistance;
	bool start;
	tagSaveMap envTemp;
	tagSaveMap waterTemp;

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

