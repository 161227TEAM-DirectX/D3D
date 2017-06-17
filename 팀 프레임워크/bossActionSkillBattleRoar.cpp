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

	//보스몬스터의 공격모션 아무거나 시작.
	owner->getSkinnedAnim().Play("Animation_13");

	//공격방식 변경 -> 0이면 스턴을 위한 방식 / 1이면 range범위에서의 전방위 마법공격 -> 둘다 도트뎀(데미지는 마법공격이 더 강하도록 설정)
	attackStyle = myUtil::RandomIntRange(0, 1);


	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillBattleRoar::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	D3DXVECTOR3 enemyNormal = playerObject->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
	D3DXVec3Normalize(&enemyNormal, &enemyNormal);
	float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

	//배틀로어 애니메이션이 끝나면 ->일반공격 또는 꼬리치기
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		if (angle >= -1.0f && angle < -0.8f)
		{
			return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
		}

		return LHS::ACTIONRESULT::ACTION_ATT;
	}

	dotTime -= 0.08f;
	//공격에 따른 범위가 필요, 공격 범위에 있는 존재는 스턴에 걸림, 스턴에 걸린 상태로 도트대미지 적용필요.
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
	{
		switch (attackStyle)
		{
		case 0:
			//적의 HP를 감소시키자. 마법공격. -> 데미지는 높지만 스턴을 걸지 않는다.
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
				//플레이어의 상태를 스턴으로 변경해야 한다. 데미지는 마법공격보다 낮게 책정.
				//PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() - ((float)temp->getAtt() * myUtil::RandomFloatRange(0.1f, 0.3f)));
				enemy->playerDamaged(((float)temp->getAtt() * myUtil::RandomFloatRange(0.1f, 0.3f)), 0.0f, 0.0f, 100.0f, 2.0f);
			}
			break;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
