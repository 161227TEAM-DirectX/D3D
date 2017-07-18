#include "stdafx.h"
#include "bossActionDie.h"


bossActionDie::bossActionDie()
{
}


bossActionDie::~bossActionDie()
{
}

int bossActionDie::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().PlayOneShotAfterHold("Animation_19");
	SOUNDMANAGER->play("��������1");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionDie::Update()
{
	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		SOUNDMANAGER->stop("��������1");
	}
	

	return LHS::ACTIONRESULT::ACTION_SAFE;
}
