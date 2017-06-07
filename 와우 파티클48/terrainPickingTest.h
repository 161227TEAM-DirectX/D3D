#pragma once
#include "gameNode.h"
#include "terrain.h"

class terrainPickingTest : public gameNode
{
private:
	terrain*		_terrain;	//지형클래스
	transform*		_trans;		//트랜스폼
	lightDirection* _dirLight;	//디렉션라이트
	D3DXVECTOR3		_hitPos;	//히트 포지션

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	terrainPickingTest() {}
	~terrainPickingTest() {}
};

