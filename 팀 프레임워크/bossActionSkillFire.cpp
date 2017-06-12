#include "stdafx.h"
#include "bossActionSkillFire.h"


bossActionSkillFire::bossActionSkillFire()
	:Action()
{
}


bossActionSkillFire::~bossActionSkillFire()
{
}

int bossActionSkillFire::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().PlayOneShot("Animation_65");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionSkillFire::Update()
{
	if (strcmp(owner->getSkinnedAnim().getAnimationSet()->GetName(), "Animation_65"))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() < 0.99f) return LHS::ACTIONRESULT::ACTION_PLAY;
		else
		{
			owner->getSkinnedAnim().Play("Animation_14");
		}
	}

	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.99f)
	{

	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
