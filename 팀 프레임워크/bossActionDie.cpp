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
	owner->getSkinnedAnim().PlayOneShotAfterHold("Animation_19");
	SOUNDMANAGER->play("보스죽음1");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionDie::Update()
{
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		SOUNDMANAGER->stop("보스죽음1");
	}
	

	return LHS::ACTIONRESULT::ACTION_SAFE;
}
