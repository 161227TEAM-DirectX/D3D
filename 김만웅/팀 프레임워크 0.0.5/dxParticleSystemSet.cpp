#include "stdafx.h"
#include "dxParticleSystemSet.h"

HRESULT dxParticleSystemSet::init()
{
	_PS = NULL;
	_PS = new dxParticleSystem;

	return S_OK;
}

void dxParticleSystemSet::release()
{
	//SAFE_DELETE(_PS);
}
