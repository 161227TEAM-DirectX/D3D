#pragma once
#include "Action.h"
#include "bossMonster.h"

class damageText;

class bossActionSkillTailAtt : public Action
{
private:
	int Frequency;
	float yPosition;
	damageText* damage;
public:
	bossActionSkillTailAtt();
	~bossActionSkillTailAtt();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
	void Render() override;
};

