#include "stdafx.h"
#include "dxColorModule.h"


HRESULT dxColorModule::init()
{
	//색 초기화
	_grpColorR_On = false;
	_grpColorG_On = false;
	_grpColorB_On = false;

	//알파 초기화
	_grpAlphaOn = false;


	return S_OK;
}

void dxColorModule::relese()
{
}

void dxColorModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//색
	if (_radPtc.radColorOn)
	{
		iter->colorInit.r = RandomFloatRange(_radPtc.colorInitR.Min, _radPtc.colorInitR.Max);
		iter->colorInit.g = RandomFloatRange(_radPtc.colorInitG.Min, _radPtc.colorInitG.Max);
		iter->colorInit.b = RandomFloatRange(_radPtc.colorInitB.Min, _radPtc.colorInitB.Max);
		iter->colorInit.a = 1.0f;
		//색 세팅
		iter->color = iter->colorInit;
	}

	//색 소멸
	if (_radPtc.radColorFadeOn)
	{
		iter->colorFade.r = RandomFloatRange(_radPtc.colorFadeR.Min, _radPtc.colorFadeR.Max);
		iter->colorFade.g = RandomFloatRange(_radPtc.colorFadeG.Min, _radPtc.colorFadeG.Max);
		iter->colorFade.b = RandomFloatRange(_radPtc.colorFadeB.Min, _radPtc.colorFadeB.Max);
	}

	//알파 초기화
	if (_radPtc.radAlphaInitOn)
	{
		iter->colorInit.a = RandomFloatRange(_radPtc.alphaInit.Min, _radPtc.alphaInit.Max);
		iter->color.a = iter->colorInit.a;
		if (_grpAlphaOn) _grpAlpha[0]->value = iter->colorInit.a;//그래프용 알파
	}
	//알파 소멸
	if (_radPtc.radAlphaFadeOn)
	{
		iter->colorFade.a = RandomFloatRange(_radPtc.alphaFade.Min, _radPtc.alphaFade.Max);
		//iter->color.a = iter->colorFade.a;
	}
	//알파 그래프
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
	//색깔
	if (_radPtc.radColorFadeOn)
	{
		iter->color = ColorLerp(iter->colorInit, iter->colorFade, (iter->age / iter->lifeTime));
	}
	//색깔 그래프
	else
	{
		if (_grpColorR_On) { this->GraphUpdate(_grpColorR, iter, iter->color.r); }
		if (_grpColorG_On) { this->GraphUpdate(_grpColorG, iter, iter->color.g); }
		if (_grpColorB_On) { this->GraphUpdate(_grpColorB, iter, iter->color.b); }
	}
	//알파값
	if (_radPtc.radAlphaFadeOn)
	{
		iter->color.a = Lerp(iter->colorInit.a, iter->colorFade.a, (iter->age / iter->lifeTime));
	}
	//알파 그래프
	else if (_grpAlphaOn)
	{
		this->GraphUpdate(_grpAlpha, iter, iter->color.a);
	}
}

