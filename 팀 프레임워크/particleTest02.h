#pragma once
#include "gameNode.h"
#include "dxParticleSystem.h"
#include "dxPointEmitter.h"


class particleTest02 :	public gameNode
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

	particleTest02() {};
	~particleTest02() {};
};

