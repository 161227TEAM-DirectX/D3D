#pragma once
#include "dxSkill.h"
class skPlayer_Whirlwind : public dxSkill
{
private:
	bool _tagetSettingOn;

	/*bool _timeOn;

	float _limitTime;
	float _currentTime;*/




	int _actionAtiveNum;



public:
	virtual HRESULT init();
	virtual void release();

public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();


	skPlayer_Whirlwind() {};
	~skPlayer_Whirlwind() {};
};

