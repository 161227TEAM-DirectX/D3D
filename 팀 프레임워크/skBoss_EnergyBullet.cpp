#include "stdafx.h"
#include "skBoss_EnergyBullet.h"

HRESULT skBoss_EnergyBullet::init()
{
	_SkillRenderType = SR_Big;

	setArrayPreparePS("Å×½ºÆ®",7);


	return S_OK;
}

void skBoss_EnergyBullet::release()
{
}

bool skBoss_EnergyBullet::Prepare()
{

	_vPrepaerPS[0]->update();
	return false;
}

bool skBoss_EnergyBullet::Action()
{
	return false;
}

void skBoss_EnergyBullet::Finsh()
{
}

void skBoss_EnergyBullet::Reset()
{
}
