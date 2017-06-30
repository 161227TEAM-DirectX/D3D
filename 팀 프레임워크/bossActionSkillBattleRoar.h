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

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
	void Render() override;
};

