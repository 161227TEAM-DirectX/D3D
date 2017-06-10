#pragma once
#include "gameNode.h"

class particleEmitter;

class _2particleEmitter : public gameNode
{
private:
	particleEmitter*		_pParticle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	_2particleEmitter() {}
	~_2particleEmitter() {}
};

