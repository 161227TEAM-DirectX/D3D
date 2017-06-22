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

	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().Play("Animation_12");
	owner->getSkinnedAnim().SetPlaySpeed(0.5f);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionAttack::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	//�ִϸ��̼� ���� �ð� �����ڿ� �������� �Է�.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() <= 0.45f && owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.40f)
	{
		enemy->playerDamaged(temp->getAtt(), 0.6f, 25.0f);
	}

	//�ִϸ��̼��� �����������̸�
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.9f)
	{
		//���� ���� hit�ڽ� �ȿ� ���ٸ� �ٸ� �������� ����.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
			{
				resultValue = myUtil::RandomFloatRange(0.1f, 1.0f);

				//�̵�
				if (resultValue >= 0.1f && resultValue <= 0.98f)
				{
					return LHS::ACTIONRESULT::ACTION_MOVE;
				}
				//��Ʋ�ξ�
				else if (resultValue >= 0.98f && resultValue <= 0.99f)
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				}
				//�극��
				else if (resultValue >= 0.99f && resultValue <= 1.0f)
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
				}
			}
			//range�ȿ� ���ٸ� �̵��̴�.
			else
			{
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		}

		//���� ���ǵ��� ��� Ʋ�ȴٸ� ATTACK�� ��������.
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