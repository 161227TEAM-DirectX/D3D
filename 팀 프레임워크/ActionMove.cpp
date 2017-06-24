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
	//움직이고자 하는 개체가 없다면 실행을 하지 마라
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//baseObject의 transform을 호출하여 world위치를 from으로 변경
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

	//장애물과 충돌하면 멈춘다. - 다시 이동??
	for (int i = 0; i < object->size(); i++)
	{
		if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, (*object)[i]->_transform, &(*object)[i]->_boundBox))
		{
			if (deleGate) deleGate->OnActionFinish(this, true);
			owner->getSkinnedAnim().Stop();
			return LHS::ACTIONRESULT::ACTION_MOVE;
		}
	}

	//적과 나의 바운드 박스가 충돌했는가?
	if (PHYSICSMANAGER->isOverlap(owner->_transform, &owner->_boundBox, playerObject->_transform, &playerObject->_boundBox))
	{
		if (deleGate) deleGate->OnActionFinish(this, true);
		owner->getSkinnedAnim().Stop();
		return LHS::ACTIONRESULT::ACTION_ATT;
	}

	m_fPassedTime += _timeDelta;
	//경과시간이 액션시간보다 커지면 멈춰라?
	//if (m_fPassedTime >= actionTime)
	D3DXVECTOR3 length = owner->_transform->GetWorldPosition() - to;
	float tempLength = D3DXVec3Length(&length);
	if(tempLength <= 1.0f)
	{
		//객체의 위치를 to위치로 변경
		owner->_transform->SetWorldPosition(to);

		//플레이어가 내 탐색 범위를 벗어나게 되면 스탠딩 상태로 돌아간다.
		if (!PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
		{
			if (deleGate) deleGate->OnActionFinish(this, true);
			owner->getSkinnedAnim().Stop();

			return LHS::ACTIONRESULT::ACTION_REMOVE;
		}

		//deleGate변수가 nullptr이 아니라면 함수 호출
		if (deleGate)deleGate->OnActionFinish(this);

		return LHS::ACTIONRESULT::ACTION_FINISH;
	}
	//선형보간을 위해 현재시간 / 전체 시간
	float t = m_fPassedTime / actionTime;
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

	//D3DXVECTOR3 result = prev - p;							//과거 위치에서 선형보간된 위치를 바라보는 방향벡터

	owner->_transform->LookPosition(to);						//방향벡터를 transform의 정면벡터에 저장
	owner->_transform->RotateSlerp(rotateMonster, *owner->_transform, _timeDelta*5);
	//owner->_transform->SetWorldPosition(p);					//개채의 위치를 선형보간된 위치로 변경

	//cout << "몬스터 바라보는 방향 x: " << owner->_transform->GetForward().x << " y: " << owner->_transform->GetForward().y << " z: " << owner->_transform->GetForward().z << endl;
	//cout << "몬스터 위치 x: " << owner->_transform->GetWorldPosition().x << " y: " << owner->_transform->GetWorldPosition().y << " z: " << owner->_transform->GetWorldPosition().z << endl;
	//cout << "목적지 위치값 x: " << to.x << " y: " << to.y << " z: " << to.z << endl;
	//cout << "플레이어 위치값 x: " << playerObject->_transform->GetWorldPosition().x << " y: " << playerObject->_transform->GetWorldPosition().y << " z: " << playerObject->_transform->GetWorldPosition().z << endl;

	D3DXVECTOR3 look(0.0f, 0.0f, 0.05f);
	float tempY = 0;
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

	//실시간 플레이어의 이동을 체크하고 경로를 다시 설정.

	//적이 나에게 스턴을 걸었는가?
	/*
	if(스턴 상태 확인)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
