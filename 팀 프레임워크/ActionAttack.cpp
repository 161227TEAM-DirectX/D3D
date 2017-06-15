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
	//����� ������ ������� ������.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		//������� �ִ� ������ �ʿ�
	}

	//stun�� �ɷȴ��� Ȯ�� ����
	/*
	if(���� ���� Ȯ��)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	monster* temp = dynamic_cast<monster*>(owner);
	//���� ���� hit�ڽ� �ȿ� �ִ°�?
	if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->_boundBox, enemy->_transform, &enemy->_boundBox))
	{
		owner->getSkinnedAnim().Stop();
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
