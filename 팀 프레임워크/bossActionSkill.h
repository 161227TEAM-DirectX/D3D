#pragma once
#include "Action.h"
class bossActionSkill :
	public Action
{
public:
	bossActionSkill();
	~bossActionSkill();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

