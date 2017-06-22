#pragma once
#include "iGameNode.h"
class stageOne :
	public iGameNode
{
public:
	stageOne();
	~stageOne();

	HRESULT init();
	void release();
	void update();
	void render();
};

