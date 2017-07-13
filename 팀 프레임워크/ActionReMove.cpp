#include "stdafx.h"
#include "ActionReMove.h"
#include "terrain.h"


ActionReMove::ActionReMove()
	:Action()
{
}


ActionReMove::~ActionReMove()
{
}

int ActionReMove::Start()
{	
	//�����̰��� �ϴ� ��ü�� ���ٸ� ������ ���� ����
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//baseObject�� transform�� ȣ���Ͽ� world��ġ�� from���� ����
	owner->getSkinnedAnim().Play("Run");
//	owner->getSkinnedAnim().SetPlaySpeed(0.5f);
	owner->_transform->SetWorldPosition(from);
	float tempY = rand->getHeight(to.x, to.z);
	to.y = tempY;
	rotateMonster = *owner->_transform;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionReMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	monster* temp = dynamic_cast<monster*>(owner);

	//��������
	if (temp->getHP() <= 0)return LHS::ACTIONRESULT::ACTION_DIE;

	D3DXVECTOR3 length = owner->_transform->GetWorldPosition() - to;
	float tempLength = D3DXVec3Length(&length);
	//����ð��� �׼ǽð����� Ŀ���� �����?
	if (tempLength - Gap <= LENGTHGAP || tempLength - Gap <= LENGTHGAP + 0.2f)
	{
		//��ü�� ��ġ�� to��ġ�� ����
		//owner->_transform->SetWorldPosition(to);
		//deleGate������ nullptr�� �ƴ϶�� �Լ� ȣ��
		return LHS::ACTIONRESULT::ACTION_REFINISH;
	}
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

	D3DXVECTOR3 tempTo = to;
	float tempY = 0;
	tempY = rand->getHeight(tempTo.x, tempTo.z);
	tempTo.y = tempY;
	owner->_transform->LookPosition(tempTo);						//���⺤�͸� transform�� ���麤�Ϳ� ����
	owner->_transform->RotateSlerp(rotateMonster, *owner->_transform, _timeDelta * 8);

	//owner->_transform->LookPosition(p);						//���⺤�͸� transform�� ���麤�Ϳ� ����
	//owner->_transform->SetWorldPosition(p);					//��ä�� ��ġ�� ���������� ��ġ�� ����

	D3DXVECTOR3 look(0.0f, 0.0f, 0.07f);
	tempY = 0;
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

	//�ǽð� �÷��̾��� �̵��� üũ�ϰ� ��θ� �ٽ� ����.

	//��ֹ��� �浹�ϸ� �����. - �ٽ� �̵�??
	for (int i = 0; i < object->size(); i++)
	{
		if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, (*object)[i]->_transform, &(*object)[i]->_boundBox))
		{
//			owner->getSkinnedAnim().Stop();

			return LHS::ACTIONRESULT::ACTION_REMOVE;
		}
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
