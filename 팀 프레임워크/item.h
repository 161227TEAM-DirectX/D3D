#pragma once

enum ITEMKIND{EMPTY = 0, WEAPON, ARMOR , HPMEDICINE , MPMEDICINE};

struct ITEMINFOMATION
{
	int price;              //����
	int attack;            //�ɷ�ġ
	int armorAbility;              
	int hpAbility;
	int mpAbility;
	int medicineCount;
	int force;
	int type;               //����
	int number;             //������ �����ѹ�
};

struct ITEMIMAGE
{
	RECT rc1, rc2;         //�������̶� �浹üũ
	LPDIRECT3DTEXTURE9 tex;//������ �̹���
	bool check;             //������ üũ ����             
	int number;            //�����ѹ�
	int kind;
};

class item
{
public:
	item();
	~item();
};

