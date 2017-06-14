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

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
};

