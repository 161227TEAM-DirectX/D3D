#include "stdafx.h"
#include "dxParticleSystemManager.h"

void dxParticleSystemManager::ParticleSystemSetInit()
{
	_set00 = new PS_Set00;
	_set00->init();
	_set01 = new PS_Set01;
	_set01->init();
	_playerSet00 = new psPlayerSet00;
	_playerSet00->init();
	_bossSet00 = new psBossSet00;
	_bossSet00->init();
	_effectSet00 = new psEffectSet00;
	_effectSet00->init();

}

void dxParticleSystemManager::ParticleSystemSetRelease()
{

	_set00->release();
	SAFE_DELETE(_set00);
	_set01->release();
	SAFE_DELETE(_set01);
	_playerSet00->release();
	SAFE_DELETE(_playerSet00);
	_bossSet00->release();
	SAFE_DELETE(_bossSet00);
	_effectSet00->release();
	SAFE_DELETE(_effectSet00);
}
