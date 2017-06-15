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
		linkBoss->setNextAction(new bossActionAttack);
		linkBoss->getNextAction().setEnemy(linkBoss->getPlayer());
		linkBoss->getNextAction().setOwner(*linkBoss);
		linkBoss->getNextAction().setRand(linkBoss->getTerrain());
		break;
	case LHS::ACTION_DIE:
		linkBoss->setNextAction(new bossActionDie);
		linkBoss->getNextAction().setEnemy(linkBoss->getPlayer());
		linkBoss->getNextAction().setOwner(*linkBoss);
		linkBoss->getNextAction().setRand(linkBoss->getTerrain());
		break;
	case LHS::ACTION_FAIL:
		MessageBox(nullptr, "문제가 발생했어요 뿌우~", "ㅋㅋ", MB_OK);
		exit(0);
		break;
	case LHS::ACTION_FINISH:
		MessageBox(nullptr, "문제가 발생했어요 뿌우~", "ㅋㅋ", MB_OK);
		linkBoss->setNextAction(new bossActionMove);
		linkBoss->getNextAction().setEnemy(linkBoss->getPlayer());
		linkBoss->getNextAction().setOwner(*linkBoss);
		linkBoss->getNextAction().setRand(linkBoss->getTerrain());
		break;
	case LHS::ACTION_MOVE:
		linkBoss->setNextAction(new bossActionMove);
		linkBoss->getNextAction().setEnemy(linkBoss->getPlayer());
		linkBoss->getNextAction().setOwner(*linkBoss);
		linkBoss->getNextAction().setRand(linkBoss->getTerrain());
		break;
	case LHS::ACTION_NONE:
		break;
	case LHS::ACTION_PLAY:
		return;
	case LHS::ACTION_REMOVE:
		break;
	case LHS::ACTION_SKILL_TAIL:
		linkBoss->setNextAction(new bossActionSkillTailAtt);
		linkBoss->getNextAction().setEnemy(linkBoss->getPlayer());
		linkBoss->getNextAction().setOwner(*linkBoss);
		linkBoss->getNextAction().setRand(linkBoss->getTerrain());
		break;
	case LHS::ACTION_SKILL_FIRE:
		linkBoss->setNextAction(new bossActionSkillFire);
		linkBoss->getNextAction().setEnemy(linkBoss->getPlayer());
		linkBoss->getNextAction().setOwner(*linkBoss);
		linkBoss->getNextAction().setRand(linkBoss->getTerrain());
		break;
	case LHS::ACTION_SKILL_BATTLE_ROAR:
		linkBoss->setNextAction(new bossActionSkillBattleRoar);
		linkBoss->getNextAction().setEnemy(linkBoss->getPlayer());
		linkBoss->getNextAction().setOwner(*linkBoss);
		linkBoss->getNextAction().setRand(linkBoss->getTerrain());
		break;
	}
}

void bossActionControl::Init(Action *& CurrAction, LHS::ACTIONRESULT& result)
{
	CurrAction = new bossActionCinema;
	CurrAction->setOwner(*linkBoss);
	CurrAction->setRand(linkBoss->getTerrain());
	CurrAction->setEnemy(linkBoss->getPlayer());
	result = (LHS::ACTIONRESULT)CurrAction->Start();
}
