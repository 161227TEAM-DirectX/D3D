#include "stdafx.h"
#include "bossActionLanding.h"


bossActionLanding::bossActionLanding()
{
}


bossActionLanding::~bossActionLanding()
{
}

int bossActionLanding::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_48");
	owner->_transform->SetWorldPosition(10.0f, 70.0f, 10.0f);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionLanding::Update()
{
	//제자리 날기 모션 일경우 내려오며 일정 거리가 성립되면 모션을 변경하는 코드
	string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	if (!strcmp("Animation_48", temp.c_str()))
	{
		owner->_transform->MovePositionSelf(0.0f, -0.4f, 0.0f);
		float tempY = rand->getHeight(owner->_transform->GetWorldPosition().x, owner->_transform->GetWorldPosition().z) + 5.2f;

		if (owner->_transform->GetWorldPosition().y < tempY)
		{
			owner->getSkinnedAnim().Play("Animation_43");
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}
	}

	temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	if (!strcmp("Animation_43", temp.c_str()))
	{
		float tempY = rand->getHeight(owner->_transform->GetWorldPosition().x, owner->_transform->GetWorldPosition().z);

		if (tempY >= owner->_transform->GetWorldPosition().y)
		{
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
			{
				D3DXVECTOR3 temp = owner->_transform->GetWorldPosition();
				temp.y = tempY;
				owner->_transform->SetWorldPosition(temp);

				owner->getSkinnedAnim().Play("Animation_13", 1.0f);
			}
		}
		else
		{
			owner->_transform->MovePositionSelf(0.0f, -0.4f, 0.0f);
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
