#pragma once
#include "dxSkill.h"
class skBoss_PatternOX :	public dxSkill
{
private:
	bool _oneSetting;

	/*D3DXMATRIXA16 _matPos[4];
	D3DXMATRIXA16 _matRot[4];*/

public:
	virtual HRESULT init();
	virtual void release();
public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();

public:
	skBoss_PatternOX() {};
	~skBoss_PatternOX() {};
};

