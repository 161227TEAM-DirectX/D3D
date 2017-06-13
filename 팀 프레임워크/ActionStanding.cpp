#include "stdafx.h"
#include "ActionStanding.h"


ActionStanding::ActionStanding()
	:Action(), PassedTime(0.0f)
{
}


ActionStanding::~ActionStanding()
{
}

int ActionStanding::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;
//	temp.setBound(&owner->_skTransform->GetWorldPosition(), &D3DXVECTOR3(RANGE, RANGE, RANGE));
	owner->getSkinnedAnim().Play("Stand01");
	PassedTime = 0.0f;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionStanding::Update()
{
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//for (int i = 0; i < object->size(); i++)
	//{
	//	if (PHYSICSMANAGER->isOverlap(owner->_skTransform, &temp, enemy->_skTransform, &enemy->_boundBox))
	//	{
	//		path->FindPath(enemy->_transform->GetWorldPosition(), owner->_skTransform->GetWorldPosition());
	//		owner->setNextAction(path->OptimizedAction(*owner, rand, (*object), owner->_skTransform->GetWorldPosition(), enemy->_transform->GetWorldPosition()));
	//		if (deleGate) deleGate->OnActionFinish(this, true);

	//		return;
	//	}
	//}

	//for (int i = 0; i < object->size(); i++)
	//{
	//	if (PHYSICSMANAGER->isOverlap(owner->_skTransform, &temp, (*object)[i]->_transform, &(*object)[i]->_boundBox))
	//	{
	//		rand->getDijkstra().FindPath((*object)[i]->_transform->GetWorldPosition(), owner->_skTransform->GetWorldPosition());
	//		owner->setNextAction(rand->getDijkstra().OptimizedAction(*owner, rand, (*object), owner->_skTransform->GetWorldPosition(), (*object)[i]->_transform->GetWorldPosition()));
	//		//path->FindPath((*object)[i]->_transform->GetWorldPosition(), owner->_skTransform->GetWorldPosition());
	//		//owner->setNextAction(path->OptimizedAction(*owner, rand, (*object), owner->_skTransform->GetWorldPosition(), (*object)[i]->_transform->GetWorldPosition()));
	//		if (deleGate) deleGate->OnActionFinish(this, true);

	//		return;
	//	}
	//}

	//owner는 baseobject클래스이고 monster클래스가 필요하기에 타입 캐스팅.
	monster* temp = dynamic_cast<monster*>(owner);
	
	//몬스터의 범위 박스에 케릭터가 오면 케릭터의 위치로 이동 - enemy설정이 필요함.
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
	{
		if (deleGate) deleGate->OnActionFinish(this, true);
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}

	//내가 공격을 받았나?
	/*if(충돌처리 확인 구문)
	{
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}*/

	//내가 스턴 공격을 받았나?
	/*
	if(스턴공격 확인 구문)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	//PassedTime += _timeDelta;
	//if (PassedTime >= actionTime)
	//{
	//	if (deleGate) deleGate->OnActionFinish(this, true);

	//	return LHS::ACTIONRESULT::ACTION_FINISH;
	//}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
