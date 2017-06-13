#include "stdafx.h"
#include "bossActionSkillFlyStandingFire.h"


bossActionSkillFlyStandingFire::bossActionSkillFlyStandingFire()
	:Action(), actionCounter(3)
{
}


bossActionSkillFlyStandingFire::~bossActionSkillFlyStandingFire()
{
}

int bossActionSkillFlyStandingFire::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_45");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillFlyStandingFire::Update()
{
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		actionCounter--;
		if (actionCounter <= 0)
		{
			owner->getSkinnedAnim().Play("Animation_13");
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}
		owner->getSkinnedAnim().Play("Animation_45", 1.0f);
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
