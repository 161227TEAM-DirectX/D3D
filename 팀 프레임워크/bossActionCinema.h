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

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

