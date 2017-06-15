#pragma once
#include "Action.h"
#include "monster.h"
class ActionAttack : public Action
{
public:
	ActionAttack();
	virtual ~ActionAttack();

	virtual int Start() override;
	virtual int Update() override;
};

