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

	//보스몬스터의 공격모션 아무거나 시작.
	owner->getSkinnedAnim().Play("Animation_65");
	owner->getSkinnedAnim().SetPlaySpeed(0.8f);
	//test.SetWorldMatrix(owner->getSkinnedAnim().getSkinnedMesh()->GetFineBONE("Deathwing_Bone129__Breath")->CombinedTransformationMatrix);
	//owner->getSkinnedAnim().AddBoneTransform("Deathwing_Bone102", &test);
	//owner->getSkinnedAnim().AddBoneTransform("Deathwing_Bone87", &test2);
	owner->getSkinnedAnim().AddBoneTransform("Deathwing_Bone129__Breath", &test);
	SKM->findSK("브레스")->setSkillPosTrans(&test);
	SKM->findSK("브레스")->setSkillDirTrans(&test);
	SKM->findSK("브레스")->Start();
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillFire::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	if (!strcmp(owner->getSkinnedAnim().getAnimationSet()->GetName(), "Animation_65"))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
		{
			owner->getSkinnedAnim().Play("Animation_14");
			owner->getSkinnedAnim().SetPlaySpeed(0.2f);
			SOUNDMANAGER->play("브레스2");
		}
		return LHS::ACTIONRESULT::ACTION_PLAY;
	}

	dotTime -= 0.5f;
	D3DXVECTOR3 enemyNormal = playerObject->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
	D3DXVec3Normalize(&enemyNormal, &enemyNormal);
	float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &enemyNormal);

	//애니메이션이 본격적으로 시작 될 때.
	if (!strcmp(owner->getSkinnedAnim().getAnimationSet()->GetName(), "Animation_14"))
	{
		//액션 종료 조건이 필요.
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
		{
			SOUNDMANAGER->stop("브레스2");

			//꼬리치기 조건
			if (angle >= -1.0f && angle <= -0.8f)
			{
				//range박스 안에 있다면.
				if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
				{
					owner->getSkinnedAnim().SetPlaySpeed(1.0f);
					return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
				}
			}

			//hit박스 안에 있다면
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
			{
				owner->getSkinnedAnim().SetPlaySpeed(1.0f);
				return LHS::ACTIONRESULT::ACTION_ATT;
			}

			owner->getSkinnedAnim().SetPlaySpeed(1.0f);
			//일반적인 경우 바로 이동패턴으로 넘어가자.
			//return LHS::ACTIONRESULT::ACTION_MOVE;
		}

		//케릭터의 위치에 따라 브레스 대미지가 들어가는 구간을 설정하는 if문
		if (1 >= angle && angle >= 0.7f)
		{
			//도트데미지가 들어가는 구간
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
