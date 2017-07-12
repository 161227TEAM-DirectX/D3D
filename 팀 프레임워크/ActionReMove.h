#pragma once
#include "Action.h"
#include "monster.h"
class ActionReMove : public Action
{
private:
	dx::transform			rotateMonster;	//임시 로테이트값
protected:
	D3DXVECTOR3 from;					//시작 위치
	D3DXVECTOR3 to;						//목표 위치
public:
	ActionReMove();
	~ActionReMove();

	D3DXVECTOR3& getFrom(void) { return from; }
	void setFrom(const D3DXVECTOR3& temp) { from = temp; }

	D3DXVECTOR3& getTo(void) { return to; }
	void setTo(const D3DXVECTOR3& temp) { to = temp; }

	//Action클래스의 Start()함수 재정의
	virtual int Start() override;
	//Action클래스의 Update()함수 재정의
	virtual int Update() override;
};

