#include "stdafx.h"
#include "cImageTest.h"

cImageTest::cImageTest()
{
}


cImageTest::~cImageTest()
{
}

HRESULT cImageTest::init()
{
	aniInit();

	tt = new cDxImg(FILEPATH_MANAGER->GetFilepath("cat"), 8, 1);
	tt->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	tt->SetDrawBoundingBox(true);
	m_vecImg.push_back(tt);

	tt = new cDxImg(FILEPATH_MANAGER->GetFilepath("cat"), 8, 1, 10);
	tt->SetPosition(D3DXVECTOR3(300, WINSIZEY / 2, 0));
	m_vecImg.push_back(tt);

	tt = new cDxImg(FILEPATH_MANAGER->GetFilepath("cat"), 8, 1, 3);
	tt->SetPosition(D3DXVECTOR3(1300, WINSIZEY / 2, 0));
	m_vecImg.push_back(tt);

	return S_OK;
}

void cImageTest::release()
{
	SAFE_DELETE(tt);

	for (int i=0; i<m_vecImg.size(); i++)
	{
		SAFE_DELETE(m_vecImg[i]);
		SAFE_DELETE(m_vecAniDxImg[i]);
	}
	m_vecImg.clear();
	m_vecAniDxImg.clear();
}

void cImageTest::update()
{
	_camera.updateBase();
}

void cImageTest::render()
{
	for each(auto v in m_vecImg)
	{
		v->renderFrame();
	}

	//DXIMGANI_MANAGER->render("ÄÆ¾À")
	//DXIMGANI_MANAGER->render("ÄÆ¾À2")
	//DXIMGANI_MANAGER->render("ÄÆ¾À3")
}

void cImageTest::aniInit()
{
	vector<cDxImg*> tp;

	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å00")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å01")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å02")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å03")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å04")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å05")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å06")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å07")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å08")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å09")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å10")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å11")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å12")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å13")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å14")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å15")));

	DXIMGANI_MANAGER->AddDxImgAni("ÄÆ¾À", tp, ST_DXIMGANI(), D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2 + 200));


	tp.clear();
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å00-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å01-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å02-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å03-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å04-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å05-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å06-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å07-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å08-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å09-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å10-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å11-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å12-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å13-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å14-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å15-2")));

	DXIMGANI_MANAGER->AddDxImgAni("ÄÆ¾À2", tp, ST_DXIMGANI(3), D3DXVECTOR2(450, 300));



	tp.clear();
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å00-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å01-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å02-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å03-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å04-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å05-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å06-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å07-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å08-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å09-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å10-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å11-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å12-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å13-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å14-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("ÄÆ½Å15-3")));

	DXIMGANI_MANAGER->AddDxImgAni("ÄÆ¾À3", tp, ST_DXIMGANI(5), D3DXVECTOR2(1200, 250));

}
