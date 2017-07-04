#include "stdafx.h"
#include "dxEffectManager.h"




void dxEffectManager::EffectSetting()
{
	//���
	this->addEffect("�ǰ�");
	this->addEffect("����");
	this->addEffect("����");
	this->addEffect("����_����");
}

void dxEffectManager::EffectRelease()
{
	//����
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

//������Ʈ
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

//����
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