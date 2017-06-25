#pragma once
#include "iGameNode.h"
class mapObject;
class Environment;
class WaterTerrain;
class monster;
class stageTwo :	public iGameNode
{
private:
	camera* _mainCamera;						//메인카메라
	camera* _directionLightCamera;				//빛카메라
	lightDirection* sceneBaseDirectionLight;	//씬기본빛

	xPlayer* player;							//플레이어
	mapObject* objectSet;						//지형오브젝트 셋팅 클래스

	terrain*			_terrain;				//지형클래스
	terrain*			_terrainShadow;			//지형 그림자
	Environment*		env;					//환경맵 정보
	WaterTerrain*		water;					//물지형 정보
private:
	vector<baseObject*> _renderObject;			//출력할 오브젝트 벡터
	vector<baseObject*>	_cullObject;			//프러스텀 컬링된 오브젝트 벡터
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

	//그림자를 위한 초기화 작업 공간
	void shadowInit(void);
	//그림자 업데이트
	void shadowUpdate(void);
	//그림자 렌더
	void shadowRender(void);

	void loadMonster(void);
	void loadNode(void);

	xMesh* findMonster(int&);
	string findMonsterName(int&);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);
};

