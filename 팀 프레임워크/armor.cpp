#include "stdafx.h"
#include "armor.h"

armor::armor() { setingItem(); setingItemRender(); }
armor::~armor() {}

void armor::setingItem()
{
	//���� (1)
	_armor.number  = 1;
	_armor.attack = 0;
	_armor.armorAbility = 10;
	_armor.hpAbility = 0;
	_armor.mpAbility = 0;
	_armor.price = 1000;
	_armor.force = 0;
	_armor.type = ITEMKIND::ARMOR;
	_vArmor.push_back(_armor);

	//���� (2)
	_armor.number = 2;
	_armor.attack = 0;
	_armor.armorAbility = 20;
	_armor.hpAbility = 0;
	_armor.mpAbility = 0;
	_armor.price = 2000;
	_armor.force = 0;
	_armor.type = ITEMKIND::ARMOR;
	_vArmor.push_back(_armor);

	//���� (3)  v
	_armor.number = 3;
	_armor.attack = 0;
	_armor.armorAbility = 30;
	_armor.hpAbility = 0;
	_armor.mpAbility = 0;
	_armor.price = 3000;
	_armor.force = 0;
	_armor.type = ITEMKIND::ARMOR;
	_vArmor.push_back(_armor);

	//���� (4)
	_armor.number = 4;
	_armor.attack = 0;
	_armor.armorAbility = 40;
	_armor.hpAbility = 0;
	_armor.mpAbility = 0;
	_armor.price = 4000;
	_armor.force = 0;
	_armor.type = ITEMKIND::ARMOR;
	_vArmor.push_back(_armor);

	//���� (5)
	_armor.number = 5;
	_armor.attack = 0;
	_armor.armorAbility = 50;
	_armor.hpAbility = 0;
	_armor.mpAbility = 0;
	_armor.price = 5000;
	_armor.force = 0;
	_armor.type = ITEMKIND::ARMOR;
	_vArmor.push_back(_armor);

}

void armor::setingItemRender()
{
	//������---------------------
	//��(1)
	_armorRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/��1.png");
	_armorRender.kind = ITEMKIND::ARMOR;
	_vArmorRender.push_back(_armorRender);

	//��(2)
	_armorRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/��2.png");
	_armorRender.kind = ITEMKIND::ARMOR;
	_vArmorRender.push_back(_armorRender);

	//��(3)
	_armorRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/��3.png");
	_armorRender.kind = ITEMKIND::ARMOR;
	_vArmorRender.push_back(_armorRender);

	//��(4)
	_armorRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/��4.png");
	_armorRender.kind = ITEMKIND::ARMOR;
	_vArmorRender.push_back(_armorRender);

	//��(5)
	_armorRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/��5.png");
	_armorRender.kind = ITEMKIND::ARMOR;
	_vArmorRender.push_back(_armorRender);
}

