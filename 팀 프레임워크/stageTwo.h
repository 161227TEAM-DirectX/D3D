#pragma once
#include "iGameNode.h"
class stageTwo :
	public iGameNode
{
public:
	stageTwo();
	~stageTwo();

	HRESULT init();
	void release();
	void update();
	void render();
};

