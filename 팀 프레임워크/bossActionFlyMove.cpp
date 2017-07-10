#include "stdafx.h"
#include "bossActionFlyMove.h"


bossActionFlyMove::bossActionFlyMove()
	:Action(), angle(0.0f), isRound(FLYSTATE::straight), isAttack(false), tempRadian(0.0f)
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

	ch = myUtil::RandomIntRange(0, 1);

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

	//애니메이션이 날며 이동하는 애니메이션으로 변경 되었을 경우.
	if (!strcmp("Animation_39", temp.c_str()))
	{
		switch (isRound)
		{
		case bossActionFlyMove::straight:	//아직 회전위치로 이동하지 못했을 경우
		{
			lerpTransform = *owner->_transform;
			D3DXVECTOR3 tempPos(pos.x, owner->_transform->GetWorldPosition().y, pos.z);
			owner->_transform->LookPosition(tempPos);
			owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
			owner->_transform->MovePositionSelf(0.0f, 0.0f, 0.5f);
			
			if (D3DXVec3Length(&(owner->_transform->GetWorldPosition() - tempPos)) <= 0.7f)
			{
				//if (ch == 0)
				//{
				//	isRound = bossActionFlyMove::FLYSTATE::round;
				//}
				//else if (ch == 1)
				{
					isRound = FLYSTATE::oxpattern;
				}
			}
			break;
		}
		case bossActionFlyMove::round:	//회전하는 위치까지 왔을 경우
		{
			lerpTransform = *owner->_transform;
			angle += D3DXToRadian(30)*_timeDelta;
			if (angle > D3DX_PI * 2) angle = 0.0f;

			D3DXMatrixRotationY(&matRotateY, angle);
			D3DXVec3TransformCoord(&pos, &playerObject->_transform->GetWorldPosition(), &matRotateY);

			D3DXVECTOR3 tempPos(pos.x * 25.0f, owner->_transform->GetWorldPosition().y, pos.z * 25.0f);
			D3DXVECTOR3 tempUp(D3DXVECTOR3(playerObject->_transform->GetWorldPosition() - owner->_transform->GetWorldPosition()));
			D3DXVec3Normalize(&tempUp, &tempUp);

			owner->_transform->LookPosition(tempPos, tempUp);
			owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
			owner->_transform->SetWorldPosition(tempPos);

			//공격코드 필요.
			if (isAttack)
			{
				playerPos = D3DXVECTOR3(playerObject->_transform->GetWorldPosition() - owner->_transform->GetWorldPosition());
				fireBall.LookPosition(playerPos);
				fireballBox.setBound(&playerPos, &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
				isAttack = true;
			}

			//공격 후 일정 위치로 다시 이동이 필요.

			break;
		}
		case bossActionFlyMove::landing:
		{
			lerpTransform = *owner->_transform;
			D3DXVECTOR3 tempPos(0.0f, 0.0f, 0.0f);
			owner->_transform->LookPosition(tempPos);
			owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
			owner->_transform->MovePositionSelf(0.0f, 0.0f, 0.5f);
			if (D3DXVec3Length(&(owner->_transform->GetWorldPosition() - tempPos)) <= 0.7f) return LHS::ACTIONRESULT::ACTION_LANDING;
			break;
		}
		case bossActionFlyMove::oxpattern:
		{
			lerpTransform = *owner->_transform;
			angle += D3DXToRadian(30)*_timeDelta;
			D3DXVECTOR3 temp = owner->_transform->GetWorldPosition();
			temp.y = 0.0f;
			D3DXVec3Normalize(&temp, &temp);
			tempRadian = D3DXVec3Dot(&temp, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
			if (tempRadian <= 1.0f && tempRadian >= (1.0f - Gap))
			{
				angle = D3DX_PI;
				owner->_transform->LookPosition(playerObject->_transform->GetWorldPosition());
				owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
				D3DXVECTOR3 tempOld = lerpTransform.GetForward();
				D3DXVECTOR3 curTemp = owner->_transform->GetForward();
				float tempLenge = D3DXVec3Length(&(tempOld - curTemp));
				if (tempLenge == 0.0f) return LHS::ACTIONRESULT::ACTION_PA_OX;
				break;
			}

			D3DXMatrixRotationY(&matRotateY, angle);
			D3DXVec3TransformCoord(&pos, &playerObject->_transform->GetWorldPosition(), &matRotateY);

			D3DXVECTOR3 tempPos(pos.x * 25.0f, owner->_transform->GetWorldPosition().y, pos.z * 25.0f);
			D3DXVECTOR3 tempUp(D3DXVECTOR3(playerObject->_transform->GetWorldPosition() - owner->_transform->GetWorldPosition()));
			D3DXVec3Normalize(&tempUp, &tempUp);

			owner->_transform->LookPosition(tempPos, tempUp);
			owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
			owner->_transform->SetWorldPosition(tempPos);
			break;
		}

		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

void bossActionFlyMove::Render()
{
	char temp[128];
	sprintf_s(temp, "%f", tempRadian);
	FONTMANAGER->fontOut(temp, 500, 500, WHITE);
}

void bossActionFlyMove::attackFireBall(void)
{
	
}
