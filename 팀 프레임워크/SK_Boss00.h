#pragma once
#include "dxSkill.h"
class SK_Boss00 :	public dxSkill
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
	SK_Boss00() {};
	~SK_Boss00() {};
};

