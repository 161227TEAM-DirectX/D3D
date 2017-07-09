#pragma once
#include "iGameNode.h"
class Environment;
class WaterTerrain;
class mapObject;
class cUIPlayer;

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
	dx::transform*		toRotate;			//�¾� ��������

	baseObject*			_gate1;
	baseObject*			_gate2;
private:
	vector<baseObject*> _renderObject;
	vector<baseObject*>	_cullObject;
	D3DXMATRIX matRotate;
private:
	float _shadowDistance;
	float currTime;
	int angleZ;

	tagSaveMap envTemp;
	tagSaveMap waterTemp;
private:
	cUIPlayer* m_pUIPlayer;
public:
	stageOne() { clear(); }
	~stageOne() { destroy(); }

	HRESULT init();
	void release();
	void update();
	void render();

	HRESULT clear(void);
	void destroy(void);

	//�׸��ڸ� ���� �ʱ�ȭ �۾� ����
	void shadowInit(void);
	//�׸��� ������Ʈ
	void shadowUpdate(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);

	void sceneChange();
};

