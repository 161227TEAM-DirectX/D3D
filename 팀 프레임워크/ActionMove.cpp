#include "stdafx.h"
#include "ActionMove.h"
#include "terrain.h"


ActionMove::ActionMove()
	:Action(), m_fPassedTime(0.0f)
{
}


ActionMove::~ActionMove()
{
}

int ActionMove::Start()
{
	//�����̰��� �ϴ� ��ü�� ���ٸ� ������ ���� ����
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//baseObject�� transform�� ȣ���Ͽ� world��ġ�� from���� ����
	owner->getSkinnedAnim().Play("Run");
	owner->_transform->SetWorldPosition(from);
	rotateMonster = *owner->_transform;
	m_fPassedTime = 0.0f;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	monster* temp = dynamic_cast<monster*>(owner);

	m_fPassedTime += _timeDelta;
	//����ð��� �׼ǽð����� Ŀ���� �����?
	if (m_fPassedTime >= actionTime)
	{
		//��ü�� ��ġ�� to��ġ�� ����
		owner->_transform->SetWorldPosition(to);

		//�÷��̾ �� Ž�� ������ ����� �Ǹ� ���ĵ� ���·� ���ư���.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			if (deleGate) deleGate->OnActionFinish(this, true);

			return LHS::ACTIONRESULT::ACTION_REMOVE;
		}

		//deleGate������ nullptr�� �ƴ϶�� �Լ� ȣ��
		if (deleGate)deleGate->OnActionFinish(this);

		return LHS::ACTIONRESULT::ACTION_FINISH;
	}
	//���������� ���� ����ð� / ��ü �ð�
	float t = m_fPassedTime / actionTime;
	D3DXVECTOR3 p;				//���������� ��ġ���� �����ϴ� ����
	//�� 3D ���� ���̿��� ���� ������ �����մϴ�.
	//D3DXVECTOR3 * D3DXVec3Lerp(
	//	_Inout_ D3DXVECTOR3 * pOut,				[in, out] ���� ����� D3DXVECTOR3 ����ü�� ������. 
	//	_In_ const D3DXVECTOR3 * pV1,			[in] ó���� �⺻���� �Ǵ� D3DXVECTOR3 ����ü�� ������. 
	//	_In_ const D3DXVECTOR3 * pV2,			[in] ó���� �⺻���� �Ǵ� D3DXVECTOR3 ����ü�� ������. 
	//	_In_FLOAT s								[in] ���Ͱ��� ���� ���� �ϴ� �Ķ����. 0 ~ 1������ �Ҽ�
	//);
	D3DXVec3Lerp(&p, &from, &to, t);
	p.y = rand->getHeight(p.x, p.z);
	D3DXVECTOR3 prev = owner->_transform->GetWorldPosition();		//��ü�� ������ġ���� ����

	//D3DXVECTOR3 result = prev - p;							//���� ��ġ���� ���������� ��ġ�� �ٶ󺸴� ���⺤��

	owner->_transform->LookPosition(p);						//���⺤�͸� transform�� ���麤�Ϳ� ����
	owner->_transform->RotateSlerp(rotateMonster, *owner->_transform, t*3);
	owner->_transform->SetWorldPosition(p);					//��ä�� ��ġ�� ���������� ��ġ�� ����

	//�ǽð� �÷��̾��� �̵��� üũ�ϰ� ��θ� �ٽ� ����.

	//��ֹ��� �浹�ϸ� �����. - �ٽ� �̵�??
	for (int i = 0; i < object->size(); i++)
	{
		if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, (*object)[i]->_transform, &(*object)[i]->_boundBox))
		{
			if (deleGate) deleGate->OnActionFinish(this, true);
		
			return LHS::ACTIONRESULT::ACTION_MOVE;
		}
	}

	//���� ���� �ٿ�� �ڽ��� �浹�ߴ°�?
	if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, enemy->_transform, &enemy->_boundBox))
	{
		if (deleGate) deleGate->OnActionFinish(this, true);

		return LHS::ACTIONRESULT::ACTION_ATT;
	}

	//���� ������ ������ �ɾ��°�?
	/*
	if(���� ���� Ȯ��)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
