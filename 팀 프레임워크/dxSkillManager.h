#pragma once
#include "singletonBase.h"
#include "dxSkill.h"
//#include "SK00.h"
//#include <typeinfo.h>

//��ũ��->�� ��ȯ��
//#define CastName(className)	className##*
//#define	CastNumber(num, className)	dynamic_cast<SK##num##*>(className);
//#define	CastName(castClass,className)	dynamic_cast<castClass##*>(className);


class dxSkillManager //:	public singletonBase<dxSkillManager>
{
private:
	map<string, dxSkill*> _mapSK;
	map<string, dxSkill*>::iterator _iter;

	//class SK00;
	
public:

	//��ƼŬ ���
	void addSK(string skName, dxSkill* inSK)
	{
		//�ִ��� Ȯ��
		if (checkName(skName)) return;
		//_mapPS.insert(pair<string, dxParticleSystem*>(psName,inPS));
		//inSK->setClassName(typeid(inSK).name());
		//inPS = dynamic_cast<>

		_mapSK.insert(pair<string, dxSkill*>(skName, inSK));
	}

	//��ƼŬ ã��
	//template <T>
	dxSkill* findSK(string skName)
	{
		
		_iter = _mapSK.find(skName);
		if (_iter != _mapSK.end())
		{
			//string inClassName = _iter->second->getClassName();

			//inClassName = "SK00";

			//_iter->second->


//			return _iter->second->castSkill(_iter->second);

			//inClassName = typeid(_iter->second).name();

			//typename

			//inClassName = inClassName.substr(0,2);

			//CastName(inClassName);

			//typeid(_iter->second);

			//return dynamic_cast<CastName(inClassName.c_str())>(_iter->second);
			//return dynamic_cast<(typeid(_iter->second))*>(_iter->second);
			//return dynamic_cast<dxSkill*>(_iter->second);
		}

		return NULL;
	}
/*
	template <tempnam T>
	T* findSK(string skName)
	{
		_iter = _mapSK.find(skName);
		if (_iter != _mapSK.end())
		{
			return dynamic_cast<>(iter->second);
		}
	}*/


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

