#include "stdafx.h"
#include "skill00_03.h"

HRESULT skill00_03::init()
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

	this->setArrayActionPS("구슬2", 100);
	this->setArrayFinishPS("터짐2", 100);

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

	for (int i = 0; i < _vActionPS.size(); i++)
	{
		_vActionPS[i]->SetActive(FALSE);
		_vFinishPS[i]->SetActive(FALSE);
		_vFinishPS[i]->SetTime(0.0f);
		_vFinishPS[i]->SetLimitTime(0.3f);
	}
	
	_skillFinshOn = false;
	_oneSettingOn = true;

	return S_OK;
}

void skill00_03::release()
{

}


bool skill00_03::Prepare()
{
	_skillStartOn = false;
	_skillActionOn = true;
	return FALSE;
}

bool skill00_03::Action()
{
	



	//if (_oneSettingOn)
	//{
	//	for (int i = 0; i < _vActionPS.size(); i++)
	//	{
	//		float angle = D3DXToRadian(RandomFloatRange(0, 360));
	//		circlePositionY = D3DXVECTOR3(cosf(angle), 0.0f, sinf(angle));
	//		D3DXVec3Normalize(&circlePositionY, &circlePositionY);
	//		circlePositionY = circlePositionY*RandomFloatRange(0.0f, 15.0f);
	//		circlePositionY.y = RandomFloatRange(20.0f, 30.0f);

	//		_vActionPS[i]->SetActive(FALSE);
	//		_vActionPS[i]->SetLimitTime(10.0f);
	//		_vActionPS[i]->Transform()->SetWorldPosition(circlePositionY);
	//		//_vActionPS[i]->Transform()->LookDirection(_playerTrans->GetForward());
	//		//_vFinishPS[i]->SetActive(FALSE);
	//		//_vFinishPS[i]->SetTime(0.0f);
	//	}
	//	_oneSettingOn = false;
	//}

	int activeNum = 0;
	for (int i = 0; i < _vActionPS.size(); i++)
	{
		if (_vActionPS[i]->GetActive())
		{
			activeNum++;
		}
	}
	for (int i = 0; i < _vActionPS.size(); i++)
	{
		if (_vActionPS[i]->GetActive() == FALSE && _vFinishPS[i]->GetActive() == FALSE && (activeNum+i) < _vActionPS.size())
		{
			float angle = D3DXToRadian(RandomFloatRange(0, 360));
			circlePositionY = D3DXVECTOR3(cosf(angle), 0.0f, sinf(angle));
			D3DXVec3Normalize(&circlePositionY, &circlePositionY);
			circlePositionY = circlePositionY*RandomFloatRange(0.0f, 5.0f);
			circlePositionY.y = RandomFloatRange(15.0f, 35.0f);

			_vActionPS[i]->Transform()->SetWorldPosition(circlePositionY);
			_vActionPS[i]->Transform()->LookDirection(D3DXVECTOR3(0.0f,-1.0f,-1.0f));
			_vActionPS[i]->SetActive(TRUE);
		}
	}
	
	for (int i = 0; i < _vActionPS.size(); i++)
	{
		if (_vActionPS[i]->GetActive())
		{
			_vActionPS[i]->Transform()->MovePositionSelf(0.0f, -30.0*_timeDelta, 0.0f);
			_vActionPS[i]->update();

			if (_vActionPS[i]->Transform()->GetWorldPosition().y <= 0.0f)
			{
				_skillFinshOn = true;
				_vActionPS[i]->SetActive(FALSE);
				_vFinishPS[i]->SetActive(TRUE);
			}
		}
	}	
	

	return TRUE;

}
void skill00_03::Finsh()
{
	//int endCount = 0;
	for (int i = 0; i < _vFinishPS.size(); i++)
	{
		if (_vFinishPS[i]->GetActive())
		{
			
			_vFinishPS[i]->Transform()->SetWorldPosition(_vActionPS[i]->Transform()->GetWorldPosition());
			_vFinishPS[i]->update();
			float time = _vFinishPS[i]->GetLimitTime();
			if (_vFinishPS[i]->GetLimitTime() <= _vFinishPS[i]->GetTime())
			{
				_vFinishPS[i]->GetLimitTime();
				_vFinishPS[i]->reset();
				_vFinishPS[i]->SetTime(0.0f);
				_vFinishPS[i]->SetActive(FALSE);
				

			}

			_vFinishPS[i]->SetTime(_vFinishPS[i]->GetTime() + _timeDelta);

			//_vFinishPS[i]->Transform()->SetWorldPosition(_vActionPS[i]->Transform()->GetWorldPosition());
			//_vFinishPS[i]->update();
		}
	}


	/*if (_endCount >= _vFinishPS.size() && _vFinishPS.back()->GetActive() == FALSE)
	{
		_skillActionOn = false;
		_skillFinshOn = false;
		_skillResetOn = true;
	}*/
}

void skill00_03::Reset()
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
