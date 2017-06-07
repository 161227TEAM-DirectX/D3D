#pragma once
#include "gameNode.h"

class cUILoadingBar;

class cLoadingBarTest : public gameNode
{
private:
	cUILoadingBar* m_pUILoadingBar;

public:
	cLoadingBarTest();
	~cLoadingBarTest();

	HRESULT init();
	void release();
	void update();
	void render();
};

