#include "stdafx.h"
#include "skBoss_EnergyBullet.h"

HRESULT skBoss_EnergyBullet::init()
{
	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(1);
	setMaxNumActionPS(1);
	setMaxNumFinishPS(1);

	setPvPreparePS(0, "»ûº°ÁØºñ1", 1);
	setPvPreparePS(1, "»ûº°ÁØºñ2", 1);
	setPvPreparePS(2, "»ûº°¸¶¹ýÁø", 1);

	setPvActionPS(0, "¿¡³ÊÁöÅº", 40);
	setPvFinishPS(0, "¿¡³ÊÁöÅº_Æø¹ß", 40);

	//setArrayPreparePS("Å×½ºÆ®",7);


	return S_OK;
}

void skBoss_EnergyBullet::release()
{
}

bool skBoss_EnergyBullet::Prepare()
{
	
		_skillActionOn = true;
	//_vPrepaerPS[0]->update();


	return false;
}

bool skBoss_EnergyBullet::Action()
{
	_skillFinshOn = true;

	return false;
}

void skBoss_EnergyBullet::Finsh()
{

}

void skBoss_EnergyBullet::Reset()
{
}
