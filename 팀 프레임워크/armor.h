#pragma once
#include "item.h"
class armor : public item
{
private:
	//����������
	ITEMINFOMATION _armor;
	vector<ITEMINFOMATION> _vArmor;
	//�����۷���
	ITEMIMAGE _armorRender;
	vector<ITEMIMAGE> _vArmorRender;

public:
	void setingItem();

	void setingItemRender();
    //�Ѱ��� get
	vector<ITEMINFOMATION> getVarmor() { return _vArmor; }

	vector<ITEMIMAGE> getVarmorRender() { return _vArmorRender; }

	armor(); 
	~armor();
};

