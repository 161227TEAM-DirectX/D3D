#include "stdafx.h"
#include "dxPositionModule.h"

HRESULT dxPositionModule::init()
{
	_grpPosDirectionVelOn = false;
	PositionType = PTC_DEFAULT;
	return S_OK;
}

void dxPositionModule::relese()
{
}

void dxPositionModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{//위치
	if (_radPtc.radPosOn)
	{
		iter->position.x = RandomFloatRange(_radPtc.positionX.Min, _radPtc.positionX.Max);
		iter->position.y = RandomFloatRange(_radPtc.positionY.Min, _radPtc.positionY.Max);
		iter->position.z = RandomFloatRange(_radPtc.positionZ.Min, _radPtc.positionZ.Max);

		if (PositionType == PTC_SPHERE)
		{
			D3DXVec3Normalize(&iter->position, &iter->position);

			//랜덤거리
			float radDistance = RandomFloatRange(_radPtc.posSphereRadius.Min, _radPtc.posSphereRadius.Max);

			//추가위치
			iter->position = iter->position * radDistance;

		}

	}

	//위치 방향성 속도
	if (_radPtc.radPosDirectionVelOn)
	{
		//방향만 뽑기
		//D3DXVECTOR3 posDirtion;
		D3DXVec3Normalize(&iter->posDirection, &iter->position);
		//속도
		iter->posDirectSpeed = RandomFloatRange(_radPtc.posDirectionVel.Min, _radPtc.posDirectionVel.Max);
		//iter->posDirectVel = iter->posDirection* iter->posDirectSpeed;

		if (_grpPosDirectionVelOn) { _grpPosDirectionVel[0]->value = iter->posDirectSpeed; }

	}
	if (_grpPosDirectionVelOn) { this->SetGraph(_grpPosDirectionVel); }

}

void dxPositionModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{

	if (_grpPosDirectionVelOn)
	{
		this->GraphVelocityUpdate(_grpPosDirectionVel, iter, iter->posDirectSpeed);
		iter->posDirectVel = iter->posDirection*iter->posDirectSpeed;
	}
}
