#pragma once
#include "iGameNode.h"
class cGameUITest : public iGameNode
{
private:
	cDxImgUI*  m_pPlBar;
	cDxImgBar* m_pBar;
	cDxImgBar* m_pBar2;
	int i = 0;

public:
	cGameUITest();
	virtual ~cGameUITest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

