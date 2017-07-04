#include "stdafx.h"
#include "skPlayer_ShootingStar.h"


HRESULT skPlayer_ShootingStar::init()
{

	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(3);
	setMaxNumActionPS(1);
	setMaxNumFinishPS(1);
	
	setPvPreparePS(0, "샛별준비1", 1);
	setPvPreparePS(1, "샛별준비2", 1);
	setPvPreparePS(2, "샛별마법진", 1);

	setPvActionPS(0,"샛별", 40);
	setPvFinishPS(0, "샛별_터짐", 40);

	//_pvPrepaerPS[0][0]->SetLimitTime(5.0f);
	_pvPrepaerPS[1][0]->SetLimitTime(1.2f);
	_pvPrepaerPS[2][0]->SetLimitTime(2.0f);
	_pvPrepaerPS[1][0]->SetActive(FALSE);
	_pvPrepaerPS[2][0]->SetActive(FALSE);


	for (int i = 0; i < _pvActionPS[0].size(); i++)
	{
		_pvActionPS[0][i]->SetActive(FALSE);
		_pvFinishPS[0][i]->SetActive(FALSE);
		_pvFinishPS[0][i]->SetTime(0.0f);
		_pvFinishPS[0][i]->SetLimitTime(0.3f);
	}

	_oneSettingOn = true;

	_sphereHeight = 0.0f;

	_endCount = 0;
	_activeCount = 0;
	_limitDropTime = 3.0f;
	_currentDropTime = 0.0f;

	return S_OK;
}

void skPlayer_ShootingStar::release()
{
}

bool skPlayer_ShootingStar::Prepare()
{
	
	
	//playerPos.y += 0.01;

	//_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());

	if (_oneSettingOn)
	{
		_startPos = _skillPosTrans->GetWorldPosition();

		_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(_startPos);

		_sphereHeight = _startPos.y = 18.0f;
		_pvPrepaerPS[2][0]->Transform()->SetWorldPosition(_startPos);
		_pvPrepaerPS[1][0]->Transform()->SetWorldPosition(_startPos);
		_pvPrepaerPS[2][0]->Transform()->LookPosition(_oneTargetTrans->GetWorldPosition());


		_oneSettingOn = false;
	}

	//_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillPosTrans->GetForward());


	float crrentHeight = _pvPrepaerPS[0][0]->Transform()->GetWorldPosition().y;

	//높이값 도달하면 작동해라~
	if (_sphereHeight <= crrentHeight)
	{
		_pvPrepaerPS[0][0]->SetActive(FALSE);
		_pvPrepaerPS[1][0]->SetActive(TRUE);
		_pvPrepaerPS[2][0]->SetActive(TRUE);
		/*if (_pvPrepaerPS[1][0]->autoTimeReset(false))
		{
			_pvPrepaerPS[1][0]->SetActive(FALSE);
			
		}*/
		
		_pvPrepaerPS[1][0]->update();

		//_pvPrepaerPS[2][0]->Transform()->SetWorldPosition(_pvPrepaerPS[0][0]->Transform()->GetWorldPosition());
		_pvPrepaerPS[2][0]->update();


		if (_pvPrepaerPS[2][0]->autoTimeReset(false))
		{
			_skillActionOn = true;
		}

	}
	else
	{
		_pvPrepaerPS[0][0]->Transform()->MovePositionLocal(0.0f, 22.0f*_timeDelta, 0.0f);
		_pvPrepaerPS[0][0]->update();
	}

	//_skillActionOn = true;
	//if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	//{
	//	//_skillPrepareOn = false;
	//	
	//	//_skillResetOn = true;
	//}

	

	return false;
}

