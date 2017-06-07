#include "stdafx.h"
#include "dxSizeModule.h"

HRESULT dxSizeModule::init()
{
	_grpSizeOn = false;
	return S_OK;
}

void dxSizeModule::relese()
{
}

void dxSizeModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//사이즈
	if (_radPtc.radSizeInitOn)
	{
		iter->sizeInit = RandomFloatRange(_radPtc.sizeInit.Min, _radPtc.sizeInit.Max);
		iter->size = iter->sizeInit;
		if (_grpSizeOn) _grpSize[0]->value = iter->sizeInit;//그래프용 사이즈
	}
	if (_grpSizeOn)
	{
		this->SetGraph(_grpSize);
	}

	if (_radPtc.radSizeEndOn)
	{
		iter->sizeEnd = RandomFloatRange(_radPtc.sizeEnd.Min, _radPtc.sizeEnd.Max);
	}

	//가로 세로 크기 조절
	iter->vertical = _radPtc.vertical;
	iter->horizontal = _radPtc.horizontal;

}

void dxSizeModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	//사이즈 조절
	if (_radPtc.radSizeEndOn)
	{
		iter->size = Lerp(iter->sizeInit, iter->sizeEnd, (iter->age / iter->lifeTime));
		//iter->size = Lerp(1.0f, 12.0f, (iter->age / iter->lifeTime));
	}
	//사이즈 그래프
	else if (_grpSizeOn)
	{
		this->GraphUpdate(_grpSize, iter, iter->size);
	}
}
