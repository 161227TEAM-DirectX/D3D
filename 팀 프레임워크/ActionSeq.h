#pragma once
#include "Action.h"

class ActionSeq : public Action
{
private:
	vector<Action*> vecAction;			//�׼�Ŭ������ �ּҰ��� �����ϴ� ���� - �����ؾ� �ϴ� �׼ǵ��� ����Ǿ� �ִ�.
	int CurrIdx;						//���� ������ �ε����� ������ �ִ� ����
	bool isCheck;
public:
	ActionSeq();
	virtual ~ActionSeq();

	//�׼��� �߰��ϴ� �Լ�(action*) �׼�Ŭ������ �ּҰ��� �޴´�.
	virtual void AddAction(Action* tAction);

	//ActionŬ������ Start�Լ� ������
	virtual int Start() override;
	//ActionŬ������ Update()�Լ� ������
	virtual int Update() override;

	void Render() override;
};

