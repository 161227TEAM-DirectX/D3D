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
	//움직이고자 하는 개체가 없다면 실행을 하지 마라
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//baseObject의 transform을 호출하여 world위치를 from으로 변경
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

	//죽음조건
	if (temp->getHP() < 0)return LHS::ACTIONRESULT::ACTION_DIE;

	//장애물과 충돌하면 멈춘다. - 다시 이동??
	for (int i = 0; i < object->size(); i++)
	{
		if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, (*object)[i]->_transform, &(*object)[i]->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_MOVE;
		}
	}

	//적과 나의 바운드 박스가 충돌했는가?
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
	{
		return LHS::ACTIONRESULT::ACTION_ATT;
	}

	//방향에 따른 회전 시 필요한 트랜스폼을 현재 owner가 가지고 있는 transform을 저장한다.
	rotateMonster = *owner->_transform;

	//D3DXVECTOR3 result = prev - p;							//과거 위치에서 선형보간된 위치를 바라보는 방향벡터
	D3DXVECTOR3 tempTo = to;
	float tempY = 0;
	//지형의 y값을 가져온다.
	tempY = rand->getHeight(tempTo.x, tempTo.z);
	tempTo.y = tempY;
	//몬스터가 바라보는 방향을 변경.
	owner->_transform->LookPosition(tempTo);						//방향벡터를 transform의 정면벡터에 저장
																	//몬스터의 회전을 보정값을 넣어서 회전시킨다.
	owner->_transform->RotateSlerp(rotateMonster, *owner->_transform, _timeDelta * 8);
	//owner->_transform->SetWorldPosition(p);					//개채의 위치를 선형보간된 위치로 변경

	//cout << "몬스터 바라보는 방향 x: " << owner->_transform->GetForward().x << " y: " << owner->_transform->GetForward().y << " z: " << owner->_transform->GetForward().z << endl;
	//cout << "몬스터 위치 x: " << owner->_transform->GetWorldPosition().x << " y: " << owner->_transform->GetWorldPosition().y << " z: " << owner->_transform->GetWorldPosition().z << endl;
	//cout << "목적지 위치값 x: " << to.x << " y: " << to.y << " z: " << to.z << endl;
	//cout << "플레이어 위치값 x: " << playerObject->_transform->GetWorldPosition().x << " y: " << playerObject->_transform->GetWorldPosition().y << " z: " << playerObject->_transform->GetWorldPosition().z << endl;

	//이동벡터값. z축으로 이동한다.
	D3DXVECTOR3 look(0.0f, 0.0f, 0.07f);
	tempY = 0;
	//현재 자신의 축을 기준으로 이동한다. look벡터내부 값 만큼.
	owner->_transform->MovePositionSelf(look);
	//이동 후 현재 월드 포시션값을 가져온다.
	look = owner->_transform->GetWorldPosition();
	//지형 높이값을 가져온다.
	tempY = rand->getHeight(look.x, look.z);
	//높이값을 적용한다.
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

	//플레이어가 내 탐색 범위를 벗어나게 되면 스탠딩 상태로 돌아간다.
	float tempDistance = 0;
	tempDistance = D3DXVec3Length(&(temp->getRegenPosition() - temp->_transform->GetWorldPosition()));
	if (tempDistance - Gap >= PLAYERDISTANCE)
	{
		return LHS::ACTIONRESULT::ACTION_REMOVE;
	}

	D3DXVECTOR3 hitBoxCenter;
	float hitBoxRadius;
	temp->getHitBox().getWorldCenterRadius(temp->_transform, &hitBoxCenter, &hitBoxRadius);

	//현재 몬스터의 히트박스의 최저위치값을 저장.
	hitBoxCenter.y = rand->getHeight(hitBoxCenter.x, hitBoxCenter.z);
	//목적지와 현재 내 위치 사이의 거리, 방향 벡터를 구한다.(목적지에서 몬스터를 바라보는 방향)
	//D3DXVECTOR3 distance = owner->_transform->GetWorldPosition() - to;
	D3DXVECTOR3 distance = hitBoxCenter - to;
	//사이 거리를 구한다.
	length = D3DXVec3Length(&distance);
	//사이 거리-0.001f 값이 0.5보다 작거나 0.7보다 작거나????
	if(length - Gap <= 0.5f)
	{
		//장애물과 충돌하면 멈춘다. - 다시 이동??
		for (int i = 0; i < object->size(); i++)
		{
			if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, (*object)[i]->_transform, &(*object)[i]->_boundBox))
			{
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		}

		//적과 나의 바운드 박스가 충돌했는가?
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_ATT;
		}

		////플레이어가 내 탐색 범위를 벗어나게 되면 스탠딩 상태로 돌아간다.
		float tempDistance = 0;
		tempDistance = D3DXVec3Length(&(temp->getRegenPosition() - temp->_transform->GetWorldPosition()));
		if (tempDistance - Gap >= PLAYERDISTANCE)
		{
			return LHS::ACTIONRESULT::ACTION_REMOVE;
		}

		return LHS::ACTIONRESULT::ACTION_FINISH;
	}

	//적이 나에게 스턴을 걸었는가?
	/*
	if(스턴 상태 확인)
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
