#include "stdafx.h"
#include "ActionAttack.h"


ActionAttack::ActionAttack()
	:PassedTime(0.0f)
{
}


ActionAttack::~ActionAttack()
{
}

void ActionAttack::collision(void)
{
}

int ActionAttack::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Attack2H");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionAttack::Update()
{
	//stun에 걸렸는지 확인 구문
	/*
	if(스턴 상태 확인)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	monster* temp = dynamic_cast<monster*>(owner);
	//적이 나의 hit박스 안에 있는가?
	if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->_boundBox, enemy->_transform, &enemy->_boundBox))
	{
		owner->getSkinnedAnim().Stop();
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}
	
	//오브젝트(적)의 피를 깍기.
	

	//PassedTime += _timeDelta;

	//if (PassedTime >= actionTime)
	//{
	//	
	//	
	//	//애니메이션 정지
	//	owner->skMesh->Stop();

	//	return LHS::ACTIONRESULT::ACTION_FINISH;
	//}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
