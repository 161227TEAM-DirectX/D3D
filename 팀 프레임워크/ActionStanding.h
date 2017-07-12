#pragma once
#include "Action.h"

class ActionStanding : public Action
{
public:
	ActionStanding();
	virtual ~ActionStanding();

	virtual int Start() override;
	virtual int Update() override;
};

