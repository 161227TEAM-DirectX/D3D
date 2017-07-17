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

	bool collisionCheckOn[40];


	D3DXVECTOR3 _startPos;


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


	skPlayer_ShootingStar() {};
	~skPlayer_ShootingStar() {};
};

