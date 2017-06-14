#include "stdafx.h"
#include "bossActionMove.h"


bossActionMove::bossActionMove()
	:Action(), ch(false), resultValue(0)
{
}


bossActionMove::~bossActionMove()
{
}

int bossActionMove::Start()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	//baseObject의 transform을 호출하여 world위치를 from으로 변경
	owner->getSkinnedAnim().Play("Animation_56");


	//몬스터의 현재 위치를 저장한다.
	from = owner->_transform->GetWorldPosition();
	//플레이어의 위치의 y값을 가져와 저장한다.
	float tempY = rand->getHeight(enemy->_transform->GetWorldPosition().x, enemy->_transform->GetWorldPosition().z);
	//현재 플레이어의 위치를 to에 저장한다.
	to = D3DXVECTOR3(enemy->_transform->GetWorldPosition().x, tempY, enemy->_transform->GetWorldPosition().z);
	//두 케릭의 사이 벡터를 구한다.
	D3DXVECTOR3	range = to - from;
	//몬스터는 플레이어를 바라보도록 설정한다.
	owner->_transform->LookPosition(range);

	//확률을 위한 벡터 및 시드 초기화
	int seed = 0;
	
	seed = 1;
	for (int i = 0; i < 5; i++)
	{
		list.push_back(seed);
	}
	seed = 2;
	list.push_back(seed);
	seed = 3;
	list.push_back(seed);
	list.push_back(seed);
	seed = 4;
	list.push_back(seed);
	list.push_back(seed);

	/*switch (resultValue)
	{
	case 1:
		return LHS::ACTIONRESULT::ACTION_ATT;
	case 2:
		return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
	case 3:
		return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
	case 4:
		return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
	}*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	D3DXVECTOR3 look(0.0f, 0.0f, 0.1f);
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	float tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

	int index = myUtil::RandomIntRange(0, 9);
	resultValue = 3;

	//현재 구현해야 할 내역이 시작되는 부분이다.
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	float angle = fabsf(D3DXVec3Dot(&temp->_transform->GetWorldPosition(), &enemy->_transform->GetWorldPosition()));
	switch (resultValue)
	{
	case 1:
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_ATT;
		}
		break;
	case 2:
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
		}
		break;
	case 3:
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			if (angle <= 0)
			{
				return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
			}
		}
		break;
	case 4:
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			if (angle > 0)
			{
				return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
			}
		}
		break;
	}

	//플레이어를 찾아서 플레이어의 바운드 박스와 나의 hit박스가 충돌했다면 공격 패턴으로 넘어가자


	//플레이어(enemy)가 보스몬스터의 range박스 안에 들어왔다면 들어와라
	//여기서 배틀로어, 꼬리공격, 불공격 확률을 정한다.
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox) && !ch)
	{
		//배틀로어 조건을 만족
		
		//배틀로어 끝---------

		

		//예각이다. 이 경우 fire스킬을 사용하자.
		
		//꼬리 공격을 한다.
		
	}

	//10개의 seed를 가진 배열을 가지고 랜덤하게 인덱스를 구해 그 결과에 따라 다음 스킬을 결정한다.
	//벡터에 값이 있다면


	////테스트
	//if (owner->_transform->GetWorldPosition() >= to)
	//{
	//	owner->_transform->SetWorldPosition(to);
	//	if (deleGate)deleGate->OnActionFinish(this, true);
	//	return LHS::ACTIONRESULT::ACTION_ATT;
	//}

	//if (speed >= 1.0f)
	//{
	//	owner->_transform->SetWorldPosition(to);
	//	return LHS::ACTIONRESULT::ACTION_ATT;
	//}


	//speed += 0.001f;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}
