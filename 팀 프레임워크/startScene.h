#pragma once
#include "iGameNode.h"

class startScene : public iGameNode
{
private:
	vector<cDxImgButton*> m_vecBtn;

public:
	startScene();
	virtual ~startScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

