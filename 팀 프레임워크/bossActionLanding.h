#pragma once
#include "Action.h"
class bossActionLanding : public Action
{
public:
	bossActionLanding();
	~bossActionLanding();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

