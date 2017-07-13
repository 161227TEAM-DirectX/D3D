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
	//움직이고자 하는 개체가 없다면 실행을 하지 마라
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//baseObject의 transform을 호출하여 world위치를 from으로 변경
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

	//죽음조건
	if (temp->getHP() <= 0)return LHS::ACTIONRESULT::ACTION_DIE;

	D3DXVECTOR3 length = owner->_transform->GetWorldPosition() - to;
	float tempLength = D3DXVec3Length(&length);
	//경과시간이 액션시간보다 커지면 멈춰라?
	if (tempLength - Gap <= LENGTHGAP || tempLength - Gap <= LENGTHGAP + 0.2f)
	{
		//객체의 위치를 to위치로 변경
		//owner->_transform->SetWorldPosition(to);
		//deleGate변수가 nullptr이 아니라면 함수 호출
		return LHS::ACTIONRESULT::ACTION_REFINISH;
	}
	//D3DXVECTOR3 p;				//선형보간한 위치값을 저장하는 벡터
	//두 3D 벡터 사이에서 선형 보간을 수행합니다.
	//D3DXVECTOR3 * D3DXVec3Lerp(
	//	_Inout_ D3DXVECTOR3 * pOut,				[in, out] 연산 결과인 D3DXVECTOR3 구조체의 포인터. 
	//	_In_ const D3DXVECTOR3 * pV1,			[in] 처리의 기본으로 되는 D3DXVECTOR3 구조체의 포인터. 
	//	_In_ const D3DXVECTOR3 * pV2,			[in] 처리의 기본으로 되는 D3DXVECTOR3 구조체의 포인터. 
	//	_In_FLOAT s								[in] 벡터간을 선형 보간 하는 파라미터. 0 ~ 1사이의 소수
	//);
	//D3DXVec3Lerp(&p, &from, &to, t);
	//p.y = rand->getHeight(p.x, p.z);
	//D3DXVECTOR3 prev = owner->_transform->GetWorldPosition();		//개체의 월드위치값을 저장
	rotateMonster = *owner->_transform;

	D3DXVECTOR3 tempTo = to;
	float tempY = 0;
	tempY = rand->getHeight(tempTo.x, tempTo.z);
	tempTo.y = tempY;
	owner->_transform->LookPosition(tempTo);						//방향벡터를 transform의 정면벡터에 저장
	owner->_transform->RotateSlerp(rotateMonster, *owner->_transform, _timeDelta * 8);

	//owner->_transform->LookPosition(p);						//방향벡터를 transform의 정면벡터에 저장
	//owner->_transform->SetWorldPosition(p);					//개채의 위치를 선형보간된 위치로 변경

	D3DXVECTOR3 look(0.0f, 0.0f, 0.07f);
	tempY = 0;
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

	//실시간 플레이어의 이동을 체크하고 경로를 다시 설정.

	//장애물과 충돌하면 멈춘다. - 다시 이동??
	for (int i = 0; i < object->size(); i++)
	{
		if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, (*object)[i]->_transform, &(*object)[i]->_boundBox))
		{
//			owner->getSkinnedAnim().Stop();

			return LHS::ACTIONRESULT::ACTION_REMOVE;
		}
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
