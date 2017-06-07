#pragma once
#include "gameNode.h"
#include "dxPointEmitter.h"
#include "dxPlaneEmitter.h"
#include "dxBoardEmitter.h"
#include "dxMeshEmitter.h"

#include "dxParticleSystem.h"

class dxParticleSystemSet : public gameNode
{
protected:
	dxParticleSystem* _PS;
	dxPointEmitter* _pointEMT;
	dxPlaneEmitter* _planeEMT;
public:
	//순수 가상함수
	virtual HRESULT init();
	virtual void release();

	virtual dxParticleSystem* getPS() { return _PS; }

public:
	dxParticleSystemSet() {}//_PS = new dxParticleSystem; }
	~dxParticleSystemSet() {}
};

