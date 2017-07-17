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

	bool _collisionOn;

	bool _soundOn[3];

	float _currentSoundTime;

public:
	virtual bool getCollision()
	{
		if (_skillActionOn && _collisionOn)
		{
			if (_pvActionPS[0][0]->Transform()->GetWorldPosition().y <= -5.0f)
			{
				_collisionOn = false;
				return true;
			}


		}
		return FALSE;
	}


	virtual D3DXVECTOR3 getSkySwordPos()
	{
		return _pvActionPS[0][0]->Transform()->GetWorldPosition();
	}

	virtual dx::transform* getSkySwordTrans()
	{
		return _pvActionPS[0][0]->Transform();
	}


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

