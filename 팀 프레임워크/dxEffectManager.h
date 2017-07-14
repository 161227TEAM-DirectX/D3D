#pragma once
#include "singletonBase.h"
#include "dxEffect.h"

class dxEffectManager :	public singletonBase<dxEffectManager>
{
private:
	map<string, dxEffect*> _mapEff;
	map<string, dxEffect*>::iterator _iter;

public:
	void update();
	void render();

public:
	//����Ʈ ���
	void addEffect(string psName)
	{
		//�ִ��� Ȯ��
		if (checkName(psName)) return;
		//_mapPS.insert(pair<string, dxParticleSystem*>(psName,inPS));
		dxEffect* effect = new dxEffect;
		effect->setPS(psName);
		effect->init();
		_mapEff.insert(pair<string, dxEffect*>(psName, effect));

	}

	//����Ʈ ã��
	dxEffect* findEffect(string psName)
	{
		_iter = _mapEff.find(psName);
		if (_iter != _mapEff.end())
		{
			return _iter->second;
		}

		return NULL;
	}

	bool checkName(string psName)
	{
		_iter = _mapEff.find(psName);
		if (_iter != _mapEff.end())
		{
			return TRUE;
		}
		return FALSE;
	}

	


public:
	void EffectSetting();
	void EffectRelease();


public:
	dxEffectManager() {};
	~dxEffectManager() {};
};

