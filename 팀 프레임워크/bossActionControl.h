#pragma once
#include "bossActionAttack.h"
#include "bossActionCinema.h"
#include "bossActionMove.h"
#include "bossActionStanding.h"
#include "bossActionFly.h"
<<<<<<< HEAD
=======
#include "bossActionLanding.h"
>>>>>>> d6e334270052364b68749c2834fb5bad8b2deb60
#include "bossActionSkill.h"
#include "bossActionSkillFire.h"
#include "bossActionSkillBattleRoar.h"
#include "bossActionSkillTailAtt.h"
<<<<<<< HEAD
=======
#include "bossActionSkillFlyStandingFire.h"
>>>>>>> d6e334270052364b68749c2834fb5bad8b2deb60
class bossMonster;
class bossActionControl
{
private:
	bossMonster* linkBoss;
public:
	bossActionControl(bossMonster* temp);
	~bossActionControl();

	void switchState(LHS::ACTIONRESULT& result);
	void Init(Action*& CurrAction, LHS::ACTIONRESULT& result);
};

