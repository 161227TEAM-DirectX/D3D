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
	//������
	if (_radPtc.radSizeInitOn)
	{
		iter->sizeInit = RandomFloatRange(_radPtc.sizeInit.Min, _radPtc.sizeInit.Max);
		iter->size = iter->sizeInit;
		if (_grpSizeOn) _grpSize[0]->value = iter->sizeInit;//�׷����� ������
	}
	if (_grpSizeOn)
	{
		this->SetGraph(_grpSize);
	}

	if (_radPtc.radSizeEndOn)
	{
		iter->sizeEnd = RandomFloatRange(_radPtc.sizeEnd.Min, _radPtc.sizeEnd.Max);
	}

	//���� ���� ũ�� ����
	iter->vertical = _radPtc.vertical;
	iter->horizontal = _radPtc.horizontal;

}

void dxSizeModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	//������ ����
	if (_radPtc.radSizeEndOn)
	{
		iter->size = Lerp(iter->sizeInit, iter->sizeEnd, (iter->age / iter->lifeTime));
		//iter->size = Lerp(1.0f, 12.0f, (iter->age / iter->lifeTime));
	}
	//������ �׷���
	else if (_grpSizeOn)
	{
		this->GraphUpdate(_grpSize, iter, iter->size);
	}
}
