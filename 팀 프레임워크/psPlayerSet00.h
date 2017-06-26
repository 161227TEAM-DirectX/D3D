#pragma once
#include "dxParticleSystemSet.h"
class psPlayerSet00 : public dxParticleSystemSet
{

public:
	virtual HRESULT init();
	virtual void release();
private:
	void MagicShootSet00(string psName);
	void MagicShootSet01(string psName);
	void MagicShootSet02(string psName);
	void MagicShootSet03(string psName);

	void HealSet00(string psName);
	void FireMagicSet00(string psName);
	void HealSet02(string psName);

public:
	psPlayerSet00() {};
	~psPlayerSet00() {};
};

