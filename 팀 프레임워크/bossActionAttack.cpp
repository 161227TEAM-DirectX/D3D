#include "stdafx.h"
#include "bossActionAttack.h"
#include "xPlayer.h"
#include "damageText.h"


bossActionAttack::bossActionAttack() :Action(), resultValue(0), yPosition(0.0f)
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

	owner->getSkinnedAnim().AddBoneTransform("Deathwing_Bone130", &effect);
	effect.MovePositionSelf(0.0f, 1.0f, 0.0f);
	SKM->findSK("ȭ������")->setSkillPosTrans(&effect);
	SKM->findSK("ȭ������")->setSkillDirTrans(owner->_transform);
	SKM->findSK("ȭ������")->Start();

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
		removeTransform();
		
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
				//if (resultValue >= 0.1f && resultValue < 0.97f)
				//{
//				//	if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
//				//	if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
//				//	if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
//				//	if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");
				//	return LHS::ACTIONRESULT::ACTION_MOVE;
				//}
				//��Ʋ�ξ�
				//if (resultValue >= 0.98f && resultValue <= 0.99f)
				{
//					if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
//					if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
//					if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
//					if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				}
				////�극��
				//else if (resultValue >= 0.99f && resultValue <= 1.0f)
				//{
//				//	if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
//				//	if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
//				//	if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
//				//	if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");
				//	return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
				//}
				//else if (resultValue - Gap >= 0.97f && resultValue - Gap <= 0.975f)
				//{
				//	return LHS::ACTIONRESULT::ACTION_FLY;
				//}
			}
			//range�ȿ� ���ٸ� �̵��̴�.
			else
			{
				//if (resultValue - Gap >= 0.97f && resultValue - Gap <= 0.975f)
				//{
				//	return LHS::ACTIONRESULT::ACTION_FLY;
				//}
		
//				if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
//				if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
//				if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
//				if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");
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
	effect.RenderGimozo();
	char temp[128];
	sprintf_s(temp, "%.2f     %.2f     %.2f", effect.GetWorldPosition().x, effect.GetWorldPosition().y, effect.GetWorldPosition().z);

	FONTMANAGER->fontOut(temp, 200, 200, WHITE);
	FONTMANAGER->fontOut(owner->getSkinnedAnim().getNowPlayAnimSet()->GetName(), 200, 250, WHITE);
	
	if (SKM->findSK("ȭ������")->getActive()) FONTMANAGER->fontOut("ȭ������ true", 200, 300, WHITE);
	else FONTMANAGER->fontOut("ȭ������ false", 200, 300, WHITE);

	if (EFFECT->findEffect("�չ����")->getActive()) FONTMANAGER->fontOut("�չ���� true", 200, 350, WHITE);
	else FONTMANAGER->fontOut("�չ���� false", 200, 350, WHITE);

	if (SKM->findSK("������")->getActive()) FONTMANAGER->fontOut("������ true", 200, 400, WHITE);
	else FONTMANAGER->fontOut("������ false", 200, 400, WHITE);
}

void bossActionAttack::removeTransform(void)
{
	string tempAniName = owner->getSkinnedAnim().getNowPlayAnimSet()->GetName();

	if (!tempAniName.compare("Animation_12"))
	{
		owner->getSkinnedAnim().RemoveBoneTransform("Deathwing_Bone130");
		SKM->findSK("ȭ������")->setResetOn();
		return;
	}
	else if (!tempAniName.compare("Animation_9"))
	{
		return;
	}
	else if (!tempAniName.compare("Animation_11"))
	{
		owner->getSkinnedAnim().RemoveBoneTransform("Deathwing_Bone89");
		SKM->findSK("������")->setResetOn();
		return;
	}
	else if (!tempAniName.compare("Animation_21"))
	{
		owner->getSkinnedAnim().RemoveBoneTransform("Deathwing_Bone92");
		EFFECT->findEffect("�չ����")->resetOn();
		return;
	}
	else if (!tempAniName.compare("Animation_10"))
	{
		owner->getSkinnedAnim().RemoveBoneTransform("Deathwing_Bone92");
		SKM->findSK("������")->setResetOn();
		return;
	}
}

void bossActionAttack::randomAttack(void)
{
	int random = myUtil::RandomIntRange(1, 5);

	

	//���� ���ǵ��� ��� Ʋ�ȴٸ� ATTACK�� ��������.
	switch (random)
	{
	case 1:
		owner->getSkinnedAnim().Play("Animation_12");
		owner->getSkinnedAnim().AddBoneTransform("Deathwing_Bone130", &effect);
		effect.MovePositionSelf(0.0f, 1.0f, 0.0f);
		
		SKM->findSK("ȭ������")->setSkillPosTrans(&effect);
		SKM->findSK("ȭ������")->setSkillDirTrans(owner->_transform);
		SKM->findSK("ȭ������")->Start();
		break;
	case 2:
		owner->getSkinnedAnim().Play("Animation_10");
		//owner->getSkinnedAnim().SetPlaySpeed(0.2f);
		owner->getSkinnedAnim().AddBoneTransform("Deathwing_Bone92", &effect);
		//effect.MovePositionSelf(0.0f, 1.0f, 0.0f);

		SKM->findSK("������")->setSkillPosTrans(&effect);
		SKM->findSK("������")->setSkillDirTrans(&effect);

		SKM->findSK("������")->Start();
		break;
	case 3:
		owner->getSkinnedAnim().Play("Animation_9");
		break;
	case 4:
		owner->getSkinnedAnim().Play("Animation_11");
		owner->getSkinnedAnim().AddBoneTransform("Deathwing_Bone89", &effect);

		SKM->findSK("������")->setSkillPosTrans(&effect);
		SKM->findSK("������")->setSkillDirTrans(&effect);

		SKM->findSK("������")->Start();
		break;
	case 5:
		owner->getSkinnedAnim().Play("Animation_21");
		owner->getSkinnedAnim().AddBoneTransform("Deathwing_Bone92", &effect);

		EFFECT->findEffect("�չ����")->setLimitTime(5.0f);
		EFFECT->findEffect("�չ����")->Start(&effect);
		break;
	}

	random = myUtil::RandomIntRange(1, 4);
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
