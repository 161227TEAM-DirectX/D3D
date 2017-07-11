#pragma once
#include "Action.h"
class bossActionFlyMove : public Action
{
private:
	enum FLYSTATE
	{
		straight = 0,
		round,
		landing,
		oxpattern
	};
	const float MOVESIZE;
private:
	D3DXMATRIX matRotateY;
	D3DXMATRIX matTranslation;
	D3DXVECTOR3 pos;
	D3DXMATRIX matWorld;
	D3DXVECTOR3 playerPos;
	boundBox fireballBox;
private:
	dx::transform lerpTransform;
	dx::transform fireBall;
private:
	float angle;
	FLYSTATE isRound;
	int ch;
	float tempRadian;
	float tempLenge;
	bool isAttack;
	float count;
	float attackCount;
public:
	bossActionFlyMove();
	~bossActionFlyMove();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;

	void Render() override;

	void attackFireBall(void);
};

