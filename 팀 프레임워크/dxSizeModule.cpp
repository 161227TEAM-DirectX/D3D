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

	if (_radPtc.centerPointHV_On)
	{
		//0----1
		//|   /|
		//|  / |
		//| /  |
		//|/   |
		//2----3

		//�׽�Ʈ
		//_radPtc.centerPointHV.x = 0.5f;
		//_radPtc.centerPointHV.y = 1.0f;


		//H����(����)
		iter->lengthHV0.x = _radPtc.centerPointHV.x;
		iter->lengthHV1.x = (1.0f -_radPtc.centerPointHV.x);
		iter->lengthHV2.x = _radPtc.centerPointHV.x;
		iter->lengthHV3.x = (1.0f - _radPtc.centerPointHV.x);

		//V����(����)
		iter->lengthHV0.y = _radPtc.centerPointHV.y;
		iter->lengthHV1.y = _radPtc.centerPointHV.y;
		iter->lengthHV2.y = (1.0f - _radPtc.centerPointHV.y);
		iter->lengthHV3.y = (1.0f - _radPtc.centerPointHV.y);
	}


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
