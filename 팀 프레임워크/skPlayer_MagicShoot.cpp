#include "stdafx.h"
#include "skPlayer_MagicShoot.h"


HRESULT skPlayer_MagicShoot::init()
{

	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(2);
	setMaxNumActionPS(1);
	setMaxNumFinishPS(1);
	
	setPvPreparePS(0, "마법진", 1);
	setPvPreparePS(1, "타겟팅", 1);

	setPvActionPS(0, "구체", 6);

	setPvFinishPS(0, "폭발", 6);

	_pvPrepaerPS[0][0]->SetLimitTime(2.0f);

	for (int i = 0; i < _pvFinishPS[0].size(); i++)
	{
		_pvFinishPS[0][i]->SetLimitTime(0.4f);
	}
	
	for (int i = 0; i < _pvActionPS[0].size(); i++)
	{
		_pvActionPS[0][i]->SetActive(FALSE);
		_pvFinishPS[0][i]->SetActive(FALSE);
	}

	//충돌 체크 초기화
	for (int i = 0; i < 6; i++)
	{
		collisionCheckOn[i] = FALSE;
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

void skPlayer_MagicShoot::release()
{
}

bool skPlayer_MagicShoot::Prepare()
{
	//_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(_skillPosTrans->GetWorldPosition());
	_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillPosTrans->GetForward());
	_pvPrepaerPS[0][0]->update();

	//_pvPrepaerPS[1][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	_pvPrepaerPS[1][0]->Transform()->SetWorldPosition(_oneTargetTrans->GetWorldPosition());
	_pvPrepaerPS[1][0]->update();


	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		//_skillPrepareOn = false;
		_skillActionOn = true;
	}

	

	return false;
}

bool skPlayer_MagicShoot::Action()
{
	D3DXVECTOR3 ActionPos = _skillPosTrans->GetWorldPosition();

	if (_OneActionSettingOn)
	{
		for (int i = 0; i < _pvActionPS[0].size(); i++)
		{
			_pvActionPS[0][i]->SetActive(FALSE);
			_pvFinishPS[0][i]->SetActive(FALSE);
			_pvActionPS[0][i]->Transform()->LookPosition(_oneTargetTrans->GetWorldPosition());
		}
		_OneActionSettingOn = false;
	}

	if(_limitShootTime <=_currentShootTime && _actionAtiveNum < _pvActionPS[0].size())
	{
		_pvActionPS[0][_actionAtiveNum]->SetActive(TRUE);

		_pvActionPS[0][_actionAtiveNum]->Transform()->SetWorldPosition(ActionPos.x, ActionPos.y + 3.0f, ActionPos.z);

		//방향 결정
		float RightDir = 1.0f;
		(_actionAtiveNum % 2 == 0) ? RightDir = 1.0f : RightDir = -1.0f;

		_BP[_actionAtiveNum].P0 = _pvActionPS[0][_actionAtiveNum]->Transform()->GetWorldPosition();
		_BP[_actionAtiveNum].P1 = _BP[_actionAtiveNum].P0 + _pvActionPS[0][_actionAtiveNum]->Transform()->GetRight() *RightDir* 5.0f + _pvActionPS[0][_actionAtiveNum]->Transform()->GetForward()*-5.0f;
		_BP[_actionAtiveNum].P2 = _BP[_actionAtiveNum].P0 + _pvActionPS[0][_actionAtiveNum]->Transform()->GetRight() *RightDir* 3.0f + _pvActionPS[0][_actionAtiveNum]->Transform()->GetForward()*-3.0f;
		_BP[_actionAtiveNum].P3 = _oneTargetTrans->GetWorldPosition();

		_currentShootTime = 0.0f;

		_tagetSettingOn = false;
		//_currentTime = _timeDelta;

		_actionAtiveNum++;
	}

	_currentShootTime += _timeDelta;


	for (int i = 0; i < _pvActionPS[0].size(); i++)
	{
		if (_pvActionPS[0][i]->GetActive())
		{
			_bpTime[i] += _timeDelta*1.4f;
			_pvActionPS[0][i]->Transform()->SetWorldPosition(BezierP3Cube(_BP[i], _bpTime[i]));
			_pvActionPS[0][i]->update();

			if (_bpTime[i] >= 1.0f)
			{
				_pvActionPS[0][i]->SetActive(FALSE);
				_pvFinishPS[0][i]->SetActive(TRUE);
				_skillFinshOn = true;
			}
		}

		
	}

	return false;
}


void skPlayer_MagicShoot::Finsh()
{
	int endCount = 0;
	for (int i = 0; i < _pvFinishPS[0].size(); i++)
	{
		if (_pvFinishPS[0][i]->GetActive())
		{
			_pvFinishPS[0][i]->Transform()->SetWorldPosition(_oneTargetTrans->GetWorldPosition());
			_pvFinishPS[0][i]->update();
			_pvFinishPS[0][i]->autoTimeReset();
		}
		else
		{
			endCount++;
		}
	}

	if(endCount >= _pvFinishPS[0].size())
	{
		_skillResetOn = true;
	}
}

void skPlayer_MagicShoot::Reset()
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

	for (int i = 0; i < 6; i++)
	{
		collisionCheckOn[i] = FALSE;
	}

}

