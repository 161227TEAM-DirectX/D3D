#include "stdafx.h"
#include "Action.h"


Action::Action()
	:owner(nullptr), deleGate(nullptr), object(nullptr), rand(nullptr), Gap(0.001f), _oldTimeDelta(0.0f)
{
}


Action::~Action()
{
}