#pragma once
#include "iGameNode.h"
#include "terrain.h"
//#include "dijkstra.h"
#include "monster.h"
#include "bossMonster.h"
#include "xPlayer.h"
#include "Environment.h"
#include "mapObject.h"
#include "WaterTerrain.h"

class terrainPickingTest : public iGameNode
{
private:
	enum SELECTFUNC
	{
		SELECT_NODE = 1,
		SELECT_LINE,
		SELECT_MOVING,
		SELECT_OBJECT,
		SELECT_NONE
	};

private:
	WaterTerrain* _waterTerrain;
	mapObject*        _mapObject;
	xPlayer*			_player;
	monster*			player;
	bossMonster*		boss;
	baseObject*			enemy;
	terrain*			_terrain;			//지형클래스
	terrain*			_terrainShadow;		//지형 그림자
//	dx::transform*		_trans;				//트랜스폼
//	lightDirection*		_dirLight;			//디렉션라이트
	D3DXVECTOR3			_hitPos;			//히트 포지션
	SELECTFUNC			lButtonState;
//	vector<light*>		_lights;
	vector<monster*>	mon;
	
	vector<baseObject*> testObject;

	vector<baseObject*>		_renderObjects;		//씬에 배치된 랜더 오브젝트 배열
	vector<baseObject*>		_cullObjects;		//컬링된 오브젝트

	camera*				_mainCamera;
	camera*				_directionLightCamera;
	lightDirection*		_sceneBaseDirectionLight;
	float				_shadowDistance;

	Environment*		_env;

	int sour;
	int dest;

//	SCENE_VERTEX			_scenePlaneVertex[4];		//씬평면 버텍스
//	WORD					_scenePlaneIndex[6];		//씬평면 인덱스
//	LPD3DXEFFECT			_postEffect;				//포스트 이펙트

//지워도댐
private:
	vector<baseObject*>	m_vecObject;
	tagSaveObject object;
private:
	float currTime;
	int oldTime;
	int angleZ;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//lButtonState값 변경 함수
	void lButtonStateChange(void);

	//lButtonState에 따른 다른 방식의 좌클릭 기능 적용
	void selectLButton(void);

	//피킹된 위치에 오브젝트를 추가합니다.
	void addObject(void);

	void InitMonster(void);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);

	void shadowInit(void);
	void shadowUpdate(void);
	void shadowRender(void);
	void testRender(void);

	terrainPickingTest(): currTime(0), oldTime(0), angleZ(90) {}
	~terrainPickingTest() {}
};