#pragma once
#include "Action.h"
class bossActionLanding : public Action
{
private:
	D3DXMATRIX matPosition;
	dx::transform lerpTransform;
private:
	bool isTrans;
public:
	bossActionLanding();
	~bossActionLanding();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

