#pragma once
#include "Action.h"
class bossActionFlyMove : public Action
{
public:
	bossActionFlyMove();
	~bossActionFlyMove();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

