#pragma once
#include "Action.h"
class bossActionMove : public Action
{
private:
	D3DXVECTOR3 to;
	D3DXVECTOR3 from;
	D3DXVECTOR3 range;

	float speed;
public:
	bossActionMove();
	~bossActionMove();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

