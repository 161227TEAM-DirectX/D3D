#pragma once
#include "Action.h"
#include "bossMonster.h"

class damageText;

class bossActionAttack : public Action
{
private:
	float resultValue;
	vector<int> list;
	damageText* text;
	float yPosition;

	int ActionRandom;

private:
	dx::transform effect;
public:
	bossActionAttack();
	~bossActionAttack();

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
	//액션중에 랜더가 필요하면 실행하는 함수.
	void Render() override;

	void randomAttack(void);
};

