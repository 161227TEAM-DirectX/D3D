#pragma once
#include "Action.h"
class bossActionFlyDie : public Action
{
private:
public:
	bossActionFlyDie();
	~bossActionFlyDie();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

