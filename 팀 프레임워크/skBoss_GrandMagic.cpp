#include "stdafx.h"
#include "skBoss_GrandMagic.h"

HRESULT skBoss_GrandMagic::init()
{
	_SkillRenderType = SR_Big;

	//_enemyTrans = new dx::transform[5];

	setMaxNumPreparePS(2);
	setMaxNumActionPS(2);
	setPvPreparePS(0, "대마법진", 1);
	//setPvActionPS(0, "대규모_마법진", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(100.0f);

	return S_OK;

}

void skBoss_GrandMagic::release()
{
}

bool skBoss_GrandMagic::Prepare()
{

	//_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(_skillPosTrans->GetWorldPosition());
	_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillDirTrans->GetForward());
	_pvPrepaerPS[0][0]->update();
	//_pvPrepaerPS[0][0]->Transform()->RotateWorld(0.0f,0.0f,0.01f);
	/*if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		_skillStartOn = false;
		_skillActionOn = true;
		_skillResetOn = true;
	}*/
	//_pvPrepaerPS[0][0]->update();
	
	_skillActionOn = true;
	


	return false;
}

bool skBoss_GrandMagic::Action()
{

//	_pvActionPS[0][0]->update();

	return false;
}

void skBoss_GrandMagic::Finsh()
{
}

void skBoss_GrandMagic::Reset()
{
}
