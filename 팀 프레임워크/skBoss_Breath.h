#pragma once
#include "dxSkill.h"
class skBoss_Breath :	public dxSkill
{
public:
	virtual HRESULT init();
	virtual void release();
public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();


public:
	skBoss_Breath() {};
	~skBoss_Breath() {};
};

