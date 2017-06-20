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

	//DXIMGANI_MANAGER->render("�ƾ�")
	//DXIMGANI_MANAGER->render("�ƾ�2")
	//DXIMGANI_MANAGER->render("�ƾ�3")
}

void cImageTest::aniInit()
{
	vector<cDxImg*> tp;

	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�00")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�01")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�02")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�03")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�04")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�05")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�06")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�07")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�08")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�09")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�10")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�11")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�12")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�13")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�14")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�15")));

	DXIMGANI_MANAGER->AddDxImgAni("�ƾ�", tp, ST_DXIMGANI(), D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2 + 200));


	tp.clear();
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�00-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�01-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�02-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�03-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�04-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�05-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�06-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�07-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�08-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�09-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�10-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�11-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�12-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�13-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�14-2")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�15-2")));

	DXIMGANI_MANAGER->AddDxImgAni("�ƾ�2", tp, ST_DXIMGANI(3), D3DXVECTOR2(450, 300));



	tp.clear();
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�00-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�01-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�02-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�03-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�04-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�05-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�06-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�07-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�08-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�09-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�10-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�11-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�12-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�13-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�14-3")));
	tp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("�ƽ�15-3")));

	DXIMGANI_MANAGER->AddDxImgAni("�ƾ�3", tp, ST_DXIMGANI(5), D3DXVECTOR2(1200, 250));

}
