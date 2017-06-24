#pragma once
#include "singletonBase.h"
//#include "dxSkill.h"

//#include "SK00.h"
//#include <typeinfo.h>

//��ũ��->�� ��ȯ��
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
	//�÷��̾� ��ų
	//skPlayer_MagicShoot* _playerMagicShoot;
private:
	//���� ��ų
	//skBoss_Breath* _bossBreath;

public:
	void skillSetting();
	void skillRelease();

public:
	void update();
	void render();

public:
	//��ų ���
	void addSK(string skName, dxSkill* inSK);
	//��ų �ʱ�ȭ
	//void skillInit();

	//��ų ã��
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


	//��ų üũ
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

