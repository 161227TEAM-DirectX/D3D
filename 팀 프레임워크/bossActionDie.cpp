#include "stdafx.h"
#include "bossActionDie.h"


bossActionDie::bossActionDie()
{
}


bossActionDie::~bossActionDie()
{
}

int bossActionDie::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//보스몬스터의 공격모션 아무거나 시작.
	owner->getSkinnedAnim().Play("Animation_19");
//	owner->getSkinnedAnim().SetPlaySpeed(0.5f);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionDie::Update()
{
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > ANIMATIONENDTIME) return LHS::ACTIONRESULT::ACTION_NONE;

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
