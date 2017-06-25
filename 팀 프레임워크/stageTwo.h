#pragma once
#include "iGameNode.h"
class mapObject;
class Environment;
class WaterTerrain;
class monster;
class stageTwo :	public iGameNode
{
private:
	camera* _mainCamera;						//����ī�޶�
	camera* _directionLightCamera;				//��ī�޶�
	lightDirection* sceneBaseDirectionLight;	//���⺻��

	xPlayer* player;							//�÷��̾�
	mapObject* objectSet;						//����������Ʈ ���� Ŭ����

	terrain*			_terrain;				//����Ŭ����
	terrain*			_terrainShadow;			//���� �׸���
	Environment*		env;					//ȯ��� ����
	WaterTerrain*		water;					//������ ����
private:
	vector<baseObject*> _renderObject;			//����� ������Ʈ ����
	vector<baseObject*>	_cullObject;			//�������� �ø��� ������Ʈ ����
	vector<monster*> _monsterRegion;
private:
	float _shadowDistance;
	tagSaveMap envTemp;
	tagSaveMap waterTemp;
public:
	stageTwo();
	~stageTwo();

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

	void loadMonster(void);
	void loadNode(void);

	xMesh* findMonster(int&);
	string findMonsterName(int&);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);
};

