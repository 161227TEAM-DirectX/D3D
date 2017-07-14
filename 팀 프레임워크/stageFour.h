#pragma once
#include "iGameNode.h"

class Environment;
class WaterTerrain;
class mapObject;

class stageFour : public iGameNode
{
private:
	xPlayer* player;
	camera* _mainCamera;
	camera* _directionLightCamera;
	lightDirection* sceneBaseDirectionLight;

	terrain*			_terrain;				//����Ŭ����
	terrain*			_terrainShadow;			//���� �׸���
	mapObject* objectSet;						//����������Ʈ ���� Ŭ����

	Environment*		env;					//ȯ���
	WaterTerrain*		water;					//������ ��
	dx::transform*		toRotate;				//�¾� ��������

	baseObject*			_gate1;
private:
	vector<baseObject*> _renderObject;
	vector<baseObject*>	_cullObject;
	D3DXMATRIX matRotate;
private:
	float _shadowDistance;
	float currTime;
	int angleZ;
	bool cinematicBool;
	tagSaveMap envTemp;
	tagSaveMap waterTemp;

public:
	stageFour();
	~stageFour();

	HRESULT init();
	void release();
	void update();
	void render();

	//�׸��ڸ� ���� �ʱ�ȭ �۾� ����
	void shadowInit(void);
	//�׸��� ������Ʈ
	void shadowUpdate(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);

	void sceneChange();

	void loadingStage();
};

extern stageFour* ex_pStage4;
