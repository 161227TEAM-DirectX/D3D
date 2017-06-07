#pragma once
#include "gameNode.h"
#include "dxParticleSystem.h"

#include "skill00.h"
#include "skill00_03.h"

class particleTest07 :	public gameNode
{
private:
	transform* _player;
	transform* _target;
	dxParticleSystem* _testPS;
	dxPlaneEmitter* _testEmitter;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	particleTest07() {};
	~particleTest07() {};
};

