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
	owner->getSkinnedAnim().SetPlaySpeed(0.5f);
	owner->_transform->SetWorldPosition(from);
	//owner->_transform->LookPosition(to);
	rotateMonster = *owner->_transform;
	m_fPassedTime = 0.0f;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	monster* temp = dynamic_cast<monster*>(owner);

	//��ֹ��� �浹�ϸ� �����. - �ٽ� �̵�??
	for (int i = 0; i < object->size(); i++)
	{
		if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, (*object)[i]->_transform, &(*object)[i]->_boundBox))
		{
			if (deleGate) deleGate->OnActionFinish(this, true);
			owner->getSkinnedAnim().Stop();
			return LHS::ACTIONRESULT::ACTION_MOVE;
		}
	}

	//���� ���� �ٿ�� �ڽ��� �浹�ߴ°�?
	if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, playerObject->_transform, &playerObject->_boundBox))
	{
		if (deleGate) deleGate->OnActionFinish(this, true);
		owner->getSkinnedAnim().Stop();
		return LHS::ACTIONRESULT::ACTION_ATT;
	}

	m_fPassedTime += _timeDelta;
	//����ð��� �׼ǽð����� Ŀ���� �����?
	//if (m_fPassedTime >= actionTime)
	D3DXVECTOR3 length = owner->_transform->GetWorldPosition() - to;
	float tempLength = D3DXVec3Length(&length);
	if(tempLength <= 1.0f)
	{
		//��ü�� ��ġ�� to��ġ�� ����
		owner->_transform->SetWorldPosition(to);

		//�÷��̾ �� Ž�� ������ ����� �Ǹ� ���ĵ� ���·� ���ư���.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
		{
			if (deleGate) deleGate->OnActionFinish(this, true);
			owner->getSkinnedAnim().Stop();

			return LHS::ACTIONRESULT::ACTION_REMOVE;
		}

		//deleGate������ nullptr�� �ƴ϶�� �Լ� ȣ��
		if (deleGate)deleGate->OnActionFinish(this);

		return LHS::ACTIONRESULT::ACTION_FINISH;
	}
	//���������� ���� ����ð� / ��ü �ð�
	float t = m_fPassedTime / actionTime;
	//D3DXVECTOR3 p;				//���������� ��ġ���� �����ϴ� ����
	//�� 3D ���� ���̿��� ���� ������ �����մϴ�.
	//D3DXVECTOR3 * D3DXVec3Lerp(
	//	_Inout_ D3DXVECTOR3 * pOut,				[in, out] ���� ����� D3DXVECTOR3 ����ü�� ������. 
	//	_In_ const D3DXVECTOR3 * pV1,			[in] ó���� �⺻���� �Ǵ� D3DXVECTOR3 ����ü�� ������. 
	//	_In_ const D3DXVECTOR3 * pV2,			[in] ó���� �⺻���� �Ǵ� D3DXVECTOR3 ����ü�� ������. 
	//	_In_FLOAT s								[in] ���Ͱ��� ���� ���� �ϴ� �Ķ����. 0 ~ 1������ �Ҽ�
	//);
	//D3DXVec3Lerp(&p, &from, &to, t);
	//p.y = rand->getHeight(p.x, p.z);
	//D3DXVECTOR3 prev = owner->_transform->GetWorldPosition();		//��ü�� ������ġ���� ����
	rotateMonster = *owner->_transform;

	//D3DXVECTOR3 result = prev - p;							//���� ��ġ���� ���������� ��ġ�� �ٶ󺸴� ���⺤��

	owner->_transform->LookPosition(to);						//���⺤�͸� transform�� ���麤�Ϳ� ����
	owner->_transform->RotateSlerp(rotateMonster, *owner->_transform, _timeDelta*5);
	//owner->_transform->SetWorldPosition(p);					//��ä�� ��ġ�� ���������� ��ġ�� ����

	//cout << "���� �ٶ󺸴� ���� x: " << owner->_transform->GetForward().x << " y: " << owner->_transform->GetForward().y << " z: " << owner->_transform->GetForward().z << endl;
	//cout << "���� ��ġ x: " << owner->_transform->GetWorldPosition().x << " y: " << owner->_transform->GetWorldPosition().y << " z: " << owner->_transform->GetWorldPosition().z << endl;
	//cout << "������ ��ġ�� x: " << to.x << " y: " << to.y << " z: " << to.z << endl;
	//cout << "�÷��̾� ��ġ�� x: " << playerObject->_transform->GetWorldPosition().x << " y: " << playerObject->_transform->GetWorldPosition().y << " z: " << playerObject->_transform->GetWorldPosition().z << endl;

	D3DXVECTOR3 look(0.0f, 0.0f, 0.05f);
	float tempY = 0;
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

	//�ǽð� �÷��̾��� �̵��� üũ�ϰ� ��θ� �ٽ� ����.

	//���� ������ ������ �ɾ��°�?
	/*
	if(���� ���� Ȯ��)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
