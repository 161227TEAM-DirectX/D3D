#pragma once
#include "Action.h"
class bossActionCinema : public Action
{
private:
	float actionTime;
	float passedTime;
	bool isShout;
public:
	bossActionCinema();
	~bossActionCinema();

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
};

