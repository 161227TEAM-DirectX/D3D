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

	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().PlayOneShotAfterHold("Animation_19");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionDie::Update()
{
	//if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME) return LHS::ACTIONRESULT::ACTION_NONE;

	return LHS::ACTIONRESULT::ACTION_SAFE;
}
