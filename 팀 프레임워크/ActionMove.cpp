#include "stdafx.h"
#include "ActionMove.h"
#include "terrain.h"


ActionMove::ActionMove()
	:Action(), length(0.0f)
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
	float tempY = rand->getHeight(to.x, to.z);
	to.y = tempY;
	rotateMonster = *owner->_transform;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	monster* temp = dynamic_cast<monster*>(owner);

	//��������
	if (temp->getHP() < 0)return LHS::ACTIONRESULT::ACTION_DIE;

	//��ֹ��� �浹�ϸ� �����. - �ٽ� �̵�??
	for (int i = 0; i < object->size(); i++)
	{
		if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, (*object)[i]->_transform, &(*object)[i]->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_MOVE;
		}
	}

	//���� ���� �ٿ�� �ڽ��� �浹�ߴ°�?
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
	{
		return LHS::ACTIONRESULT::ACTION_ATT;
	}

	//���⿡ ���� ȸ�� �� �ʿ��� Ʈ�������� ���� owner�� ������ �ִ� transform�� �����Ѵ�.
	rotateMonster = *owner->_transform;

	//D3DXVECTOR3 result = prev - p;							//���� ��ġ���� ���������� ��ġ�� �ٶ󺸴� ���⺤��
	D3DXVECTOR3 tempTo = to;
	float tempY = 0;
	//������ y���� �����´�.
	tempY = rand->getHeight(tempTo.x, tempTo.z);
	tempTo.y = tempY;
	//���Ͱ� �ٶ󺸴� ������ ����.
	owner->_transform->LookPosition(tempTo);						//���⺤�͸� transform�� ���麤�Ϳ� ����
																	//������ ȸ���� �������� �־ ȸ����Ų��.
	owner->_transform->RotateSlerp(rotateMonster, *owner->_transform, _timeDelta * 8);
	//owner->_transform->SetWorldPosition(p);					//��ä�� ��ġ�� ���������� ��ġ�� ����

	//cout << "���� �ٶ󺸴� ���� x: " << owner->_transform->GetForward().x << " y: " << owner->_transform->GetForward().y << " z: " << owner->_transform->GetForward().z << endl;
	//cout << "���� ��ġ x: " << owner->_transform->GetWorldPosition().x << " y: " << owner->_transform->GetWorldPosition().y << " z: " << owner->_transform->GetWorldPosition().z << endl;
	//cout << "������ ��ġ�� x: " << to.x << " y: " << to.y << " z: " << to.z << endl;
	//cout << "�÷��̾� ��ġ�� x: " << playerObject->_transform->GetWorldPosition().x << " y: " << playerObject->_transform->GetWorldPosition().y << " z: " << playerObject->_transform->GetWorldPosition().z << endl;

	//�̵����Ͱ�. z������ �̵��Ѵ�.
	D3DXVECTOR3 look(0.0f, 0.0f, 0.07f);
	tempY = 0;
	//���� �ڽ��� ���� �������� �̵��Ѵ�. look���ͳ��� �� ��ŭ.
	owner->_transform->MovePositionSelf(look);
	//�̵� �� ���� ���� ���üǰ��� �����´�.
	look = owner->_transform->GetWorldPosition();
	//���� ���̰��� �����´�.
	tempY = rand->getHeight(look.x, look.z);
	//���̰��� �����Ѵ�.
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

	//�÷��̾ �� Ž�� ������ ����� �Ǹ� ���ĵ� ���·� ���ư���.
	float tempDistance = 0;
	tempDistance = D3DXVec3Length(&(temp->getRegenPosition() - temp->_transform->GetWorldPosition()));
	if (tempDistance - Gap >= PLAYERDISTANCE)
	{
		return LHS::ACTIONRESULT::ACTION_REMOVE;
	}

	D3DXVECTOR3 hitBoxCenter;
	float hitBoxRadius;
	temp->getHitBox().getWorldCenterRadius(temp->_transform, &hitBoxCenter, &hitBoxRadius);

	//���� ������ ��Ʈ�ڽ��� ������ġ���� ����.
	hitBoxCenter.y = rand->getHeight(hitBoxCenter.x, hitBoxCenter.z);
	//�������� ���� �� ��ġ ������ �Ÿ�, ���� ���͸� ���Ѵ�.(���������� ���͸� �ٶ󺸴� ����)
	//D3DXVECTOR3 distance = owner->_transform->GetWorldPosition() - to;
	D3DXVECTOR3 distance = hitBoxCenter - to;
	//���� �Ÿ��� ���Ѵ�.
	length = D3DXVec3Length(&distance);
	//���� �Ÿ�-0.001f ���� 0.5���� �۰ų� 0.7���� �۰ų�????
	if(length - Gap <= 0.5f)
	{
		//��ֹ��� �浹�ϸ� �����. - �ٽ� �̵�??
		for (int i = 0; i < object->size(); i++)
		{
			if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, (*object)[i]->_transform, &(*object)[i]->_boundBox))
			{
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		}

		//���� ���� �ٿ�� �ڽ��� �浹�ߴ°�?
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_ATT;
		}

		////�÷��̾ �� Ž�� ������ ����� �Ǹ� ���ĵ� ���·� ���ư���.
		float tempDistance = 0;
		tempDistance = D3DXVec3Length(&(temp->getRegenPosition() - temp->_transform->GetWorldPosition()));
		if (tempDistance - Gap >= PLAYERDISTANCE)
		{
			return LHS::ACTIONRESULT::ACTION_REMOVE;
		}

		return LHS::ACTIONRESULT::ACTION_FINISH;
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

void ActionMove::Render()
{
	char temp[128];
	sprintf_s(temp, "%f", length);
	FONTMANAGER->fontOut(temp, 250, 250, WHITE);
}
