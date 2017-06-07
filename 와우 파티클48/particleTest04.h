#pragma once
#include "gameNode.h"
#include "dxParticleSystem.h"
#include "dxPointEmitter.h"
#include "skill00.h"
#include "skill00_01.h"

class particleTest04:	public gameNode
{
private:
	transform* _player;
	transform* _target;
	dxParticleSystem* _testPS;
	dxPointEmitter* _testEmitter;

	skill00* _testSkill;
	
	skill00_01* _testSkill01;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	particleTest04() {};
	~particleTest04() {};
};

