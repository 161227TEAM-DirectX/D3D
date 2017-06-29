#include "stdafx.h"
#include "shop.h"
#include "inven.h"
#include "playerItem.h"

HRESULT shop::init(void)
{
	_armor = new armor;
	_weapon = new weapon;


	//���ⱸ
	for (int i = 0; i < _weapon->getVweaponRender().size(); i++)
	{
		_ShopWeaponRender[i].tex = _weapon->getVweaponRender()[i].tex;
		_ShopWeaponRender[i].kind = _weapon->getVweaponRender()[i].kind;
		_ShopWeaponRender[i].check = false;
		_ShopWeaponRender[i].number = 0;
	}

	//���ⱸ ����
	for (int i = 0; i < _weapon->getVweapon().size(); i++)
	{
		_ShopWeapon.push_back(_weapon->getVweapon()[i]);
	}

	//��
	for (int i = 0; i < _armor->getVarmorRender().size(); i++)
	{
		_ShopArmorRender[i].tex = _armor->getVarmorRender()[i].tex;
		_ShopArmorRender[i].kind = _armor->getVarmorRender()[i].kind;
		_ShopArmorRender[i].check = false;
		_ShopArmorRender[i].number = 0;
	}

	//�� ����
	for (int i = 0; i < _armor->getVarmor().size(); i++)
	{
		_ShopArmor.push_back(_armor->getVarmor()[i]);
	}

	//���� temp�� �ʱ�ȭ
	_tempInfomation.attack = 0;
	_tempInfomation.armorAbility = 0;
	_tempInfomation.number = 0;
	_tempInfomation.price = 0;
	_tempInfomation.type = 0;

	//���,�ȱ� ��ư
	for (int i = 0; i < 2; i++)
	{
		_ShopButton[0].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/������ư.png");
		_ShopButton[1].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/������ư.png");
		_ShopButton[i].check = false;
	}

    //���ù�ư
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
	//��������UI
	_SHOP.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/��������1.png");
	_SHOP.rc2 = { 350,150,862,662 };
	SPRITEMANAGER->renderRectTexture(_SHOP.tex, &_SHOP.rc1, &_SHOP.rc2, 0, 0, 512, 512, 350,150);

	//���� ������
	for (int i = 0; i < _weapon->getVweaponRender().size(); i++)
	{
		_ShopWeaponRender[i].rc2 = { _SHOP.rc2.left + 20, (_SHOP.rc2.top + 118) + i * 62 ,_ShopWeaponRender[i].rc2.left + 53,_ShopWeaponRender[i].rc2.top + 51 };
		SPRITEMANAGER->renderRectTexture(_ShopWeaponRender[i].tex, &_ShopWeaponRender[i].rc1, &_ShopWeaponRender[i].rc2, 0, 0, 64, 64, _SHOP.rc2.left + 20, (_SHOP.rc2.top + 118) + i * 62);
	}

	//��� ������
	for (int i = 0; i < _armor->getVarmorRender().size(); i++)
	{
		_ShopArmorRender[i].rc2 = { _SHOP.rc2.left + 218, (_SHOP.rc2.top + 118) + i * 62 ,_ShopArmorRender[i].rc2.left + 53,_ShopArmorRender[i].rc2.top + 51 };
		SPRITEMANAGER->renderRectTexture(_ShopArmorRender[i].tex, &_ShopArmorRender[i].rc1, &_ShopArmorRender[i].rc2, 0, 0, 64, 64, _SHOP.rc2.left + 218, (_SHOP.rc2.top + 118) + i * 62);
	}

	//���ù�ư
	if (_pick.first == true)
	{
		LPDIRECT3DTEXTURE9 temp = RM_TEXTURE->getResource("ResourceUI/inven/shop/��1.png");
		for (int i = 0; i < 5; i++)
		{
			SPRITEMANAGER->renderRectTexture(temp, &_ShopWeaponRender[i].rc1, &_ShopWeaponRender[i].rc2, 0, 0, 64, 64, _pick.second.x, _pick.second.y);
			SPRITEMANAGER->renderRectTexture(temp, &_ShopArmorRender[i].rc1, &_ShopArmorRender[i].rc2, 0, 0, 64, 64, _pick.second.x, _pick.second.y);
		}
	}

	//���,�ȱ� ��ư
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
	//���ⱸ ����
	for (int i = 0; i < 5; i++)
	{
		if (PtInRect(&_ShopWeaponRender[i].rc2, GetMousePos()))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				//�����ϸ� �׵θ�
				_pick.second = { _ShopWeaponRender[i].rc2.left,_ShopWeaponRender[i].rc2.top };
				_pick.first = true;

				//Ŭ���ϸ� �� �����ۺ��͸� ��´�.
				_temp = _ShopWeaponRender[i];

				//������ ���
				_tempInfomation = _ShopWeapon[i];

				//�κ��丮 ������ ���ֱ�
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
				//�����ϸ� �׵θ�
				_pick.second = { _ShopArmorRender[i].rc2.left,_ShopArmorRender[i].rc2.top };
				_pick.first = true;

				//Ŭ���ϸ� �� �����ۺ��͸� ��´�.
				_temp = _ShopArmorRender[i];

				//������ ���
				_tempInfomation = _ShopArmor[i];

				//�κ��丮 ������ ���ֱ�
				pair<bool, POINT> temp;
				temp.first = false;
				_inven->setPick(temp);
				_playerItem->setPick(temp);
			}
		}
	}

	//����ư
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

	//�ȱ��ư
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
