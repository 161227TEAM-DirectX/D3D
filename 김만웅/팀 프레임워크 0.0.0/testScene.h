#pragma once
#include "gameNode.h"
class testScene : public gameNode
{
public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

