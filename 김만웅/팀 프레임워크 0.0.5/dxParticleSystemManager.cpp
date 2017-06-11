#include "stdafx.h"
#include "dxParticleSystemManager.h"

void dxParticleSystemManager::ParticleSystemSetInit()
{
	_set00 = new PS_Set00;
	_set00->init();
}

void dxParticleSystemManager::ParticleSystemSetRelease()
{

	_set00->release();
	SAFE_DELETE(_set00);
}
