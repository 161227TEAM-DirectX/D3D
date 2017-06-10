#pragma once
#include "gameNode.h"

class phongShaderTest : public gameNode
{
private:
	camera			_mainCamera;
	transform		_lightTrans;
	transform		_meshTrans;
	LPD3DXMESH		_mesh;
	LPD3DXEFFECT	_effect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	phongShaderTest() {}
	~phongShaderTest() {}
};

