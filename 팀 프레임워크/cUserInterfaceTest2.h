#pragma once
#include "iGameNode.h"
//
class cUIPlayer;

class cUserInterfaceTest2 : public iGameNode
{
private:
	cUIPlayer* m_pUIPlayer;

public:
	cUserInterfaceTest2();
	virtual ~cUserInterfaceTest2();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

