#pragma once
#include "dxSkill.h"
class skPlayer_ShootingStar : public dxSkill
{
private:
	tagBezierPoint* _BP;
	float _bpTime[6];

	bool _oneSettingOn;

	float _limitDropTime;
	float _currentDropTime;

	int _actionAtiveNum;

	D3DXVECTOR3 circlePositionY;

	float _sphereHeight;

	//D3DXVECTOR3 _skillPos;

	int _endCount;

	int _activeCount;

	float _currentCollisionTime;


	D3DXVECTOR3 _startPos;


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


public:
	virtual HRESULT init();
	virtual void release();

public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();


	skPlayer_ShootingStar() {};
	~skPlayer_ShootingStar() {};
};

