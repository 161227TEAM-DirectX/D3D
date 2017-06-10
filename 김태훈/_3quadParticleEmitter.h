#pragma once
#include "gameNode.h"

class _3quadParticleEmitter : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	_3quadParticleEmitter() {}
	~_3quadParticleEmitter() {}
};

