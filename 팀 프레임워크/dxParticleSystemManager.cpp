#include "stdafx.h"
#include "dxParticleSystemManager.h"

void dxParticleSystemManager::ParticleSystemSetInit()
{
	_playerSet00 = new psPlayerSet00;
	_playerSet00->init();
	_bossSet00 = new psBossSet00;
	_bossSet00->init();
	_effectSet00 = new psEffectSet00;
	_effectSet00->init();

}

void dxParticleSystemManager::ParticleSystemSetRelease()
{
	if (_playerSet00 != NULL)
	{
		_playerSet00->release();
		SAFE_DELETE(_playerSet00);
	}
	if (_bossSet00 != NULL)
	{
		_bossSet00->release();
		SAFE_DELETE(_bossSet00);
	}
	if (_effectSet00 != NULL)
	{
		_effectSet00->release();
		SAFE_DELETE(_effectSet00);
	}
}
