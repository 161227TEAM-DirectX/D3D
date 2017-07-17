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

	//��������
	if (temp->getHP() <= 0)return LHS::ACTIONRESULT::ACTION_DIE;

	//��� ���� �ÿ�
	if (owner->getSkinnedAnim().getAnimationPlayFactor() - Gap < 0.05f)
	{
		//������� �ִ� ������ �ʿ�
		yPosition = playerObject->_boundBox._localMaxPos.y;
		enemy->playerDamaged(temp->getAtt(), 1.0f, 15.0f, 0.1f, 0.5f);
		SOUNDMANAGER->play("���Ͱ���");
	}

	//����� ������ ������� ������.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		//���� ���� hit�ڽ� �ȿ� �ִ°�?
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			float tempLengthY = playerObject->_transform->GetWorldPosition().y - owner->_transform->GetWorldPosition().y;
			if (tempLengthY >= 1.0f) return LHS::ACTIONRESULT::ACTION_PLAY;
			else return LHS::ACTIONRESULT::ACTION_MOVE;
		}

		SOUNDMANAGER->stop("���Ͱ���");
	}
	yPosition += 0.01f;
	damage->setPos(D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, yPosition, playerObject->_transform->GetWorldPosition().z));
	damage->update();

	//stun�� �ɷȴ��� Ȯ�� ����
	/*
	if(���� ���� Ȯ��)
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
