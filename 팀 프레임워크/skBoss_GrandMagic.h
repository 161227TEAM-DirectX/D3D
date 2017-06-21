#pragma once
#include "dxSkill.h"
class skBoss_GrandMagic :	public dxSkill
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
	skBoss_GrandMagic() {};
	~skBoss_GrandMagic() {};
};

