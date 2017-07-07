#pragma once
#include "Action.h"
class bossActionOXPattern : public Action
{
private:
	dx::transform rotateTemp;
	LPDIRECT3DTEXTURE9 emergency;
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ib;
private:
	float chargeTime;
public:
	bossActionOXPattern();
	~bossActionOXPattern();

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
};

