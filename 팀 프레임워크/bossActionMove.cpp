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
	owner->getSkinnedAnim().Play("Animation_56");
	if (!SOUNDMANAGER->isPlaySound("걷기"))
	{
		SOUNDMANAGER->play("걷기");
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	PHYSICSMANAGER->isBlocking(owner, playerObject);
	//몬스터의 현재 위치를 저장한다.
	from = owner->_transform->GetWorldPosition();
	rotateTemp = *owner->_transform;
	//플레이어의 위치의 y값을 가져와 저장한다.
	float tempY = rand->getHeight(playerObject->_transform->GetWorldPosition().x, playerObject->_transform->GetWorldPosition().z);
	//현재 플레이어의 위치를 to에 저장한다.
	to = D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, tempY, playerObject->_transform->GetWorldPosition().z);
	//몬스터는 플레이어를 바라보도록 설정한다.
	owner->_transform->LookPosition(to);

	owner->_transform->RotateSlerp(rotateTemp, *owner->_transform, _timeDelta);

	D3DXVECTOR3 look(0.0f, 0.0f, 0.1f);
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);


	//현재 구현해야 할 내역이 시작되는 부분이다.
	//한번 생성해 놓아서 index가 초기화가 필요하다.
	index = myUtil::RandomFloatRange(0.1f, 1.0f);

	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		//걷다가 hit박스에 플레이어가 있다면.
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			SOUNDMANAGER->stop("걷기");
			return LHS::ACTIONRESULT::ACTION_ATT;
		}
		//걷다가 range박스 안에 플레이어가 있다면.
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
		{
			SOUNDMANAGER->stop("걷기");
			if (index >= 0.98f && index <= 0.99f) return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
			else if (index >= 0.99f && index <= 1.0f) return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
		}

		//확률적으로 날기패턴으로 이동
		if (index - Gap >= 0.97f && index - Gap <= 0.975f)
		{
			return LHS::ACTIONRESULT::ACTION_FLY;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
