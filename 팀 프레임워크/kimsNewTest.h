#pragma once
#include "iGameNode.h"
#include "Environment.h"
#include "xPlayer.h"

class kimsNewTest :	public iGameNode
{
private :
	xPlayer* _player;

	camera* _mainCamera;

	camera*				_directionLightCamera;
	camera*				_playerDirectionLightCamera;
	lightDirection*		_sceneBaseDirectionLight;
	terrain*			_terrain;
	terrain*			_terrainShadow;		//���� �׸���

	float _shadowDistance;
	//D3DXVECTOR3 _hitPos;

	//�÷��̾�� ���� ������Ʈ�� ���� �ʴ´�! �ֳ�! �÷��̾�ϱ�! �ϳ��� �ִµ��� ���� �װ� �ø��� �� �־ ������ ������ ����ڴ°�!

	vector<baseObject*>		_renderObjects;		//���� ��ġ�� ���� ������Ʈ �迭

	vector<baseObject*>		_cullObjects;		//�ø��� ������Ʈ

	vector<baseObject*>		shadowCullObject;

	Environment*			_env;

	//SELECTFUNC			lButtonState;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain);

	void readyPlayerShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain);

//	void readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain);

	//void readyShadowMap(vector<baseObject*>* renderObjects);

	//void renderShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain);

	kimsNewTest() {};
	~kimsNewTest() {};
};

