#pragma once
#include "Action.h"
#include "bossMonster.h"
class bossActionSkillBattleRoar : public Action
{
private:
	float resultValue;
	float dotTime;
	float passedTime;
	int attackStyle;
public:
	bossActionSkillBattleRoar();
	~bossActionSkillBattleRoar();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

