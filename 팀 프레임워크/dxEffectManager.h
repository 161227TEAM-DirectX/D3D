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
	//이펙트 등록
	void addEffect(string psName)
	{
		//있는지 확인
		if (checkName(psName)) return;
		//_mapPS.insert(pair<string, dxParticleSystem*>(psName,inPS));
		dxEffect* effect = new dxEffect;
		effect->setPS(psName);
		effect->init();
		_mapEff.insert(pair<string, dxEffect*>(psName, effect));

	}

	//이펙트 찾기
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

