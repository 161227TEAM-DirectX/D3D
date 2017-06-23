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
	SOUNDMANAGER->play("�������Ҹ�2", 0.5f);

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
				SOUNDMANAGER->stop("������4");
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}

			if (!strcmp("Animation_61", temp.c_str()))
			{
				owner->getSkinnedAnim().Play("Animation_13", 1.0f);
				owner->getSkinnedAnim().SetPlaySpeed(0.5f);
				//SOUNDMANAGER->play("������4");
				SOUNDMANAGER->stop("�ȱ�");
			}

			if (!strcmp("Animation_62", temp.c_str()))
			{
				owner->getSkinnedAnim().Play("Animation_61", 1.0f);
				SOUNDMANAGER->stop("�������Ҹ�2");
				SOUNDMANAGER->play("�ȱ�");
				SOUNDMANAGER->setMusicSpeed("�ȱ�", 0.8F);
			}
		}

		
		if (!strcmp("Animation_13", owner->getSkinnedAnim().getAnimationSet()->GetName()))
		{
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.5f && isShout)
			{
				SOUNDMANAGER->play("������4");
				isShout = false;
			}
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
