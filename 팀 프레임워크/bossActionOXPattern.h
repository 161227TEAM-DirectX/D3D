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

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

