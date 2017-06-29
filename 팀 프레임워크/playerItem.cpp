#include "stdafx.h"
#include "playerItem.h"
#include "inven.h"
#include "shop.h"

HRESULT playerItem::init(void)
{
	_pick.first = false;
	_statItemWeapon.check = false;
	_statItemArmor.check = false;
	_pick.second = { 0,0 };

	_tempItem = 0;

	playerAttack = 300;
	playerArmor = 200;

	return S_OK;
}

void playerItem::release(void)
{
}

void playerItem::update(void)
{
	if (_playerWeaponItemRender.size() != 0)
	{
		for (int i = 0; i < _playerWeaponItemRender.size(); i++)
		{
			//웨폰장착
			if (PtInRect(&_playerWeaponItemRender[i].rc2, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
				{
					_temp = _playerWeaponItemRender[i];
					_playerInfomation = _playerWeaponItem[i];

					_tempItem = i;
					_pick.second = { _playerWeaponItemRender[i].rc2.left,_playerWeaponItemRender[i].rc2.top };
					_pick.first = true;

					pair<bool, POINT> temp;
					temp.first = false;
					_inven->setPick(temp);
					_shop->setPick(temp);

					//스탯창
					_statItemWeapon.check = true;

				}
			}
			else
			{
				//스탯창
				_statItemWeapon.check = false;
			}
		}
	}

	if (_playerArmorItemRender.size() != 0)
	{
		for (int i = 0; i < _playerArmorItemRender.size(); i++)
		{
			//방어장착
			if (PtInRect(&_playerArmorItemRender[i].rc2, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
				{
					_temp = _playerArmorItemRender[i];
					_playerInfomation = _playerArmorItem[i];

					_tempItem = i;
					_pick.second = { _playerArmorItemRender[i].rc2.left,_playerArmorItemRender[i].rc2.top };
					_pick.first = true;

					pair<bool, POINT> temp;
					temp.first = false;
					_inven->setPick(temp);
					_shop->setPick(temp);

					//스탯창
					_statItemArmor.check = true;
				}
			}
			else
			{
				//스탯창
				_statItemArmor.check = false;
			}
		}
	}

}

void playerItem::render(void)
{
	//무기아이템
	if (_playerWeaponItemRender.size() != 0)
	{
		for (int i = 0; i < _playerWeaponItemRender.size(); i++)
		{
			_playerWeaponItemRender[i].rc2 = { _inven->getInvenBack().rc2.left + 198,_inven->getInvenBack().rc2.top + 234,_playerWeaponItemRender[i].rc2.left + 53,_playerWeaponItemRender[i].rc2.top + 51};
			SPRITEMANAGER->renderRectTexture(_playerWeaponItemRender[i].tex, &_playerWeaponItemRender[i].rc1, &_playerWeaponItemRender[i].rc2, 0, 0, 64, 64, _inven->getInvenBack().rc2.left + 198, _inven->getInvenBack().rc2.top + 234);
		}
	}

	//방어아이템
	if (_playerArmorItemRender.size() != 0)
	{
		for (int i = 0; i < _playerArmorItemRender.size(); i++)
		{
			_playerArmorItemRender[i].rc2 = { _inven->getInvenBack().rc2.left + 253,_inven->getInvenBack().rc2.top + 234,_playerArmorItemRender[i].rc2.left + 53,_playerArmorItemRender[i].rc2.top + 51 };
			SPRITEMANAGER->renderRectTexture(_playerArmorItemRender[i].tex, &_playerArmorItemRender[i].rc1, &_playerArmorItemRender[i].rc2, 0, 0, 64, 64, _inven->getInvenBack().rc2.left + 253, _inven->getInvenBack().rc2.top + 234);
		}
	}

	if (_pick.first == true)
	{
		LPDIRECT3DTEXTURE9 temp = RM_TEXTURE->getResource("ResourceUI/inven/shop/픽1.png");
		
		if (_playerWeaponItemRender.size() != 0)
		{
			for (int i = 0; i < _playerWeaponItemRender.size(); i++)
			{
				SPRITEMANAGER->renderRectTexture(temp, &_playerWeaponItemRender[i].rc1, &_playerWeaponItemRender[i].rc2, 0, 0, 64, 64, _pick.second.x, _pick.second.y);
			}
		}

		if (_playerArmorItemRender.size() != 0)
		{
			for (int i = 0; i < _playerArmorItemRender.size(); i++)
			{
				SPRITEMANAGER->renderRectTexture(temp, &_playerArmorItemRender[i].rc1, &_playerArmorItemRender[i].rc2, 0, 0, 64, 64, _pick.second.x, _pick.second.y);
			}
		}
	}

	if (_statItemWeapon.check == true)
	{
		_statItemWeapon.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/정보창.png");
		SPRITEMANAGER->renderRectTexture(_statItemWeapon.tex, &_statItemWeapon.rc1, &_statItemWeapon.rc2, 0, 0, 256, 256, GetMousePos().x, GetMousePos().y);

		//인벤정보창
		char str1[128];
		char str2[128];
		char str3[128];
		sprintf(str1, "%d", _playerInfomation.attack);
		sprintf(str2, "%d", _playerInfomation.armorAbility);
		sprintf(str3, "%d", _playerInfomation.price);
		FONTMANAGER->fontOut(str1, GetMousePos().x + 102, GetMousePos().y + 58, D3DCOLOR_XRGB(255, 255, 255));
		FONTMANAGER->fontOut(str2, GetMousePos().x + 110, GetMousePos().y + 84, D3DCOLOR_XRGB(255, 255, 255));
		FONTMANAGER->fontOut(str3, GetMousePos().x + 90, GetMousePos().y + 111, D3DCOLOR_XRGB(255, 255, 255));
		FONTMANAGER->fontOut("+" + to_string(_playerInfomation.force), GetMousePos().x + 105, GetMousePos().y + 135, D3DCOLOR_XRGB(255, 255, 255));
	}

	if (_statItemArmor.check == true)
	{
		_statItemArmor.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/정보창.png");
		SPRITEMANAGER->renderRectTexture(_statItemArmor.tex, &_statItemArmor.rc1, &_statItemArmor.rc2, 0, 0, 256, 256, GetMousePos().x, GetMousePos().y);

		//인벤정보창
		char str1[128];
		char str2[128];
		char str3[128];
		sprintf(str1, "%d", _playerInfomation.attack);
		sprintf(str2, "%d", _playerInfomation.armorAbility);
		sprintf(str3, "%d", _playerInfomation.price);
		FONTMANAGER->fontOut(str1, GetMousePos().x + 110, GetMousePos().y + 58, D3DCOLOR_XRGB(255, 255, 255));
		FONTMANAGER->fontOut(str2, GetMousePos().x + 102, GetMousePos().y + 84, D3DCOLOR_XRGB(255, 255, 255));
		FONTMANAGER->fontOut(str3, GetMousePos().x + 90, GetMousePos().y + 111, D3DCOLOR_XRGB(255, 255, 255));
		FONTMANAGER->fontOut("+" + to_string(_playerInfomation.force), GetMousePos().x + 105, GetMousePos().y + 135, D3DCOLOR_XRGB(255, 255, 255));
	}

	char CharAttack[128];
	char CharArmor[128];

	sprintf(CharAttack, "%d", playerAttack);
	sprintf(CharArmor, "%d", playerArmor);

	FONTMANAGER->fontOut(CharAttack, _inven->getInvenBack().rc2.left + 265, _inven->getInvenBack().rc2.top + 140, D3DCOLOR_XRGB(255, 255, 255));
	FONTMANAGER->fontOut(CharArmor, _inven->getInvenBack().rc2.left + 265, _inven->getInvenBack().rc2.top + 175, D3DCOLOR_XRGB(255, 255, 255));

}

void playerItem::removePlayerItem(int num, ITEMIMAGE temp)
{ 
	if (temp.kind == ITEMKIND::WEAPON)
	{
		_playerWeaponItemRender.erase(_playerWeaponItemRender.begin() + num);
	}

	if (temp.kind == ITEMKIND::ARMOR)
	{
		_playerArmorItemRender.erase(_playerArmorItemRender.begin() + num);
	}

}

void playerItem::removePlayerItemInformation(int num, ITEMINFOMATION temp)
{
	if (temp.type == ITEMKIND::WEAPON)
	{
		_playerWeaponItem.erase(_playerWeaponItem.begin() + num);
	}

	if (temp.type == ITEMKIND::ARMOR)
	{
		_playerArmorItem.erase(_playerArmorItem.begin() + num);
	}
}

void playerItem::removePlaterInformation(ITEMINFOMATION temp)
{
	if (temp.type == ITEMKIND::WEAPON)
	{
		playerAttack = playerAttack - _playerInfomation.attack;
	}

	if (temp.type == ITEMKIND::ARMOR)
	{
		playerArmor = playerArmor - _playerInfomation.armorAbility;
	}
}
