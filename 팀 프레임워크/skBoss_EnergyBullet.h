#pragma once
#include "dxSkill.h"
class skBoss_EnergyBullet :	public dxSkill
{
private:
	bool _oneSettingOn;

	float _groundPos;

	bool _collisionOn;

public:
	virtual bool getCollision()
	{
		if (_skillFinshOn)
		{
			if (_collisionOn)
			{
				_collisionOn = false;
				return true;
			}
			
		}
		else
		{
			_collisionOn = true;
		}

		return FALSE;
	}

	virtual D3DXVECTOR3 getActionShperePos()
	{
		return _pvFinishPS[0][0]->Transform()->GetWorldPosition();
	}

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

