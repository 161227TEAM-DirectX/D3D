#include "stdafx.h"
#include "dxAccelerationModule.h"


HRESULT dxAccelerationModule::init()
{
	_grpAccelX_On = false;
	_grpAccelY_On = false;
	_grpAccelZ_On = false;

	return S_OK;
}

void dxAccelerationModule::relese()
{
}

void dxAccelerationModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//가속도
	if (_radPtc.radAccelOn)
	{
		iter->acceleration.x = RandomFloatRange(_radPtc.accelerationX.Min, _radPtc.accelerationX.Max);
		iter->acceleration.y = RandomFloatRange(_radPtc.accelerationY.Min, _radPtc.accelerationY.Max);
		iter->acceleration.z = RandomFloatRange(_radPtc.accelerationZ.Min, _radPtc.accelerationZ.Max);

		//가속도 그래프 초기화
		if (_grpAccelX_On) { _grpAccelX[0]->value = iter->acceleration.x; }
		if (_grpAccelY_On) { _grpAccelY[0]->value = iter->acceleration.y; }
		if (_grpAccelZ_On) { _grpAccelZ[0]->value = iter->acceleration.z; }
	}

	//가속도 그래프 초기화
	if (_grpAccelX_On) { this->SetGraph(_grpAccelX); }
	if (_grpAccelY_On) { this->SetGraph(_grpAccelY); }
	if (_grpAccelZ_On) { this->SetGraph(_grpAccelZ); }

}

void dxAccelerationModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	//가속도 그래프
	if (_grpAccelX_On) { this->GraphVelocityUpdate(_grpAccelX, iter, iter->acceleration.x); }
	if (_grpAccelY_On) { this->GraphVelocityUpdate(_grpAccelY, iter, iter->acceleration.y); }
	if (_grpAccelZ_On) { this->GraphVelocityUpdate(_grpAccelZ, iter, iter->acceleration.z); }
}
