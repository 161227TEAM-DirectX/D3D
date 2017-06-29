#pragma once
#include "item.h"
class weapon : public item
{
private:
	//������ ����
	ITEMINFOMATION _weapon;
	vector<ITEMINFOMATION> _vWeapon;
	//������ ����
	ITEMIMAGE _weaponRender;
	vector<ITEMIMAGE> _vWeaponRender;
	
public:
	void setingItem();
	void setingItemRender();
    //���������� get
	vector<ITEMINFOMATION> getVweapon() { return _vWeapon; }
	//�����۷���  get
	vector<ITEMIMAGE> getVweaponRender() { return _vWeaponRender; }
	//�����۷��� set
	void setVweaponRender(ITEMIMAGE& vWeaponRender) { _vWeaponRender.push_back(vWeaponRender); }

	weapon(); 
	~weapon();
};

