#include "stdafx.h"
#include "bossActionAttack.h"
#include "xPlayer.h"


bossActionAttack::bossActionAttack() :Action(), resultValue(0)
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
	owner->getSkinnedAnim().SetPlaySpeed(0.5f);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionAttack::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	//애니메이션 일정 시간 지난뒤에 데미지를 입력.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() <= 0.45f && owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.40f)
	{
		enemy->playerDamaged(temp->getAtt(), 0.6f, 25.0f);
	}

	//애니메이션이 끝나갈때쯤이면
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.9f)
	{
		//적이 나의 hit박스 안에 없다면 다른 패턴으로 간다.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
			{
				resultValue = myUtil::RandomFloatRange(0.1f, 1.0f);

				//이동
				if (resultValue >= 0.1f && resultValue <= 0.98f)
				{
					return LHS::ACTIONRESULT::ACTION_MOVE;
				}
				//배틀로어
				else if (resultValue >= 0.98f && resultValue <= 0.99f)
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				}
				//브레스
				else if (resultValue >= 0.99f && resultValue <= 1.0f)
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
				}
			}
			//range안에 없다면 이동이다.
			else
			{
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		}

		//위의 조건들이 모두 틀렸다면 ATTACK을 시작하자.
		int random = myUtil::RandomIntRange(1, 5);

		switch (random)
		{
		case 1:
			owner->getSkinnedAnim().Play("Animation_12");
			owner->getSkinnedAnim().SetPlaySpeed(0.5f);
			break;
		case 2:
			owner->getSkinnedAnim().Play("Animation_10");
			owner->getSkinnedAnim().SetPlaySpeed(0.5f);
			break;
		case 3:
			owner->getSkinnedAnim().Play("Animation_9");
			owner->getSkinnedAnim().SetPlaySpeed(0.5f);
			break;
		case 4:
			owner->getSkinnedAnim().Play("Animation_11");
			owner->getSkinnedAnim().SetPlaySpeed(0.5f);
			break;
		case 5:
			owner->getSkinnedAnim().Play("Animation_21");
			owner->getSkinnedAnim().SetPlaySpeed(0.5f);
			break;
		default:
			owner->getSkinnedAnim().Play("Animation_10");
			owner->getSkinnedAnim().SetPlaySpeed(0.5f);
			break;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}