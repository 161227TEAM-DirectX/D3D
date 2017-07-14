#pragma once
#include "iGameNode.h"
//class terrain;
class bossMonster;
class Environment;
class WaterTerrain;
class cUIPlayer;
class monster;

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

	Environment*		env;
	WaterTerrain*		water;
private:
	vector<monster*> _mon;
	vector<baseObject*> _renderObject;
	vector<baseObject*>	_cullObject;

private:
	float _shadowDistance;
	bool cinematicBool;
	tagSaveMap envTemp;
	tagSaveMap waterTemp;

private:
	cUIPlayer* m_pUIPlayer;

public:
	stageThree();
	~stageThree();

	HRESULT init();
	void release();
	void update();
	void render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//그림자를 위한 초기화 작업 공간
	void shadowInit(void);
	//그림자 업데이트
	void shadowUpdate(void);
	//그림자 렌더
	void shadowRender(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);

	void loadingStage();
};

extern stageThree* ex_pStage3;

