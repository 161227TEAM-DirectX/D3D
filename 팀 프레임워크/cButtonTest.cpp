#include "stdafx.h"
#include "cButtonTest.h"



cButtonTest::cButtonTest()
{
}


cButtonTest::~cButtonTest()
{
}

HRESULT cButtonTest::init()
{
	DXIMG_MANAGER->AddDxImg("시작버튼오버", new cDxImg(FILEPATH_MANAGER->GetFilepath("UI_시작버튼오버")));

	m_pDxImgButton = new cDxImgButton(DXIMG_MANAGER->GetDxImg("시작버튼오버"),
									  D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2),
									  true);

	return S_OK;
}

void cButtonTest::release()
{
}

void cButtonTest::update()
{
	if(m_pDxImgButton->click())
		exit(0);
}

void cButtonTest::render()
{
	m_pDxImgButton->render();
}
