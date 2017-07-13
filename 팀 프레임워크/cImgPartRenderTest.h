#pragma once
#include "iGameNode.h"
class cImgPartRenderTest : public iGameNode
{
private:
	int x = 0,y= 0;

public:
	cImgPartRenderTest();
	virtual ~cImgPartRenderTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

