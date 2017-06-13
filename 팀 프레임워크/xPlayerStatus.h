#pragma once
#include "gameNode.h"
#include "singletonBase.h"

enum PL_WEAPON
{
	W_NONE = 0,
	W_BLACK_WING,
	W_대충대충검,
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
class xPlayerStatus : public singletonBase<xPlayerStatus>
{
private:
	SYNTHESIZE(int, _lv, Lv);
	SYNTHESIZE(int, _att, att);
	SYNTHESIZE(int, _mAtt, mAtt);
	SYNTHESIZE(int, _def, Def);
	SYNTHESIZE(int, _mDef, mDef);
	SYNTHESIZE(int, _hp, Hp);
	SYNTHESIZE(int, _mp, Mp);
	SYNTHESIZE(PL_WEAPON, _weapon, Weapon);
	SYNTHESIZE(PL_ARMOR, _armor, Armor);
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