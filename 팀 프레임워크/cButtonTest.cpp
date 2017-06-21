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
	DXIMG_MANAGER->AddDxImg("���۹�ư����", new cDxImg(FILEPATH_MANAGER->GetFilepath("UI_���۹�ư����")));

	m_pDxImgButton = new cDxImgButton(DXIMG_MANAGER->GetDxImg("���۹�ư����"),
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
