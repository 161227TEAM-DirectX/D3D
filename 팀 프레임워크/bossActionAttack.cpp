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
//	owner->getSkinnedAnim().SetPlaySpeed(0.5f);
	text->init(temp->getAtt(), LHS::FONT_RED);
	SOUNDMANAGER->play("��������1");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionAttack::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	if (owner->getSkinnedAnim().getAnimationPlayFactor() < 0.05f)
	{
		yPosition = playerObject->_boundBox._localMaxPos.y;
		enemy->playerDamaged(temp->getAtt(), 0.6f, 25.0f);
	}
	

	//�ִϸ��̼� ���� �ð� �����ڿ� �������� �Է�.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() <= 0.45f && owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.40f)
	{
		
	}

	yPosition += 0.01f;
	text->setPos(D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, yPosition, playerObject->_transform->GetWorldPosition().z));
	text->update();

	//�ִϸ��̼��� �����������̸�
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.9f)
	{
		//���� ���� hit�ڽ� �ȿ� ���ٸ� �ٸ� �������� ����.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			//���� ���� range�ڽ� �ȿ� �ִٸ�
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
			{
				resultValue = myUtil::RandomFloatRange(0.1f, 1.0f);

				//�̵�
				if (resultValue >= 0.1f && resultValue <= 0.98f)
				{
					if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
					if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
					if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
					if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");
					return LHS::ACTIONRESULT::ACTION_MOVE;
				}
				//��Ʋ�ξ�
				else if (resultValue >= 0.98f && resultValue <= 0.99f)
				{
					if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
					if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
					if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
					if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				}
				//�극��
				else if (resultValue >= 0.99f && resultValue <= 1.0f)
				{
					if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
					if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
					if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
					if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");
					return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
				}
			}
			//range�ȿ� ���ٸ� �̵��̴�.
			else
			{
				if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
				if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
				if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
				if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		}

		//���� ���ǵ��� ��� Ʋ�ȴٸ� ATTACK�� ��������.
		int random = myUtil::RandomIntRange(1, 5);

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

		if (SOUNDMANAGER->isPlaySound("��������1")) SOUNDMANAGER->stop("��������1");
		if (SOUNDMANAGER->isPlaySound("��������2")) SOUNDMANAGER->stop("��������2");
		if (SOUNDMANAGER->isPlaySound("��������3")) SOUNDMANAGER->stop("��������3");
		if (SOUNDMANAGER->isPlaySound("��������4")) SOUNDMANAGER->stop("��������4");

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

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

void bossActionAttack::Render()
{
	if (text->getStrLength() > 1)text->render();
}
