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
//	owner->getSkinnedAnim().SetPlaySpeed(0.5f);
	SOUNDMANAGER->play("º¸½º¼û¼Ò¸®2", 0.5f);

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionCinema::Update()
{
	passedTime += 0.01f;
	//¼ö¸é Á¾·á
	if (actionTime < passedTime)
	{
		string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
		if (!strcmp("Animation_13", temp.c_str()))
		{
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.2f && isShout)
			{
				SOUNDMANAGER->play("»þ¿ìÆÃ4");
				isShout = false;
			}

			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.95f)
			{
				if (deleGate) deleGate->OnActionFinish(this, true);
				SOUNDMANAGER->stop("»þ¿ìÆÃ4");
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		}

		if (!strcmp("Animation_61", temp.c_str()))
		{
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.90f)
			{
				SOUNDMANAGER->stop("°È±â");
				owner->getSkinnedAnim().Stop();
				owner->getSkinnedAnim().Play("Animation_13", 0.3f);
			}

		}

		if (!strcmp("Animation_62", temp.c_str()))
		{
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.8f)
			{
				owner->getSkinnedAnim().Play("Animation_61", 1.0f);
				SOUNDMANAGER->stop("º¸½º¼û¼Ò¸®2");
				SOUNDMANAGER->play("°È±â");
				SOUNDMANAGER->setMusicSpeed("°È±â", 0.7f);
			}

		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
