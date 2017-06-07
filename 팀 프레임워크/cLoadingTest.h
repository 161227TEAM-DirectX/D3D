#pragma once
#include "gameNode.h"
//
class cUILoading;

class cLoadingTest : public gameNode
{
private:
	cUILoading* m_pUILoading;

public:
	cLoadingTest();
	~cLoadingTest();

	HRESULT init();
	void release();
	void update();
	void render();
};

