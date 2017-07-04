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

	D3DXVECTOR3 _startPos;


	

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

