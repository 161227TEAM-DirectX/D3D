#include "stdafx.h"
#include "shop.h"
#include "inven.h"
#include "playerItem.h"

HRESULT shop::init(void)
{
	_armor = new armor;
	_weapon = new weapon;


	//무기구
	for (int i = 0; i < _weapon->getVweaponRender().size(); i++)
	{
		_ShopWeaponRender[i].tex = _weapon->getVweaponRender()[i].tex;
		_ShopWeaponRender[i].kind = _weapon->getVweaponRender()[i].kind;
		_ShopWeaponRender[i].check = false;
		_ShopWeaponRender[i].number = 0;
	}

	//무기구 정보
	for (int i = 0; i < _weapon->getVweapon().size(); i++)
	{
		_ShopWeapon.push_back(_weapon->getVweapon()[i]);
	}

	//방어구
	for (int i = 0; i < _armor->getVarmorRender().size(); i++)
	{
		_ShopArmorRender[i].tex = _armor->getVarmorRender()[i].tex;
		_ShopArmorRender[i].kind = _armor->getVarmorRender()[i].kind;
		_ShopArmorRender[i].check = false;
		_ShopArmorRender[i].number = 0;
	}

	//방어구 정보
	for (int i = 0; i < _armor->getVarmor().size(); i++)
	{
		_ShopArmor.push_back(_armor->getVarmor()[i]);
	}

	//정보 temp값 초기화
	_tempInfomation.attack = 0;
	_tempInfomation.armorAbility = 0;
	_tempInfomation.number = 0;
	_tempInfomation.price = 0;
	_tempInfomation.type = 0;

	//사기,팔기 버튼
	for (int i = 0; i < 2; i++)
	{
		_ShopButton[0].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/상점버튼.png");
		_ShopButton[1].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/상점버튼.png");
		_ShopButton[i].check = false;
	}

    //선택버튼
	_pick.first = false;
	_pick.second = { 0,0 };

	return S_OK;
}

void shop::release(void)
{

}

void shop::update(void)
{
	this->shopPickUpdate();
}

void shop::render(void)
{
	//상점바탕UI
	_SHOP.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/상점바탕1.png");
	_SHOP.rc2 = { 350,150,862,662 };
	SPRITEMANAGER->renderRectTexture(_SHOP.tex, &_SHOP.rc1, &_SHOP.rc2, 0, 0, 512, 512, 350,150);

	//무기 아이템
	for (int i = 0; i < _weapon->getVweaponRender().size(); i++)
	{
		_ShopWeaponRender[i].rc2 = { _SHOP.rc2.left + 20, (_SHOP.rc2.top + 118) + i * 62 ,_ShopWeaponRender[i].rc2.left + 53,_ShopWeaponRender[i].rc2.top + 51 };
		SPRITEMANAGER->renderRectTexture(_ShopWeaponRender[i].tex, &_ShopWeaponRender[i].rc1, &_ShopWeaponRender[i].rc2, 0, 0, 64, 64, _SHOP.rc2.left + 20, (_SHOP.rc2.top + 118) + i * 62);
	}

	//방어 아이템
	for (int i = 0; i < _armor->getVarmorRender().size(); i++)
	{
		_ShopArmorRender[i].rc2 = { _SHOP.rc2.left + 218, (_SHOP.rc2.top + 118) + i * 62 ,_ShopArmorRender[i].rc2.left + 53,_ShopArmorRender[i].rc2.top + 51 };
		SPRITEMANAGER->renderRectTexture(_ShopArmorRender[i].tex, &_ShopArmorRender[i].rc1, &_ShopArmorRender[i].rc2, 0, 0, 64, 64, _SHOP.rc2.left + 218, (_SHOP.rc2.top + 118) + i * 62);
	}

	//선택버튼
	if (_pick.first == true)
	{
		LPDIRECT3DTEXTURE9 temp = RM_TEXTURE->getResource("ResourceUI/inven/shop/픽1.png");
		for (int i = 0; i < 5; i++)
		{
			SPRITEMANAGER->renderRectTexture(temp, &_ShopWeaponRender[i].rc1, &_ShopWeaponRender[i].rc2, 0, 0, 64, 64, _pick.second.x, _pick.second.y);
			SPRITEMANAGER->renderRectTexture(temp, &_ShopArmorRender[i].rc1, &_ShopArmorRender[i].rc2, 0, 0, 64, 64, _pick.second.x, _pick.second.y);
		}
	}

	//사기,팔기 버튼
	if (_ShopButton[0].check == true)
	{
		_ShopButton[0].rc2 = { _SHOP.rc2.left + 180, _SHOP.rc2.top + 445 ,_ShopButton[0].rc2.left + 96,_ShopButton[0].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_ShopButton[0].tex, &_ShopButton[0].rc1, &_ShopButton[0].rc2, 0, 0, 96, 37, _SHOP.rc2.left + 180, _SHOP.rc2.top + 445);
	}
	else
	{
		_ShopButton[0].rc2 = { _SHOP.rc2.left + 180, _SHOP.rc2.top + 445 ,_ShopButton[0].rc2.left + 96,_ShopButton[0].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_ShopButton[0].tex, &_ShopButton[0].rc1, &_ShopButton[0].rc2, 0, 37, 96, 74, _SHOP.rc2.left + 180, _SHOP.rc2.top + 445);
	}

	if (_ShopButton[1].check == true)
	{
		_ShopButton[1].rc2 = { _SHOP.rc2.left + 300, _SHOP.rc2.top + 445 ,_ShopButton[1].rc2.left + 96,_ShopButton[1].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_ShopButton[1].tex, &_ShopButton[1].rc1, &_ShopButton[1].rc2, 0, 74, 96, 111, _SHOP.rc2.left + 300, _SHOP.rc2.top + 445);
	}
	else
	{
		_ShopButton[1].rc2 = { _SHOP.rc2.left + 300, _SHOP.rc2.top + 445 ,_ShopButton[1].rc2.left + 96,_ShopButton[1].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_ShopButton[1].tex, &_ShopButton[1].rc1, &_ShopButton[1].rc2, 0, 111, 96, 148, _SHOP.rc2.left + 300, _SHOP.rc2.top + 445);
	} 
}

