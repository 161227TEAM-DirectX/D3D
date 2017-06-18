#include "stdafx.h"
#include "cTerrainTest.h"
#include "terrain.h"

cTerrainTest::cTerrainTest()
{
}


cTerrainTest::~cTerrainTest()
{
}

HRESULT cTerrainTest::init()
{
	//기본 광원 생성
	_sceneBaseDirectionLight = new lightDirection;
	//기본 값
	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;

	//카메라 월드 위치 설정
	_mainCamera.SetWorldPosition(0.0f, 0.0f, 0.0f);

	//지형 생성
	_terrain = new terrain;
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_3"));
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_1"));
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_2"));
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_3"));
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_4"));
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_1"));
	_terrain->setHeightscale(100.0f);
	_terrain->setBrushmap(FILEPATH_MANAGER->GetFilepath("브러쉬_brush01"));
	_terrain->setBrushScale(1.0f);
	_terrain->setting();

	_hitPos = D3DXVECTOR3(0, 0, 0);

	return S_OK;
}

void cTerrainTest::release()
{
}

void cTerrainTest::update()
{
	_mainCamera.updateBase();

	if(KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		IOHEIGHTMANAGER->saveFile("지형정보",_terrain->getMapPosition());
	}

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		_terrain->setMapPosition(IOHEIGHTMANAGER->loadHeight("지형정보"));
		_terrain->changeHeightTerrain();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		_mainCamera.computeRay(&ray, &screenPos);

		//Terrain 이랑 Ray체크
		_terrain->isIntersectRay(&_hitPos, &ray);

		//Terrain의 높이값이 변경된다.
		_terrain->changeHeightTerrain(_hitPos.x, _hitPos.z);
	}
}

void cTerrainTest::render()
{
	_terrain->render(&_mainCamera, _sceneBaseDirectionLight);

	//Hit 위치에 구만들기
	GIZMOMANAGER->WireSphere(_hitPos, 0.5f, RED);

	/*FONTMANAGER->fontOut("x:" + to_string(_hitPos.x), 100, 100, BLUE);
	FONTMANAGER->fontOut("y:" + to_string(_hitPos.y), 100, 120, BLUE);
	FONTMANAGER->fontOut("z:" + to_string(_hitPos.z), 100, 140, BLUE);
	FONTMANAGER->fontOut("[x]:" + to_string(_terrain->getIdx(_hitPos.x, _hitPos.z).first), 100, 160, BLUE);
	FONTMANAGER->fontOut("[z]:" + to_string(_terrain->getIdx(_hitPos.x, _hitPos.z).second), 100, 180, BLUE);
*/
	//for (int i=0; i < IOHEIGHTMANAGER->loadHeight("지형정보").size(); i++)
	//{
	//	FONTMANAGER->fontOut("" + to_string(IOHEIGHTMANAGER->loadHeight("지형정보")[i].x), 100, 100 + 20 * i, BLUE);
	//	FONTMANAGER->fontOut("" + to_string(IOHEIGHTMANAGER->loadHeight("지형정보")[i].x), 130, 100 + 20 * i, BLUE);
	//	FONTMANAGER->fontOut("" + to_string(IOHEIGHTMANAGER->loadHeight("지형정보")[i].x), 160, 100 + 20 * i, BLUE);
	//}
}
