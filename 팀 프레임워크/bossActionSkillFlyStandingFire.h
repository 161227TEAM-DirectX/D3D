#pragma once
#include "Action.h"
class bossActionSkillFlyStandingFire : public Action
{
private:
	int actionCounter;
public:
	bossActionSkillFlyStandingFire();
	~bossActionSkillFlyStandingFire();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

