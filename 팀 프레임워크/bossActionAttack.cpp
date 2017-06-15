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

	//보스몬스터의 공격모션 아무거나 시작.
	owner->getSkinnedAnim().Play("Animation_12");

	//확률을 위한 벡터 및 시드 초기화
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

		//플레이어의 hp를 소모시키자.

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
		//적이 나의 hit박스 안에 없다면 이동해라.
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

	//오브젝트(적)의 피를 깍기.


	//PassedTime += _timeDelta;

	//if (PassedTime >= actionTime)
	//{
	//	
	//	
	//	//애니메이션 정지
	//	owner->skMesh->Stop();

	//	return LHS::ACTIONRESULT::ACTION_FINISH;
	//}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
