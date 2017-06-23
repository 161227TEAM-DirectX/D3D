#pragma once
#include "iGameNode.h"
class cGameUITest : public iGameNode
{
public:
	cGameUITest();
	virtual ~cGameUITest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

