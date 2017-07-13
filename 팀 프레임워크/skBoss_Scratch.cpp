#include "stdafx.h"
#include "skBoss_Scratch.h"

HRESULT skBoss_Scratch::init()
{
	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(1);

	//setPvActionPS(0, "¸ÕÁö_ÆÛÁü", 1);
	setPvPreparePS(0, "ºÒ²ÉÇÒÄû±â", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(5.0f);

	_oneSetting = true;

	return S_OK;
}

void skBoss_Scratch::release()
{
}

bool skBoss_Scratch::Prepare()
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

bool skBoss_Scratch::Action()
{
	return false;
}

void skBoss_Scratch::Finsh()
{
}

void skBoss_Scratch::Reset()
{
	_oneSetting = true;
}
