#pragma once
#include "Action.h"
class ActionDie : public Action
{
private:
	float PassedTime;
protected:
	float actionTime;
public:
	ActionDie();
	virtual ~ActionDie();

	virtual int Start() override;
	virtual int Update() override;
};

