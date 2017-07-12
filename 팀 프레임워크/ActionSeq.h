#pragma once
#include "Action.h"

class ActionSeq : public Action
{
private:
	vector<Action*> vecAction;			//액션클래스의 주소값을 저장하는 벡터 - 실행해야 하는 액션들이 저장되어 있다.
	int CurrIdx;						//현재 벡터의 인덱스를 가지고 있는 변수
	bool isCheck;
public:
	ActionSeq();
	virtual ~ActionSeq();

	//액션을 추가하는 함수(action*) 액션클래스의 주소값을 받는다.
	virtual void AddAction(Action* tAction);

	//Action클래스의 Start함수 재정의
	virtual int Start() override;
	//Action클래스의 Update()함수 재정의
	virtual int Update() override;

	void Render() override;
};

