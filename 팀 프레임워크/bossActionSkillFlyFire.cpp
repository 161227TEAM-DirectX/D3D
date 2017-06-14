#include "stdafx.h"
#include "bossActionSkillFlyFire.h"


bossActionSkillFlyFire::bossActionSkillFlyFire()
{
}


bossActionSkillFlyFire::~bossActionSkillFlyFire()
{
}

int bossActionSkillFlyFire::Start()
{
	if (!owner)LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_38", 1.0f);

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillFlyFire::Update()
{
	return LHS::ACTIONRESULT::ACTION_PLAY;
}
