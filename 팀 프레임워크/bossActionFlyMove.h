#pragma once
#include "Action.h"
class bossActionFlyMove : public Action
{
private:
	D3DXMATRIX matRotateX;
	D3DXMATRIX matRotateZ;
	D3DXMATRIX matTranslation;
	D3DXVECTOR3 pos;
	D3DXMATRIX matWorld;
	float angle;
public:
	bossActionFlyMove();
	~bossActionFlyMove();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

