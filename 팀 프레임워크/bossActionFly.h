#pragma once
#include "Action.h"
class bossActionFly : public Action
{
private:
	D3DXMATRIX matTranslation;
	dx::transform test;
public:
	bossActionFly();
	~bossActionFly();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

