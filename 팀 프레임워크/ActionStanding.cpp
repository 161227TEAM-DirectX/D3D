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
	owner->getSkinnedAnim().Play("Stand01");
	PassedTime = 0.0f;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionStanding::Update()
{
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//owner�� baseobjectŬ�����̰� monsterŬ������ �ʿ��ϱ⿡ Ÿ�� ĳ����.
	monster* temp = dynamic_cast<monster*>(owner);

	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
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
	
	//������ ���� �ڽ��� �ɸ��Ͱ� ���� �ɸ����� ��ġ�� �̵� - enemy������ �ʿ���.
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
	{
		if (deleGate) deleGate->OnActionFinish(this, true);
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}

	//���� ������ �޾ҳ�?
	/*if(PLAYERMANAGER->get)
	{
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
