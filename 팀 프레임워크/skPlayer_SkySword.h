#pragma once
#include "dxSkill.h"
class skPlayer_SkySword : public dxSkill
{
private:
	

	bool _tagetSettingOn;

	float _limitShootTime;
	float _currentShootTime;

	int _actionAtiveNum;

	bool _oneSettingOn;

	float _accel;

public:
	virtual HRESULT init();
	virtual void release();

public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();


	skPlayer_SkySword() {};
	~skPlayer_SkySword() {};
};

