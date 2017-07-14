#include "stdafx.h"
#include "cAniTest.h"


cAniTest::cAniTest()
{
}


cAniTest::~cAniTest()
{
}

HRESULT cAniTest::init()
{
	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("Ani_Fire01_30").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Fire01_30")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Fire01_30")[i]->SetCenterDraw(false);
	}
	return S_OK;
}

void cAniTest::release()
{
}

void cAniTest::update()
{
}

void cAniTest::render()
{
	DXIMGANI_MANAGER->render("Ani_Fire01_30");


	FONTMANAGER->fontOut("%d", DXIMGANI_MANAGER->getAniSize("Ani_Fire01"), 100, 100, WHITE);

	//for (int i=0; i <; i++)
	//{
	//	DXIMGANI_MANAGER->render("Ani_Fire01_" + to_string(i));
	//}
}
