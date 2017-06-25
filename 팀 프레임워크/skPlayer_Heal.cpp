#include "stdafx.h"
#include "skPlayer_Heal.h"


HRESULT skPlayer_Heal::init()
{

	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(2);
	setMaxNumActionPS(1);
	setMaxNumFinishPS(1);
	
	setPvPreparePS(0, "Èú_¸¶¹ýÁø", 1);
	//setPvPreparePS(1, "Å¸°ÙÆÃ", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(2.0f);

	for (int i = 0; i < _pvFinishPS[0].size(); i++)
	{
		_pvFinishPS[0][i]->SetLimitTime(0.4f);
	}
	


	_OneActionSettingOn = true;

	_BP = new tagBezierPoint[6];

	for (int i = 0; i < 6; i++)
	{
		_bpTime[i] = 0.0f;
	}

	_actionAtiveNum = 0;

	_limitShootTime = 0.3f;
	_currentShootTime = 0.0f;

	return S_OK;
}

void skPlayer_Heal::release()
{
}

bool skPlayer_Heal::Prepare()
{
	D3DXVECTOR3 circlePos = _skillPosTrans->GetWorldPosition();
	
	circlePos.y += 0.01;

	//_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(circlePos);
	//_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillPosTrans->GetForward());
	_pvPrepaerPS[0][0]->update();

	//_pvPrepaerPS[1][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	//_pvPrepaerPS[1][0]->Transform()->SetWorldPosition(_oneTagerTrans->GetWorldPosition());
	//_pvPrepaerPS[1][0]->update();


	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		//_skillPrepareOn = false;
		//_skillActionOn = true;
		_skillResetOn = true;
	}

	

	return false;
}

bool skPlayer_Heal::Action()
{
	D3DXVECTOR3 ActionPos = _skillPosTrans->GetWorldPosition();

	

	return false;
}


void skPlayer_Heal::Finsh()
{
	

}

void skPlayer_Heal::Reset()
{
	_OneActionSettingOn = true;

	_BP = new tagBezierPoint[6];

	for (int i = 0; i < 6; i++)
	{
		_bpTime[i] = 0.0f;
	}

	_actionAtiveNum = 0;

	_limitShootTime = 0.3f;
	_currentShootTime = 0.0f;
}