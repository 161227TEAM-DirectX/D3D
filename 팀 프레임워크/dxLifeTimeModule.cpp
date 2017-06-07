#include "stdafx.h"
#include "dxLifeTimeModule.h"


HRESULT dxLifeTimeModule::init()
{
	return S_OK;
}

void dxLifeTimeModule::relese()
{
}

void dxLifeTimeModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//라이프 타임
	if (_radPtc.radLifeOn)
	{
		iter->lifeTime = RandomFloatRange(_radPtc.lifeTime.Min, _radPtc.lifeTime.Max);
	}
}

void dxLifeTimeModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
}