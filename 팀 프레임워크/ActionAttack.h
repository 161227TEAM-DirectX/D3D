#pragma once
#include "Action.h"
#include "monster.h"
#include "xPlayer.h"

class damageText;

class ActionAttack : public Action
{
private:
	damageText* damage;
	float yPosition;
public:
	ActionAttack();
	virtual ~ActionAttack();

	virtual int Start() override;
	virtual int Update() override;
	virtual void Render() override;
};

