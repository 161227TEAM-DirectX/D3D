#pragma once
#include "gameNode.h"
#include "singletonBase.h"


enum PL_STATE
{
	P_STAND = 0,
	P_RUN,
	P_MOVE,
	P_READYTOATTACK,
	P_ATTACK,
	P_ATTACK2,
	P_ATTACK3,
	P_ATTACK4,
	P_ATTACK5,
	P_READYSPELL,
	P_CASTSPELL,
	P_READYOMNI,
	P_CASTOMNI,
	P_JUMPUP,
	P_JUMP,
	P_JUMPDOWN,
	P_STUN,
	P_DEATH,
	P_MOUNT,
	P_WALKBACK,
	P_DAMAGED,
	P_COMBO1,
	P_COMBO2,
	P_COMBO3,
	P_COMBO4,
	P_END
};

enum PL_WEAPON
{
	W_NONE = 0,
	W_WOOD,
	W_BROAD,
	W_KATANA,
	W_DEAMON,
	W_BLACK_WING,
	W_END
};

enum PL_ARMOR
{
	A_NONE = 0,
	A_ROBE,
	A_LEATHER,
	A_PLATE,
	A_END
};

enum PL_SHIELD
{
	SH_NONE = 0,
	SH_BUCKLER,
	SH_BRONZE,
	SH_KITE,
	SH_SPIKE,
	SH_CROSS,
	SH_END
};

class xPlayerStatus : public singletonBase<xPlayerStatus>
{
private:
	SYNTHESIZE(int, _lv, Lv);
	SYNTHESIZE(int, _att, att);
	SYNTHESIZE(int, _mAtt, mAtt);
	SYNTHESIZE(int, _def, Def);
	SYNTHESIZE(int, _mDef, mDef);
	SYNTHESIZE(float, _crit, Crit);
	SYNTHESIZE(int, _hp, Hp);
	SYNTHESIZE(int, _mp, Mp);
	SYNTHESIZE(PL_WEAPON, _weapon, Weapon);
	SYNTHESIZE(PL_ARMOR, _armor, Armor);
	SYNTHESIZE(PL_SHIELD, _shield, Shield);	
	SYNTHESIZE(int, _soul, Soul);
	SYNTHESIZE(int, _gold, Gold);
	SYNTHESIZE(D3DXVECTOR3, _pos, Pos);

	int _totalAtt;//기본 + 무기 합산 물리 공격력
	int _totalmAtt;//기본 + 무기 합산 마법 공격력
	int _totalDef;//기본 + 방어구 합산 물리 방어력
	int _totalmDef;//기본 + 방어구 합산 마법 방어력

public:
	xPlayerStatus() {};
	~xPlayerStatus() {};
};