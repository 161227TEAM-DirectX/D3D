#pragma once
#include "Action.h"
class ActionReMove : public Action
{
private:
	float m_fPassedTime;				//경과 시간
	dx::transform			rotateMonster;	//임시 로테이트값
protected:
	D3DXVECTOR3 from;					//시작 위치
	D3DXVECTOR3 to;						//목표 위치
	float actionTime;					//액션 시간
public:
	ActionReMove();
	~ActionReMove();

	D3DXVECTOR3& getFrom(void) { return from; }
	void setFrom(const D3DXVECTOR3& temp) { from = temp; }

	D3DXVECTOR3& getTo(void) { return to; }
	void setTo(const D3DXVECTOR3& temp) { to = temp; }

	float& getActionTime(void) { return actionTime; }
	void setActionTime(const float& temp) { actionTime = temp; }

	//Action클래스의 Start()함수 재정의
	virtual int Start() override;
	//Action클래스의 Update()함수 재정의
	virtual int Update() override;
};

