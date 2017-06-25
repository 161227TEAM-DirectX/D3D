#include "stdafx.h"
#include "bossActionSkillBattleRoar.h"


bossActionSkillBattleRoar::bossActionSkillBattleRoar()
	:Action(), resultValue(0.0f), dotTime(2.0f), passedTime(0), attackStyle(555), isShout(true)
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
//	owner->getSkinnedAnim().SetPlaySpeed(0.5f);

	//���ݹ�� ���� -> 0�̸� ������ ���� ��� / 1�̸� range���������� ������ �������� -> �Ѵ� ��Ʈ��(�������� ���������� �� ���ϵ��� ����)
	attackStyle = myUtil::RandomIntRange(0, 1);


	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillBattleRoar::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);
	//�������� ���� ���� ������ ���غ���~ ��~~~
	//���� ���� ���� ��ġ���� ���� �ٶ󺸴� ���͸� ���Ѵ�.
	D3DXVECTOR3 enemyNormal = playerObject->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
	//����ȭ�� ���� ���⸸�� ���Ѵ�.
	D3DXVec3Normalize(&enemyNormal, &enemyNormal);
	//�׸��� ���� ���� ���麤�Ϳ� ���� �ٶ󺸴� ������ ������ ���ش�.
	//�׷��� ���� �ű��ϰԵ� 0~1, 0~-1���̰��� ���´�.
	float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

	//��Ʋ�ξ� ��ǿ� ���� ������
	if (isShout && owner->getSkinnedAnim().getAnimationPlayFactor() > 0.3f)
	{
		SOUNDMANAGER->play("������3");
		isShout = false;
	}

	//��Ʋ�ξ� �ִϸ��̼��� ������ ->�Ϲݰ��� �Ǵ� ����ġ��
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		SOUNDMANAGER->stop("������3");

		//range�ڽ� �ȿ� �ִٸ�
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
		{
			//������ ���� ���� ���� ������ ǥ���Ͽ���. 
			if (angle >= -1.0f && angle < -0.8f)
			{
				return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
			}
		}
		//hitBox�ȿ� �÷��̾ �ִٸ�
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_ATT;
		}

		return LHS::ACTIONRESULT::ACTION_MOVE;
	}

	dotTime -= 0.08f;
	//���ݿ� ���� ������ �ʿ�, ���� ������ �ִ� ����� ���Ͽ� �ɸ�, ���Ͽ� �ɸ� ���·� ��Ʈ����� �����ʿ�.
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
	{
		switch (attackStyle)
		{
		case 0:
			//���� HP�� ���ҽ�Ű��. ��������. -> �������� ������ ������ ���� �ʴ´�.
			if (dotTime < 0)
			{
				dotTime = 2.0f;
				//PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() - ((float)temp->getAtt()*myUtil::RandomFloatRange(1.3f, 1.8f)));
				enemy->playerDamaged(((float)temp->getAtt()*myUtil::RandomFloatRange(1.3f, 1.8f)), 0.6f, 100.0f, 0.0f, 0.0f);
			}
			break;
		case 1:
			if (dotTime < 0)
			{
				dotTime = 2.0f;
				//�÷��̾��� ���¸� �������� �����ؾ� �Ѵ�. �������� �������ݺ��� ���� å��.
				//PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() - ((float)temp->getAtt() * myUtil::RandomFloatRange(0.1f, 0.3f)));
				enemy->playerDamaged(((float)temp->getAtt() * myUtil::RandomFloatRange(0.1f, 0.3f)), 0.0f, 0.0f, 100.0f, 2.0f);
			}
			break;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
