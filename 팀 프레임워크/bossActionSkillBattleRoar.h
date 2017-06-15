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

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
};

