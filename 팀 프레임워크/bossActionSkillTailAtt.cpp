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
		//보스몬스터의 공격모션 아무거나 시작.
		owner->getSkinnedAnim().Play("Animation_18");
		break;
	case 2:
		//보스몬스터의 공격모션 아무거나 시작.
		owner->getSkinnedAnim().Play("Animation_68");
		break;
	}

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillTailAtt::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, enemy);

	//액션이 종료.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		//owner->getSkinnedAnim().Stop();
		//return LHS::ACTIONRESULT::ACTION_ATT;
		D3DXVECTOR3 enemyNormal = enemy->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
		D3DXVec3Normalize(&enemyNormal, &enemyNormal);
		float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

		if (angle >= -1 && angle <= -0.8f)
		{
			//케릭터의 체력을 한번에 깍는다.

			//아직 있다는 뜻이므로 한번 더 실행한다.
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
		}
		else
		{
			//레인지(광범위 박스)안에 있다면
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
			{
				Frequency = myUtil::RandomIntRange(1, 5);
				switch (Frequency)
				{
				case 1:
					return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
				case 2:
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
