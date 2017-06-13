#include "stdafx.h"
#include "bossActionFly.h"


bossActionFly::bossActionFly()
{
}


bossActionFly::~bossActionFly()
{
}

int bossActionFly::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_44");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionFly::Update()
{
	string name = owner->getSkinnedAnim().getAnimationSet()->GetName();
	if (!strcmp("Animation_44", name.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.95f)
		{
			owner->_transform->MovePositionSelf(0.0f, 3.3f, 0.0f);
			owner->getSkinnedAnim().Play("Animation_48");
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}

		//owner->_transform->MovePositionSelf(0.0f, 0.05f, 0.0f);
	}

	//if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.99f)
	//{
	//	owner->getSkinnedAnim().Play("Animation_48");
	//	//if (strcmp("Animation_44", owner->getSkinnedAnim().getAnimationSet()->GetName()))
	//	//{
	//	//	return LHS::ACTIONRESULT::ACTION_PLAY;
	//	//	if
	//	//}
	//	//else
	//	//{
	//	//	owner->getSkinnedAnim().Play("Animation_48");
	//	//}
	//}
	//else
	//{
	//	return LHS::ACTIONRESULT::ACTION_PLAY;
	//}

	//공격에 따른 범위가 필요, 큰 데미지 적용, 넉백가능?

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
