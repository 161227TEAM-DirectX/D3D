#include "stdafx.h"
#include "dxAccelerationModule.h"


HRESULT dxAccelerationModule::init()
{
	return S_OK;
}

void dxAccelerationModule::relese()
{
}

void dxAccelerationModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//°¡¼Óµµ
	if (_radPtc.radAccelOn)
	{
		iter->acceleration.x = RandomFloatRange(_radPtc.accelerationX.Min, _radPtc.accelerationX.Max);
		iter->acceleration.y = RandomFloatRange(_radPtc.accelerationY.Min, _radPtc.accelerationY.Max);
		iter->acceleration.z = RandomFloatRange(_radPtc.accelerationZ.Min, _radPtc.accelerationZ.Max);
	}
}

void dxAccelerationModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
}
