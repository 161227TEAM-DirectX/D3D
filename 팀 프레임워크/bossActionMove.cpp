#include "stdafx.h"
#include "bossActionMove.h"


bossActionMove::bossActionMove()
	:Action(), ch(false), resultValue(0), index(0.0f)
{
}


bossActionMove::~bossActionMove()
{
}

int bossActionMove::Start()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	//baseObject의 transform을 호출하여 world위치를 from으로 변경
	owner->getSkinnedAnim().Play("Animation_56", 0.5f);
	
	//확률을 위한 벡터 및 시드 초기화
	int seed = 0;
	
	seed = 1;
	for (int i = 0; i < 8; i++)
	{
		list.push_back(seed);
	}
	seed = 2;
	list.push_back(seed);
	seed = 3;
	list.push_back(seed);

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	//한번 생성해 놓아서 index가 초기화가 필요하다.
	index = myUtil::RandomFloatRange(0.1f, 1.0f);
	//index = 0.991f;

	PHYSICSMANAGER->isBlocking(owner, enemy);
	//몬스터의 현재 위치를 저장한다.
	from = owner->_transform->GetWorldPosition();
	rotateTemp = *owner->_transform;
	//플레이어의 위치의 y값을 가져와 저장한다.
	float tempY = rand->getHeight(enemy->_transform->GetWorldPosition().x, enemy->_transform->GetWorldPosition().z);
	//현재 플레이어의 위치를 to에 저장한다.
	to = D3DXVECTOR3(enemy->_transform->GetWorldPosition().x, tempY, enemy->_transform->GetWorldPosition().z);
	//몬스터는 플레이어를 바라보도록 설정한다.
	owner->_transform->LookPosition(to);

	owner->_transform->RotateSlerp(rotateTemp, *owner->_transform, _timeDelta);

	D3DXVECTOR3 look(0.0f, 0.0f, 0.01f);
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);


	//현재 구현해야 할 내역이 시작되는 부분이다.
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	if (index >= 0.1f && index <= 0.98f)
	{
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_ATT;
		}
	}
	else if (index >= 0.98f && index <= 0.99f)
	{
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
		}
	}
	else if(index >= 0.99f && index <= 1.0f)
	{
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
