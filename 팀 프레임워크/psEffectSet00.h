#pragma once
#include "dxParticleSystemSet.h"

//#define EffectMake() 

class psEffectSet00 : public dxParticleSystemSet
{

public:
	virtual HRESULT init();
	virtual void release();
private:
	void EffectSet00(string psName);
	void EffectSet01(string psName);
	void EffectSet02(string psName);

public:
	psEffectSet00() {};
	~psEffectSet00() {};
};

