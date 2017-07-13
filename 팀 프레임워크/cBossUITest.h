#pragma once
#include "iGameNode.h"
class cBossUITest : public iGameNode
{
private:
	cDxImgBar* m_pBar;

public:
	cBossUITest();
	~cBossUITest();

	HRESULT init();
	void release();
	void update();
	void render();
};

