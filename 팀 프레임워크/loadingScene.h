#pragma once
#include "iGameNode.h"
class loadingScene : public iGameNode
{
private:
public:
	loadingScene();
	virtual ~loadingScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){}
};

