#pragma once
#include "dxSkill.h"

class SK00 : public dxSkill
{
private:
	dx::transform* _targetTrans;
	int _targetMaxNum;

public:
	virtual HRESULT init();
	//HRESULT init(transform * playerTrans, transform * tagetTrans);
	virtual void release();
public:
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();

public:
	//virtual void* ThisFunction() {}
	//virtual void* ThisSKill() { return this; }

	//virtual void SSS() {};

	//void* castSkill();

	void SetAllTarget(dx::transform*& allTarget, int targetMaxNum)
	{
		_targetTrans = allTarget;
		_targetMaxNum = targetMaxNum;

	};
public:
	SK00() { _className = "SK00"; };
	~SK00() {}
};

