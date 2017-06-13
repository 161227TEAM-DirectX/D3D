#include "stdafx.h"
#include "bossActionControl.h"
#include "bossMonster.h"

bossActionControl::bossActionControl(bossMonster* temp)
	:linkBoss(temp)
{
}


bossActionControl::~bossActionControl()
{
	linkBoss = nullptr;
}

void bossActionControl::switchState(LHS::ACTIONRESULT& result)
{
	switch (result)
	{
	case LHS::ACTION_ATT:
		break;
	case LHS::ACTION_DIE:
		break;
	case LHS::ACTION_FAIL:
		break;
	case LHS::ACTION_FINISH:
		break;
	case LHS::ACTION_MOVE:
		break;
	case LHS::ACTION_NONE:
		break;
	case LHS::ACTION_PLAY:
		return;
	case LHS::ACTION_REMOVE:
		break;
	}
}

void bossActionControl::Init(Action *& CurrAction, LHS::ACTIONRESULT& result)
{
<<<<<<< HEAD
	CurrAction = new bossActionFly;
=======
	CurrAction = new bossActionSkillFlyStandingFire;
>>>>>>> d6e334270052364b68749c2834fb5bad8b2deb60
	CurrAction->setOwner(linkBoss);
	CurrAction->setObject(&linkBoss->getObject());
	CurrAction->setRand(linkBoss->getTerrain());
	CurrAction->setEnemy(&linkBoss->getPlayer());
	result = (LHS::ACTIONRESULT)CurrAction->Start();
}
