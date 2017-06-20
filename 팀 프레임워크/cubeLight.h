#pragma once
#include "iGameNode.h"
#include "xPlayer.h"

class cubeLight : public iGameNode
{
private:
	xPlayer* _player;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	

	cubeLight() {};
	~cubeLight() {};
};

