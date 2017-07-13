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

	_groundPos = 0.0f;

	return S_OK;
}

void skBoss_EnergyBullet::release()
{
}

bool skBoss_EnergyBullet::Prepare()
{
	
	/*_skillActionOn = true;
	_skillFinshOn = true;*/

	D3DXVECTOR3 startPos = _skillPosTrans->GetWorldPosition();
	//startPos.y = _skillPosTrans->GetWorldPosition().y + 8.0f;

	//_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillPosTrans->GetForward());
	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(startPos + (_skillPosTrans->GetUp()*10.0f));
	_pvPrepaerPS[0][0]->update();

	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		_pvPrepaerPS[0][0]->SetActive(FALSE);
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
		_groundPos = _oneTargetTrans->GetWorldPosition().y + 0.5f;

		_oneSettingOn = false;


	}

	

	_pvActionPS[0][0]->Transform()->MovePositionSelf(0.0f,0.0f,32.0f*_timeDelta);
	_pvActionPS[0][0]->update();
	


	if (_pvActionPS[0][0]->Transform()->GetWorldPosition().y <= _groundPos)
	{

		_skillActionOn = false;
		_skillFinshOn = true;
	}

	_collisionOn = true;

	return false;
}

void skBoss_EnergyBullet::Finsh()
{
	D3DXVECTOR3 actionPos = _pvActionPS[0][0]->Transform()->GetWorldPosition();

	actionPos.y = _groundPos;
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
	_pvPrepaerPS[0][0]->SetActive(TRUE);
	//_pvActionPS[0][0]->reset();
	_oneSettingOn = true;
}
