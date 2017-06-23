#include "stdafx.h"
#include "bossActionCinema.h"


bossActionCinema::bossActionCinema()
	:Action(), actionTime(5.0f), passedTime(0.0f), isShout(true)
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
	SOUNDMANAGER->play("º¸½º¼û¼Ò¸®2", 0.5f);

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
				SOUNDMANAGER->stop("»þ¿ìÆÃ4");
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}

			if (!strcmp("Animation_61", temp.c_str()))
			{
				owner->getSkinnedAnim().Play("Animation_13", 1.0f);
				owner->getSkinnedAnim().SetPlaySpeed(0.5f);
				//SOUNDMANAGER->play("»þ¿ìÆÃ4");
				SOUNDMANAGER->stop("°È±â");
			}

			if (!strcmp("Animation_62", temp.c_str()))
			{
				owner->getSkinnedAnim().Play("Animation_61", 1.0f);
				SOUNDMANAGER->stop("º¸½º¼û¼Ò¸®2");
				SOUNDMANAGER->play("°È±â");
				SOUNDMANAGER->setMusicSpeed("°È±â", 0.8F);
			}
		}

		
		if (!strcmp("Animation_13", owner->getSkinnedAnim().getAnimationSet()->GetName()))
		{
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.5f && isShout)
			{
				SOUNDMANAGER->play("»þ¿ìÆÃ4");
				isShout = false;
			}
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
