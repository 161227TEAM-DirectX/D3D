#pragma once
#include "gameNode.h"
#include "particleEmitter.h"

class _4snowPaticle : public gameNode
{
private:
	particleEmitter*	_particle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	_4snowPaticle() {}
	~_4snowPaticle() {}
};

