#pragma once
#include "dxSkill.h"
class skPlayer_FireMagic : public dxSkill
{
private:

	bool _tagetSettingOn;

	float _limitShootTime;
	float _currentCollisionTime;

	int _actionAtiveNum;

	bool _oneSettingOn;

	boundSphere _collisonSphere[2];


public:

	virtual bool getCollision()
	{
		if (_skillActionOn)
		{
			_currentCollisionTime += _timeDelta;
			if (_pvActionPS[1][0]->GetLimitTime()/5.0f <= _currentCollisionTime)
			{
			
				_currentCollisionTime = 0.0f;
				return true;
			}
			


		}
		else
		{
			_currentCollisionTime = 0.0f;
		}

		return FALSE;
	}

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

