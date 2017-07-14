#pragma once
#include "Action.h"
#include "bossMonster.h"

class damageText;

class bossActionAttack : public Action
{
private:
	float resultValue;
	vector<int> list;
	damageText* text;
	float yPosition;

	int ActionRandom;

private:
	dx::transform effect;
public:
	bossActionAttack();
	~bossActionAttack();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
	//�׼��߿� ������ �ʿ��ϸ� �����ϴ� �Լ�.
	void Render() override;

	void randomAttack(void);
};

