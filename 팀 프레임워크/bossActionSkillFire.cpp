#include "stdafx.h"
#include "bossActionSkillFire.h"


bossActionSkillFire::bossActionSkillFire()
	:Action()
{
}


bossActionSkillFire::~bossActionSkillFire()
{
}

int bossActionSkillFire::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//보스몬스터의 공격모션 아무거나 시작.
	owner->getSkinnedAnim().Play("Animation_65");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillFire::Update()
{
	
	if (!strcmp(owner->getSkinnedAnim().getAnimationSet()->GetName(), "Animation_65"))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() < 0.9f) return LHS::ACTIONRESULT::ACTION_PLAY;
		else
		{
			owner->getSkinnedAnim().Play("Animation_14");
		}
	}
	//액션 종료 조건이 필요.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.99f)
	{
	
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
