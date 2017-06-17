#include "stdafx.h"
#include "bossActionSkillFire.h"


bossActionSkillFire::bossActionSkillFire()
	:Action(), dotTime(0.5f)
{
}


bossActionSkillFire::~bossActionSkillFire()
{
}

int bossActionSkillFire::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().Play("Animation_65", 1.0f);
	owner->getSkinnedAnim().SetPlaySpeed(0.3f);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillFire::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	if (!strcmp(owner->getSkinnedAnim().getAnimationSet()->GetName(), "Animation_65"))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
		{
			owner->getSkinnedAnim().Play("Animation_14");
			owner->getSkinnedAnim().SetPlaySpeed(1.0f);
		}

		return LHS::ACTIONRESULT::ACTION_PLAY;
	}

	dotTime -= 0.5f;
	D3DXVECTOR3 enemyNormal = playerObject->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
	D3DXVec3Normalize(&enemyNormal, &enemyNormal);
	float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

	//�ִϸ��̼��� ���������� ���� �� ��.
	if (!strcmp(owner->getSkinnedAnim().getAnimationSet()->GetName(), "Animation_14"))
	{
		//�ɸ����� ��ġ�� ���� �극�� ������� ���� ������ �����ϴ� if��
		if (1 >= angle && angle >= 0.7f)
		{
			//��Ʈ�������� ���� ����
			if (dotTime < 0)
			{
				dotTime = 2.0f;
				//PLAYERMANAGER->SetHp( PLAYERMANAGER->GetHp() - ((float)temp->getAtt() * myUtil::RandomFloatRange(0.05f, 0.09f)));
				enemy->playerDamaged(((float)temp->getAtt() * myUtil::RandomFloatRange(0.05f, 0.09f)), 0.6f, 30.0f);
				//cout << "mForword.x : " << temp->_transform->GetForward().x << "mForword.y : " << temp->_transform->GetForward().y << "mForword.z : " << temp->_transform->GetForward().z << endl;
				//cout << "enemy.x:" << enemyNormal.x << "enemy.y:" << enemyNormal.y << "enemy.z:" << enemyNormal.z << endl;
				//cout << "dotTime: " << dotTime << endl;
			}
		}
		//cout << "angle : " << angle << endl;
		//�׼� ���� ������ �ʿ�.
		if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
		{
			//����ġ�� ����
			if (angle >= -1.0f && angle <= -0.8f)
			{
				return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
			}

			//�Ϲ����� ��� �ٷ� �Ϲݰ����������� �Ѿ��.
			return LHS::ACTIONRESULT::ACTION_ATT;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
