#pragma once
#include "Action.h"
class bossActionOXPattern : public Action
{
public:
	bossActionOXPattern();
	~bossActionOXPattern();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

