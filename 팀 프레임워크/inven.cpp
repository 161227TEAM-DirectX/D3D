#include "stdafx.h"
#include "inven.h"
#include "shop.h"
#include "playerItem.h"
#include "medicineShop.h"
#include "force.h"

HRESULT inven::init(void)
{
	_pick.first = false;
	_pick.second = { 0,0 };

	_tempItem = 0;

	_temp.kind = 0;                   //플레이어 아이템으로 넘길 변수 0초기화
	_tempInformation.type = 0;        //유형 0 초기화
	

	//버튼초기화
	for (int i = 0; i < 2; i++)
	{
		_invenButton[i].check = false;
	}

	//렉트 갯수대로 bool형이 없으니 정보창이 충돌 됫을때 false가 안되서 제대로 정보창 이 안떠서 생성
	for (int i = 0; i < 18; i++)
	{
		_tempNumberBool[i] = false;
	}

	return S_OK;
}

void inven::release(void)
{

}

void inven::update(void)
{
	this->invenPickUpdate();
	this->invenButtonUpdate();
}

void inven::render(void)
{
	_inven.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/인벤바탕.png");
	_inven.rc2 ={ 900,150,1412,662 };
	SPRITEMANAGER->renderRectTexture(_inven.tex, &_inven.rc1, &_inven.rc2, 0, 0, 512, 512, 900, 150);

	if (_vinvenItemRender.size() != 0)
	{
		for (int i = 0; i < _vinvenItemRender.size(); i++)
		{
				_vinvenItemRender[i].rc2 = { (_inven.rc2.left + 21) + (i % 6) * 52, _inven.rc2.top + 311 + (i / 6) * 52 ,_vinvenItemRender[i].rc2.left+53,_vinvenItemRender[i].rc2.top +51};
				SPRITEMANAGER->renderRectTexture(_vinvenItemRender[i].tex, &_vinvenItemRender[i].rc1, &_vinvenItemRender[i].rc2, 0, 0, 64, 64, (_inven.rc2.left + 21) + (i% 6) * 52, _inven.rc2.top + 311+(i/6)*52);

				if (_vinvenItem[i].type == ITEMKIND::HPMEDICINE || _vinvenItem[i].type == ITEMKIND::MPMEDICINE)
				{
					if (_vinvenItem[i].medicineCount < 10)
					{
						FONTMANAGER->fontOut(to_string(_vinvenItem[i].medicineCount), _vinvenItemRender[i].rc2.left + 36, _vinvenItemRender[i].rc2.top + 30, D3DCOLOR_XRGB(255, 255, 255));
					}
					else
					{
						FONTMANAGER->fontOut(to_string(_vinvenItem[i].medicineCount), _vinvenItemRender[i].rc2.left + 29, _vinvenItemRender[i].rc2.top + 30, D3DCOLOR_XRGB(255, 255, 255));
					}
				}
		}

		//선택버튼
		if (_pick.first == true)
		{
			LPDIRECT3DTEXTURE9 temp = RM_TEXTURE->getResource("ResourceUI/inven/shop/픽1.png");
			for (int i = 0; i < _vinvenItemRender.size(); i++)
			{
				SPRITEMANAGER->renderRectTexture(temp, &_vinvenItemRender[i].rc1, &_vinvenItemRender[i].rc2, 0, 0, 64, 64, _pick.second.x, _pick.second.y);
			}
		}
	}

	
	_invenButton[0].tex =RM_TEXTURE->getResource("ResourceUI/inven/shop/장착해제.png");
	_invenButton[1].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/장착해제.png");

	_invenButton[0].rc2 = { _inven.rc2.left + 160,_inven.rc2.top + 472 ,_invenButton[0].rc2.left + 68,_invenButton[0].rc2.top + 29 };
	_invenButton[1].rc2 = { _inven.rc2.left + 250,_inven.rc2.top + 472 ,_invenButton[1].rc2.left + 68,_invenButton[1].rc2.top + 29 };

	if (_invenButton[0].check == false)
	{
		SPRITEMANAGER->renderRectTexture(_invenButton[0].tex, &_invenButton[0].rc1, &_invenButton[0].rc2, 0, 0, 128, 29, _inven.rc2.left + 160, _inven.rc2.top + 472);
	}
	else
	{
		SPRITEMANAGER->renderRectTexture(_invenButton[0].tex, &_invenButton[0].rc1, &_invenButton[0].rc2, 0, 29, 128, 58, _inven.rc2.left + 160, _inven.rc2.top + 472);
	}

	if (_invenButton[1].check == false)
	{
		SPRITEMANAGER->renderRectTexture(_invenButton[1].tex, &_invenButton[1].rc1, &_invenButton[1].rc2, 0, 58, 128, 87, _inven.rc2.left + 250, _inven.rc2.top + 472);
	}
	else
	{
		SPRITEMANAGER->renderRectTexture(_invenButton[1].tex, &_invenButton[1].rc1, &_invenButton[1].rc2, 0, 87, 128, 116, _inven.rc2.left + 250, _inven.rc2.top + 472);
	}

	//스탯창true값
	for (int i = 0; i < 18; i++)
	{
		if (_tempNumberBool[i] == true)
		{
			if (_tempNumber.type == ITEMKIND::ARMOR || _tempNumber.type == ITEMKIND::WEAPON)
			{
				_invenItemInformation.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/정보창.png");
				SPRITEMANAGER->renderRectTexture(_invenItemInformation.tex, &_invenItemInformation.rc1, &_invenItemInformation.rc2, 0, 0, 256, 256, GetMousePos().x, GetMousePos().y);

				//인벤정보창
				char str1[128];
				char str2[128];
				char str3[128];
				char str4[128];

				sprintf(str1, "%d", _tempNumber.attack);
				sprintf(str2, "%d", _tempNumber.armorAbility);
				sprintf(str3, "%d", _tempNumber.price);

				if (_tempNumber.attack == 0) FONTMANAGER->fontOut(str1, GetMousePos().x + 110, GetMousePos().y + 58, D3DCOLOR_XRGB(255, 255, 255));
				else 	FONTMANAGER->fontOut(str1, GetMousePos().x + 102, GetMousePos().y + 58, D3DCOLOR_XRGB(255, 255, 255));

				if (_tempNumber.armorAbility == 0) FONTMANAGER->fontOut(str2, GetMousePos().x + 108, GetMousePos().y + 84, D3DCOLOR_XRGB(255, 255, 255));
				else FONTMANAGER->fontOut(str2, GetMousePos().x + 102, GetMousePos().y + 84, D3DCOLOR_XRGB(255, 255, 255));

				FONTMANAGER->fontOut(str3, GetMousePos().x + 90, GetMousePos().y + 111, D3DCOLOR_XRGB(255, 255, 255));

				FONTMANAGER->fontOut("+" + to_string(_tempNumber.force), GetMousePos().x + 105, GetMousePos().y + 135, D3DCOLOR_XRGB(255, 255, 255));
			}

			if(_tempNumber.type == ITEMKIND::HPMEDICINE || _tempNumber.type == ITEMKIND::MPMEDICINE)
			{
				_invenItemInformation.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/물약정보창.png");
				SPRITEMANAGER->renderRectTexture(_invenItemInformation.tex, &_invenItemInformation.rc1, &_invenItemInformation.rc2, 0, 0, 256, 256, GetMousePos().x, GetMousePos().y);

				//인벤정보창
				char str1[128];
				char str2[128];
				char str3[128];

				sprintf(str1, "%d", _tempNumber.hpAbility);
				sprintf(str2, "%d", _tempNumber.mpAbility);
				sprintf(str3, "%d", _tempNumber.price);

				if (_tempNumber.hpAbility == 0) FONTMANAGER->fontOut(str1, GetMousePos().x + 110, GetMousePos().y + 58, D3DCOLOR_XRGB(255, 255, 255));
				else 	FONTMANAGER->fontOut(str1, GetMousePos().x + 96, GetMousePos().y + 58, D3DCOLOR_XRGB(255, 255, 255));

				if (_tempNumber.mpAbility == 0) FONTMANAGER->fontOut(str2, GetMousePos().x + 110, GetMousePos().y + 84, D3DCOLOR_XRGB(255, 255, 255));
				else FONTMANAGER->fontOut(str2, GetMousePos().x + 96, GetMousePos().y + 84, D3DCOLOR_XRGB(255, 255, 255));

				FONTMANAGER->fontOut(str3, GetMousePos().x + 96, GetMousePos().y + 111, D3DCOLOR_XRGB(255, 255, 255));
			}
		}
	}

}

