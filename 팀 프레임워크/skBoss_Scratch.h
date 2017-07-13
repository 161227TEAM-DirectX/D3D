#pragma once
#include "dxSkill.h"
class skBoss_Scratch :	public dxSkill
{
private:
	bool _oneSetting;
public:
	virtual HRESULT init();
	virtual void release();
public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();

public:
	skBoss_Scratch() {};
	~skBoss_Scratch() {};
};

