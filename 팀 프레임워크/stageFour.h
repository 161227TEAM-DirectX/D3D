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
	tagSaveMap envTemp;
	tagSaveMap waterTemp;
public:
	stageFour() { clear(); }
	~stageFour() { destroy(); }

	HRESULT clear(void);
	void destroy(void);

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	//�׸��ڸ� ���� �ʱ�ȭ �۾� ����
	void shadowInit(void);
	//�׸��� ������Ʈ
	void shadowUpdate(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);

	void sceneChange();
};

