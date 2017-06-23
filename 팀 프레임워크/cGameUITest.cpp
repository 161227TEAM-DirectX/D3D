#include "stdafx.h"
#include "cGameUITest.h"


cGameUITest::cGameUITest()
{
}


cGameUITest::~cGameUITest()
{
}

HRESULT cGameUITest::init()
{
	cDxImgUI* temp;
	temp = new cDxImgUI("Äü½½·Ô");
	temp->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	temp->GetUI()->SetDrawBoundingBox(true);
	temp->GetUI()->SetCenterDraw(true);
	UI_MANAGER->AddUI("Äü½½·Ô", temp);

	return S_OK;
}

void cGameUITest::release()
{
}

void cGameUITest::update()
{
	UI_MANAGER->update();
}

void cGameUITest::render()
{
	LineMake(0, WINSIZEY / 2, WINSIZEX, WINSIZEY / 2);
	LineMake(WINSIZEX / 2, 0, WINSIZEX / 2, WINSIZEY);

	UI_MANAGER->render();
}
