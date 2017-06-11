#pragma once
#include "gameNode.h"
#include "dxParticleSystem.h"

#include "skill00.h"
#include "skill00_03.h"

class particleTest08 :	public gameNode
{
private:
	dx::transform* _player;
	dx::transform* _target;
	dxParticleSystem* _testPS;
	dxBoardEmitter* _testEmitter;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	particleTest08() {};
	~particleTest08() {};
};

