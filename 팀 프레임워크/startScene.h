#pragma once
#include "iGameNode.h"
//
class cUIStart;

class startScene : public iGameNode
{
private:
	cUIStart* m_pUIStart;

public:
	startScene();
	virtual ~startScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){}
};

