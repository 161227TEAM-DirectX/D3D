#pragma once
#include "Action.h"
#include "bossMonster.h"
#include "xPlayer.h"

class damageText;

class bossActionSkillBattleRoar : public Action
{
private:
	float resultValue;
	float dotTime;
	float passedTime;
	int attackStyle;
	bool isShout;
	float yPosition;
	damageText* damage;
public:
	bossActionSkillBattleRoar();
	~bossActionSkillBattleRoar();

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
	void Render() override;
};

