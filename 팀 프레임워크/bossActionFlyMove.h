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

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
};

