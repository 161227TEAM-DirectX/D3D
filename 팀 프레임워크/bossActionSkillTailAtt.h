#pragma once
#include "Action.h"
class bossActionSkillTailAtt : public Action
{
private:
	int Frequency;
public:
	bossActionSkillTailAtt();
	~bossActionSkillTailAtt();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

