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
	SOUNDMANAGER->play("��������");

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionDie::Update()
{
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		SOUNDMANAGER->stop("��������");
		return LHS::ACTIONRESULT::ACTION_NONE;
	}
	return LHS::ACTIONRESULT::ACTION_PLAY;
}
