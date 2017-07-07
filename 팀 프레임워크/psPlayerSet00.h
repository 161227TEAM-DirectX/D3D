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
	void MagicShieldSet00(string psName);

	void LightningSet00(string psName);
	void LightningSet01(string psName);

	void ShootingStarSet00(string psName);
	void ShootingStarSet01(string psName);
	void ShootingStarSet02(string psName);
	void ShootingStarSet03(string psName);
	void ShootingStarSet04(string psName);

	void SkySwordSet00(string psName);
	void SkySwordSet01(string psName);
	void SkySwordSet02(string psName);


public:
	psPlayerSet00() {};
	~psPlayerSet00() {};
};

