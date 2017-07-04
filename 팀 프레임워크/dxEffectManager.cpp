#include "stdafx.h"
#include "dxEffectManager.h"




void dxEffectManager::EffectSetting()
{
	//등록
	this->addEffect("피격");
	this->addEffect("스턴");
	this->addEffect("먼지");
	this->addEffect("날기_먼지");
}

void dxEffectManager::EffectRelease()
{
	//삭제
	if (_mapEff.empty() == FALSE)
	{
		_iter = _mapEff.begin();
		while (_iter != _mapEff.end())
		{
			SAFE_DELETE(_iter->second);
			_mapEff.erase(_iter);
		}
	}
	_mapEff.clear();
}

//업데이트
void dxEffectManager::update()
{
	if (_mapEff.empty() == FALSE)
	{
		_iter = _mapEff.begin();
		for (_iter; _iter != _mapEff.end(); ++_iter)
		{
			_iter->second->update();
		}
	}
}

//리셋
void dxEffectManager::render()
{
	if (_mapEff.empty() == FALSE)
	{
		_iter = _mapEff.begin();
		for (_iter; _iter != _mapEff.end(); ++_iter)
		{
			_iter->second->render();
		}
	}
}