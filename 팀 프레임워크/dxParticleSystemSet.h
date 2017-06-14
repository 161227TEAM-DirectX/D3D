#pragma once
#include "gameNode.h"
#include "dxPointEmitter.h"
#include "dxPlaneEmitter.h"
#include "dxBoardEmitter.h"
#include "dxMeshEmitter.h"

#include "dxParticleSystem.h"

class dxParticleSystemSet
{
protected:
	dxParticleSystem* _PS;
	dxPointEmitter* _pointEMT;
	dxPlaneEmitter* _planeEMT;
	dxBoardEmitter* _boardEMT;
	dxMeshEmitter* _meshEMT;
public:
	//순수 가상함수
	virtual HRESULT init();
	virtual void release();
	virtual void update(void) {}
	virtual void render(void) {}


	virtual dxParticleSystem* getPS() { return _PS; }

public:
	dxParticleSystemSet() {}//_PS = new dxParticleSystem; }
	~dxParticleSystemSet() {}
};

