#include "stdafx.h"
#include "bossActionFlyMove.h"
#include "xPlayer.h"
#include "bossMonster.h"


bossActionFlyMove::bossActionFlyMove()
	:Action(), angle(0.0f), isRound(FLYSTATE::straight), isAttack(false), MOVESIZE(5.0f), count(0),
	attackEnergyBallCount(0), attackTime(0.0f)
{
}


bossActionFlyMove::~bossActionFlyMove()
{
}

int bossActionFlyMove::Start()
{
	if (!owner) LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_48", 0.5f);

	angle += D3DXToRadian(30)*_timeDelta;
	D3DXMatrixRotationY(&matRotateY, angle);
	D3DXVec3TransformCoord(&pos, &playerObject->_transform->GetWorldPosition(), &matRotateY);

	ch = myUtil::RandomIntRange(0, 1);

	pos.x *= MOVESIZE;
	pos.z *= MOVESIZE;

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionFlyMove::Update()
{
	string tempName = owner->getSkinnedAnim().getAnimationSet()->GetName();

	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	if (temp->getHP() <= 0)
	{
		return LHS::ACTIONRESULT::ACTION_FLY_DIE;
	}

	temp->gettailTrans().SetWorldPosition(temp->gettailTrans().GetWorldPosition().x, 
		rand->getHeight(temp->gettailTrans().GetWorldPosition().x, temp->gettailTrans().GetWorldPosition().z), 
		temp->gettailTrans().GetWorldPosition().z);

	if (!strcmp("Animation_48", tempName.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() > ANIMATIONENDTIME)
		{
			owner->getSkinnedAnim().Play("Animation_39", 1.0f);
			SKM->findSK("불꽃길")->setSkillPosTrans(&temp->gettailTrans());
			SKM->findSK("불꽃길")->setSkillDirTrans(&temp->gettailTrans());
			
			SKM->findSK("불꽃길")->Start();
		}
	}

	//애니메이션이 날며 이동하는 애니메이션으로 변경 되었을 경우.
	if (!strcmp("Animation_39", tempName.c_str()))
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
				if (ch == 0)
				{
					isRound = bossActionFlyMove::FLYSTATE::round;
					SKM->findSK("에너지탄")->setSkillPosTrans(owner->_transform);
					SKM->findSK("에너지탄")->setOneTargetTrans(playerObject->_transform);
					attackEnergyBallCount = myUtil::RandomIntRange(5, 10);
				}
				else if (ch == 1)
				{
					isRound = FLYSTATE::oxpattern;
				}
			}
			break;
		}
		case bossActionFlyMove::round:	//회전하는 위치까지 왔을 경우
		{
			attackTime += _timeDelta;
			lerpTransform = *owner->_transform;
			angle += D3DXToRadian(30)*_timeDelta;
			if (angle > D3DX_PI * 2) angle = 0.0f;

			D3DXMatrixRotationY(&matRotateY, angle);
			D3DXVec3TransformCoord(&pos, &playerObject->_transform->GetWorldPosition(), &matRotateY);

			D3DXVECTOR3 tempPos(pos.x * MOVESIZE, owner->_transform->GetWorldPosition().y, pos.z * MOVESIZE);
			D3DXVECTOR3 tempUp(D3DXVECTOR3(playerObject->_transform->GetWorldPosition() - owner->_transform->GetWorldPosition()));
			D3DXVec3Normalize(&tempUp, &tempUp);

			owner->_transform->LookPosition(tempPos, tempUp);
			owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
			owner->_transform->SetWorldPosition(tempPos);

			if (attackEnergyBallCount == 0)
			{
				isRound = bossActionFlyMove::landing;
				break;
			}

			//공격코드 필요.
			if (!isAttack && (attackEnergyBallCount != 0))
			{
				SKM->findSK("에너지탄")->Start();
				SOUNDMANAGER->play("파이어");
				isAttack = true;
				attackEnergyBallCount--;
			}
			//바닥에 떨어졌냐 1번의 true가 반환된다.
			if (SKM->findSK("에너지탄")->getCollision())
			{
				SOUNDMANAGER->stop("파이어");
				fireballBox.setBound(&playerObject->_transform->GetWorldPosition(), &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
				SOUNDMANAGER->play("파이어폭발");
			}

			//끝이났냐? 1번의 true가 나온다.
			if (SKM->findSK("에너지탄")->getEnd())
			{
				if (SOUNDMANAGER->isPlaySound("파이어폭발")) SOUNDMANAGER->stop("파이어폭발");
				isAttack = false;
				fireballBox.setBound(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				attackTime = 0.0f;
			}

			if (PHYSICSMANAGER->isOverlap(&fireBall, &fireballBox, playerObject->_transform, &playerObject->_boundBox))
			{
				if (attackTime >= 1.0f)
				{
					enemy->playerDamaged(10000);
					attackTime = 0.0f;
				}
			}

			//공격 후 일정 위치로 다시 이동이 필요.
			break;
		}
		case bossActionFlyMove::landing:
			//SKM->findSK("불꽃길")->InitActiveSettingOn();
			return LHS::ACTIONRESULT::ACTION_LANDING;
		case bossActionFlyMove::oxpattern:
		{
			lerpTransform = *owner->_transform;
			angle += D3DXToRadian(30)*_timeDelta;
			D3DXVECTOR3 temp = owner->_transform->GetWorldPosition();
			temp.y = 0.0f;
			D3DXVec3Normalize(&temp, &temp);
			float Radian = D3DXVec3Dot(&temp, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
			if (Radian <= 1.0f && Radian >= (1.0f - Gap))
			{
				owner->_transform->LookPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
				D3DXVECTOR3 tempOld = owner->_transform->GetForward();
				D3DXVECTOR3 curTemp = playerObject->_transform->GetWorldPosition() - owner->_transform->GetWorldPosition();
				D3DXVec3Normalize(&curTemp, &curTemp);
				float Lenge = D3DXVec3Dot(&tempOld, &curTemp);
				count += 0.05f;
				if (Lenge >= 0.99f && count >= 5)
				{
					return LHS::ACTIONRESULT::ACTION_PA_OX;
				}
				break;
			}

			D3DXMatrixRotationY(&matRotateY, angle);
			D3DXVec3TransformCoord(&pos, &playerObject->_transform->GetWorldPosition(), &matRotateY);

			D3DXVECTOR3 tempPos(pos.x * MOVESIZE, owner->_transform->GetWorldPosition().y, pos.z * MOVESIZE);
			D3DXVECTOR3 tempUp(D3DXVECTOR3(playerObject->_transform->GetWorldPosition() - owner->_transform->GetWorldPosition()));
			D3DXVec3Normalize(&tempUp, &tempUp);

			owner->_transform->LookPosition(tempPos, tempUp);
			owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
			owner->_transform->SetWorldPosition(tempPos);
			break;
		}

		}
	}

	return LHS::ACTIONRESULT::ACTION_SAFE;
}