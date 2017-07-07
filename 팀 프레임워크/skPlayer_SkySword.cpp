#include "stdafx.h"
#include "skPlayer_SkySword.h"


HRESULT skPlayer_SkySword::init()
{

	_SkillRenderType = SR_Big;

	//setMaxNumPreparePS(3);
	setMaxNumActionPS(3);
	//setMaxNumFinishPS(1);

	setPvActionPS(0, "대검", 1);
	setPvActionPS(1, "대검_이펙트", 1);
	setPvActionPS(2, "대검_먼지", 1);

	for (int i = 0; i < _pvActionMaxNum; i++)
	{
		_pvActionPS[i][0]->SetLimitTime(7.0f);
	}
	_pvActionPS[2][0]->SetActive(FALSE);


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
	_skillActionOn = true;
	
	//for (int i = 0; i < _pvPrepaerMaxNum; i++)
	//{

	//	if (_oneSettingOn)
	//	{
	//		
	//		//tagetPos.y += 0.01;

	//		if (i == 0)
	//		{
	//			
	//			_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(tagetPos);
	//		}
	//		else
	//		{
	//			_pvPrepaerPS[i][0]->Transform()->SetWorldPosition(_oneTargetTrans->GetWorldPosition());
	//		}
	//		
	//	}
	//	tagetPos.y = 100.0f;
	//	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(tagetPos);

	//	/*if (i == 0)
	//	{
	//		if (_pvPrepaerPS[0][0]->Transform()->GetWorldPosition().y >= -80.0f)
	//		{
	//			_accel -= 0.05f;
	//			_pvPrepaerPS[0][0]->Transform()->MovePositionSelf(0.0f, (-100.0f+_accel)*_timeDelta, 0.0f);
	//		}
	//	}*/

	//	//_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillPosTrans->GetForward());
	//	_pvPrepaerPS[i][0]->update();

	//	//_pvPrepaerPS[1][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	//	//_pvPrepaerPS[1][0]->Transform()->SetWorldPosition(_oneTagerTrans->GetWorldPosition());
	//	//_pvPrepaerPS[1][0]->update();


	//	if (_pvPrepaerPS[i][0]->autoTimeReset(false))
	//	{
	//		//_skillPrepareOn = false;
	//		//_skillActionOn = true;
	//		_skillResetOn = true;
	//	}

	//}

	//_oneSettingOn = false;



	return false;
}

bool skPlayer_SkySword::Action()
{
	//D3DXVECTOR3 ActionPos = _skillPosTrans->GetWorldPosition();

	D3DXVECTOR3 tagetPos = _oneTargetTrans->GetWorldPosition();

	if (_oneSettingOn)
	{
		_pvActionPS[2][0]->Transform()->SetWorldPosition(tagetPos);

		//대검 초기 위치
		tagetPos.y = 100.0f;
		_pvActionPS[0][0]->Transform()->SetWorldPosition(tagetPos);
		
		_oneSettingOn = false;
	}

	_accel += -0.06f;
	//D3DXVECTOR3 currentPos = _pvActionPS[0][0]->Transform()->GetWorldPosition();
	//D3DXVECTOR3 movePos = D3DXVECTOR3(0.0f, (-1.0f),0.0f);

	//_pvActionPS[0][0]->Transform()->SetWorldPosition(currentPos+movePos);
	if (_pvActionPS[0][0]->Transform()->GetWorldPosition().y >= -10.0f)
	{
		_pvActionPS[0][0]->Transform()->MovePositionLocal(0.0f, (-22.0f + _accel)*_timeDelta, 0.0f);
	}
	//_pvActionPS[0][0]->update();

	if (_pvActionPS[0][0]->Transform()->GetWorldPosition().y >= 0.0f)
	{
		_pvActionPS[1][0]->Transform()->SetWorldPosition(_pvActionPS[0][0]->Transform()->GetWorldPosition());
	}

	//먼지여 작동하라
	if (_pvActionPS[0][0]->Transform()->GetWorldPosition().y <= 60.0f)
	{
		_pvActionPS[2][0]->SetActive(TRUE);
		
	}

	//업데이트
	for (int i = 0; i < _pvActionMaxNum; i++)
	{
		_pvActionPS[i][0]->update();
	}
	
	//_pvActionPS[1][0]->update();


	if (_pvActionPS[0][0]->autoTimeReset(false))
	{
		//_skillPrepareOn = false;
		//_skillActionOn = true;
		_skillResetOn = true;
	}



	return false;
}


void skPlayer_SkySword::Finsh()
{


}

void skPlayer_SkySword::Reset()
{
	_oneSettingOn = true;

	_pvActionPS[2][0]->SetActive(FALSE);

	_accel = 0.0f;

	_actionAtiveNum = 0;

	_limitShootTime = 0.3f;
	_currentShootTime = 0.0f;
}