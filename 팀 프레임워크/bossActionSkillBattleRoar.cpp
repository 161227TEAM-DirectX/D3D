#include "stdafx.h"
#include "bossActionSkillBattleRoar.h"


bossActionSkillBattleRoar::bossActionSkillBattleRoar()
	:Action(), resultValue(0.0f), dotTime(2.0f), passedTime(0), attackStyle(555)
{
}


bossActionSkillBattleRoar::~bossActionSkillBattleRoar()
{
}

int bossActionSkillBattleRoar::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().Play("Animation_13");

	//���ݹ�� ���� -> 0�̸� ������ ���� ��� / 1�̸� range���������� ������ �������� -> �Ѵ� ��Ʈ��(�������� ���������� �� ���ϵ��� ����)
	attackStyle = myUtil::RandomIntRange(0, 1);


	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillBattleRoar::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, enemy);

	D3DXVECTOR3 enemyNormal = enemy->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
	D3DXVec3Normalize(&enemyNormal, &enemyNormal);
	float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

	//��Ʋ�ξ� �ִϸ��̼��� ������ ->�Ϲݰ��� �Ǵ� ����ġ��
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		if (angle >= -1.0f && angle < -0.8f)
		{
			return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
		}

		return LHS::ACTIONRESULT::ACTION_ATT;
	}

	dotTime -= 0.08f;
	//���ݿ� ���� ������ �ʿ�, ���� ������ �ִ� ����� ���Ͽ� �ɸ�, ���Ͽ� �ɸ� ���·� ��Ʈ����� �����ʿ�.
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
	{
		switch (attackStyle)
		{
		case 0:
			//���� HP�� ���ҽ�Ű��. ��������. -> �������� ������ ������ ���� �ʴ´�.
			if (dotTime < 0)
			{
				dotTime = 2.0f;

			}
			break;
		case 1:
			if (dotTime < 0)
			{
				dotTime = 2.0f;
				//�÷��̾��� ���¸� �������� �����ؾ� �Ѵ�. �������� �������ݺ��� ���� å��.
			}
			break;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
