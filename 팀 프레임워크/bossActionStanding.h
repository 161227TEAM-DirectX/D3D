#pragma once
#include "Action.h"
class bossActionStanding : public Action
{
private:
	int Frequency;
public:
	bossActionStanding();
	~bossActionStanding();
	
	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

