#include "stdafx.h"
#include "bossActionAttack.h"
#include "xPlayer.h"
#include "damageText.h"


bossActionAttack::bossActionAttack() :Action(), resultValue(0), yPosition(0.0f), ActionRandom(0)
{
	text = new damageText;
}


bossActionAttack::~bossActionAttack()
{
	SAFE_DELETE(text);
}

int bossActionAttack::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().Play("Animation_12");
	temp->getfieldTrans().SetWorldPosition(temp->getfieldTrans().GetWorldPosition().x, 0.5f, temp->getfieldTrans().GetWorldPosition().z);
	SKM->findSK("ȭ������")->setSkillPosTrans(&temp->getfieldTrans());
	SKM->findSK("ȭ������")->setSkillDirTrans(owner->_transform);
	SKM->findSK("ȭ������")->Start();
	//SKM->findSK("ȭ������")->re();

	text->init(temp->getAtt(), LHS::FONT_RED);
	SOUNDMANAGER->play("��������1");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionAttack::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	if (temp->getHP() <= 0) return LHS::ACTIONRESULT::ACTION_DIE;

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	//�ִϸ��̼� ���� �ð� �����ڿ� �������� �Է�.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() < 0.05f)
	{
		yPosition = playerObject->_boundBox._localMaxPos.y;
		enemy->playerDamaged(temp->getAtt(), 0.6f, 10.0f);
	}

	yPosition += 0.01f;
	text->setPos(D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, yPosition, playerObject->_transform->GetWorldPosition().z));
	text->update();

	//�ִϸ��̼��� �����������̸�
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
		else if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
		else if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
		else if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");

		resultValue = myUtil::RandomFloatRange(0.88f, 1.0f);


		//���� ���� hit�ڽ� �ȿ� ���ٸ� �ٸ� �������� ����.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox) || resultValue >= 0.97f)
		{
			//���� ���� range�ڽ� �ȿ� �ִٸ�
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
			{
				//�̵�
				if (resultValue >= 0.1f && resultValue < 0.97f)
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
				else if (resultValue - Gap >= 0.97f && resultValue - Gap <= 0.975f)
				{
					return LHS::ACTIONRESULT::ACTION_FLY;
				}
			}
			//range�ȿ� ���ٸ� �̵��̴�.
			else
			{
				if (resultValue - Gap >= 0.97f && resultValue - Gap <= 0.975f)
				{
					return LHS::ACTIONRESULT::ACTION_FLY;
				}
				
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		}
		randomAttack();
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

void bossActionAttack::Render()
{
	if (text->getStrLength() > 1)text->render();
}

void bossActionAttack::randomAttack(void)
{
//	int random = myUtil::RandomIntRange(1, 5);
	int preNum = ActionRandom;
	ActionRandom = myUtil::RandomIntRange(1, 5);
	while (ActionRandom == preNum)
	{
		ActionRandom = myUtil::RandomIntRange(1, 5);
	}

	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	//���� ���ǵ��� ��� Ʋ�ȴٸ� ATTACK�� ��������.
	switch (ActionRandom)
	{
	case 1:
		owner->getSkinnedAnim().Play("Animation_12");
		temp->getfieldTrans().SetWorldPosition(temp->getfieldTrans().GetWorldPosition().x, 0.5f, temp->getfieldTrans().GetWorldPosition().z);
		
		if (SKM->findSK("ȭ������")->getActive() == FALSE)
		{
			SKM->findSK("ȭ������")->setSkillPosTrans(&temp->getfieldTrans());
			SKM->findSK("ȭ������")->setSkillDirTrans(owner->_transform);
			SKM->findSK("ȭ������")->Start();
		}
		else
		{
			SKM->findSK("ȭ������2")->setSkillPosTrans(&temp->getfieldTrans());
			SKM->findSK("ȭ������2")->setSkillDirTrans(owner->_transform);
			SKM->findSK("ȭ������2")->Start();
		}

		break;
	case 2:
		owner->getSkinnedAnim().Play("Animation_10");

		SKM->findSK("������_������")->setSkillPosTrans(&temp->getrightTrans());
		SKM->findSK("������_������")->setSkillDirTrans(&temp->getrightTrans());

		SKM->findSK("������_������")->Start();
		break;
	case 3:
		owner->getSkinnedAnim().Play("Animation_9");
		break;
	case 4:
		owner->getSkinnedAnim().Play("Animation_11");

		SKM->findSK("������_�޹�")->setSkillPosTrans(&temp->getleftTrans());
		SKM->findSK("������_�޹�")->setSkillDirTrans(&temp->getleftTrans());

		SKM->findSK("������_�޹�")->Start();

		break;
	case 5:
		owner->getSkinnedAnim().Play("Animation_21");

		EFFECT->findEffect("�չ����")->setLimitTime(3.5f);
		EFFECT->findEffect("�չ����")->Start(&temp->getrightTrans());
		break;
	}

	int random = myUtil::RandomIntRange(1, 4);
	switch (random)
	{
	case 1:
		SOUNDMANAGER->play("��������1");
		break;
	case 2:
		SOUNDMANAGER->play("��������2");
		break;
	case 3:
		SOUNDMANAGER->play("��������3");
		break;
	case 4:
		SOUNDMANAGER->play("��������4");
		break;
	}
}