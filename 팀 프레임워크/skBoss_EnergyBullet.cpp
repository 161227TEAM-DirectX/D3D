#include "stdafx.h"
#include "skBoss_EnergyBullet.h"

HRESULT skBoss_EnergyBullet::init()
{
	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(1);
	setMaxNumActionPS(1);
	setMaxNumFinishPS(1);

	setPvPreparePS(0, "¿¡³ÊÁöÅº_ÁØºñ", 1);

	setPvActionPS(0, "¿¡³ÊÁöÅº", 1);
	setPvFinishPS(0, "¿¡³ÊÁöÅº_Æø¹ß", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(3.0f);
	//_pvActionPS[0][0]->SetLimitTime(6.0f);
	_pvFinishPS[0][0]->SetLimitTime(5.4f);
	

	//setArrayPreparePS("Å×½ºÆ®",7);

	_oneSettingOn = true;

	return S_OK;
}

void skBoss_EnergyBullet::release()
{
}

bool skBoss_EnergyBullet::Prepare()
{
	
	/*_skillActionOn = true;
	_skillFinshOn = true;*/

	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(_skillPosTrans->GetWorldPosition());
	_pvPrepaerPS[0][0]->update();

	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		_skillPrepareOn = false;
		_skillActionOn = true;
	}

	return false;
}

bool skBoss_EnergyBullet::Action()
{

	if (_oneSettingOn)
	{
		_pvActionPS[0][0]->Transform()->SetWorldPosition(_pvPrepaerPS[0][0]->Transform()->GetWorldPosition());
		_pvActionPS[0][0]->Transform()->LookPosition(_oneTargetTrans->GetWorldPosition());

		_oneSettingOn = false;
	}

	

	_pvActionPS[0][0]->Transform()->MovePositionSelf(0.0f,0.0f,32.0f*_timeDelta);
	_pvActionPS[0][0]->update();
	


	if (_pvActionPS[0][0]->Transform()->GetWorldPosition().y <= 0.1f)
	{

		_skillActionOn = false;
		_skillFinshOn = true;
	}

	return false;
}

void skBoss_EnergyBullet::Finsh()
{
	D3DXVECTOR3 actionPos = _pvActionPS[0][0]->Transform()->GetWorldPosition();

	actionPos.y = 0.1f;
	//actionPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	_pvFinishPS[0][0]->Transform()->SetWorldPosition(actionPos);
	//_pvFinishPS[0][0]->Transform()->SetWorldPosition(_skillPosTrans->GetWorldPosition());
	_pvFinishPS[0][0]->update();

	if (_pvFinishPS[0][0]->autoTimeReset(false))
	{
		_skillResetOn = true;
	}
}

void skBoss_EnergyBullet::Reset()
{
	_oneSettingOn = true;
}
