#include "stdafx.h"
#include "bossActionSkillBattleRoar.h"
#include "damageText.h"

bossActionSkillBattleRoar::bossActionSkillBattleRoar()
	:Action(), resultValue(0.0f), dotTime(2.0f), passedTime(0), attackStyle(555), isShout(true), yPosition(0.0f)
{
	damage = new damageText;
}


bossActionSkillBattleRoar::~bossActionSkillBattleRoar()
{
	SAFE_DELETE(damage);
}

int bossActionSkillBattleRoar::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//보스몬스터의 공격모션 아무거나 시작.
	owner->getSkinnedAnim().Play("Animation_13");
//	owner->getSkinnedAnim().SetPlaySpeed(0.5f);
	//공격방식 변경 -> 0이면 스턴을 위한 방식 / 1이면 range범위에서의 전방위 마법공격 -> 둘다 도트뎀(데미지는 마법공격이 더 강하도록 설정)
	attackStyle = myUtil::RandomIntRange(0, 1);


	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillBattleRoar::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);
	//이제부터 나와 적의 각도를 구해보자~ 예~~~
	//먼저 현재 나의 위치에서 적을 바라보는 벡터를 구한다.
	D3DXVECTOR3 enemyNormal = playerObject->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
	//정규화를 통해 방향만을 구한다.
	D3DXVec3Normalize(&enemyNormal, &enemyNormal);
	//그리고 현재 나의 정면벡터와 적을 바라보는 방향을 내적을 해준다.
	//그러면 무려 신기하게도 0~1, 0~-1사이값이 나온다.
	float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

	//배틀로어 모션에 맞춰 샤우팅
	if (isShout && owner->getSkinnedAnim().getAnimationPlayFactor() > 0.3f)
	{
		SOUNDMANAGER->play("샤우팅3");
		isShout = false;
	}

	//배틀로어 애니메이션이 끝나면 ->일반공격 또는 꼬리치기
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		SOUNDMANAGER->stop("샤우팅3");

		//range박스 안에 있다면
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
		{
			//내적을 통해 구한 값을 범위로 표현하였다. 
			if (angle >= -1.0f && angle < -0.8f)
			{
				return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
			}
		}
		//hitBox안에 플레이어가 있다면
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_ATT;
		}

		return LHS::ACTIONRESULT::ACTION_MOVE;
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
				float tempAtt = (float)temp->getAtt()*myUtil::RandomFloatRange(1.3f, 1.8f);
				dotTime = 2.0f;
				//PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() - ((float)temp->getAtt()*myUtil::RandomFloatRange(1.3f, 1.8f)));
				enemy->playerDamaged(tempAtt, 0.6f, 100.0f, 0.0f, 0.0f);
				damage->init(tempAtt, LHS::FONTCOLOR::FONT_RED);
				yPosition = playerObject->_boundBox._localMaxPos.y;
			}
			break;
		case 1:
			if (dotTime < 0)
			{
				float tempAtt = (float)temp->getAtt() * myUtil::RandomFloatRange(0.1f, 0.3f);
				dotTime = 2.0f;
				//플레이어의 상태를 스턴으로 변경해야 한다. 데미지는 마법공격보다 낮게 책정.
				//PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() - ((float)temp->getAtt() * myUtil::RandomFloatRange(0.1f, 0.3f)));
				enemy->playerDamaged(tempAtt, 0.0f, 0.0f, 100.0f, 2.0f);
				damage->init(tempAtt, LHS::FONTCOLOR::FONT_RED);
				yPosition = playerObject->_boundBox._localMaxPos.y;
			}
			break;
		}
	}
	yPosition += 0.01f;
	damage->setPos(D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, yPosition, playerObject->_transform->GetWorldPosition().z));
	damage->update();

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

void bossActionSkillBattleRoar::Render()
{
	if (damage->getStrLength() > 1)damage->render();
}
