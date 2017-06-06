#include "stdafx.h"
#include "cLoadingBarTest.h"
//
#include "cUILoadingBar.h"

cLoadingBarTest::cLoadingBarTest()
{
}


cLoadingBarTest::~cLoadingBarTest()
{
}

HRESULT cLoadingBarTest::init()
{
	m_pUILoadingBar = new cUILoadingBar("Resources/UI/Loading/loadingBarBack.bmp",
										"Resources/UI/Loading/loadingBarFront.bmp",
										D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	return S_OK;
}

void cLoadingBarTest::release()
{
}

void cLoadingBarTest::update()
{
	m_pUILoadingBar->OnUpdate();
}

void cLoadingBarTest::render()
{
	m_pUILoadingBar->OnRender();
}
