#include "stdafx.h"
#include "bossActionAttack.h"


bossActionAttack::bossActionAttack()
{
}


bossActionAttack::~bossActionAttack()
{
}

int bossActionAttack::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//���������� ���ݸ�� �ƹ��ų� ����.
	//owner->getSkinnedAnim().Play("Attack2H");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionAttack::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
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
