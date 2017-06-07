#include "stdafx.h"
#include "skill00_01.h"

HRESULT skill00_01::init()
{
	////동작들 초기화
	//_skillStartOn = false;
	//_skillActionOn = false;
	//_skillFinshOn = false;
	//_skillReset = false;
	////시간 초기화
	//_currentResetTime = 0.0f;
	//_resetTime = 0.0f;
/*
	this->setActionPS("구슬");
	this->setFinishPS("터짐");
*/
/*PSM->initPS(_actionPS, "구슬");
PSM->initPS(_finshPS, "터짐");
*/
//_defualtRendrOn = true;

/*_actionSphereCollision = new boundSphere;
_actionSphereCollision->setBound(&_actionPS->Transform()->GetWorldPosition(), &D3DXVECTOR3(0.1f, 0.1f, 0.1f));
_targetSphereCollision = new boundSphere;
_targetSphereCollision->setBound(&_targetTrans->GetWorldPosition(), &D3DXVECTOR3(0.1f, 0.1f, 0.1f));*/

	_oneSettingOn = true;

	this->setArrayActionPS("구슬", 20);
	this->setArrayFinishPS("터짐", 20);

	_firstPlayerPos = new D3DXVECTOR3[20];

	_SkillRenderType = SR_Array;

	_resetTime = 0.3f;

	_isActiveTime = 0.3f;
	_currentTime = _isActiveTime;
	_activeNum = 0;

	for (int i = 0; i < 8; i++)
	{
		_testLimitTime[i] = 5.0f;
		_testLimitTime2[i] = 0.3f;

		_testTime[i] = 0.0f;
		_testTime2[i] = 0.0f;
	}

	_endCount = 0;


	return S_OK;
}

void skill00_01::release()
{

}


bool skill00_01::Prepare()
{
	_skillStartOn = false;
 	_skillActionOn = true;
	return FALSE;
}

bool skill00_01::Action()
{
	

	if (_oneSettingOn)
	{
		for (int i = 0; i < _vActionPS.size(); i++)
		{
			_vActionPS[i]->SetActive(FALSE);
			_vActionPS[i]->SetLimitTime(3.0f);
			_vActionPS[i]->Transform()->SetWorldPosition(_playerTrans->GetWorldPosition());
			_vActionPS[i]->Transform()->LookDirection(_playerTrans->GetForward());
			_vFinishPS[i]->SetActive(FALSE);
			//_vFinishPS[i]->SetTime(0.0f);
		}
		_oneSettingOn = false;
	}
	//_vActionPS[i]->Transform()

	if ((_isActiveTime <= _currentTime) && (_activeNum < _vActionPS.size()))
	{
		_vActionPS[_activeNum]->SetActive(TRUE);
		//거리 구하기용
		_firstPlayerPos[_activeNum] = _playerTrans->GetWorldPosition();
		_activeNum++;
		_currentTime = _timeDelta;
	}
	else if(_activeNum < _vActionPS.size())
	{
		_currentTime += _timeDelta;
	}
	//_vActionPS[i]->Transform()->MovePositionSelf(0.0f, 0.0f, (1.0f + i*2.0f)*_timeDelta);


	for (int i = 0; i < _vActionPS.size(); i++)
	{
		if (_vActionPS[i]->GetActive())
		{
			_vActionPS[i]->Transform()->MovePositionSelf(0.0f, 0.0f, 20.0f*_timeDelta);
			//_vActionPS[i]->Transform()->MovePositionSelf(0.0f, 0.0f, (1.0f+i*2.0f)*_timeDelta);
			_vActionPS[i]->update();

			
			//_testTime[i] += _timeDelta;
			D3DXVECTOR3 VecLength = _vActionPS[i]->Transform()->GetWorldPosition() - _firstPlayerPos[i];
			if (D3DXVec3Length(&VecLength) >= 30.0f)
			//if(_vActionPS[i]->GetLimitTime() <= _vActionPS[i]->GetTime())
			//if(_testLimitTime[i] <=_testTime[i])
			{
				_vActionPS[i]->SetActive(FALSE);

				_vFinishPS[i]->SetActive(TRUE);

				_endCount++;

				_skillFinshOn = true;
			}
			
			_vActionPS[i]->SetTime(_vActionPS[i]->GetTime() + _timeDelta);
		}
	}

	//_actionPS->Transform()->LookPosition(_targetTrans->GetWorldPosition());

	//_actionPS->Transform()->MovePositionSelf(0.0f, 0.0f, 20.0f*_timeDelta);

	//_actionPS->update();
	/*if (PHYSICSMANAGER->isOverlap(_actionPS->Transform(), _actionSphereCollision, _targetTrans, _targetSphereCollision))
	{
		return FALSE;
	}*/

	//if()

	return TRUE;

}
void skill00_01::Finsh()
{
	//int endCount = 0;
	for (int i = 0; i < _vFinishPS.size(); i++)
	{
		if (_vFinishPS[i]->GetActive())
		{

			_testTime2[i] += _timeDelta;
			_vFinishPS[i]->SetLimitTime(0.3f);
			_vFinishPS[i]->Transform()->SetWorldPosition(_vActionPS[i]->Transform()->GetWorldPosition());
			_vFinishPS[i]->update();
			if (_vFinishPS[i]->GetLimitTime() <= _vFinishPS[i]->GetTime())
			//if (_testLimitTime2[i] <= _testTime2[i])
			{
				_vFinishPS[i]->GetLimitTime();
				_vFinishPS[i]->GetTime();
				//_vFinishPS[i]->reset();
				_vFinishPS[i]->SetActive(FALSE);
				
			}

			_vFinishPS[i]->SetTime(_vFinishPS[i]->GetTime() + _timeDelta);
			
			//_vFinishPS[i]->Transform()->SetWorldPosition(_vActionPS[i]->Transform()->GetWorldPosition());
			//_vFinishPS[i]->update();
		}
	}
	

	if (_endCount >= _vFinishPS.size() && _vFinishPS.back()->GetActive() == FALSE)
	{
		_skillActionOn = false;
		_skillFinshOn = false;
		_skillResetOn = true;
		
	}
}

void skill00_01::Reset()
{
	_activeNum = 0;
	_endCount = 0;
	_oneSettingOn = true;
	_currentTime = _isActiveTime;

	for (int i = 0; i < _vActionPS.size(); i++)
	{
		_vActionPS[i]->reset();
		_vActionPS[i]->SetTime(0.0f);
	}
	for (int i = 0; i < _vFinishPS.size(); i++)
	{
		_vFinishPS[i]->reset();
		_vFinishPS[i]->SetTime(0.0f);
		//_testTime2[i] = 0;
	}
}
//
//void skill00::RenderAction()
//{
//}
//
