#pragma once
#include "iGameNode.h"
class cCameraTest : public iGameNode
{
public:
	cCameraTest();
	virtual ~cCameraTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

