#pragma once
#include "dxParticleSystemSet.h"
class PS_Set00 : public dxParticleSystemSet
{

public:
	virtual HRESULT init();
	virtual void release();
private:
	void set00_00(string psName);
	void set00_01(string psName);

	void set01_00(string psName);
	void set01_01(string psName);

public:
	PS_Set00() {};
	~PS_Set00() {};
};

