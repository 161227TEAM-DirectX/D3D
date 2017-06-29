#pragma once
#include "item.h"
class armor : public item
{
private:
	//아이템정보
	ITEMINFOMATION _armor;
	vector<ITEMINFOMATION> _vArmor;
	//아이템렌더
	ITEMIMAGE _armorRender;
	vector<ITEMIMAGE> _vArmorRender;

public:
	void setingItem();

	void setingItemRender();
    //넘겨줄 get
	vector<ITEMINFOMATION> getVarmor() { return _vArmor; }

	vector<ITEMIMAGE> getVarmorRender() { return _vArmorRender; }

	armor(); 
	~armor();
};

