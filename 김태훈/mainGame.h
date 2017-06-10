#pragma once
/*앞으로 씬의 헤더만 이곳에서 추가할것!!!*/
#include "shadowTest1.h"
#include "shadowTest2.h"
#include "testScene1.h"

class mainGame
{
private:
	//매니져 세팅
	void initManager(void);
	//매니져 해제
	void releaseManager(void);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	//메인 프로시져
	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame() {}
	~mainGame() {}
};