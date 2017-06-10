#pragma once
#include "gameNode.h"

class _4snowPaticle : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	_4snowPaticle() {}
	~_4snowPaticle() {}
};

