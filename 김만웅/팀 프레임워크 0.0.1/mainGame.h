#pragma once
/*앞으로 씬의 헤더만 이곳에서 추가할것!!!*/
#include "testScene.h"

class mainGame
{
private:
	void initManager();		//매니져 세팅
	void releaseManager();	//매니져 해제

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	//메인 프로시져
	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame() {}
	~mainGame() {}
};