#include "stdafx.h"
#include "cUITestChatting.h"


cUITestChatting::cUITestChatting()
{
}


cUITestChatting::~cUITestChatting()
{
}

HRESULT cUITestChatting::init()
{
	m_pUIchat = new cUIchatting();
	return S_OK;
}

void cUITestChatting::release()
{
}

void cUITestChatting::update()
{
	m_pUIchat->update();
}

void cUITestChatting::render()
{
	m_pUIchat->render();
}

void cUITestChatting::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pUIchat->WndProc(hWnd,message,wParam,lParam);
}

