#pragma once
#include "Action.h"
#include "bossMonster.h"
class bossActionAttack : public Action
{
private:
	float resultValue;
	vector<int> list;
public:
	bossActionAttack();
	~bossActionAttack();

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
};

