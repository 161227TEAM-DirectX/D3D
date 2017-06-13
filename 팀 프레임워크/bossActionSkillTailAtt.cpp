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
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.99f)
	{
		//owner->getSkinnedAnim().Stop();
		//return LHS::ACTIONRESULT::ACTION_ATT;

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

	//공격에 따른 범위가 필요, 큰 데미지 적용, 넉백가능?

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
