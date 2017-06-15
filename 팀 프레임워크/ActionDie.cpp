#include "stdafx.h"
#include "ActionDie.h"


ActionDie::ActionDie()
	:Action()
{
}


ActionDie::~ActionDie()
{
}

int ActionDie::Start()
{
	if (!owner)LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Death");

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionDie::Update()
{
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		return LHS::ACTIONRESULT::ACTION_NONE;
	}
	return LHS::ACTIONRESULT::ACTION_PLAY;
}
