#include "stdafx.h"
#include "ActionAttack.h"


ActionAttack::ActionAttack()
	:Action()
{
}


ActionAttack::~ActionAttack()
{
}

int ActionAttack::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Attack01");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionAttack::Update()
{
	//모션이 끝나면 대미지를 입힌다.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		//대미지를 넣는 구문이 필요
	}

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

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