void shop::shopPickUpdate()
{
	//무기구 선택
	for (int i = 0; i < 5; i++)
	{
		if (PtInRect(&_ShopWeaponRender[i].rc2, GetMousePos()))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				//선택하면 테두리
				_pick.second = { _ShopWeaponRender[i].rc2.left,_ShopWeaponRender[i].rc2.top };
				_pick.first = true;

				//클릭하면 그 아이템벡터를 담는다.
				_temp = _ShopWeaponRender[i];

				//정보값 담기
				_tempInfomation = _ShopWeapon[i];

				//인벤토리 선택픽 없애기
				pair<bool, POINT> temp;
				temp.first = false;
				_inven->setPick(temp);
				_playerItem->setPick(temp);
			}
		}
		else if (PtInRect(&_ShopArmorRender[i].rc2, GetMousePos()))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				//선택하면 테두리
				_pick.second = { _ShopArmorRender[i].rc2.left,_ShopArmorRender[i].rc2.top };
				_pick.first = true;

				//클릭하면 그 아이템벡터를 담는다.
				_temp = _ShopArmorRender[i];

				//정보값 담기
				_tempInfomation = _ShopArmor[i];

				//인벤토리 선택픽 없애기
				pair<bool, POINT> temp;
				temp.first = false;
				_inven->setPick(temp);
				_playerItem->setPick(temp);
			}
		}
	}

	//사기버튼
	if (PtInRect(&_ShopButton[0].rc2, GetMousePos()))
	{
		_ShopButton[0].check = true;
		if (_pick.first == true)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				if (_inven->getVinvenitemRender().size() < NUMBER)
				{
					_inven->setVinvenItemRender(_temp);
					_inven->setVinvenItem(_tempInfomation);
					_pick.first = false;
				}
			}
		}
	}
	else
	{
		_ShopButton[0].check = false;
	}

	//팔기버튼
	if (PtInRect(&_ShopButton[1].rc2, GetMousePos()))
	{
		_ShopButton[1].check = true;
		if (_pick.first == true)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				_pick.first = false;
			}
		}

		if (_inven->getPick().first == true)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				_inven->removeInvenItem(_inven->getTempItem());
				_inven->removeInvenItemInformation(_inven->getTempItem());

				pair<bool, POINT> temp;
				temp.first = false;
				_inven->setPick(temp);
			}
		}
	}
	else
	{
		_ShopButton[1].check = false;
	}


}
