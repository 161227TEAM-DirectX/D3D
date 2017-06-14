#pragma once
#include "dxParticleSystemSet.h"
class PS_Set02 : public dxParticleSystemSet
{

public:
	virtual HRESULT init();
	virtual void release();
private:
	void set00_00(string psName);
	void set00_01(string psName);

public:
	PS_Set02() {};
	~PS_Set02() {};
};