bool skPlayer_ShootingStar::Action()
{
	//D3DXVECTOR3 ActionPos = _skillPosTrans->GetWorldPosition();

	//ActionPos.y = _sphereHeight;

	int activeNum = 0;
	for (int i = 0; i < _pvActionPS[0].size(); i++)
	{
		if (_pvActionPS[0][i]->GetActive())
		{
			activeNum++;
		}
	}
	for (int i = 0; i < _pvActionPS[0].size(); i++)
	{
		if (_limitDropTime <= _currentDropTime) break;

		if (_pvActionPS[0][i]->GetActive() == FALSE && _pvFinishPS[0][i]->GetActive() == FALSE && (activeNum + i) < _pvActionPS[0].size())
		{
			_pvActionPS[0][i]->Transform()->SetWorldPosition(_startPos);
			_pvActionPS[0][i]->Transform()->LookPosition(_oneTargetTrans->GetWorldPosition());

			D3DXVECTOR3 dirSphere;

			dirSphere.x = RandomFloatRange(-1.0f,1.0f);
			dirSphere.y = RandomFloatRange(-1.0f,1.0f);
			dirSphere.z = RandomFloatRange(-1.0f,1.0f);

			D3DXVec3Normalize(&dirSphere, &dirSphere);

			//랜덤거리
			float randomDistance = RandomFloatRange(0.0f, 4.5f);

			_pvActionPS[0][i]->Transform()->SetWorldPosition(_startPos + (dirSphere * randomDistance));
			
			_pvActionPS[0][i]->SetActive(TRUE);
		}

		
	}

	
	//액션 업데이트
	for (int i = 0; i < _pvActionPS[0].size(); i++)
	{
		if (_pvActionPS[0][i]->GetActive())
		{
			_pvActionPS[0][i]->Transform()->MovePositionSelf(0.0f, 0.0f, 32.0f*_timeDelta);
			_pvActionPS[0][i]->update();

			if (_pvActionPS[0][i]->Transform()->GetWorldPosition().y <= 0.0f)
			{
				
				_pvActionPS[0][i]->SetActive(FALSE);
				_pvFinishPS[0][i]->SetActive(TRUE);
				_skillFinshOn = true;
			}
		}
	}


	return false;
}


void skPlayer_ShootingStar::Finsh()
{
	
	for (int i = 0; i < _pvFinishPS[0].size(); i++)
	{
		if (_pvFinishPS[0][i]->GetActive())
		{
			_pvFinishPS[0][i]->Transform()->SetWorldPosition(_pvActionPS[0][i]->Transform()->GetWorldPosition());
			_pvFinishPS[0][i]->update();
		
			_endCount++;

			//if (_pvFinishPS[0][i]->GetLimitTime() <= _pvFinishPS[0][i]->GetTime())
			if (_pvFinishPS[0][i]->autoTimeReset(false))
			{
				_pvFinishPS[0][i]->reset();
				_pvFinishPS[0][i]->SetTime(0.0f);
				_pvFinishPS[0][i]->SetActive(FALSE);
			}

			_pvFinishPS[0][i]->SetTime(_pvFinishPS[0][i]->GetTime() + _timeDelta);

			
		}
	}



	int endCount = 0;
	if (_limitDropTime <= _currentDropTime)
	{
		for (int i = 0; i < _pvFinishPS[0].size(); i++)
		{
			if (_pvActionPS[0][i]->GetActive() == FALSE && _pvFinishPS[0][i]->GetActive() == FALSE)
			{
				endCount++;
			}
		}
		if (endCount >= _pvFinishPS[0].size())
		{
			//스킬 종료
			_skillResetOn = true;
		}
	}
	//시간 업데이트
	if (_limitDropTime >= _currentDropTime) _currentDropTime += _timeDelta;
}

void skPlayer_ShootingStar::Reset()
{
	_oneSettingOn = true;

	_endCount = 0;
	_activeCount = 0.0f;
	_currentDropTime = 0.0f;

	for (int i = 0; i < _pvActionPS[0].size(); i++)
	{
		_pvActionPS[0][i]->SetActive(FALSE);
		_pvFinishPS[0][i]->SetActive(FALSE);
	}
}