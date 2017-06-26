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

	bool collisionCheckOn[6];

public:
	virtual bool getCollision()
	{
		if (_skillFinshOn)
		{
			for (int i = 0; i < _pvFinishPS[0].size(); i++)
			{
				if (_pvFinishPS[0][i]->GetActive() && collisionCheckOn[i] == FALSE)
				{
					collisionCheckOn[i] = true;
					return true;
				}
			}
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


	skPlayer_MagicShoot() {};
	~skPlayer_MagicShoot() {};
};

