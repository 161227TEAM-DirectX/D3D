#pragma once
#include "Action.h"
class bossActionDie : public Action
{
public:
	bossActionDie();
	~bossActionDie();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

