#pragma once
#include "Action.h"
#include "bossMonster.h"
class bossActionMove : public Action
{
private:
	D3DXVECTOR3 to;
	D3DXVECTOR3 from;
	D3DXVECTOR3 range;

	bool ch;
	int resultValue;
	vector<int> list;
public:
	bossActionMove();
	~bossActionMove();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;
};

