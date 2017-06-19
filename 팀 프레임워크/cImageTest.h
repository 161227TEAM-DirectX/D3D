#pragma once
#include "iGameNode.h"
//
#include "cUIObject.h"

class cUIImageView;

class cImageTest 
	: public iGameNode
	, public cUIObject
{
private:
	cUIImageView* pImage;
	camera		  _camera;
	RECT		  _rt;
	
	vector<cDxImg*> m_vecImg;

public:
	cImageTest();
	virtual ~cImageTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

