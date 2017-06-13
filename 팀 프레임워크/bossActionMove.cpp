#include "stdafx.h"
#include "bossActionMove.h"


bossActionMove::bossActionMove()
	:Action(), speed(0.001f)
{
}


bossActionMove::~bossActionMove()
{
}

int bossActionMove::Start()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	//baseObject�� transform�� ȣ���Ͽ� world��ġ�� from���� ����
	owner->getSkinnedAnim().Play("Animation_56");
//	owner->_transform->SetWorldPosition(from);
	from = owner->_transform->GetWorldPosition();
	
	float tempY = rand->getHeight(10.0f, 10.0f);
	to = D3DXVECTOR3(10.0f, tempY, 10.0f);
	D3DXVECTOR3	range = to - from;
	owner->_transform->LookPosition(range);
//	to = enemy->_transform->GetWorldPosition();
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	//D3DXVECTOR3 p;				//���������� ��ġ���� �����ϴ� ����
	//float sample = rangeTest;
	D3DXVECTOR3 look(0.0f, 0.0f, 0.1f);
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	float tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

//	D3DXVec3Lerp(&p, &from, &to, speed);
//	p.y = rand->getHeight(p.x, p.z);
//	D3DXVECTOR3 prev = owner->_transform->GetWorldPosition();

//	owner->_transform->LookPosition(p);						//���⺤�͸� transform�� ���麤�Ϳ� ����
//	owner->_transform->SetWorldPosition(p);					//��ä�� ��ġ�� ���������� ��ġ�� ����

	
	//if(owner->)

	//�׽�Ʈ
	if (owner->_transform->GetWorldPosition() >= to)
	{
		owner->_transform->SetWorldPosition(to);
		if (deleGate)deleGate->OnActionFinish(this, true);
		return LHS::ACTIONRESULT::ACTION_ATT;
	}

	if (speed >= 1.0f)
	{
		owner->_transform->SetWorldPosition(to);
		return LHS::ACTIONRESULT::ACTION_ATT;
	}


	speed += 0.001f;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}
