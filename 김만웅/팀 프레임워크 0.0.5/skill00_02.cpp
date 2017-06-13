#include "stdafx.h"
#include "skill00_02.h"

HRESULT skill00_02::init()
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

	this->setArrayActionPS("구슬", 8);
	this->setArrayFinishPS("터짐", 8);

	_firstPlayerPos = new D3DXVECTOR3[8];

	_SkillRenderType = SR_Array;

	_resetTime = 0.3f;

	_isActiveTime = 0.2f;
	_currentTime = _isActiveTime;
	_activeNum = 0;

	_endCount = 0;

	_BP = new tagBezierPoint[8];
	_SelfPos = new D3DXVECTOR3[8];

	//_bpTime = new float[8];
	ZeroMemory(_bpTime,sizeof(_bpTime));

	return S_OK;
}

void skill00_02::release()
{

}


bool skill00_02::Prepare()
{
	_skillStartOn = false;
	_skillActionOn = true;
	return FALSE;
}

bool skill00_02::Action()
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

	//if ((_isActiveTime <= _currentTime) && (_activeNum < _vActionPS.size()))
	//{
	//	//int random = RandomTwoNum(-1, 1);
	//	int random;
	//	(_activeNum % 2 == 0) ? random = 1 : random = -1;
	//	
	//	_vActionPS[_activeNum]->SetActive(TRUE);
	//	//거리 구하기용
	//	_firstPlayerPos[_activeNum] = _playerTrans->GetWorldPosition();
	//	//_SelfPos[_activeNum] = _playerTrans->GetLocalPosition
	//	//D3DXVECTOR3 dir = D3DXVECTOR3(_vActionPS[_activeNum]->Transform()->GetRight().x, _vActionPS[_activeNum]->Transform()->GetUp().y, _vActionPS[_activeNum]->Transform()->GetForward().z);
	//	_BP[_activeNum].P0 = _firstPlayerPos[_activeNum];
	//	//_BP[_activeNum].P1 = _BP[_activeNum].P0 + D3DXVECTOR3(dir.x+random*12.0f,dir.y, dir.z -8.0f);
	//	//_BP[_activeNum].P2 = _BP[_activeNum].P0 + D3DXVECTOR3(dir.x+random*6.0f, dir.y, dir.z - 4.0f);
	//	_BP[_activeNum].P1 = _BP[_activeNum].P0 + _vActionPS[_activeNum]->Transform()->GetRight() *random* 12 + _vActionPS[_activeNum]->Transform()->GetForward()*-8.0f;
	//	_BP[_activeNum].P2 = _BP[_activeNum].P0 + _vActionPS[_activeNum]->Transform()->GetRight() *random* 6 + _vActionPS[_activeNum]->Transform()->GetForward()*-4.0f;
	//	//_BP[_activeNum].P1 = D3DXVECTOR3(_SelfPos[_activeNum].x + random*12.0f, _SelfPos[_activeNum].y, _SelfPos[_activeNum].z - 8.0f);
	//	_BP[_activeNum].P3 = _BP[_activeNum].P0 + _vActionPS[_activeNum]->Transform()->GetForward()*20.0f;

	//	/*_BP[_activeNum].P0 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//	_BP[_activeNum].P1 = D3DXVECTOR3(1.0f,0.0f,2.0f);
	//	_BP[_activeNum].P2 = D3DXVECTOR3(1.0f,0.0f,5.0f);
	//	_BP[_activeNum].P3 = D3DXVECTOR3(0.0f,0.0f,10.0f);*/

	//	_activeNum++;
	//	_currentTime = _timeDelta;
	//}
	if ((_isActiveTime <= _currentTime) && (_activeNum < _vActionPS.size()))
	{
		//int random = RandomTwoNum(-1, 1);
		int random = 1;
		int random2 = -1;
		//(_activeNum % 2 == 0) ? random = 1 : random = -1;

		_vActionPS[_activeNum]->SetActive(TRUE);
		_vActionPS[_activeNum+1]->SetActive(TRUE);
		//거리 구하기용
		_firstPlayerPos[_activeNum] = _playerTrans->GetWorldPosition();
		_firstPlayerPos[_activeNum+1] = _playerTrans->GetWorldPosition();

		_BP[_activeNum].P0 = _firstPlayerPos[_activeNum];
		_BP[_activeNum].P1 = _BP[_activeNum].P0 + _vActionPS[_activeNum]->Transform()->GetRight() *random * 12 + _vActionPS[_activeNum]->Transform()->GetForward()*-8.0f;
		_BP[_activeNum].P2 = _BP[_activeNum].P0 + _vActionPS[_activeNum]->Transform()->GetRight() *random * 6 + _vActionPS[_activeNum]->Transform()->GetForward()*-4.0f;
		_BP[_activeNum].P3 = _BP[_activeNum].P0 + _vActionPS[_activeNum]->Transform()->GetForward()*20.0f;

		_BP[_activeNum+1].P0 = _firstPlayerPos[_activeNum];
		_BP[_activeNum+1].P1 = _BP[_activeNum].P0 + _vActionPS[_activeNum]->Transform()->GetRight() *random2 * 12 + _vActionPS[_activeNum]->Transform()->GetForward()*-8.0f;
		_BP[_activeNum+1].P2 = _BP[_activeNum].P0 + _vActionPS[_activeNum]->Transform()->GetRight() *random2 * 6 + _vActionPS[_activeNum]->Transform()->GetForward()*-4.0f;
		_BP[_activeNum+1].P3 = _BP[_activeNum].P0 + _vActionPS[_activeNum]->Transform()->GetForward()*20.0f;


		_activeNum+=2;
		_currentTime = _timeDelta;
	}





	else if (_activeNum < _vActionPS.size())
	{
		_currentTime += _timeDelta;
	}
	//_vActionPS[i]->Transform()->MovePositionSelf(0.0f, 0.0f, (1.0f + i*2.0f)*_timeDelta);


	for (int i = 0; i < _vActionPS.size(); i++)
	{
		if (_vActionPS[i]->GetActive())
		{
			_bpTime[i] += _timeDelta;
			//_vActionPS[i]->Transform()->MovePositionSelf(0.0f, 0.0f, 20.0f*_timeDelta);
			_vActionPS[i]->Transform()->SetWorldPosition(BezierP3Cube(_BP[i], _bpTime[i] / 1.0f));
			//_vActionPS[i]->Transform()->SetWorldPosition(BezierP3Cube(_BP[i], 0.0f));
			//_vActionPS[i]->Transform()->MovePositionSelf(0.0f, 0.0f, (1.0f+i*2.0f)*_timeDelta);
			_vActionPS[i]->update();

			/*if (_bpTime[i] >= 2.0f)
			{
				_vActionPS[i]->SetActive(FALSE);
			}*/

		/*	_testTime[i] += _timeDelta;
			D3DXVECTOR3 VecLength = _vActionPS[i]->Transform()->GetWorldPosition() - _firstPlayerPos[i];
			if (D3DXVec3Length(&VecLength) >= 20.0f)*/
				//if(_vActionPS[i]->GetLimitTime() <= _vActionPS[i]->GetTime())
				//if(_testLimitTime[i] <=_testTime[i])
			if (_bpTime[i] >= 1.0f)
			{

				_vActionPS[i]->SetActive(FALSE);
				_vFinishPS[i]->SetActive(TRUE);

				_endCount++;

				_skillFinshOn = true;
			}

			_vActionPS[i]->SetTime(_vActionPS[i]->GetTime() + _timeDelta);
		}
	}

	

	return TRUE;

}
void skill00_02::Finsh()
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

void skill00_02::Reset()
{
	_activeNum = 0;
	_endCount = 0;
	_oneSettingOn = true;
	_currentTime = _isActiveTime;

	for (int i = 0; i < _vActionPS.size(); i++)
	{
		_vActionPS[i]->reset();
		_vActionPS[i]->SetTime(0.0f);
		_bpTime[i] = 0.0f;
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
