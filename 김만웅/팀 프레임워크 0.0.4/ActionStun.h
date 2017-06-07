#pragma once
#include "Action.h"
class ActionStun : public Action
{
private:
	float PassedTime;
protected:
	float actionTime;
public:
	ActionStun();
	virtual ~ActionStun();

	virtual int Start() override;
	virtual int Update() override;
};

