#pragma once
#include "Action.h"
#include "bossMonster.h"
class bossActionAttack : public Action
{
public:
	bossActionAttack();
	~bossActionAttack();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

