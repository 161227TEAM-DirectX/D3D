#include "stdafx.h"
#include "skBoss_FirePath.h"

HRESULT skBoss_FirePath::init()
{
	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(1);

	//setPvActionPS(0, "¸ÕÁö_ÆÛÁü", 1);
	setPvPreparePS(0, "ºÒ²É±æ", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(60.0f);

	_oneSetting = true;

	return S_OK;
}

void skBoss_FirePath::release()
{
}

bool skBoss_FirePath::Prepare()
{
	/*if (_oneSetting)
	{*/
		_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(_skillPosTrans->GetWorldPosition());
		_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillDirTrans->GetForward());

		_oneSetting = false;
	//}
	
	_pvPrepaerPS[0][0]->update();

	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		_skillResetOn = true;
	}


	return false;
}

bool skBoss_FirePath::Action()
{
	return false;
}

void skBoss_FirePath::Finsh()
{
}

void skBoss_FirePath::Reset()
{
	_oneSetting = true;
}
