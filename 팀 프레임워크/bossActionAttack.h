#pragma once
#include "Action.h"
#include "bossMonster.h"
class bossActionAttack : public Action
{
private:
	float passedTime;
	float activeTime;
public:
	bossActionAttack();
	~bossActionAttack();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