void inven::invenPickUpdate()
{
	if (_vinvenItemRender.size() != 0)
	{
		for (int i = 0; i < _vinvenItemRender.size(); i++)
		{
			if (PtInRect(&_vinvenItemRender[i].rc2, GetMousePos()))
			{
				//스탯창
				_tempNumberBool[i] = true;
				_tempNumber = _vinvenItem[i];   //정보스탯창 담을 변수

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
				{
					_tempItem = i;

					//temp값에 클릭한값을 담는다.
					_temp = _vinvenItemRender[i];
					_tempInformation = _vinvenItem[i];

					_pick.second = { _vinvenItemRender[i].rc2.left,_vinvenItemRender[i].rc2.top };
					_pick.first = true;

					pair<bool, POINT> temp;
					temp.first = false;

					_shop->setPick(temp);
					_playerItem->setPick(temp);		
					_medicineShop->setPick(temp);
				}
			}
			else
			{
				_tempNumberBool[i] = false;
			}
		}
	}

	if (_medicineShop->gettempTemp() == true)
	{
		_vinvenItem[_tempItem] = _tempInformation;
		_medicineShop->settempTemp(false);
	}

	
}

void inven::invenButtonUpdate()
{
	if (PtInRect(&_invenButton[0].rc2, GetMousePos()))
	{
		_invenButton[0].check = true;

		if (_pick.first == true)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON,false))
			{
				if (_temp.kind == ITEMKIND::WEAPON)
				{
					if (_playerItem->getPlaterWeaponItemRender().size() < 1)
					{
			
						_playerItem->setPlayerWeaponItem(_temp);
						this->removeInvenItem(_tempItem);
						_pick.first = false;
					}

					if (_playerItem->getWeaponInfomation().size() < 1)
					{
						_playerItem->setWeaponInfomation(_tempInformation);
						//스탯창 공격력 더하기
						_playerItem->setPlayerAttack(_playerItem->getPlayerAttack() + _tempInformation.attack);

						this->removeInvenItemInformation(_tempItem);
					}
				}

				if (_temp.kind == ITEMKIND::ARMOR)
				{
					
					if (_playerItem->getplayerArmorItemRender().size() < 1)
					{
						_playerItem->setPlayerArmorItem(_temp);
						this->removeInvenItem(_tempItem);
						_pick.first = false;
					}

					if (_playerItem->getArmorInformation().size() < 1)
					{
						_playerItem->setArmorInformation(_tempInformation);
						//스탯창 방어 더하기
						_playerItem->setPlayerArmor(_playerItem->getPlayerArmor() + _tempInformation.armorAbility);

						this->removeInvenItemInformation(_tempItem);
					}
				}
			}
		}
	}
	else
	{
		_invenButton[0].check = false;
	}

	if (PtInRect(&_invenButton[1].rc2, GetMousePos()))
	{
		_invenButton[1].check = true;

		if (_playerItem->getPick().first == true)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				pair<bool, POINT> temp;
				temp.first = false;

				_playerItem->setPick(temp);
				_playerItem->removePlayerItem(_playerItem->getTempItem(), _playerItem->getTemp());
				_playerItem->removePlayerItemInformation(_playerItem->getTempItem(), _playerItem->getTempInformation());

				_vinvenItem.push_back(_playerItem->getTempInformation());
				_vinvenItemRender.push_back(_playerItem->getTemp());

				//해제당시 공격력 , 방어력 빼주기
				_playerItem->removePlaterInformation(_playerItem->getTempInformation());
			}
		}
	}
	else
	{
		_invenButton[1].check = false;
	}

}

void inven::removeInvenItem(int num)
{
	_vinvenItemRender.erase(_vinvenItemRender.begin() + num);
}

void inven::removeInvenItemInformation(int num)
{
	_vinvenItem.erase(_vinvenItem.begin() + num);
}
