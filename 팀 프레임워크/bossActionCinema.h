#pragma once
#include "Action.h"
class bossActionCinema : public Action
{
public:
	bossActionCinema();
	~bossActionCinema();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

