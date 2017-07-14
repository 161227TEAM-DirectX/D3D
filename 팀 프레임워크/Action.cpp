#include "stdafx.h"
#include "Action.h"


Action::Action()
	:owner(nullptr), object(nullptr), rand(nullptr), enemy(nullptr), playerObject(nullptr), mainCamera(nullptr), Gap(0.001f), _oldTimeDelta(0.0f), LENGTHGAP(0.5f), PLAYERDISTANCE(6.0f),
	ANIMATIONENDTIME(0.95f)
{
}


Action::~Action()
{
}