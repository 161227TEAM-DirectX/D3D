#include "stdafx.h"
#include "bossActionFlyDie.h"


bossActionFlyDie::bossActionFlyDie()
	:Action()
{
}


bossActionFlyDie::~bossActionFlyDie()
{
}

int bossActionFlyDie::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	//���������� ���ݸ�� �ƹ��ų� ����.
	owner->getSkinnedAnim().Play("Animation_31");

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionFlyDie::Update()
{
	string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	if (!strcmp("Animation_31", temp.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
		{
			owner->getSkinnedAnim().Play("Animation_27");
		}
	}

	if (!strcmp("Animation_27", temp.c_str()))
	{
		float tempY = rand->getHeight(owner->_transform->GetWorldPosition().x, owner->_transform->GetWorldPosition().z);
		if (owner->_transform->GetWorldPosition().y < tempY + 5.0f)
		{
			owner->getSkinnedAnim().Play("Animation_30");
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
