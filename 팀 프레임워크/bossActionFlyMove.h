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

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;

	void Render() override;

	void attackFireBall(void);
};

