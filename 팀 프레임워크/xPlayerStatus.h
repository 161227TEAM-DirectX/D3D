#pragma once
<<<<<<< HEAD
#include "gameNode.h"
#include "singletonBase.h"
=======
#include "singletonBase.h"
#include "gameNode.h"
>>>>>>> d6e334270052364b68749c2834fb5bad8b2deb60

enum PL_WEAPON
{
	W_NONE = 0,
	W_BLACK_WING,
<<<<<<< HEAD
	W_��������,
=======
>>>>>>> d6e334270052364b68749c2834fb5bad8b2deb60
	W_END
};

enum PL_ARMOR
{
	A_NONE = 0,
<<<<<<< HEAD
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

	int _totalAtt;//�⺻ + ���� �ջ� ���� ���ݷ�
	int _totalmAtt;//�⺻ + ���� �ջ� ���� ���ݷ�
	int _totalDef;//�⺻ + �� �ջ� ���� ����
	int _totalmDef;//�⺻ + �� �ջ� ���� ����

public:
	xPlayerStatus() {};
	~xPlayerStatus() {};
};
=======
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

>>>>>>> d6e334270052364b68749c2834fb5bad8b2deb60
