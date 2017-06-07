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
	
	//������Ʈ(��)�� �Ǹ� ���.
	

	//PassedTime += _timeDelta;

	//if (PassedTime >= actionTime)
	//{
	//	
	//	
	//	//�ִϸ��̼� ����
	//	owner->skMesh->Stop();

	//	return LHS::ACTIONRESULT::ACTION_FINISH;
	//}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
