#pragma once
#include "dxSkill.h"
class skPlayer_FireMagic : public dxSkill
{
private:

	bool _tagetSettingOn;

	float _limitShootTime;
	float _currentShootTime;

	int _actionAtiveNum;

	bool _oneSettingOn;

	boundSphere _collisonSphere[2];

public:
	virtual HRESULT init();
	virtual void release();

public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();


	skPlayer_FireMagic() {};
	~skPlayer_FireMagic() {};
};

