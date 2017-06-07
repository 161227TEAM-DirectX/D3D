#include "stdafx.h"
#include "dxColorModule.h"


HRESULT dxColorModule::init()
{
	//�� �ʱ�ȭ
	_grpColorR_On = false;
	_grpColorG_On = false;
	_grpColorB_On = false;

	//���� �ʱ�ȭ
	_grpAlphaOn = false;


	return S_OK;
}

void dxColorModule::relese()
{
}

void dxColorModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//��
	if (_radPtc.radColorOn)
	{
		iter->colorInit.r = RandomFloatRange(_radPtc.colorInitR.Min, _radPtc.colorInitR.Max);
		iter->colorInit.g = RandomFloatRange(_radPtc.colorInitG.Min, _radPtc.colorInitG.Max);
		iter->colorInit.b = RandomFloatRange(_radPtc.colorInitB.Min, _radPtc.colorInitB.Max);
		iter->colorInit.a = 1.0f;
		//�� ����
		iter->color = iter->colorInit;
	}

	//�� �Ҹ�
	if (_radPtc.radColorFadeOn)
	{
		iter->colorFade.r = RandomFloatRange(_radPtc.colorFadeR.Min, _radPtc.colorFadeR.Max);
		iter->colorFade.g = RandomFloatRange(_radPtc.colorFadeG.Min, _radPtc.colorFadeG.Max);
		iter->colorFade.b = RandomFloatRange(_radPtc.colorFadeB.Min, _radPtc.colorFadeB.Max);
	}

	//���� �ʱ�ȭ
	if (_radPtc.radAlphaInitOn)
	{
		iter->colorInit.a = RandomFloatRange(_radPtc.alphaInit.Min, _radPtc.alphaInit.Max);
		iter->color.a = iter->colorInit.a;
		if (_grpAlphaOn) _grpAlpha[0]->value = iter->colorInit.a;//�׷����� ����
	}
	//���� �Ҹ�
	if (_radPtc.radAlphaFadeOn)
	{
		iter->colorFade.a = RandomFloatRange(_radPtc.alphaFade.Min, _radPtc.alphaFade.Max);
		//iter->color.a = iter->colorFade.a;
	}
	//���� �׷���
	else if (_grpAlphaOn)
	{
		this->SetGraph(_grpAlpha);

		/*for (int i = 1; i < _grpAlpha.size(); i++)
		{
		_grpAlpha[i]->value = RandomFloatRange(_grpAlpha[i]->radValue.Min, _grpAlpha[i]->radValue.Max);
		}*/
	}
}

void dxColorModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	//����
	if (_radPtc.radColorFadeOn)
	{
		iter->color = ColorLerp(iter->colorInit, iter->colorFade, (iter->age / iter->lifeTime));
	}
	//���� �׷���
	else
	{
		if (_grpColorR_On) { this->GraphUpdate(_grpColorR, iter, iter->color.r); }
		if (_grpColorG_On) { this->GraphUpdate(_grpColorG, iter, iter->color.g); }
		if (_grpColorB_On) { this->GraphUpdate(_grpColorB, iter, iter->color.b); }
	}
	//���İ�
	if (_radPtc.radAlphaFadeOn)
	{
		iter->color.a = Lerp(iter->colorInit.a, iter->colorFade.a, (iter->age / iter->lifeTime));
	}
	//���� �׷���
	else if (_grpAlphaOn)
	{
		this->GraphUpdate(_grpAlpha, iter, iter->color.a);
	}
}

