#pragma once
#include "dxSkill.h"
class skPlayer_MagicShoot : public dxSkill
{
private:
	tagBezierPoint* _BP;
	float _bpTime[6];

	bool _tagetSettingOn;

	float _limitShootTime;
	float _currentShootTime;

	int _actionAtiveNum;

public:
	virtual HRESULT init();
	virtual void release();

public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();


	skPlayer_MagicShoot() {};
	~skPlayer_MagicShoot() {};
};

