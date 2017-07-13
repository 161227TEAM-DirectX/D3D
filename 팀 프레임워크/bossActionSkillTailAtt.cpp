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
		//보스몬스터의 공격모션 아무거나 시작.
		owner->getSkinnedAnim().Play("Animation_18");
		break;
	case 2:
		//보스몬스터의 공격모션 아무거나 시작.
		owner->getSkinnedAnim().Play("Animation_68");
		break;
	}

	SOUNDMANAGER->play("꼬리공격");
	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillTailAtt::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	if (temp->getHP() <= 0) return LHS::ACTIONRESULT::ACTION_DIE;

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	//액션이 종료.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		D3DXVECTOR3 enemyNormal = playerObject->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
		D3DXVec3Normalize(&enemyNormal, &enemyNormal);
		float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

		if (angle >= -1 && angle <= -0.8f)
		{
			float tempAtt = temp->getAtt() * myUtil::RandomFloatRange(0.9f, 1.8f);
			//케릭터의 체력을 한번에 깍는다.
			enemy->playerDamaged(tempAtt, 0.0f, 0.0f, 50.0f, 2.0f);
			damage->init(tempAtt, LHS::FONTCOLOR::FONT_RED);
			yPosition = playerObject->_boundBox._localMaxPos.y;

			//아직 있다는 뜻이므로 한번 더 실행한다.
			Frequency = myUtil::RandomIntRange(1, 2);

			switch (Frequency)
			{
			case 1:
				//보스몬스터의 공격모션 아무거나 시작.
				owner->getSkinnedAnim().Play("Animation_18");
				SOUNDMANAGER->play("꼬리공격");
				break;
			case 2:
				//보스몬스터의 공격모션 아무거나 시작.
				owner->getSkinnedAnim().Play("Animation_68");
				SOUNDMANAGER->play("꼬리공격");
				break;
			}
		}
		else
		{
			//레인지(광범위 박스)안에 있다면
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
