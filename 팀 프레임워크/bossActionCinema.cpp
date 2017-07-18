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
	SOUNDMANAGER->play("�������Ҹ�2", 0.5f);

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionCinema::Update()
{
	passedTime += 0.01f;
	//���� ����
	if (actionTime < passedTime)
	{
		string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
		if (!strcmp("Animation_13", temp.c_str()))
		{
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.2f && isShout)
			{
				SOUNDMANAGER->play("������4");
				isShout = false;
			}

			if (owner->getSkinnedAnim().getAnimationPlayFactor() > ANIMATIONENDTIME)
			{
				SOUNDMANAGER->stop("������4");
				SOUNDMANAGER->setMusicSpeed("�ȱ�", 1.0f);
				if(SOUNDMANAGER->isPlaySound("�ȱ�")) SOUNDMANAGER->stop("�ȱ�");
				if (SOUNDMANAGER->isPauseSound("�ȱ�")) SOUNDMANAGER->stop("�ȱ�");
				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		}

		if (!strcmp("Animation_61", temp.c_str()))
		{
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.90f)
			{
				SOUNDMANAGER->stop("�ȱ�");
				SOUNDMANAGER->setMusicSpeed("�ȱ�", 1.0f);
				owner->getSkinnedAnim().Stop();
				owner->getSkinnedAnim().Play("Animation_13", 0.3f);
			}

		}

		if (!strcmp("Animation_62", temp.c_str()))
		{
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.8f)
			{
				owner->getSkinnedAnim().Play("Animation_61", 1.0f);
				SOUNDMANAGER->stop("�������Ҹ�2");
				SOUNDMANAGER->play("�ȱ�");
				SOUNDMANAGER->setMusicSpeed("�ȱ�", 0.7f);
			}

		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
