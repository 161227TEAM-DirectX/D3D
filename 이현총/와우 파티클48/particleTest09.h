#pragma once
#include "gameNode.h"
#include "dxParticleSystem.h"

#include "skill00.h"
#include "skill00_03.h"

class particleTest09 :	public gameNode
{
private:
	transform* _player;
	transform* _target;
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

	particleTest09() {};
	~particleTest09() {};
};

