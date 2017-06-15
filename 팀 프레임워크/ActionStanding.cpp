#include "stdafx.h"
#include "ActionStanding.h"


ActionStanding::ActionStanding()
	:Action(), PassedTime(0.0f)
{
}


ActionStanding::~ActionStanding()
{
}

int ActionStanding::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;
	owner->getSkinnedAnim().Play("Stand01");
	PassedTime = 0.0f;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionStanding::Update()
{
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//owner는 baseobject클래스이고 monster클래스가 필요하기에 타입 캐스팅.
	monster* temp = dynamic_cast<monster*>(owner);
	
	//몬스터의 범위 박스에 케릭터가 오면 케릭터의 위치로 이동 - enemy설정이 필요함.
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
	{
		if (deleGate) deleGate->OnActionFinish(this, true);
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}

	//내가 공격을 받았나?
	/*if(충돌처리 확인 구문)
	{
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}*/

	//내가 스턴 공격을 받았나?
	/*
	if(스턴공격 확인 구문)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
