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
	terrain*			_terrainShadow;		//지형 그림자

	float _shadowDistance;
	//D3DXVECTOR3 _hitPos;

	//플레이어는 렌더 오브젝트에 넣지 않는다! 왜냐! 플레이어니까! 하나만 있는데왜 구지 그걸 컬링에 꼭 넣어서 구조를 귀찮게 만들겠는가!

	vector<baseObject*>		_renderObjects;		//씬에 배치된 랜더 오브젝트 배열

	vector<baseObject*>		_cullObjects;		//컬링된 오브젝트

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

