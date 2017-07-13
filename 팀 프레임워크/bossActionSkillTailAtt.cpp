#include "stdafx.h"
#include "bossActionSkillTailAtt.h"
#include "xPlayer.h"
#include "damageText.h"

bossActionSkillTailAtt::bossActionSkillTailAtt()
	:Action(), Frequency(0), yPosition(0.0f)
{
	damage = new damageText;
}


bossActionSkillTailAtt::~bossActionSkillTailAtt()
{
	SAFE_DELETE(damage);
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

	SOUNDMANAGER->play("��������");
	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillTailAtt::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	if (temp->getHP() <= 0) return LHS::ACTIONRESULT::ACTION_DIE;

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	//�׼��� ����.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		D3DXVECTOR3 enemyNormal = playerObject->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
		D3DXVec3Normalize(&enemyNormal, &enemyNormal);
		float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

		if (angle >= -1 && angle <= -0.8f)
		{
			float tempAtt = temp->getAtt() * myUtil::RandomFloatRange(0.9f, 1.8f);
			//�ɸ����� ü���� �ѹ��� ��´�.
			enemy->playerDamaged(tempAtt, 0.0f, 0.0f, 50.0f, 2.0f);
			damage->init(tempAtt, LHS::FONTCOLOR::FONT_RED);
			yPosition = playerObject->_boundBox._localMaxPos.y;

			//���� �ִٴ� ���̹Ƿ� �ѹ� �� �����Ѵ�.
			Frequency = myUtil::RandomIntRange(1, 2);

			switch (Frequency)
			{
			case 1:
				//���������� ���ݸ�� �ƹ��ų� ����.
				owner->getSkinnedAnim().Play("Animation_18");
				SOUNDMANAGER->play("��������");
				break;
			case 2:
				//���������� ���ݸ�� �ƹ��ų� ����.
				owner->getSkinnedAnim().Play("Animation_68");
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

	yPosition += 0.01f;
	damage->setPos(D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, yPosition, playerObject->_transform->GetWorldPosition().z));
	damage->update();

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

void bossActionSkillTailAtt::Render()
{

	if(damage->getStrLength() > 1) damage->render();
}
