#include "stdafx.h"
#include "bossActionStanding.h"


bossActionStanding::bossActionStanding()
{
}


bossActionStanding::~bossActionStanding()
{
}

int bossActionStanding::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	Frequency = myUtil::RandomIntRange(1, 4);

	switch (Frequency)
	{
	case 1:
		//���������� ���ݸ�� �ƹ��ų� ����.
		owner->getSkinnedAnim().Play("Animation_6");
		break;
	case 2:
		//���������� ���ݸ�� �ƹ��ų� ����.
		owner->getSkinnedAnim().Play("Animation_7");
		break;
	case 3:
		owner->getSkinnedAnim().Play("Animation_8");
		break;
	case 4:
		owner->getSkinnedAnim().Play("Animation_55");
		break;
	}

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionStanding::Update()
{
	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.99f)
	{
		//owner->getSkinnedAnim().Stop();
		//return LHS::ACTIONRESULT::ACTION_ATT;

		Frequency = myUtil::RandomIntRange(1, 4);

		switch (Frequency)
		{
		case 1:
			//���������� ���ݸ�� �ƹ��ų� ����.
			owner->getSkinnedAnim().Play("Animation_6");
			break;
		case 2:
			//���������� ���ݸ�� �ƹ��ų� ����.
			owner->getSkinnedAnim().Play("Animation_7");
			break;
		case 3:
			owner->getSkinnedAnim().Play("Animation_8");
			break;
		case 4:
			owner->getSkinnedAnim().Play("Animation_55");
			break;
		}
	}

	//���ݹ�����?


	return LHS::ACTIONRESULT::ACTION_PLAY;
}
