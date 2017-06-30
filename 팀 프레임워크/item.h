#pragma once

enum ITEMKIND{EMPTY = 0, WEAPON, ARMOR , HPMEDICINE , MPMEDICINE};

struct ITEMINFOMATION
{
	int price;              //가격
	int attack;            //능력치
	int armorAbility;              
	int hpAbility;
	int mpAbility;
	int medicineCount;
	int force;
	int type;               //유형
	int number;             //아이템 고유넘버
};

struct ITEMIMAGE
{
	RECT rc1, rc2;         //아이템이랑 충돌체크
	LPDIRECT3DTEXTURE9 tex;//아이템 이미지
	bool check;             //아이템 체크 영향             
	int number;            //고유넘버
	int kind;
};

class item
{
public:
	item();
	~item();
};

