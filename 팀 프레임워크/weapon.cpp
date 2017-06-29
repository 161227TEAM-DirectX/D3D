#include "stdafx.h"
#include "weapon.h"

weapon::weapon() { setingItem(); setingItemRender(); }
weapon::~weapon() {}

void weapon::setingItem()
{
	//公扁沥焊----------------------
	//公扁(1)
	_weapon.number = 1;
	_weapon.attack = 10;
	_weapon.armorAbility = 0;
	_weapon.hpAbility = 0;
	_weapon.mpAbility = 0;
	_weapon.price = 1000;
	_weapon.force = 1;
	_weapon.type = ITEMKIND::WEAPON;
	_vWeapon.push_back(_weapon);

	//公扁(2)
	_weapon.number = 2;
	_weapon.attack = 20;
	_weapon.armorAbility = 0;
	_weapon.hpAbility = 0;
	_weapon.mpAbility = 0;
	_weapon.price = 2000;
	_weapon.force = 1;
	_weapon.type = ITEMKIND::WEAPON;
	_vWeapon.push_back(_weapon);

	//公扁(3)
	_weapon.number = 3;
	_weapon.attack = 30;
	_weapon.armorAbility = 0;
	_weapon.hpAbility = 0;
	_weapon.mpAbility = 0;
	_weapon.price = 3000;
	_weapon.force = 1;
	_weapon.type = ITEMKIND::WEAPON;
	_vWeapon.push_back(_weapon);

	//公扁(4)
	_weapon.number = 4;
	_weapon.attack = 40;
	_weapon.armorAbility = 0;
	_weapon.hpAbility = 0;
	_weapon.mpAbility = 0;
	_weapon.price = 4000;
	_weapon.force = 1;
	_weapon.type = ITEMKIND::WEAPON;
	_vWeapon.push_back(_weapon);

	//公扁(5)
	_weapon.number = 5;
	_weapon.attack = 50;
	_weapon.armorAbility = 0;
	_weapon.hpAbility = 0;
	_weapon.mpAbility = 0;
	_weapon.price = 5000;
	_weapon.force = 1;
	_weapon.type = ITEMKIND::WEAPON;
	_vWeapon.push_back(_weapon);

	
	
}

void weapon::setingItemRender()
{
	//公扁坊歹---------------------
	//公扁(1)
	_weaponRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/公扁备1.png");
	_weaponRender.kind = ITEMKIND::WEAPON;
	_vWeaponRender.push_back(_weaponRender);

	//公扁(2)
	_weaponRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/公扁备2.png");
	_weaponRender.kind = ITEMKIND::WEAPON;
	_vWeaponRender.push_back(_weaponRender);

	//公扁(3)
	_weaponRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/公扁备3.png");
	_weaponRender.kind = ITEMKIND::WEAPON;
	_vWeaponRender.push_back(_weaponRender);

	//公扁(4)
	_weaponRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/公扁备4.png");
	_weaponRender.kind = ITEMKIND::WEAPON;
	_vWeaponRender.push_back(_weaponRender);

	//公扁(5)
	_weaponRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/公扁备5.png");
	_weaponRender.kind = ITEMKIND::WEAPON;
	_vWeaponRender.push_back(_weaponRender);
}

