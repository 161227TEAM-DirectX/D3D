#pragma once
#include "dxSkill.h"
class skBoss_Shouting :	public dxSkill
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
	skBoss_Shouting() {};
	~skBoss_Shouting() {};
};

