#include "stdafx.h"
#include "ActionAttack.h"
#include "damageText.h"

ActionAttack::ActionAttack()
	:Action(), yPosition(0.0f)
{
	damage = new damageText;
}


ActionAttack::~ActionAttack()
{
	SAFE_DELETE(damage);
}

int ActionAttack::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;
	monster* temp = dynamic_cast<monster*>(owner);
	owner->getSkinnedAnim().Play("Attack01");
	damage->init(temp->getAtt(), LHS::FONT_RED);
	yPosition = playerObject->_boundBox._localMaxPos.y;
	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionAttack::Update()
{
	monster* temp = dynamic_cast<monster*>(owner);

	//죽음조건
	if (temp->getHP() <= 0)return LHS::ACTIONRESULT::ACTION_DIE;

	//모션 시작 시에
	if (owner->getSkinnedAnim().getAnimationPlayFactor() - Gap < 0.05f)
	{
		//대미지를 넣는 구문이 필요
		yPosition = playerObject->_boundBox._localMaxPos.y;
		enemy->playerDamaged(temp->getAtt(), 1.0f, 15.0f, 0.1f, 0.5f);
		SOUNDMANAGER->play("몬스터공격");
	}

	//모션이 끝나면 대미지를 입힌다.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		//적이 나의 hit박스 안에 있는가?
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			float tempLengthY = playerObject->_transform->GetWorldPosition().y - owner->_transform->GetWorldPosition().y;
			if (tempLengthY >= 1.0f) return LHS::ACTIONRESULT::ACTION_PLAY;
			else return LHS::ACTIONRESULT::ACTION_MOVE;
		}

		SOUNDMANAGER->stop("몬스터공격");
	}
	yPosition += 0.01f;
	damage->setPos(D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, yPosition, playerObject->_transform->GetWorldPosition().z));
	damage->update();

	//stun에 걸렸는지 확인 구문
	/*
	if(스턴 상태 확인)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

void ActionAttack::Render()
{
	if (damage->getStrLength()) damage->render();
}
