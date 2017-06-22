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

	terrain*			_terrain;			//지형클래스
	terrain*			_terrainShadow;		//지형 그림자
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

	//그림자를 위한 초기화 작업 공간
	void shadowInit(void);
	//그림자 업데이트
	void shadowUpdate(void);
	//그림자 렌더
	void shadowRender(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);
};

