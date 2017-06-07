#pragma once
#include "gameNode.h"
#include "dxParticleSystem.h"
#include "dxPointEmitter.h"


class particleTest03:	public gameNode
{
private:
	dxParticleSystem* _testPS;
	dxPointEmitter* _testEmitter;

	dxPointEmitter* _testEmitter02;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	particleTest03() {};
	~particleTest03() {};
};

