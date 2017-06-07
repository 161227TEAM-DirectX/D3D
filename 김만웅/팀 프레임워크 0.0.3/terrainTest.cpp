#include "stdafx.h"
#include "terrainTest.h"

HRESULT terrainTest::init(void)
{
	_terrain = new terrain;
	_terrain->init(32, 3.0f);

	return S_OK;
}

void terrainTest::release(void)
{
	_terrain->release();
	SAFE_DELETE(_terrain);
}

void terrainTest::update(void)
{
	//카메라 업데이트
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();
}

void terrainTest::render(void)
{
	_terrain->render();
}
