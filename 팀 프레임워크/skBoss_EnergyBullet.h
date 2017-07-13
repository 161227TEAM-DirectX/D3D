#pragma once
#include "dxSkill.h"
class skBoss_EnergyBullet :	public dxSkill
{
private:
	bool _oneSettingOn;

	float _groundPos;

public:
	virtual HRESULT init();
	virtual void release();
public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();

public:
	skBoss_EnergyBullet() {};
	~skBoss_EnergyBullet() {};
};

