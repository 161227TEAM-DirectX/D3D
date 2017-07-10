#include "stdafx.h"
#include "cUIPlayer.h"
//
#include "cUIShopSlot.h"
//
#include "inven.h"
#include "shop.h"
#include "playerItem.h"
#include "medicineShop.h"
#include "force.h"
#include "medicinePlayer.h"

cUIPlayer::cUIPlayer()
{
}


cUIPlayer::~cUIPlayer()
{
}

HRESULT cUIPlayer::init()
{
	//============================================================================================
	// 플레이어 바
	//============================================================================================
	m_pPlBar = new cDxImgUI("playerbar_back");
	m_pPlBar->GetUI()->SetPosition(D3DXVECTOR3(18, 10, 0));

	m_pBar = new cDxImgBar("playerbarHP_cover", "playerbarHP_move",
						   D3DXVECTOR2(m_pPlBar->GetUI()->GetPosition().x,
									   m_pPlBar->GetUI()->GetPosition().y));
	m_pBar->setMoveGauge(m_pBar->GetMove()->GetSize().fWidth);

	m_pBar2 = new cDxImgBar("playerbarMP_cover", "playerbarMP_move",
							D3DXVECTOR2(m_pPlBar->GetUI()->GetPosition().x,
										m_pPlBar->GetUI()->GetPosition().y));
	m_pBar2->setMoveGauge(m_pBar2->GetMove()->GetSize().fWidth);



	//============================================================================================
	// 퀵슬롯
	//============================================================================================
	m_pQuick = new cDxImgUI("quickSlotUI_back");
	m_pQuick->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY - 68, 0));
	m_pQuick->GetUI()->SetCenterDraw(true);



	//============================================================================================
	// 채팅창
	//============================================================================================
	m_pChat = new cUIchatting;



	//============================================================================================
	// 상점 슬롯
	//============================================================================================
	m_pShopSlot = new cUIShopSlot("shopSlot_back", 80, 50, 30, 250);
	m_pShopSlot->GetUI()->SetPosition(D3DXVECTOR3(-85, 200, 0));
	m_pShopSlot->SetCountMax(40);
	m_pShopSlot->SetBtnSpeed(2);



	//============================================================================================
	// 무기, 포션, 대장간 버튼
	//============================================================================================
	m_vBtnWeaponPos ={ 17, 59 };
	m_pBtnWeapon = new cDxImgButton(DXIMG_MANAGER->GetDxImg("shopSlot_off00"),
									DXIMG_MANAGER->GetDxImg("shopSlot_over00"),
									D3DXVECTOR2(m_pShopSlot->GetUI()->GetPosition().x + m_vBtnWeaponPos.x,
												m_pShopSlot->GetUI()->GetPosition().y + m_vBtnWeaponPos.y),
									"무기상점아이콘");

	m_vBtnPotionPos ={ 17,142 };
	m_pBtnPotion = new cDxImgButton(DXIMG_MANAGER->GetDxImg("shopSlot_off01"),
									DXIMG_MANAGER->GetDxImg("shopSlot_over01"),
									D3DXVECTOR2(m_pShopSlot->GetUI()->GetPosition().x + m_vBtnPotionPos.x,
												m_pShopSlot->GetUI()->GetPosition().y + m_vBtnPotionPos.y),
									"물약상점아이콘");

	m_vBtnReinforcePos ={ 17 ,223 };
	m_pBtnReinforce = new cDxImgButton(DXIMG_MANAGER->GetDxImg("shopSlot_off02"),
									   DXIMG_MANAGER->GetDxImg("shopSlot_over02"),
									   D3DXVECTOR2(m_pShopSlot->GetUI()->GetPosition().x + m_vBtnReinforcePos.x,
												   m_pShopSlot->GetUI()->GetPosition().y + m_vBtnReinforcePos.y),
									   "강화상점아이콘");

	m_pBtnInven = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_invetory_off"),
								   DXIMG_MANAGER->GetDxImg("btn_invetory_over"),
								   D3DXVECTOR2(880, 856),
								   "인벤토리아이콘");

	m_pBtnSkillBook = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_skillbook_off"),
									   DXIMG_MANAGER->GetDxImg("btn_skillbook_over"),
									   D3DXVECTOR2(920, 856),
									   "스킬북아이콘");

	m_pBtnWorldMap = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_worldmap_off"),
									  DXIMG_MANAGER->GetDxImg("btn_worldmap_over"),
									  D3DXVECTOR2(960, 856),
									  "월드맵아이콘");


	//============================================================================================
	// 소울, 돈, 미니맵
	//============================================================================================
	m_pSour = new cDxImgUI("numbox_soul");
	m_pSour->GetUI()->SetPosition(D3DXVECTOR3(1000, 858, 0));

	m_pMoney = new cDxImgUI("numbox_money");
	m_pMoney->GetUI()->SetPosition(D3DXVECTOR3(1120, 860, 0));

	m_pMiniMap = new cDxImgUI("minimap");
	m_pMiniMap->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX - m_pMiniMap->GetUI()->GetSize().fWidth,
												 0, 0));



	//=================================================================================
	// 상점 관련
	//=================================================================================
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

	_medicinePlayer->setInvenLink(_inven);

	_force->setForceLink(_inven);

	return S_OK;
}

