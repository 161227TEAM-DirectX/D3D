#pragma once
#include "iGameNode.h"
class Environment;
class WaterTerrain;
class mapObject;

class stageOne : public iGameNode
{
private:
	xPlayer* player;
	camera* _mainCamera;
	camera* _directionLightCamera;
	lightDirection* sceneBaseDirectionLight;

	terrain*			_terrain;			//����Ŭ����
	terrain*			_terrainShadow;		//���� �׸���
	mapObject* objectSet;						//����������Ʈ ���� Ŭ����

	Environment*		env;				//ȯ���
	WaterTerrain*		water;				//������ ��
private:
	vector<baseObject*> _renderObject;
	vector<baseObject*>	_cullObject;
private:
	float _shadowDistance;
	tagSaveMap envTemp;
	tagSaveMap waterTemp;
public:
	stageOne();
	~stageOne();

	HRESULT init();
	void release();
	void update();
	void render();

	//�׸��ڸ� ���� �ʱ�ȭ �۾� ����
	void shadowInit(void);
	//�׸��� ������Ʈ
	void shadowUpdate(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);
};

