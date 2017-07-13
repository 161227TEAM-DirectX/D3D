#include "stdafx.h"
#include "cImgPartRenderTest.h"


cImgPartRenderTest::cImgPartRenderTest()
{
}


cImgPartRenderTest::~cImgPartRenderTest()
{
}

HRESULT cImgPartRenderTest::init()
{
	DXIMG_MANAGER->GetDxImg("partTest")->SetCenterDraw(true);
	DXIMG_MANAGER->GetDxImg("partTest")->setPos(WINSIZEX/2,WINSIZEY/2);
	return S_OK;
}

void cImgPartRenderTest::release()
{
}

void cImgPartRenderTest::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) x++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) x--;
	if (KEYMANAGER->isStayKeyDown(VK_UP)) y--;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) y++;
}

void cImgPartRenderTest::render()
{
	//524 700
	DXIMG_MANAGER->GetDxImg("partTest")->render(x,			//그리는 위치x
												y,			//그리는 위치y
												300,		//그릴 가로 길이
												300);		//그릴 세로 길이
}
