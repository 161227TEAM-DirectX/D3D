#pragma once
#include "iGameNode.h"

class Environment;
class WaterTerrain;
class mapObject;
class cUIPlayer;

class stageFour : public iGameNode
{
private:
	xPlayer* player;
	camera* _mainCamera;
	camera* _directionLightCamera;
	lightDirection* sceneBaseDirectionLight;

	terrain*			_terrain;				//지형클래스
	terrain*			_terrainShadow;			//지형 그림자
	mapObject* objectSet;						//지형오브젝트 셋팅 클래스

	Environment*		env;					//환경맵
	WaterTerrain*		water;					//물지형 맵
	dx::transform*		toRotate;				//태양 보정값용

	baseObject*			_gate1;
private:
	cUIPlayer* m_pUIPlayer;
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

	//그림자를 위한 초기화 작업 공간
	void shadowInit(void);
	//그림자 업데이트
	void shadowUpdate(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);

	void sceneChange();

	void loadingStage();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

extern stageFour* ex_pStage4;
