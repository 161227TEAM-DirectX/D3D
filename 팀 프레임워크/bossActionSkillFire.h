#pragma once
#include "Action.h"
class bossActionSkillFire : public Action
{
public:
	bossActionSkillFire();
	~bossActionSkillFire();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

