#pragma once
#include "Action.h"
#include "bossMonster.h"
#include "xPlayer.h"
class bossActionSkillBattleRoar : public Action
{
private:
	float resultValue;
	float dotTime;
	float passedTime;
	int attackStyle;
	bool isShout;
public:
	bossActionSkillBattleRoar();
	~bossActionSkillBattleRoar();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

