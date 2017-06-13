#include "stdafx.h"
#include "bossActionSkillBattleRoar.h"


bossActionSkillBattleRoar::bossActionSkillBattleRoar()
	:Action()
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

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillBattleRoar::Update()
{
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.99f)
	{
		owner->getSkinnedAnim().Stop();
		return LHS::ACTIONRESULT::ACTION_ATT;
	}

	//공격에 따른 범위가 필요, 공격 범위에 있는 존재는 스턴에 걸림, 스턴에 걸린 상태로 도트대미지 적용필요.

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
