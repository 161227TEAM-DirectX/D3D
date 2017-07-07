#include "stdafx.h"
#include "skPlayer_SkySword.h"


HRESULT skPlayer_SkySword::init()
{

	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(3);
	//setMaxNumActionPS(1);
	//setMaxNumFinishPS(1);
	
	setPvPreparePS(0, "대검", 1);
	setPvPreparePS(1, "대검_이펙트", 1);
	setPvPreparePS(2, "대검_먼지", 1);

	for (int i = 0; i < _pvPrepaerMaxNum; i++)
	{
		_pvPrepaerPS[i][0]->SetLimitTime(20.0f);
	}



	//_OneActionSettingOn = true;


	_actionAtiveNum = 0;

	_limitShootTime = 0.3f;
	_currentShootTime = 0.0f;

	_oneSettingOn = true;

	_accel = 0.0f;

	return S_OK;
}

void skPlayer_SkySword::release()
{
}

bool skPlayer_SkySword::Prepare()
{

	

	//_pvPrepaerPS[0][0]->update();

	D3DXVECTOR3 tagetPos = _oneTargetTrans->GetWorldPosition();

	for (int i = 0; i < _pvPrepaerMaxNum; i++)
	{

		if (_oneSettingOn)
		{
			
			//tagetPos.y += 0.01;

			if (i == 0)
			{
				
				_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(tagetPos);
			}
			else
			{
				_pvPrepaerPS[i][0]->Transform()->SetWorldPosition(_oneTargetTrans->GetWorldPosition());
			}
			
		}
		tagetPos.y = 100.0f;
		_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(tagetPos);

		/*if (i == 0)
		{
			if (_pvPrepaerPS[0][0]->Transform()->GetWorldPosition().y >= -80.0f)
			{
				_accel -= 0.05f;
				_pvPrepaerPS[0][0]->Transform()->MovePositionSelf(0.0f, (-100.0f+_accel)*_timeDelta, 0.0f);
			}
		}*/

		//_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillPosTrans->GetForward());
		_pvPrepaerPS[i][0]->update();

		//_pvPrepaerPS[1][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
		//_pvPrepaerPS[1][0]->Transform()->SetWorldPosition(_oneTagerTrans->GetWorldPosition());
		//_pvPrepaerPS[1][0]->update();


		if (_pvPrepaerPS[i][0]->autoTimeReset(false))
		{
			//_skillPrepareOn = false;
			//_skillActionOn = true;
			_skillResetOn = true;
		}

	}

	_oneSettingOn = false;

	

	return false;
}

bool skPlayer_SkySword::Action()
{
	D3DXVECTOR3 ActionPos = _skillPosTrans->GetWorldPosition();

	

	return false;
}


void skPlayer_SkySword::Finsh()
{
	

}

void skPlayer_SkySword::Reset()
{
	_oneSettingOn = true;



	_actionAtiveNum = 0;

	_limitShootTime = 0.3f;
	_currentShootTime = 0.0f;
}