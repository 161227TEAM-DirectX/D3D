#pragma once
#include "Action.h"
class bossActionMove : public Action
{
public:
	bossActionMove();
	~bossActionMove();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

