#pragma once
#include "dxSkill.h"
class skPlayer_Lightning : public dxSkill
{
private:
	tagBezierPoint* _BP;
	float _bpTime[6];

	bool _tagetSettingOn;

	float _limitShootTime;
	float _currentCollisionTime;

	int _actionAtiveNum;

public:
	virtual bool getCollision()
	{
		if (_skillActionOn)
		{
			_currentCollisionTime += _timeDelta;
			if (_pvActionPS[0][0]->GetLimitTime() / 5.0f <= _currentCollisionTime)
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


	virtual HRESULT init();
	virtual void release();

public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();


	skPlayer_Lightning() {};
	~skPlayer_Lightning() {};
};

