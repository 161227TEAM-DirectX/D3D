#pragma once
#include "Action.h"
class bossActionSkillBattleRoar : public Action
{
public:
	bossActionSkillBattleRoar();
	~bossActionSkillBattleRoar();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

