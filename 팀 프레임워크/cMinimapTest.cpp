#include "stdafx.h"
#include "cMinimapTest.h"


cMinimapTest::cMinimapTest()
{
}


cMinimapTest::~cMinimapTest()
{
}

HRESULT cMinimapTest::init()
{
	////기본 광원 생성
	//_baseLight = new lightDirection;
	////기본 값
	//_baseLight->_color = D3DXCOLOR(1, 1, 1, 1);
	//_baseLight->_intensity = 1.0f;

	////카메라 월드 위치 설정
	//_mainCamera.SetWorldPosition(0.0f, 0.0f, 0.0f);

	////지형 생성
	//_terrain = new terrain;
	//_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("height_base"));
	//_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_1"));
	//_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_2"));
	//_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_3"));
	//_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_4"));
	//_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("splat_base"));
	////_terrain->setHeightscale(100.0f);
	////_terrain->setBrushmap(FILEPATH_MANAGER->GetFilepath("브러쉬_brush01"));
	////_terrain->setBrushScale(1.0f);
	//_terrain->setting();

	//_hitPos = D3DXVECTOR3(0, 0, 0);

	DXIMG_MANAGER->GetDxImg("minimap")->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	DXIMG_MANAGER->GetDxImg("minimap")->SetCenterDraw(true);

	DXIMG_MANAGER->GetDxImg("minimapTest")->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	DXIMG_MANAGER->GetDxImg("minimapTest")->SetCenterDraw(true);

	miniWidth = 400;
	miniHeight = 400;
	miniX = (DXIMG_MANAGER->GetDxImg("minimap")->GetSize().fWidth / 2) - miniWidth / 2;
	miniY = (DXIMG_MANAGER->GetDxImg("minimap")->GetSize().fHeight / 2) - miniHeight / 2;



	return S_OK;
}

void cMinimapTest::release()
{
}

void cMinimapTest::update()
{
	_mainCamera.updateBase();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		moveX += 1;
		//miniX-=1;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		moveX -= 1;
		//miniX+=1;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		moveY += 1;
		//miniY-=1;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		moveY -= 1;
		//miniY+=1;
	}

	/*if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
	Ray ray;
	POINT ptMousePos = GetMousePos();
	D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	_mainCamera.computeRay(&ray, &screenPos);

	_terrain->isIntersectRay(&_hitPos, &ray);
	}*/
}

void cMinimapTest::render()
{
	//_terrain->render(&_mainCamera, _baseLight);


	//DXIMG_MANAGER->render("minimap");
	//DXIMG_MANAGER->render("minimapTest");
	DXIMG_MANAGER->render("minimap", miniX, miniY, miniWidth, miniHeight, moveX, moveY);
	//Hit 위치에 구만들기
	//GIZMOMANAGER->WireSphere(_hitPos, 0.5f, RED);

	FONTMANAGER->fontOut("x: " + to_string(GetMousePos().x), 100, 60, GREEN);
	FONTMANAGER->fontOut("y: " + to_string(GetMousePos().y), 100, 80, GREEN);
	FONTMANAGER->fontOut("startX: " + to_string(DXIMG_MANAGER->GetDxImg("minimap")->GetMiniStartX()), 100, 100, RED);
	FONTMANAGER->fontOut("startY: " + to_string(DXIMG_MANAGER->GetDxImg("minimap")->GetMiniStartY()), 100, 120, RED);
	FONTMANAGER->fontOut("Width: " + to_string(DXIMG_MANAGER->GetDxImg("minimap")->GetMiniWidth()), 100, 140, RED);
	FONTMANAGER->fontOut("Height: " + to_string(DXIMG_MANAGER->GetDxImg("minimap")->GetMiniHeight()), 100, 160, RED);
}
