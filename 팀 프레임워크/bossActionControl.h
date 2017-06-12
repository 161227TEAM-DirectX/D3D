#pragma once
#include "bossActionAttack.h"
#include "bossActionCinema.h"
#include "bossActionMove.h"
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

