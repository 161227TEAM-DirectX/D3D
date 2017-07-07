#include "stdafx.h"
#include "bossActionFlyMove.h"


bossActionFlyMove::bossActionFlyMove()
	:Action(), angle(0.0f), isRound(FLYSTATE::straight)
{
}


bossActionFlyMove::~bossActionFlyMove()
{
}

int bossActionFlyMove::Start()
{
	if (!owner) LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_48", 1.0f);

	angle += D3DXToRadian(30)*_timeDelta;
	D3DXMatrixRotationY(&matRotateY, angle);
	D3DXVec3TransformCoord(&pos, &playerObject->_transform->GetWorldPosition(), &matRotateY);
	pos.x *= 25.0f;
	pos.z *= 25.0f;

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionFlyMove::Update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F11))
	{
		isRound = FLYSTATE::landing;
	}

	string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();

	if (!strcmp("Animation_48", temp.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f) owner->getSkinnedAnim().Play("Animation_39", 1.0f);
	}

	//�ִϸ��̼��� ���� �̵��ϴ� �ִϸ��̼����� ���� �Ǿ��� ���.
	if (!strcmp("Animation_39", temp.c_str()))
	{
		switch (isRound)
		{
		case bossActionFlyMove::straight:	//���� ȸ����ġ�� �̵����� ������ ���
		{
			lerpTransform = *owner->_transform;
			D3DXVECTOR3 tempPos(pos.x, owner->_transform->GetWorldPosition().y, pos.z);
			owner->_transform->LookPosition(tempPos);
			owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
			owner->_transform->MovePositionSelf(0.0f, 0.0f, 0.5f);
			if (D3DXVec3Length(&(owner->_transform->GetWorldPosition() - tempPos)) <= 0.7f) isRound = FLYSTATE::round;
			break;
		}
		case bossActionFlyMove::round:	//ȸ���ϴ� ��ġ���� ���� ���
		{
			lerpTransform = *owner->_transform;
			angle += D3DXToRadian(30)*_timeDelta;
			D3DXMatrixRotationY(&matRotateY, angle);
			D3DXVec3TransformCoord(&pos, &playerObject->_transform->GetWorldPosition(), &matRotateY);

			D3DXVECTOR3 tempPos(pos.x * 25.0f, owner->_transform->GetWorldPosition().y, pos.z * 25.0f);
			D3DXVECTOR3 tempUp(D3DXVECTOR3(playerObject->_transform->GetWorldPosition() - owner->_transform->GetWorldPosition()));
			D3DXVec3Normalize(&tempUp, &tempUp);

			owner->_transform->LookPosition(tempPos, tempUp);
			owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
			owner->_transform->SetWorldPosition(tempPos);

			//�����ڵ� �ʿ�.

			//���� �� ���� ��ġ�� �ٽ� �̵��� �ʿ�.

			break;
		}
		case bossActionFlyMove::landing:
		{
			lerpTransform = *owner->_transform;
			D3DXVECTOR3 tempPos(0.0f, 0.0f, 0.0f);
			owner->_transform->LookPosition(tempPos);
			owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
			owner->_transform->MovePositionSelf(0.0f, 0.0f, 0.5f);
			//if (D3DXVec3Length(&(owner->_transform->GetWorldPosition() - tempPos)) <= 0.7f)
			break;
		}
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
