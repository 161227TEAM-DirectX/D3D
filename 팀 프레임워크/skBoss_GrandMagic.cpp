#include "stdafx.h"
#include "skBoss_GrandMagic.h"

HRESULT skBoss_GrandMagic::init()
{
	_SkillRenderType = SR_Big;

	//_enemyTrans = new dx::transform[5];

	setMaxNumPreparePS(2);
	//setMaxNumActionPS(2);
	setPvPreparePS(0, "대마법진", 1);
	//setPvActionPS(0, "대규모마법", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(5.0f);
	//_pvActionPS[0][0]->SetLimitTime(8.0f);

	return S_OK;

}

void skBoss_GrandMagic::release()
{
}

bool skBoss_GrandMagic::Prepare()
{
	D3DXVECTOR3 pos = _skillPosTrans->GetWorldPosition();

	pos.y += 25.0f;

	//_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(pos);
	//_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillDirTrans->GetForward());
	_pvPrepaerPS[0][0]->update();
	//_pvPrepaerPS[0][0]->Transform()->RotateWorld(0.0f,0.0f,0.01f);
	/*if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		_skillStartOn = false;
		_skillActionOn = true;
		_skillResetOn = true;
	}*/
	//_pvPrepaerPS[0][0]->update();
	
	//_skillActionOn = true;

	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		_skillResetOn = true;
	}

	return false;
}

bool skBoss_GrandMagic::Action()
{

	/*_pvActionPS[0][0]->update();

	if (_pvActionPS[0][0]->autoTimeReset(false))
	{
		_skillResetOn = true;
	}*/

	return false;
}

void skBoss_GrandMagic::Finsh()
{
}

void skBoss_GrandMagic::Reset()
{
}
