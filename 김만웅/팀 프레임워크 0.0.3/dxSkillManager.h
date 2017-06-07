#pragma once
#include "singletonBase.h"
#include "dxSkill.h"
class dxSkillManager :	public singletonBase<dxSkillManager>
{
private:
	map<string, dxSkill*> _mapSK;
	map<string, dxSkill*>::iterator _iter;

public:


public:
	dxSkillManager() {};
	~dxSkillManager() {};
};

