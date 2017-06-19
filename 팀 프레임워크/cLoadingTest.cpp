#include "stdafx.h"
#include "cLoadingTest.h"
//
#include "cUILoading.h"

cLoadingTest::cLoadingTest()
{
}


cLoadingTest::~cLoadingTest()
{
}

HRESULT cLoadingTest::init()
{
	m_pUILoading = new cUILoading("Resource/UI/StartScreen/Å×½ºÆ®.jpg",
								  "Resource/UI/Loading/loadingBarBack.bmp",
								  "Resource/UI/Loading/loadingBarFront.bmp",
								  D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	return S_OK;
}


void cLoadingTest::release()
{
}

void cLoadingTest::update()
{
	m_pUILoading->OnUpdate();
}

void cLoadingTest::render()
{
	m_pUILoading->OnRender();
}
