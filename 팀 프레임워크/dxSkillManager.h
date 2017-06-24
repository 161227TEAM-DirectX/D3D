#pragma once
#include "singletonBase.h"
//#include "dxSkill.h"

//#include "SK00.h"
//#include <typeinfo.h>

//매크로->형 변환용
//#define CastName(className)	className##*
//#define	CastNumber(num, className)	dynamic_cast<SK##num##*>(className);
//#define	CastName(castClass,className)	dynamic_cast<castClass##*>(className);
class dxSkill;

class dxSkillManager : public singletonBase<dxSkillManager>
{
private:
	map<string, dxSkill*> _mapSK;
	map<string, dxSkill*>::iterator _iter;

	//class SK00;
private:
	//플레이어 스킬
	//skPlayer_MagicShoot* _playerMagicShoot;
private:
	//보스 스킬
	//skBoss_Breath* _bossBreath;

public:
	void skillSetting();
	void skillRelease();

public:
	void update();
	void render();

public:
	//스킬 등록
	void addSK(string skName, dxSkill* inSK);
	//스킬 초기화
	//void skillInit();

	//스킬 찾기
	//template <T>
	dxSkill* findSK(string skName)
	{

		_iter = _mapSK.find(skName);
		if (_iter != _mapSK.end())
		{
			return _iter->second;
		}

		return NULL;
	}


	//스킬 체크
	bool checkName(string skName)
	{
		_iter = _mapSK.find(skName);
		if (_iter != _mapSK.end())
		{
			return TRUE;
		}
		return FALSE;
	}


public:
	dxSkillManager() {};
	~dxSkillManager() {};
};

