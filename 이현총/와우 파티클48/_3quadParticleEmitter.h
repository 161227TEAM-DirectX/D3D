#pragma once
#include "gameNode.h";
#include "quadParticleEmitter.h"

class _3quadParticleEmitter : public gameNode
{
private:
	quadParticleEmitter* _particle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	_3quadParticleEmitter() {}
	~_3quadParticleEmitter() {}
};

