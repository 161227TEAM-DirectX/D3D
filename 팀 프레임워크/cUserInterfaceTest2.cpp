#include "stdafx.h"
#include "cUserInterfaceTest2.h"
//
#include "cUIPlayer.h"

cUserInterfaceTest2::cUserInterfaceTest2()
{
}


cUserInterfaceTest2::~cUserInterfaceTest2()
{
}

HRESULT cUserInterfaceTest2::init()
{
	m_pUIPlayer = new cUIPlayer;
	m_pUIPlayer->init();

	return S_OK;
}

void cUserInterfaceTest2::release()
{
	SAFE_DELETE(m_pUIPlayer);
}

void cUserInterfaceTest2::update()
{
	m_pUIPlayer->update();
}

void cUserInterfaceTest2::render()
{
	m_pUIPlayer->render();
}

void cUserInterfaceTest2::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pUIPlayer->WndProc(hWnd,message,wParam,lParam);
}
