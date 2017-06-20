#pragma once
#include "iGameNode.h"

class cImageTest : public iGameNode
{
private:
	camera		  _camera;
	
	vector<cDxImg*> m_vecImg;
	vector<cDxImg*> m_vecAniDxImg;

	cDxImg* tt;

public:
	cImageTest();
	virtual ~cImageTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void aniInit();
};

