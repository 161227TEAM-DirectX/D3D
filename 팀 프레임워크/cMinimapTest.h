#pragma once
#include "iGameNode.h"

class cMinimapTest : public iGameNode
{
private:
	terrain*		_terrain;
	camera			_mainCamera;
	lightDirection* _baseLight;
	D3DXVECTOR3		_hitPos;

	float miniX = 0;
	float miniY = 0;
	float miniWidth = 0;
	float miniHeight = 0;

	float moveX = 0;
	float moveY = 0;

public:
	cMinimapTest();
	virtual ~cMinimapTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

