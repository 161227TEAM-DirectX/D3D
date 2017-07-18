#include "stdafx.h"
#include "bossActionFlyDie.h"


bossActionFlyDie::bossActionFlyDie()
	:Action()
{
}


bossActionFlyDie::~bossActionFlyDie()
{
}

int bossActionFlyDie::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//보스몬스터의 공격모션 아무거나 시작.
	owner->getSkinnedAnim().Play("Animation_31");
	SOUNDMANAGER->play("보스죽음2");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionFlyDie::Update()
{
	string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	if (!strcmp("Animation_31", temp.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
		{
			owner->getSkinnedAnim().Play("Animation_27");
		}
	}

	if (!strcmp("Animation_27", temp.c_str()))
	{
		float tempY = rand->getHeight(owner->_transform->GetWorldPosition().x, owner->_transform->GetWorldPosition().z);
		owner->_transform->MovePositionSelf(0.0f, -0.5f, 0.0f);
		if (owner->_transform->GetWorldPosition().y <= tempY)
		{
			owner->getSkinnedAnim().PlayOneShotAfterHold("Animation_30");
			SOUNDMANAGER->stop("보스죽음2");
		}
	}

	return LHS::ACTIONRESULT::ACTION_SAFE;
}
