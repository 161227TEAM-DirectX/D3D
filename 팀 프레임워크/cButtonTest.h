#pragma once
#include "iGameNode.h"

class cButtonTest : public iGameNode
{
private:
	cDxImgButton* m_pDxImgButton;

public:
	cButtonTest();
	virtual ~cButtonTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

