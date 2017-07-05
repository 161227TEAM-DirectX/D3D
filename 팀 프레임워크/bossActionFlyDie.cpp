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

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionFlyDie::Update()
{
	string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	if (!strcmp("Animation_31", temp.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.95f)
		{
			owner->getSkinnedAnim().Play("Animation_27");
		}
	}

	if (!strcmp("Animation_27", temp.c_str()))
	{
		float tempY = rand->getHeight(owner->_transform->GetWorldPosition().x, owner->_transform->GetWorldPosition().z);
		owner->_transform->MovePositionSelf(0.0f, -0.5f, 0.0f);
		if (owner->_transform->GetWorldPosition().y < tempY + 5.0f)
		{
			owner->getSkinnedAnim().Play("Animation_30");
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
