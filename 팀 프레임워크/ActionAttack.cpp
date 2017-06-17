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
	monster* temp = dynamic_cast<monster*>(owner);

	//����� ������ ������� ������.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.95f)
	{
		//������� �ִ� ������ �ʿ�
		enemy->playerDamaged(temp->getAtt(), 0.5f, 30.0f, 0.5f, 0.5f);
	}

	//stun�� �ɷȴ��� Ȯ�� ����
	/*
	if(���� ���� Ȯ��)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	
	//���� ���� hit�ڽ� �ȿ� �ִ°�?
	if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->_boundBox, playerObject->_transform, &playerObject->_boundBox))
	{
		owner->getSkinnedAnim().Stop();
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
