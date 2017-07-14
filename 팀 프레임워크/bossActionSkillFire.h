#pragma once
#include "Action.h"
#include "bossMonster.h"

class damageText;

class bossActionSkillFire : public Action
{
private:
	float dotTime;
	boundBox breathRange;
	float yPosition;
	damageText* damage;
public:
	bossActionSkillFire();
	~bossActionSkillFire();

	//액션의 시작을 정의하는 함수 - 순수가상함수
	int Start() override;
	//액션을 실행하는 함수 - 순수가상함수
	int Update() override;
	void Render() override;
};

