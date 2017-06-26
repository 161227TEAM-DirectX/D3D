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
//	owner->getSkinnedAnim().SetPlaySpeed(0.5f);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionAttack::Update()
{
	monster* temp = dynamic_cast<monster*>(owner);

	//모션이 끝나면 대미지를 입힌다.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.95f)
	{
		//대미지를 넣는 구문이 필요
		enemy->playerDamaged(temp->getAtt(), 0.5f, 30.0f, 0.5f, 0.5f);
	}

	//stun에 걸렸는지 확인 구문
	/*
	if(스턴 상태 확인)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/


	
	//적이 나의 hit박스 안에 있는가?
	if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
	{
		float tempLengthY = playerObject->_transform->GetWorldPosition().y - owner->_transform->GetWorldPosition().y;
		if (tempLengthY >= 1.0f) return LHS::ACTIONRESULT::ACTION_PLAY;
		else return LHS::ACTIONRESULT::ACTION_MOVE;
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
