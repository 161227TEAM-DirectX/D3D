#pragma once
#include "item.h"
class weapon : public item
{
private:
	//아이템 정보
	ITEMINFOMATION _weapon;
	vector<ITEMINFOMATION> _vWeapon;
	//아이템 렌더
	ITEMIMAGE _weaponRender;
	vector<ITEMIMAGE> _vWeaponRender;
	
public:
	void setingItem();
	void setingItemRender();
    //아이템정보 get
	vector<ITEMINFOMATION> getVweapon() { return _vWeapon; }
	//아이템렌더  get
	vector<ITEMIMAGE> getVweaponRender() { return _vWeaponRender; }
	//아이템렌더 set
	void setVweaponRender(ITEMIMAGE& vWeaponRender) { _vWeaponRender.push_back(vWeaponRender); }

	weapon(); 
	~weapon();
};

