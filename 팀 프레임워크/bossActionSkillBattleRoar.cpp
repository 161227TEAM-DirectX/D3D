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

	//���������� ���ݸ�� �ƹ��ų� ����.
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

	//���ݿ� ���� ������ �ʿ�, ���� ������ �ִ� ����� ���Ͽ� �ɸ�, ���Ͽ� �ɸ� ���·� ��Ʈ����� �����ʿ�.

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
