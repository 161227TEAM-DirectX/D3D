#include "stdafx.h"
#include "shopHead.h"

HRESULT shopHead::init(void)
{
	_medicineShop = new medicineShop;
	_medicineShop->init();

	_shop = new shop;
	_shop->init();

	_inven = new inven;
	_inven->init();

	_playerItem = new playerItem;
	_playerItem->init();

	_force = new force;
	_force->init();

	_medicinePlayer = new medicinePlayer;
	_medicinePlayer->init();

	_shop->setInvenLink(_inven);
	_shop->setPlayerItemLink(_playerItem);

	_inven->setShopLink(_shop);
	_inven->setPlayerItemLink(_playerItem);
	_inven->setmedicineShopLink(_medicineShop);
	_inven->setForceLink(_force);
	_inven->setMedicinePlayerLink(_medicinePlayer);

	_playerItem->setInvenLink(_inven);
	_playerItem->setShopLink(_shop);

	_medicineShop->setmedicineShopLink(_inven);

	_force->setForceLink(_inven);

	_medicinePlayer->setInvenLink(_inven);

	return S_OK;
}

void shopHead::release(void)
{
	SAFE_DELETE(_medicineShop);
	SAFE_DELETE(_shop);
	SAFE_DELETE(_inven);
	SAFE_DELETE(_playerItem);
	SAFE_DELETE(_force);
}

void shopHead::update(void)
{
	if (KEYMANAGER->isToggleKey(VK_RIGHT))
	{
		_shop->update();
		//_medicineShop->update();
	}

	if (KEYMANAGER->isToggleKey(VK_LEFT))
	{
		_force->update();
	}
	//_shop->update();
	_medicinePlayer->update();
	_inven->update();
	_playerItem->update();
}

void shopHead::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_RIGHT))
	{
		_shop->render();
		//_medicineShop->render();
	}


	if (KEYMANAGER->isToggleKey(VK_LEFT))
	{
		_force->render();
	}
	//_shop->render();
	_medicinePlayer->render();
	_inven->render();
	_playerItem->render();
}
