#pragma once
#include "Action.h"
#include "bossMonster.h"
class bossActionSkillFire : public Action
{
private:
	float dotTime;
	boundBox breathRange;
public:
	bossActionSkillFire();
	~bossActionSkillFire();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

