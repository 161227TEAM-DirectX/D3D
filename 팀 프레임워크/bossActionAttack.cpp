#include "stdafx.h"
#include "bossActionAttack.h"


bossActionAttack::bossActionAttack() :Action(), passedTime(0.0f), activeTime(2.0f), resultValue(0)
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

	//Ȯ���� ���� ���� �� �õ� �ʱ�ȭ
	//int seed = 0;

	//seed = 1;
	//for (int i = 0; i < 5; i++)
	//{
	//	list.push_back(seed);
	//}
	//seed = 2;
	//list.push_back(seed);
	//list.push_back(seed);
	//seed = 3;
	//list.push_back(seed);
	//list.push_back(seed);
	//list.push_back(seed);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionAttack::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, enemy);

	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.9f)
	{
		passedTime = 0.0f;
		int random = myUtil::RandomIntRange(1, 5);

		//�÷��̾��� hp�� �Ҹ��Ű��.

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
	//	bool check = ;
		//���� ���� hit�ڽ� �ȿ� ���ٸ� �̵��ض�.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), enemy->_transform, &enemy->_boundBox))
		{
			//int index = myUtil::RandomIntRange(0, 9);
			resultValue = myUtil::RandomFloatRange(0.1f, 1.0f);

			if (resultValue >= 0.1f && resultValue <= 0.96f)
			{
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
			else if (resultValue >= 0.96f && 0.98f)
			{
				if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				}
			}
			else if (resultValue >= 0.98f && resultValue <= 1.0f)
			{
				if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
				}
			}

		/*	switch (resultValue)
			{
			case 1:
				return LHS::ACTIONRESULT::ACTION_MOVE;
				break;
			case 2:
				if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				}
				break;
			case 3:
				if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
				}
				break;
			}*/
		}
	}

	
	

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
