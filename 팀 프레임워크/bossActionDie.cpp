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
	owner->getSkinnedAnim().Play("Animation_19");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionDie::Update()
{
	

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
