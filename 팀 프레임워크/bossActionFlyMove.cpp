#include "stdafx.h"
#include "bossActionFlyMove.h"


bossActionFlyMove::bossActionFlyMove()
	:Action(), angle(0.0f), isRound(false)
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
	string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();

	if (!strcmp("Animation_48", temp.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f) owner->getSkinnedAnim().Play("Animation_39", 1.0f);
	}

	//애니메이션이 날며 이동하는 애니메이션으로 변경 되었을 경우.
	if (!strcmp("Animation_39", temp.c_str()))
	{
		//회전하는 위치까지 왔을 경우
		if (isRound)
		{
			angle += D3DXToRadian(30)*_timeDelta;
			D3DXMatrixRotationY(&matRotateY, angle);
			D3DXVec3TransformCoord(&pos, &playerObject->_transform->GetWorldPosition(), &matRotateY);

			D3DXVECTOR3 tempPos(pos.x * 25.0f, owner->_transform->GetWorldPosition().y, pos.z * 25.0f);
			D3DXVECTOR3 tempUp(D3DXVECTOR3(playerObject->_transform->GetWorldPosition() - owner->_transform->GetWorldPosition()));
			D3DXVec3Normalize(&tempUp, &tempUp);

			owner->_transform->LookPosition(tempPos, tempUp);
			owner->_transform->SetWorldPosition(tempPos);
		}
		//아직 회전위치로 이동하지 못했을 경우
		else
		{
			D3DXVECTOR3 tempPos(pos.x, owner->_transform->GetWorldPosition().y, pos.z);
			owner->_transform->LookPosition(tempPos);
			owner->_transform->MovePositionSelf(0.0f, 0.0f, 0.5f);
			if (D3DXVec3Length(&(owner->_transform->GetWorldPosition() - tempPos)) <= 0.7f) isRound = true;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
