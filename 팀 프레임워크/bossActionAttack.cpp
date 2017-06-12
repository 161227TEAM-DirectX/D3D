#include "stdafx.h"
#include "bossActionAttack.h"


bossActionAttack::bossActionAttack() :Action(), passedTime(0.0f), activeTime(2.0f)
{
}


bossActionAttack::~bossActionAttack()
{
}

int bossActionAttack::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().Play("Animation_12");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionAttack::Update()
{
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.99f)
	{
		passedTime = 0.0f;
		int random = myUtil::RandomIntRange(1, 5);

		switch (random)
		{
		case 1:
			owner->getSkinnedAnim().Play("Animation_12");
			break;
		case 2:
			owner->getSkinnedAnim().Play("Animation_10");
			break;
		case 3:
			owner->getSkinnedAnim().Play("Animation_9");
			break;
		case 4:
			owner->getSkinnedAnim().Play("Animation_11");
			break;
		case 5:
			owner->getSkinnedAnim().Play("Animation_21");
			break;
		default:
			owner->getSkinnedAnim().Play("Animation_10");
			break;
		}
	}

	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	//���� ���� hit�ڽ� �ȿ� ���ٸ� �̵��ض�.
	//if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->_boundBox, enemy->_transform, &enemy->_boundBox))
	//{
	//	owner->getSkinnedAnim().Stop();
	//	return LHS::ACTIONRESULT::ACTION_MOVE;
	//}

	//

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
