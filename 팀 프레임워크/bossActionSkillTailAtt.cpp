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
		//���������� ���ݸ�� �ƹ��ų� ����.
		owner->getSkinnedAnim().Play("Animation_18");
		break;
	case 2:
		//���������� ���ݸ�� �ƹ��ų� ����.
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
			//���������� ���ݸ�� �ƹ��ų� ����.
			owner->getSkinnedAnim().Play("Animation_18");
			break;
		case 2:
			//���������� ���ݸ�� �ƹ��ų� ����.
			owner->getSkinnedAnim().Play("Animation_68");
			break;
		}
	}

	//���ݿ� ���� ������ �ʿ�, ū ������ ����, �˹鰡��?

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
