#pragma once
#include "Action.h"
#include "bossMonster.h"

class damageText;

class bossActionSkillFire : public Action
{
private:
	float dotTime;
	boundBox breathRange;
	float yPosition;
	damageText* damage;
public:
	bossActionSkillFire();
	~bossActionSkillFire();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
	void Render() override;
};

