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

	//owner�� baseobjectŬ�����̰� monsterŬ������ �ʿ��ϱ⿡ Ÿ�� ĳ����.
	monster* temp = dynamic_cast<monster*>(owner);

	//��������
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
	
	//���� �÷��̾ ���� ���¶�� �׳� ��� ��������.
	if (playerObject == nullptr) return LHS::ACTIONRESULT::ACTION_STAND;

	//������ ���� �ڽ��� �ɸ��Ͱ� ���� �ɸ����� ��ġ�� �̵� - enemy������ �ʿ���.
	float tempdistance = 0;
	tempdistance = D3DXVec3Length(&(temp->getRegenPosition() - playerObject->_transform->GetWorldPosition()));
	
	if (tempdistance - Gap <= PLAYERDISTANCE) return LHS::ACTIONRESULT::ACTION_MOVE;
//	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
//	{
//		if (deleGate) deleGate->OnActionFinish(this, true);
////		owner->getSkinnedAnim().Stop();
//		return LHS::ACTIONRESULT::ACTION_MOVE;
//	}

	//���� ������ �޾ҳ�?
	/*if(PLAYERMANAGER->get)
	{
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