void cUIPlayer::release()
{
	SAFE_DELETE(m_pPlBar);
	SAFE_DELETE(m_pBar);
	SAFE_DELETE(m_pBar2);
	SAFE_DELETE(m_pQuick);
	SAFE_DELETE(m_pChat);

	SAFE_DELETE(m_pShopSlot);

	SAFE_DELETE(m_pBtnWeapon);
	SAFE_DELETE(m_pBtnPotion);
	SAFE_DELETE(m_pBtnReinforce);

	SAFE_DELETE(m_pBtnInven);
	SAFE_DELETE(m_pBtnSkillBook);
	SAFE_DELETE(m_pBtnWorldMap);

	SAFE_DELETE(m_pSour);
	SAFE_DELETE(m_pMoney);
	SAFE_DELETE(m_pMiniMap);


	SAFE_DELETE(_medicineShop);
	SAFE_DELETE(_shop);
	SAFE_DELETE(_inven);
	SAFE_DELETE(_playerItem);
	SAFE_DELETE(_force);
}

void cUIPlayer::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//m_pBar->moveBar(-1);
		//m_pBar2->moveBar(-1);

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//m_pBar->moveBar(1);
		//m_pBar2->moveBar(1);
	}
	
	m_pBar->moveBar((float)PLAYERMANAGER->GetHp() / (float)PLAYERMANAGER->GetMaxHp() * 100);
	


	//=================================================================================
	// 상점 슬롯
	//=================================================================================
	m_pShopSlot->update();


	//=================================================================================
	// 무기,포션,대장간 버튼 -> 상점 슬롯
	//=================================================================================
	m_pBtnWeapon->setPos(D3DXVECTOR2(m_pShopSlot->GetUI()->GetPosition().x + m_vBtnWeaponPos.x,
									 m_pShopSlot->GetUI()->GetPosition().y + m_vBtnWeaponPos.y));

	m_pBtnPotion->setPos(D3DXVECTOR2(m_pShopSlot->GetUI()->GetPosition().x + m_vBtnPotionPos.x,
									 m_pShopSlot->GetUI()->GetPosition().y + m_vBtnPotionPos.y));

	m_pBtnReinforce->setPos(D3DXVECTOR2(m_pShopSlot->GetUI()->GetPosition().x + m_vBtnReinforcePos.x,
										m_pShopSlot->GetUI()->GetPosition().y + m_vBtnReinforcePos.y));


	if (m_pBtnWeapon->click())
	{
		m_eShopType = E_WEAPON_SHOP;
		m_isInven = true;
	}

	if (m_pBtnPotion->click())
	{
		m_eShopType = E_POTION_SHOP;
		m_isInven = true;
	}

	if (m_pBtnReinforce->click())
	{
		m_eShopType = E_REINFORCE_SHOP;
		m_isInven = true;
	}


	switch (m_eShopType)
	{
	case E_WEAPON_SHOP:
		_shop->update();
		break;
	case E_POTION_SHOP:
		_medicineShop->update();
		break;
	case E_REINFORCE_SHOP:
		_force->update();
		break;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON, false))
	{
		m_eShopType = E_NONE_SHOP;
		m_isInven = false;
	}



	//================================================================================
	// 인벤 버튼
	//================================================================================
	if (PtInRect(&m_pBtnInven->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false)) {}
	}
	if (PtInRect(&m_pBtnInven->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			m_isInven = m_isInven ? false : true;
		}
	}

	if (m_isInven)
	{
		_inven->update();
		_playerItem->update();
	}

	//================================================================================
	// 물약장착하면 생기게하는 update
	//================================================================================
	_medicinePlayer->update();



	//================================================================================
	// 스킬북 버튼
	//================================================================================
	if (PtInRect(&m_pBtnSkillBook->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false)) {}
	}
	if (PtInRect(&m_pBtnSkillBook->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			m_isSkillBook = m_isSkillBook ? false : true;
		}
	}

	if (m_isSkillBook)
	{

	}




	//================================================================================
	// 월드맵 버튼
	//================================================================================
	if (PtInRect(&m_pBtnWorldMap->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false)) {}
	}
	if (PtInRect(&m_pBtnWorldMap->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			m_isWorldMap = m_isWorldMap ? false : true;
		}
	}

	if (m_isWorldMap)
	{

	}
}

void cUIPlayer::render()
{
	m_pPlBar->render();
	m_pBar->render();
	m_pBar2->render();

	m_pQuick->render();

	m_pChat->render();


	m_pShopSlot->render();

	switch (m_eShopType)
	{
	case E_WEAPON_SHOP:
		_shop->render();
		break;
	case E_POTION_SHOP:
		_medicineShop->render();
		break;
	case E_REINFORCE_SHOP:
		_force->render();
		break;
	}


	m_pBtnWeapon->render();
	m_pBtnPotion->render();
	m_pBtnReinforce->render();

	m_pBtnInven->render();
	m_pBtnSkillBook->render();
	m_pBtnWorldMap->render();

	m_pSour->render();
	m_pMoney->render();
	m_pMiniMap->render();

	if (m_isInven)
	{
		_inven->render();
		_playerItem->render();
	}

	_medicinePlayer->render();
}

void cUIPlayer::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pChat->WndProc(hWnd, message, wParam, lParam);
}
