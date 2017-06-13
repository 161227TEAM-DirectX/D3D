#pragma once
#include "Action.h"
#include "monster.h"
class ActionAttack : public Action
{
private:
	float PassedTime;
protected:
	float actionTime;
public:
	ActionAttack();
	virtual ~ActionAttack();

	float& getActionTime(void) { return actionTime; }
	void setActionTime(const float& temp) { actionTime = temp; }

	float& getPassedTime(void) { return PassedTime; }
	void setPassedTime(const float& temp) { PassedTime = temp; }

	void collision(void);

	virtual int Start() override;
	virtual int Update() override;
};

