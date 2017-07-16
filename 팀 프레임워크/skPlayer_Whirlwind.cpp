#include "stdafx.h"
#include "skPlayer_Whirlwind.h"


HRESULT skPlayer_Whirlwind::init()
{

	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(2);
	setMaxNumActionPS(1);
	setMaxNumFinishPS(1);
	
	setPvPreparePS(0, "ºù±Ûºù±Û", 1);
	//setPvPreparePS(1, "Å¸°ÙÆÃ", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(10.0f);

	for (int i = 0; i < _pvFinishPS[0].size(); i++)
	{
		_pvFinishPS[0][i]->SetLimitTime(3.0f);
	}


	_actionAtiveNum = 0;


	_LimitTimeOn = false;

	_limitTime = 2.0f;
	_currentTime = 0.0f;

	return S_OK;
}

void skPlayer_Whirlwind::release()
{
}

bool skPlayer_Whirlwind::Prepare()
{
	D3DXVECTOR3 playerPos = _skillPosTrans->GetWorldPosition();
	
	playerPos.y += 0.01;

	//_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(playerPos);
	//_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillPosTrans->GetForward());
	_pvPrepaerPS[0][0]->update();

	//_pvPrepaerPS[1][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	//_pvPrepaerPS[1][0]->Transform()->SetWorldPosition(_oneTagerTrans->GetWorldPosition());
	//_pvPrepaerPS[1][0]->update();

	if (_LimitTimeOn)
	{
		
		_currentTime += _timeDelta;
		
		if (_limitTime <= _currentTime)
		{
			_skillResetOn = true;
		}

	}


	/*if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{*/
		//_skillPrepareOn = false;
		//_skillActionOn = true;
		//_skillResetOn = true;
	//}

	


	return false;
}

bool skPlayer_Whirlwind::Action()
{
	//D3DXVECTOR3 ActionPos = _skillPosTrans->GetWorldPosition();

	return false;
}


void skPlayer_Whirlwind::Finsh()
{
	

}

void skPlayer_Whirlwind::Reset()
{
	_OneActionSettingOn = true;

	_LimitTimeOn = false;

	_actionAtiveNum = 0;

	//_limitShootTime = 0.3f;
	_currentTime = 0.0f;
}