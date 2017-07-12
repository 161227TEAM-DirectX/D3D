#include "stdafx.h"
#include "ActionStanding.h"
#include "monster.h"

ActionStanding::ActionStanding()
	:Action()
{
}


ActionStanding::~ActionStanding()
{
}

int ActionStanding::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;
	owner->getSkinnedAnim().Play("Stand");
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionStanding::Update()
{
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//owner는 baseobject클래스이고 monster클래스가 필요하기에 타입 캐스팅.
	monster* temp = dynamic_cast<monster*>(owner);

	//죽음조건
	if (temp->getHP() < 0)return LHS::ACTIONRESULT::ACTION_DIE;

	if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	{
		int random = myUtil::RandomIntRange(0, 4);
		switch (random)
		{
		case 0:
			owner->getSkinnedAnim().Play("Stand01", 0.5f);
			break;
		case 1:
			if (owner->getSkinnedAnim().getSkinnedMesh()->getAnimMap().find("Stand02") != owner->getSkinnedAnim().getSkinnedMesh()->getAnimMap().end())
				owner->getSkinnedAnim().Play("Stand02", 0.5f);
			else
				owner->getSkinnedAnim().Play("Stand01", 0.5f);
			break;
		case 2:
			if (owner->getSkinnedAnim().getSkinnedMesh()->getAnimMap().find("Stand03") != owner->getSkinnedAnim().getSkinnedMesh()->getAnimMap().end())
				owner->getSkinnedAnim().Play("Stand03", 0.5f);
			else
				owner->getSkinnedAnim().Play("Stand01", 0.5f);
			break;
		case 3:
			if (owner->getSkinnedAnim().getSkinnedMesh()->getAnimMap().find("Stand04") != owner->getSkinnedAnim().getSkinnedMesh()->getAnimMap().end())
				owner->getSkinnedAnim().Play("Stand04", 0.5f);
			else
				owner->getSkinnedAnim().Play("Stand01", 0.5f);
			break;
		}
	}
	
	//만약 플레이어가 없는 상태라면 그냥 계속 진행하자.
	if (playerObject == nullptr) return LHS::ACTIONRESULT::ACTION_STAND;

	//몬스터의 범위 박스에 케릭터가 오면 케릭터의 위치로 이동 - enemy설정이 필요함.
	float tempdistance = 0;
	tempdistance = D3DXVec3Length(&(temp->getRegenPosition() - playerObject->_transform->GetWorldPosition()));
	
	if (tempdistance - Gap <= PLAYERDISTANCE) return LHS::ACTIONRESULT::ACTION_MOVE;
//	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
//	{
//		if (deleGate) deleGate->OnActionFinish(this, true);
////		owner->getSkinnedAnim().Stop();
//		return LHS::ACTIONRESULT::ACTION_MOVE;
//	}

	//내가 공격을 받았나?
	/*if(PLAYERMANAGER->get)
	{
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
