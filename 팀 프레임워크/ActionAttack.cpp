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
	owner->getSkinnedAnim().Stop();
	owner->getSkinnedAnim().Play("Attack01");
//	owner->getSkinnedAnim().SetPlaySpeed(0.5f);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionAttack::Update()
{
	monster* temp = dynamic_cast<monster*>(owner);

	//��������
	if (temp->getHP() < 0)return LHS::ACTIONRESULT::ACTION_DIE;

	if(owner->getSkinnedAnim().getAnimationPlayFactor() - Gap < 0.05f) SOUNDMANAGER->play("���Ͱ���");

	//����� ������ ������� ������.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.95f)
	{
		//���� ���� hit�ڽ� �ȿ� �ִ°�?
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			float tempLengthY = playerObject->_transform->GetWorldPosition().y - owner->_transform->GetWorldPosition().y;
			if (tempLengthY >= 1.0f) return LHS::ACTIONRESULT::ACTION_PLAY;
			else return LHS::ACTIONRESULT::ACTION_MOVE;
		}

		//������� �ִ� ������ �ʿ�
		enemy->playerDamaged(temp->getAtt(), 0.5f, 30.0f, 0.5f, 0.5f);
		SOUNDMANAGER->stop("���Ͱ���");
	}

	//stun�� �ɷȴ��� Ȯ�� ����
	/*
	if(���� ���� Ȯ��)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
