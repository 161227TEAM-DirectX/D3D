#pragma once
#include "singletonBase.h"
#include "gameNode.h"

enum PL_WEAPON
{
	W_NONE = 0,
	W_BLACK_WING,
	W_END
};

enum PL_ARMOR
{
	A_NONE = 0,
	A_LEATHER,
	A_ROBE,
	A_PLATE,
	A_END
};


class xPlayerStatus : public singletonBase<xPlayerStatus>
{
private:
	float _exp;
	int _att;
	int _def;
	int _hp;
	int _mp;
	

public:
	xPlayerStatus();
	~xPlayerStatus();

	

	int& getHp() { return _hp; }
	int& getMp() { return _mp; }
};

