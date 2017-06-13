#pragma once
#include "bossActionAttack.h"
#include "bossActionCinema.h"
#include "bossActionMove.h"
#include "bossActionStanding.h"
#include "bossActionFly.h"
<<<<<<< HEAD
#include "bossActionLanding.h"
#include "bossActionFlyDie.h"
#include "bossActionDie.h"
=======
>>>>>>> db041f6741b33c85b3cac01450c2fbaa9cc8e6d7
#include "bossActionSkill.h"
#include "bossActionSkillFire.h"
#include "bossActionSkillBattleRoar.h"
#include "bossActionSkillTailAtt.h"
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

