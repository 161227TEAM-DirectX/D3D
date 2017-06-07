#include "stdafx.h"
#include "dxVelocityModule.h"


HRESULT dxVelocityModule::init()
{
	_grpVelocityX_On = false;
	_grpVelocityY_On = false;
	_grpVelocityZ_On = false;

	return S_OK;
}

void dxVelocityModule::relese()
{
}

void dxVelocityModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	if (_radPtc.radVelOn)
	{
		iter->velocity.x = RandomFloatRange(_radPtc.velocityX.Min, _radPtc.velocityX.Max);
		iter->velocity.y = RandomFloatRange(_radPtc.velocityY.Min, _radPtc.velocityY.Max);
		iter->velocity.z = RandomFloatRange(_radPtc.velocityZ.Min, _radPtc.velocityZ.Max);


		if (_grpVelocityX_On) { _grpVelocityX[0]->value = iter->velocity.x; }
		if (_grpVelocityY_On) { _grpVelocityY[0]->value = iter->velocity.y; }
		if (_grpVelocityZ_On) { _grpVelocityZ[0]->value = iter->velocity.z; }

	}
	//속도 그래프 초기화
	if (_grpVelocityX_On) { this->SetGraph(_grpVelocityX); }
	if (_grpVelocityY_On) { this->SetGraph(_grpVelocityY); }
	if (_grpVelocityZ_On) { this->SetGraph(_grpVelocityZ); }
}

void dxVelocityModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{

	//속도 그래프
	if (_grpVelocityX_On) { this->GraphVelocityUpdate(_grpVelocityX, iter, iter->velocity.x); }
	if (_grpVelocityY_On) { this->GraphVelocityUpdate(_grpVelocityY, iter, iter->velocity.y); }
	if (_grpVelocityZ_On) { this->GraphVelocityUpdate(_grpVelocityZ, iter, iter->velocity.z); }

	
}
