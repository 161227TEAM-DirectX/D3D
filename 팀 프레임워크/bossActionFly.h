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

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
};

