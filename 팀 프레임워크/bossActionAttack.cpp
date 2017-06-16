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

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionAttack::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.9f)
	{
		passedTime = 0.0f;
		int random = myUtil::RandomIntRange(1, 5);

		//�÷��̾��� hp�� �Ҹ��Ű��.
		PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() - temp->getAtt());

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

		//���� ���� hit�ڽ� �ȿ� ���ٸ� �̵��ض�.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			resultValue = myUtil::RandomFloatRange(0.1f, 1.0f);

			if (resultValue >= 0.1f && resultValue <= 0.98f)
			{
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
			else if (resultValue >= 0.98f && resultValue <= 0.99f)
			{
				if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				}
			}
			else if (resultValue >= 0.99f && resultValue <= 1.0f)
			{
				if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
				}
			}
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}