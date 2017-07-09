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
	P_ATTACK6,
	P_WHIRLWIND,
	P_SLAM,
	P_BATTLEROAR,
	P_SITDOWN,
	P_SIT,
	P_SITUP,
	P_SLEEPDOWN,
	P_SLEEP,
	P_SLEEPUP,
	P_SWIM,
	P_SWIMIDLE,
	P_SWIMBACK,
	P_READYSPELL,
	P_CASTSPELL,
	P_READYOMNI,
	P_CASTOMNI,
	P_JUMPUP,
	P_JUMP,
	P_JUMPDOWN,
	P_STUN,
	P_DEATH,
	P_MOUNT_S,
	P_MOUNT_R,
	P_MOUNT_WB,
	P_WALKBACK,
	P_DAMAGED,
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
	SYNTHESIZE(int, _orgAtt, orgAtt);
	SYNTHESIZE(int, _mAtt, mAtt);
	SYNTHESIZE(int, _orgMAtt, orgMAtt);
	SYNTHESIZE(int, _def, Def);
	SYNTHESIZE(int, _orgDef, _orgDef);
	SYNTHESIZE(int, _mDef, mDef);
	SYNTHESIZE(int, _orgMDef, orgMDef);
	SYNTHESIZE(float, _crit, Crit);
	SYNTHESIZE(int, _hp, Hp);
	SYNTHESIZE(int, _MaxHp, MaxHp);
	SYNTHESIZE(int, _mp, Mp);
	SYNTHESIZE(int, _MaxMp, MaxMp);
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
	xPlayerStatus() { 
		_pos = { 0,0,0 };
		_armor = A_PLATE;
		_orgAtt = 10000;
		_att = _orgAtt;
		_MaxHp = 100000;
		_hp = _MaxHp;
		_crit = 20.0f;
	};
	~xPlayerStatus() {};


};