#pragma once
#include "Action.h"
#include "monster.h"
class ActionMove : public Action
{
private:
	float m_fPassedTime;				//��� �ð�
	dx::transform		rotateMonster;	//�ӽ� ������Ʈ��
	dx::transform		rotatePlayer;
protected:
	D3DXVECTOR3 from;					//���� ��ġ
	D3DXVECTOR3 to;						//��ǥ ��ġ
	float actionTime;					//�׼� �ð�
	float length;
public:
	ActionMove();
	virtual ~ActionMove();

	D3DXVECTOR3& getFrom(void) { return from; }
	void setFrom(const D3DXVECTOR3& temp) { from = temp; }

	D3DXVECTOR3& getTo(void) { return to; }
	void setTo(const D3DXVECTOR3& temp) { to = temp; }

	float& getActionTime(void) { return actionTime; }
	void setActionTime(const float& temp) { actionTime = temp; }

	//ActionŬ������ Start()�Լ� ������
	virtual int Start() override;
	//ActionŬ������ Update()�Լ� ������
	virtual int Update() override;

	void Render() override;
};