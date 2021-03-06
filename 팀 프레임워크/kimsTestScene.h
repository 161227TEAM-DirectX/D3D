#pragma once
#include "gameNode.h"
#include "terrain.h"
//#include "dijkstra.h"
#include "monster.h"
#include "bossMonster.h"
#include "xPlayer.h"
#include "xNpc.h"

class kimsTestScene : public gameNode
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
	//	dijkstra*			tempDijkstra;
	xPlayer* _player;
	xNpc* _thrall;//쓰랄씨.
	xNpc* _sylvanas;//시바나스.

	monster*			player;
	bossMonster*		boss;
	baseObject*			enemy;
	terrain*			_terrain;	//지형클래스
	terrain*			_terrainShadow;		//지형 그림자
	dx::transform*		_trans;		//트랜스폼
	lightDirection*		_dirLight;	//디렉션라이트
	D3DXVECTOR3			_hitPos;	//히트 포지션
	SELECTFUNC			lButtonState;
	vector<light*>		_lights;


	vector<baseObject*> testObject;

	vector<baseObject*>		_renderObjects;		//씬에 배치된 랜더 오브젝트 배열
	vector<baseObject*>		_cullObjects;		//컬링된 오브젝트



	int sour;					//노드 연결시 출발 노드 인덱스값
	int dest;					//노드 연결시 목적지 노드 인덱스값

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

	kimsTestScene() {};
	~kimsTestScene() {};
};

