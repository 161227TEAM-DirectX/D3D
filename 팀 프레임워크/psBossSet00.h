#pragma once
#include "dxParticleSystemSet.h"
class psBossSet00 : public dxParticleSystemSet
{

public:
	virtual HRESULT init();
	virtual void release();
private:
	void BreathSet00(string psName);

	void ShoutingSet00(string psName);

	void GrandMagic00(string psName);
	void GrandMagic01(string psName);


	void EnergyBullet00(string psName);
	void EnergyBullet01(string psName);

public:
	psBossSet00() {};
	~psBossSet00() {};
};

