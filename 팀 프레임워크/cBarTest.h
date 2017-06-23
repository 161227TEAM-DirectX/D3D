#pragma once
#include "iGameNode.h"

class cBarTest : public iGameNode
{
private:
	cDxImgBar* bar;
	camera m_camera;
	int i = 0;

public:
	cBarTest();
	virtual ~cBarTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

