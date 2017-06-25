#include "stdafx.h"
#include "bossActionSkillTailAtt.h"
#include "xPlayer.h"

bossActionSkillTailAtt::bossActionSkillTailAtt()
	:Action(), Frequency(0)
{
}


bossActionSkillTailAtt::~bossActionSkillTailAtt()
{
}

int bossActionSkillTailAtt::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	Frequency = myUtil::RandomIntRange(1, 2);

	switch (Frequency)
	{
	case 1:
		//���������� ���ݸ�� �ƹ��ų� ����.
		owner->getSkinnedAnim().Play("Animation_18");
//		owner->getSkinnedAnim().SetPlaySpeed(0.5f);
		break;
	case 2:
		//���������� ���ݸ�� �ƹ��ų� ����.
		owner->getSkinnedAnim().Play("Animation_68");
	//	owner->getSkinnedAnim().SetPlaySpeed(0.5f);
		break;
	}

	SOUNDMANAGER->play("��������");
	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillTailAtt::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	//�׼��� ����.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		//owner->getSkinnedAnim().Stop();
		//return LHS::ACTIONRESULT::ACTION_ATT;
		D3DXVECTOR3 enemyNormal = playerObject->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
		D3DXVec3Normalize(&enemyNormal, &enemyNormal);
		float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

		if (angle >= -1 && angle <= -0.8f)
		{
			//�ɸ����� ü���� �ѹ��� ��´�.
			//PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() - temp->getAtt() * myUtil::RandomFloatRange(0.9f, 1.8f));
			enemy->playerDamaged(temp->getAtt() * myUtil::RandomFloatRange(0.9f, 1.8f), 0.0f, 0.0f, 50.0f, 2.0f);
			//���� �ִٴ� ���̹Ƿ� �ѹ� �� �����Ѵ�.
			Frequency = myUtil::RandomIntRange(1, 2);

			switch (Frequency)
			{
			case 1:
				//���������� ���ݸ�� �ƹ��ų� ����.
				owner->getSkinnedAnim().Play("Animation_18");
//				owner->getSkinnedAnim().SetPlaySpeed(0.5f);
				SOUNDMANAGER->play("��������");
				break;
			case 2:
				//���������� ���ݸ�� �ƹ��ų� ����.
				owner->getSkinnedAnim().Play("Animation_68");
//				owner->getSkinnedAnim().SetPlaySpeed(0.5f);
				SOUNDMANAGER->play("��������");
				break;
			}
		}
		else
		{
			//������(������ �ڽ�)�ȿ� �ִٸ�
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
			{
				Frequency = myUtil::RandomIntRange(1, 5);
				switch (Frequency)
				{
				case 1:
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				default:
					return LHS::ACTIONRESULT::ACTION_MOVE;
				}
			}
			else
			{
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
