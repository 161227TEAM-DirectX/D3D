#pragma once
#include "Action.h"
class bossActionFly : public Action
{
private:
	D3DXMATRIX matTranslation;
	float random;
public:
	bossActionFly();
	~bossActionFly();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

