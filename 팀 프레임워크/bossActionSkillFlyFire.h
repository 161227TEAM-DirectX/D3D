#pragma once
#include "Action.h"
class bossActionSkillFlyFire : public Action
{
public:
	bossActionSkillFlyFire();
	~bossActionSkillFlyFire();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

