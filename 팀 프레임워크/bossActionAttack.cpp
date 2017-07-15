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
	//보스몬스터의 공격모션 아무거나 시작.
	owner->getSkinnedAnim().Play("Animation_12");
	temp->getfieldTrans().SetWorldPosition(temp->getfieldTrans().GetWorldPosition().x, 0.5f, temp->getfieldTrans().GetWorldPosition().z);
	SKM->findSK("화염장판")->setSkillPosTrans(&temp->getfieldTrans());
	SKM->findSK("화염장판")->setSkillDirTrans(owner->_transform);
	SKM->findSK("화염장판")->Start();
	//SKM->findSK("화염장판")->re();

	text->init(temp->getAtt(), LHS::FONT_RED);
	SOUNDMANAGER->play("보스공격1");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionAttack::Update()
{
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	if (temp->getHP() <= 0) return LHS::ACTIONRESULT::ACTION_DIE;

	PHYSICSMANAGER->isBlocking(owner, playerObject);

	//애니메이션 일정 시간 지난뒤에 데미지를 입력.
	if (owner->getSkinnedAnim().getAnimationPlayFactor() < 0.05f)
	{
		yPosition = playerObject->_boundBox._localMaxPos.y;
		enemy->playerDamaged(temp->getAtt(), 0.6f, 10.0f);
	}

	yPosition += 0.01f;
	text->setPos(D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, yPosition, playerObject->_transform->GetWorldPosition().z));
	text->update();

	//애니메이션이 끝나갈때쯤이면
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		if (SOUNDMANAGER->isPlaySound("보스공격1")) SOUNDMANAGER->stop("보스공격1");
		else if (SOUNDMANAGER->isPlaySound("보스공격2")) SOUNDMANAGER->stop("보스공격2");
		else if (SOUNDMANAGER->isPlaySound("보스공격3")) SOUNDMANAGER->stop("보스공격3");
		else if (SOUNDMANAGER->isPlaySound("보스공격4")) SOUNDMANAGER->stop("보스공격4");

		resultValue = myUtil::RandomFloatRange(0.88f, 1.0f);


		//적이 나의 hit박스 안에 없다면 다른 패턴으로 간다.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox) || resultValue >= 0.97f)
		{
			//적이 나의 range박스 안에 있다면
			if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
			{
				//이동
				if (resultValue >= 0.1f && resultValue < 0.97f)
				{
					return LHS::ACTIONRESULT::ACTION_MOVE;
				}
				//배틀로어
				else if (resultValue >= 0.98f && resultValue <= 0.99f)
				{
					return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
				}
				//브레스
				else if (resultValue >= 0.99f && resultValue <= 1.0f)
				{
				return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
				}
				else if (resultValue - Gap >= 0.97f && resultValue - Gap <= 0.975f)
				{
					return LHS::ACTIONRESULT::ACTION_FLY;
				}
			}
			//range안에 없다면 이동이다.
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

	//위의 조건들이 모두 틀렸다면 ATTACK을 시작하자.
	switch (ActionRandom)
	{
	case 1:
		owner->getSkinnedAnim().Play("Animation_12");
		temp->getfieldTrans().SetWorldPosition(temp->getfieldTrans().GetWorldPosition().x, 0.5f, temp->getfieldTrans().GetWorldPosition().z);
		
		if (SKM->findSK("화염장판")->getActive() == FALSE)
		{
			SKM->findSK("화염장판")->setSkillPosTrans(&temp->getfieldTrans());
			SKM->findSK("화염장판")->setSkillDirTrans(owner->_transform);
			SKM->findSK("화염장판")->Start();
		}
		else
		{
			SKM->findSK("화염장판2")->setSkillPosTrans(&temp->getfieldTrans());
			SKM->findSK("화염장판2")->setSkillDirTrans(owner->_transform);
			SKM->findSK("화염장판2")->Start();
		}

		break;
	case 2:
		owner->getSkinnedAnim().Play("Animation_10");

		SKM->findSK("할퀴기_오른발")->setSkillPosTrans(&temp->getrightTrans());
		SKM->findSK("할퀴기_오른발")->setSkillDirTrans(&temp->getrightTrans());

		SKM->findSK("할퀴기_오른발")->Start();
		break;
	case 3:
		owner->getSkinnedAnim().Play("Animation_9");
		break;
	case 4:
		owner->getSkinnedAnim().Play("Animation_11");

		SKM->findSK("할퀴기_왼발")->setSkillPosTrans(&temp->getleftTrans());
		SKM->findSK("할퀴기_왼발")->setSkillDirTrans(&temp->getleftTrans());

		SKM->findSK("할퀴기_왼발")->Start();

		break;
	case 5:
		owner->getSkinnedAnim().Play("Animation_21");

		EFFECT->findEffect("앞발찍기")->setLimitTime(3.5f);
		EFFECT->findEffect("앞발찍기")->Start(&temp->getrightTrans());
		break;
	}

	int random = myUtil::RandomIntRange(1, 4);
	switch (random)
	{
	case 1:
		SOUNDMANAGER->play("보스공격1");
		break;
	case 2:
		SOUNDMANAGER->play("보스공격2");
		break;
	case 3:
		SOUNDMANAGER->play("보스공격3");
		break;
	case 4:
		SOUNDMANAGER->play("보스공격4");
		break;
	}
}