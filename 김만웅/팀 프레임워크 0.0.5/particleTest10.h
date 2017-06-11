#pragma once
#include "gameNode.h"
#include "dxParticleSystem.h"

#include "skill00.h"
#include "skill00_03.h"

class particleTest10 :	public gameNode
{
private:
	dx::transform* _player;
	dx::transform* _target;
	dxParticleSystem* _testPS;
	dxMeshEmitter* _testEmitter;

	camera* _mineCamera;

	float rotateY;
	float wave;

	float radius;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	particleTest10() {};
	~particleTest10() {};
};

