#include "stdafx.h"
#include "bossActionSkillFire.h"
#include "xPlayer.h"
#include "damageText.h"

bossActionSkillFire::bossActionSkillFire()
	:Action(), dotTime(0.5f), yPosition(0.0f)
{
	damage = new damageText;
}


bossActionSkillFire::~bossActionSkillFire()
{
	SAFE_DELETE(damage);
}

int bossActionSkillFire::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().Play("Animation_65");
	owner->getSkinnedAnim().SetPlaySpeed(0.8f);

	SKM->findSK("�극��")->setSkillPosTrans(&temp->getbreathTrans());
	SKM->findSK("�극��")->setSkillDirTrans(&temp->getbreathTrans());
	SKM->findSK("�극��")->Start();
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillFire::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	if (temp->getHP() <= 0)
	{
		owner->getSkinnedAnim().SetPlaySpeed(1.0f);
		SKM->findSK("�극��")->InitActiveSettingOn();
		return LHS::ACTIONRESULT::ACTION_DIE;
	}

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	if (!strcmp(owner->getSkinnedAnim().getAnimationSet()->GetName(), "Animation_65"))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
		{
			owner->getSkinnedAnim().Play("Animation_14");
			owner->getSkinnedAnim().SetPlaySpeed(0.2f);
			SOUNDMANAGER->setMusicSpeed("�극��2", 0.8f);
			SOUNDMANAGER->play("�극��2");
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
		//�׼� ���� ������ �ʿ�.
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
		{
			SOUNDMANAGER->setMusicSpeed("�극��2", 1.0f);
			SOUNDMANAGER->stop("�극��2");

			//����ġ�� ����
			if (angle >= -1.0f && angle <= -0.8f)
			{
				//range�ڽ� �ȿ� �ִٸ�.
				if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
				{
					owner->getSkinnedAnim().SetPlaySpeed(1.0f);
					SKM->findSK("�극��")->InitActiveSettingOn();
					return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
				}
			}

			//hit�ڽ� �ȿ� �ִٸ�
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
			{
				SKM->findSK("�극��")->InitActiveSettingOn();
				owner->getSkinnedAnim().SetPlaySpeed(1.0f);
				return LHS::ACTIONRESULT::ACTION_ATT;
			}

			SKM->findSK("�극��")->InitActiveSettingOn();
			owner->getSkinnedAnim().SetPlaySpeed(1.0f);
			//�Ϲ����� ��� �ٷ� �̵��������� �Ѿ��.
			return LHS::ACTIONRESULT::ACTION_MOVE;
		}

		//�ɸ����� ��ġ�� ���� �극�� ������� ���� ������ �����ϴ� if��
		if (1 >= angle && angle >= 0.7f)
		{
			//��Ʈ�������� ���� ����
			if (dotTime < 0)
			{
				float tempAtt = (float)temp->getAtt() * myUtil::RandomFloatRange(0.05f, 0.09f);
				dotTime = 2.0f;
				enemy->playerDamaged(tempAtt, 0.6f, 15.0f);
				damage->init(tempAtt, LHS::FONTCOLOR::FONT_RED);
				yPosition = playerObject->_boundBox._localMaxPos.y;
			}
		}
	}

	yPosition += 0.01f;
	damage->setPos(D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, yPosition, playerObject->_transform->GetWorldPosition().z));
	damage->update();

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

void bossActionSkillFire::Render()
{
	if(damage->getStrLength() > 1)damage->render();
}
