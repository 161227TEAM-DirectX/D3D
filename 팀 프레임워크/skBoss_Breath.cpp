#include "stdafx.h"
#include "skBoss_Breath.h"

HRESULT skBoss_Breath::init()
{
	_SkillRenderType = SR_Big;

	//_enemyTrans = new dx::transform[5];

	setMaxNumPreparePS(2);
	setPvPreparePS(0, "ºê·¹½º", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(10.5f);

	return S_OK;

}

void skBoss_Breath::release()
{
}

bool skBoss_Breath::Prepare()
{

	//_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	
	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(_skillPosTrans->GetWorldPosition());
	_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillDirTrans->GetRight());
	_pvPrepaerPS[0][0]->update();

	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		_skillResetOn = true;
	}
	//_pvPrepaerPS[0][0]->Transform()->RotateWorld(0.0f,0.0f,0.01f);
	//if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	//{
	//	_skillStartOn = false;
	//	_skillActionOn = true;
	//	_skillResetOn = true;
	//}



	return false;
}

bool skBoss_Breath::Action()
{
	return false;
}

void skBoss_Breath::Finsh()
{
}

void skBoss_Breath::Reset()
{
}
