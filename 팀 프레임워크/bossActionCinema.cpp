#include "stdafx.h"
#include "bossActionCinema.h"


bossActionCinema::bossActionCinema()
	:Action(), actionTime(5.0f), passedTime(0.0f)
{
}


bossActionCinema::~bossActionCinema()
{
}

int bossActionCinema::Start()
{
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_62");
	owner->getSkinnedAnim().SetPlaySpeed(0.5f);
	SOUNDMANAGER->play("�������Ҹ�1", 0.5f);

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionCinema::Update()
{
	passedTime += 0.01f;
	if (actionTime < passedTime)
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.8f)
		{
			string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
			if (!strcmp("Animation_13", temp.c_str()))
			{
				if (deleGate) deleGate->OnActionFinish(this, true);
				SOUNDMANAGER->stop("������");
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}

			if (!strcmp("Animation_61", temp.c_str()))
			{
				SOUNDMANAGER->stop("�������Ҹ�1");
				owner->getSkinnedAnim().Play("Animation_13", 1.0f);
				owner->getSkinnedAnim().SetPlaySpeed(0.5f);
				SOUNDMANAGER->play("������");
			}

			if(!strcmp("Animation_62", temp.c_str())) owner->getSkinnedAnim().Play("Animation_61", 1.0f);
		}
	}


	return LHS::ACTIONRESULT::ACTION_PLAY;
}
