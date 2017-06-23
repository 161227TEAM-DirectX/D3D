#include "stdafx.h"
#include "cBarTest.h"


cBarTest::cBarTest()
{
}


cBarTest::~cBarTest()
{
}

HRESULT cBarTest::init()
{
	bar = new cDxImgBar("UI_loadingbar_cover",
						"UI_loadingbar_back",
						"UI_loadingbar_move",
						D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2), true);
	//bar->SetGaugeSpeed(3);
	//bar->SetGaugeInterval(2);
	//DXIMG_MANAGER->AddDxImg("UI_loadingbar_move",
	//						new cDxImg(FILEPATH_MANAGER->GetFilepath("UI_loadingbar_move"),
	//								   D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2),
	//								   true));

	//DXIMG_MANAGER->AddDxImg("UI_loadingbar_back",
	//						new cDxImg(FILEPATH_MANAGER->GetFilepath("UI_loadingbar_back"),
	//								   D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2),
	//								   true));

	//DXIMG_MANAGER->AddDxImg("UI_loadingbar_cover",
	//						new cDxImg(FILEPATH_MANAGER->GetFilepath("UI_loadingbar_cover"),
	//								   D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2),
	//								   true));

	//DXIMG_MANAGER->GetDxImg("배경바")->SetDrawBoundingBox(true);
	//DXIMG_MANAGER->GetDxImg("배경바")->SetBoundingColor(GREEN);

	//DXIMG_MANAGER->AddDxImg("무브바", new cDxImg(FILEPATH_MANAGER->GetFilepath("UI_moveBar"), D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2), true));

	//DXIMG_MANAGER->AddDxImg("커버바", new cDxImg(FILEPATH_MANAGER->GetFilepath("UI_coverBar"), D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2), true));


	return S_OK;
}

void cBarTest::release()
{
}

void cBarTest::update()
{
	m_camera.updateBase();
	bar->update();
	//DXIMG_MANAGER->GetDxImg("UI_loadingbar_move")->SetCurX(DXIMG_MANAGER->GetDxImg("UI_loadingbar_move")->GetCurX() + 1);
}

void cBarTest::render()
{
	LineMake(WINSIZEX / 2, 0, WINSIZEX / 2, WINSIZEY, WHITE);
	LineMake(0, WINSIZEY / 2, WINSIZEX, WINSIZEY / 2, WHITE);


	//bar->render();

	//DXIMGANI_MANAGER->render("Ani_Fire01");
	//DXIMG_MANAGER->GetDxImg("UI_loadingbar_back")->render();
	//DXIMG_MANAGER->GetDxImg("UI_loadingbar_move")->renderBarX();
	//DXIMG_MANAGER->GetDxImg("UI_loadingbar_cover")->render();
	//DXIMG_MANAGER->render();
}
