#include "stdafx.h"
#include "bossActionSkillTailAtt.h"


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
		break;
	case 2:
		//���������� ���ݸ�� �ƹ��ų� ����.
		owner->getSkinnedAnim().Play("Animation_68");
		break;
	}

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillTailAtt::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, enemy);

	//�׼��� ����.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		//owner->getSkinnedAnim().Stop();
		//return LHS::ACTIONRESULT::ACTION_ATT;
		D3DXVECTOR3 enemyNormal = enemy->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
		D3DXVec3Normalize(&enemyNormal, &enemyNormal);
		float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

		if (angle >= -1 && angle <= -0.8f)
		{
			//�ɸ����� ü���� �ѹ��� ��´�.

			//���� �ִٴ� ���̹Ƿ� �ѹ� �� �����Ѵ�.
			Frequency = myUtil::RandomIntRange(1, 2);

			switch (Frequency)
			{
			case 1:
				//���������� ���ݸ�� �ƹ��ų� ����.
				owner->getSkinnedAnim().Play("Animation_18");
				break;
			case 2:
				//���������� ���ݸ�� �ƹ��ų� ����.
				owner->getSkinnedAnim().Play("Animation_68");
				break;
			}
		}
		else
		{
			//������(������ �ڽ�)�ȿ� �ִٸ�
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
			{
				Frequency = myUtil::RandomIntRange(1, 5);
				switch (Frequency)
				{
				case 1:
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				default:
					return LHS::ACTIONRESULT::ACTION_ATT;
				}
			}
			else
			{
				return LHS::ACTIONRESULT::ACTION_ATT;
			}
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
