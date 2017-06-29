#pragma once
#include "iGameNode.h"
class cUITestChatting : public iGameNode
{
private:
	cUIchatting* m_pUIchat;

public:
	cUITestChatting();
	~cUITestChatting();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

