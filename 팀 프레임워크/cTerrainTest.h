#pragma once
#include "iGameNode.h"

class cTerrainTest : public iGameNode
{
private:
	terrain* _terrain;			//지형
	camera			_mainCamera;
	lightDirection* _sceneBaseDirectionLight;	//씬에 배치된 기본라이팅

	D3DXVECTOR3		_hitPos;	//히트 포지션

public:
	cTerrainTest();
	virtual ~cTerrainTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

