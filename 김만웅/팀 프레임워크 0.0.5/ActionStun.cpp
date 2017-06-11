#include "stdafx.h"
#include "ActionStun.h"


ActionStun::ActionStun()
	:actionTime(5.0f)
{
}


ActionStun::~ActionStun()
{
}

int ActionStun::Start()
{
	PassedTime = 0.0f;

	//스턴 애니메이션 설정
	//owner->skMesh->Play()

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionStun::Update()
{



	return LHS::ACTIONRESULT::ACTION_FINISH;
}
