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
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionDie::Update()
{
	return LHS::ACTIONRESULT::ACTION_FINISH;
}
