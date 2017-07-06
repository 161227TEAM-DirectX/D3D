#pragma once
#include "Action.h"
class bossActionFlyMove : public Action
{
private:
	enum FLYSTATE
	{
		straight = 0,
		round,
		landing
	};
private:
	D3DXMATRIX matRotateY;
	D3DXMATRIX matTranslation;
	D3DXVECTOR3 pos;
	D3DXMATRIX matWorld;
	dx::transform lerpTransform;
private:
	float angle;
	FLYSTATE isRound;
public:
	bossActionFlyMove();
	~bossActionFlyMove();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

