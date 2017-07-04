#pragma once
#include "iGameNode.h"
class cAniTest : public iGameNode
{
public:
	cAniTest();
	virtual ~cAniTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

