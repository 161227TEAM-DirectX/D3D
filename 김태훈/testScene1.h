#pragma once
#include "gameNode.h"
#include "xPlayer.h"

class testScene1 :	public gameNode
{
private:

	xPlayer* _player;

public:
	testScene1() {};
	~testScene1() {};

	HRESULT init();
	void update();
	void render();
	void release(void);
};

