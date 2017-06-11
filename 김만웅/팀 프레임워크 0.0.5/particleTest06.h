#pragma once
#include "gameNode.h"
#include "dxParticleSystem.h"
#include "dxPointEmitter.h"
#include "skill00.h"
#include "skill00_03.h"

class particleTest06 :	public gameNode
{
private:
	dx::transform* _player;
	dx::transform* _target;
	dxParticleSystem* _testPS;
	dxPointEmitter* _testEmitter;

	skill00* _testSkill;
	
	skill00_03* _testSkill03;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	particleTest06() {};
	~particleTest06() {};
};

