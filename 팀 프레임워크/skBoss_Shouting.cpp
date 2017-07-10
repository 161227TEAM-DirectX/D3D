#include "stdafx.h"
#include "skBoss_Shouting.h"

HRESULT skBoss_Shouting::init()
{
	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(1);

	setPvPreparePS(0, "»þ¿ìÆÃ", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(5.0f);


	return S_OK;
}

void skBoss_Shouting::release()
{
}

bool skBoss_Shouting::Prepare()
{

	_pvPrepaerPS[0][0]->update();

	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		_skillResetOn = true;
	}


	return false;
}

bool skBoss_Shouting::Action()
{
	return false;
}

void skBoss_Shouting::Finsh()
{
}

void skBoss_Shouting::Reset()
{
}
