#include "stdafx.h"
#include "cUIPlayer.h"
//
#include "cUIShopSlot.h"
#include "cUIQuest.h"
#include "cUISkill.h"
#include "cUISKillBook.h"
#include "cUIYouDied.h"
//
#include "inven.h"
#include "shop.h"
#include "playerItem.h"
#include "medicineShop.h"
#include "force.h"

cUIPlayer::cUIPlayer()
	: m_pPlBar(nullptr)			//체력바 본체
	, m_pBar(nullptr)			//체력바
	, m_pBar2(nullptr)			//마나바
	, m_pQuick(nullptr)			//퀵슬롯(스킬)
	, m_pChat(nullptr)			//채팅창
	, m_pShopSlot(nullptr)		//상점슬롯
	, m_pBtnWeapon(nullptr)		//무기상점 버튼
	, m_pBtnPotion(nullptr)		//포션상점 버튼
	, m_pBtnReinforce(nullptr)	//대장간 버튼
	, m_pBtnInven(nullptr)		//인벤토리 버튼
	, m_pBtnSkillBook(nullptr)	//스킬북 버튼
	, m_pBtnWorldMap(nullptr)	//월드맵 버튼
	, m_pBtnChat(nullptr)		//채팅창 설정 버튼
	, m_isInven(false)			//인벤토리를 눌렀는지
	, m_isSkillBook(false)		//스킬북을 눌렀는지
	, m_isWorldMap(false)		//월드맵을 눌렀는지
	, m_pSour(false)			//소울 UI
	, m_pMoney(false)			//머니 UI
	, m_pMiniMap(false)			//미니맵틀 UI
	, m_pBtnMap(nullptr)		//미니맵 버튼
	, m_nMapNum(0)				//어떤 월드맵을 보여줄지 번호
	, m_fRaderAngle(0)			//레이더 각도(미니맵)
	, m_fMinimapMoveX(0)		//미니맵 관련 좌표X
	, m_fMinimapMoveY(0)		//미니맵 관련 좌표Y
	, m_fPlayerPosX(0)			//인게임에서의 플레이어 좌표X
	, m_fPlayerPosY(0)			//인게임에서의 플레이어 좌표Y
	, m_fTerrainSizeX(0)		//지형의 크기
	, m_szMinimap(nullptr)		//어떤 맵을 미니맵으로 띄울 건지
	, _shop(nullptr)			//상점 클래스
	, _inven(nullptr)			//인벤 클래스
	, _medicineShop(nullptr)	//물약 클래스
	, _playerItem(nullptr)		//플레이어 아이템 클래스
	, _force(nullptr)			//대장간 클래스
	, m_eShopType(E_NONE_SHOP)	//상점 타입
{
	m_vBtnWeaponPos ={ 0.0f,0.0f };		//무기상점 버튼 위치
	m_vBtnPotionPos ={ 0.0f,0.0f };		//포션상점 버튼 위치
	m_vBtnReinforcePos ={ 0.0f,0.0f };	//대장간 버튼 위치
}


cUIPlayer::~cUIPlayer()
{
}

HRESULT cUIPlayer::init()
{
	m_pSkillBook = new cUISkillBook("skillbook01");

	m_pYouDied = new cUIYouDied;


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
	// 퀵슬롯 부분
	//============================================================================================

	//퀵슬롯
	m_pQuick = new cDxImgUI("quickSlotUI_back");
	//m_pQuick->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY - 68, 0));
	m_pQuick->GetUI()->setPos(800, 835);
	m_pQuick->GetUI()->SetCenterDraw(true);

	//소울
	m_pBtnSoul = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_soul_off"),
								  DXIMG_MANAGER->GetDxImg("btn_soul_on"),
								  D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 70,
											  m_pQuick->GetUI()->getPosY() + 26),
								  "소울버튼");
	DXIMG_MANAGER->GetDxImg("death_soul")->setPos(465, 440);


	//m_pSour = new cDxImgUI("numbox_soul");
	//m_pSour->GetUI()->SetPosition(D3DXVECTOR3(1000, 858, 0));
	//m_pSour->GetUI()->setPos(m_pQuick->GetUI()->getPosX() - 70,
	//						 m_pQuick->GetUI()->getPosY() + 26);


	//골드
	m_pBtnGold = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_gold_off"),
								  DXIMG_MANAGER->GetDxImg("btn_gold_on"),
								  D3DXVECTOR2(m_pQuick->GetUI()->getPosX() + 40,
											  m_pQuick->GetUI()->getPosY() + 26),
								  "골드버튼");
	DXIMG_MANAGER->GetDxImg("gold_god")->setPos(880, 440);

	//m_pMoney = new cDxImgUI("numbox_money");
	//m_pMoney->GetUI()->SetPosition(D3DXVECTOR3(1120, 860, 0));
	//m_pMoney->GetUI()->setPos(m_pQuick->GetUI()->getPosX() + 40,
	//						  m_pQuick->GetUI()->getPosY() + 29);

	//퀘스트
	m_pBtnQuest = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_quest_off"),
								   DXIMG_MANAGER->GetDxImg("btn_quest_on"),
								   D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 240,
											   m_pQuick->GetUI()->getPosY() + 21),
								   "퀘스트아이콘");

	//인벤토리
	m_pBtnInven = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_invetory_off"),
								   DXIMG_MANAGER->GetDxImg("btn_invetory_over"),
								   D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 200,
											   m_pQuick->GetUI()->getPosY() + 21),
								   "인벤토리아이콘");

	//스킬북
	m_pBtnSkillBook = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_skillbook_off"),
									   DXIMG_MANAGER->GetDxImg("btn_skillbook_over"),
									   D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 160,
												   m_pQuick->GetUI()->getPosY() + 21),
									   "스킬북아이콘");

	//월드맵
	m_pBtnWorldMap = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_worldmap_off"),
									  DXIMG_MANAGER->GetDxImg("btn_worldmap_over"),
									  D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 120,
												  m_pQuick->GetUI()->getPosY() + 21),
									  "월드맵아이콘");



	//============================================================================================
	// 월드맵
	//============================================================================================
	cDxImgUI* temp;
	int mapX = WINSIZEX / 2;
	int mapY = WINSIZEY / 2;

	//맵1
	temp = new cDxImgUI("worldmap");
	//temp = new cDxImgUI("worldmapTest");
	temp->GetUI()->SetPosition(D3DXVECTOR3(mapX, mapY, 0));
	temp->GetUI()->SetCenterDraw(true);
	m_vecWorldmap.push_back(temp);

	//맵2
	temp = new cDxImgUI("worldmap2");
	temp->GetUI()->SetPosition(D3DXVECTOR3(mapX, mapY, 0));
	temp->GetUI()->SetCenterDraw(true);
	m_vecWorldmap.push_back(temp);

	//맵3
	temp = new cDxImgUI("worldmap3");
	temp->GetUI()->SetPosition(D3DXVECTOR3(mapX, mapY, 0));
	temp->GetUI()->SetCenterDraw(true);
	m_vecWorldmap.push_back(temp);

	DXIMG_MANAGER->GetDxImg("worldmap_cover")->setPos(mapX, mapY);
	DXIMG_MANAGER->GetDxImg("worldmap_cover")->SetCenterDraw(true);


	//============================================================================================
	// 스킬 
	//============================================================================================

	//스킬북 애니메이션 반복할지 설정
	DXIMGANI_MANAGER->setDxAniIsOnce("skillbook01", true);

	//스킬 셋팅
	cUISkill* tempSkill;

	tempSkill = new cUISkill("btn_skill00_on", "btn_skill00_off", "쿨타임0", '1', 1308, 761, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill01_on", "btn_skill01_off", "쿨타임1", '2', m_vecUISkill[0]->GetUI()->getPos().x + 64 + 10, 761, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill02_on", "btn_skill02_off", "쿨타임2", '3', m_vecUISkill[1]->GetUI()->getPos().x + 64 + 10, 761, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill03_on", "btn_skill03_off", "쿨타임3", '4', m_vecUISkill[2]->GetUI()->getPos().x + 64 + 10, 761, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill04_on", "btn_skill04_off", "쿨타임4", '5', 1308, 833, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill05_on", "btn_skill05_off", "쿨타임5", '6', m_vecUISkill[0]->GetUI()->getPos().x + 64 + 10, 833, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill06_on", "btn_skill06_off", "쿨타임6", '7', m_vecUISkill[1]->GetUI()->getPos().x + 64 + 10, 833, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill07_on", "btn_skill07_off", "쿨타임7", '8', m_vecUISkill[2]->GetUI()->getPos().x + 64 + 10, 833, false);	m_vecUISkill.push_back(tempSkill);



	//============================================================================================
	// 채팅창
	//============================================================================================
	m_pChat = new cUIchatting;
	m_pBtnChat = new cDxImgButton(DXIMG_MANAGER->GetDxImg("chat_Icon"),
								  DXIMG_MANAGER->GetDxImg("chat_Icon"),
								  D3DXVECTOR2(0, WINSIZEY - 64), "채팅버튼");



	//============================================================================================
	// 상점 슬롯
	//============================================================================================
	m_pShopSlot = new cUIShopSlot("shopSlot_back", 80, 50, 30, 250);
	m_pShopSlot->GetUI()->SetPosition(D3DXVECTOR3(-85, 200, 0));
	m_pShopSlot->SetCountMax(40);
	m_pShopSlot->SetBtnSpeed(2);


	m_pQuest = new cUIQuest("questBox", 127, 422, 97, 29);
	//m_pQuest->GetUI()->SetPosition(D3DXVECTOR3(800, 300, 0));
	m_pQuest->GetUI()->setPos(850, 100);



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




	//=============================================================================
	// 미니맵 관련
	//=============================================================================

	//미니맵 틀
	m_pMiniMap = new cDxImgUI("minimap_cover");
	m_pMiniMap->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX - m_pMiniMap->GetUI()->GetSize().fWidth,
												 0, 0));

	//미니맵 버튼
	m_pBtnMap  = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_minimap_off"),
								  DXIMG_MANAGER->GetDxImg("btn_minimap_on"),
								  D3DXVECTOR2(1390, 320),
								  "맵아이콘");
	m_pBtnMap->SetIsCheck(true);


	//레이더
	DXIMG_MANAGER->GetDxImg("radar")->SetCenterDraw(true);
	DXIMG_MANAGER->GetDxImg("radar")->SetImgAlpha(64);

	
	//비례식
	//m_fMinimapMoveX = DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth * m_fPlayerPosX / m_fTerrainSizeX;
	//m_fMinimapMoveY = DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fHeight * (m_fTerrainSizeX - m_fPlayerPosY) / m_fTerrainSizeX;

	m_fMinimapMoveX = m_vecWorldmap[m_nMapNum]->GetUI()->GetSize().fWidth * m_fPlayerPosX / m_fTerrainSizeX;
	m_fMinimapMoveY = m_vecWorldmap[m_nMapNum]->GetUI()->GetSize().fHeight * (m_fTerrainSizeX - m_fPlayerPosY) / m_fTerrainSizeX;


	

	//우상단의 미니맵
	DXIMG_MANAGER->GetDxImg(m_szMinimap)->SetPosition(D3DXVECTOR3(WINSIZEX - DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth / 2, 0, 0));
	DXIMG_MANAGER->GetDxImg(m_szMinimap)->SetCenterDraw(false);

	//미니맵 플레이어 -> 미니맵에서의 위치를 비례식으로 구해낸다.
	DXIMG_MANAGER->GetDxImg("minimap_player")->SetPosition(D3DXVECTOR3(m_fMinimapMoveX / 2 + DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetPosition().x,
																	   m_fMinimapMoveY / 2 + DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetPosition().y,
																	   0));
	DXIMG_MANAGER->GetDxImg("minimap_player")->SetCenterDraw(true);

	//미니맵에서 레이더의 위치는 미니맵플레이어+미니맵의 좌표
	DXIMG_MANAGER->GetDxImg("radar")->SetPosition(D3DXVECTOR3(DXIMG_MANAGER->GetDxImg("minimap_player")->GetPosition().x,
															  DXIMG_MANAGER->GetDxImg("minimap_player")->GetPosition().y,
															  0));


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

	_shop->setInvenLink(_inven);
	_shop->setPlayerItemLink(_playerItem);

	_inven->setShopLink(_shop);
	_inven->setPlayerItemLink(_playerItem);
	_inven->setmedicineShopLink(_medicineShop);
	_inven->setForceLink(_force);

	_playerItem->setInvenLink(_inven);
	_playerItem->setShopLink(_shop);

	_medicineShop->setmedicineShopLink(_inven);

	_force->setForceLink(_inven);

	return S_OK;
}

void cUIPlayer::release()
{
	SAFE_DELETE(m_pPlBar);
	SAFE_DELETE(m_pBar);
	SAFE_DELETE(m_pBar2);
	SAFE_DELETE(m_pQuick);

	for (int i=0; i < m_vecWorldmap.size(); i++)
	{
		SAFE_DELETE(m_vecWorldmap[i]);
	}
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
	SAFE_DELETE(m_pBtnSoul);
	SAFE_DELETE(m_pBtnGold);
	SAFE_DELETE(m_pMiniMap);


	SAFE_DELETE(_medicineShop);
	SAFE_DELETE(_shop);
	SAFE_DELETE(_inven);
	SAFE_DELETE(_playerItem);
	SAFE_DELETE(_force);
}

void cUIPlayer::update()
{
	//=================================================================================
	// 체력
	//=================================================================================
	//m_pBar->moveBar((float)PLAYERMANAGER->GetHp() / (float)PLAYERMANAGER->GetMaxHp() * 100);
	//m_pBar->moveBar(0.0f);

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pBar->moveBar(-1);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pBar->moveBar(1);
	}

	//체력이 0이하가 된다면...
	if (m_pBar->getCursorBar() <= 0)
	{
		m_pYouDied->SetIsDied(true);
	}
	else
	{
		m_pYouDied->SetIsDied(false);
	}


	//=================================================================================
	// 마력
	//=================================================================================
	m_pBar2->moveBar((float)PLAYERMANAGER->GetMp() / (float)PLAYERMANAGER->GetMaxMp() * 100);
	//m_pBar2->moveBar(0.0f);



	//=================================================================================
	// 스킬
	//=================================================================================
	for (int i=0; i<m_vecUISkill.size(); i++)
	{
		m_vecUISkill[i]->update();
	}


	//=================================================================================
	// 채팅 슬롯
	//=================================================================================
	m_pChat->update();



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
	// 퀘스트 버튼
	//================================================================================
	if (PtInRect(&m_pBtnQuest->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false)) {}
	}
	if (PtInRect(&m_pBtnQuest->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			bool isCheck = m_pBtnQuest->GetIsCheck() ? false : true;
			m_pBtnQuest->SetIsCheck(isCheck);
		}
	}
	m_pQuest->update();

	if (m_pQuest->GetIsSure())
	{
	}






	//================================================================================
	// 미니맵 버튼
	//================================================================================
	if (PtInRect(&m_pBtnMap->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false)) {}
	}
	if (PtInRect(&m_pBtnMap->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			bool isCheck = m_pBtnMap->GetIsCheck() ? false : true;
			m_pBtnMap->SetIsCheck(isCheck);
		}
	}

	//만약 미니맵을 off상태라면
	if (!m_pBtnMap->GetIsCheck())
	{
		//m_pBtnMap->setPos(D3DXVECTOR2(m_pBtnMap->GetOff()->GetPosition().x, 0));
		m_pBtnMap->setPos(D3DXVECTOR2(1500, 0));
	}
	else if (m_pBtnMap->GetIsCheck())
	{
		m_pBtnMap->setPos(D3DXVECTOR2(1390, 320));
	}



	//================================================================================
	// 채팅창 설정 버튼
	//================================================================================
	if (PtInRect(&m_pBtnChat->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false)) {}
	}
	if (PtInRect(&m_pBtnChat->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			bool isCheck = m_pBtnChat->GetIsCheck() ? false : true;
			m_pBtnChat->SetIsCheck(isCheck);
		}
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
			m_pSkillBook->SetIsAct(!m_pSkillBook->GetIsAct());
			m_pSkillBook->update();
		}
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


	//m_fMinimapMoveX = DXIMG_MANAGER->GetDxImg("worldmapTest")->GetSize().fWidth * m_fPlayerPosX / m_fTerrainSizeX;
	//m_fMinimapMoveY = DXIMG_MANAGER->GetDxImg("worldmapTest")->GetSize().fHeight * (m_fTerrainSizeX - m_fPlayerPosY) / m_fTerrainSizeX;

	m_fMinimapMoveX = m_vecWorldmap[m_nMapNum]->GetUI()->GetSize().fWidth * m_fPlayerPosX / m_fTerrainSizeX;
	m_fMinimapMoveY = m_vecWorldmap[m_nMapNum]->GetUI()->GetSize().fHeight * (m_fTerrainSizeX - m_fPlayerPosY) / m_fTerrainSizeX;

	



	//================================================================================
	// 소울 버튼
	//================================================================================
	if (PtInRect(&m_pBtnSoul->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false)) {}
	}
	if (PtInRect(&m_pBtnSoul->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			bool isCheck = m_pBtnSoul->GetIsCheck() ? false : true;
			m_pBtnSoul->SetIsCheck(isCheck);
		}
	}



	//================================================================================
	// 골드 버튼
	//================================================================================
	if (PtInRect(&m_pBtnGold->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false)) {}
	}
	if (PtInRect(&m_pBtnGold->GetRtBtn(), GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			bool isCheck = m_pBtnGold->GetIsCheck() ? false : true;
			m_pBtnGold->SetIsCheck(isCheck);
		}
	}

}



void cUIPlayer::render()
{
	m_pPlBar->render();
	m_pBar->render();
	m_pBar2->render();
	m_pQuick->render();

	//채팅창을 그리자.
	if (m_pBtnChat->GetIsCheck())
	{
		m_pChat->render();
	}
	m_pBtnChat->render();

	//채팅창 설정 버튼을 그리자.
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

	//퀘스트 버튼을 그리자.
	m_pBtnQuest->render();
	if (m_pBtnQuest->GetIsCheck())
	{
		//DXIMG_MANAGER->GetDxImg("quest")->render();
		m_pQuest->render();
	}

	if (m_pQuest->GetIsSure())
	{
		//DXIMG_MANAGER->GetDxImg("questSlot_Test")->render();
	}


	//소울
	if (m_pBtnSoul->GetIsCheck())
	{
		DXIMG_MANAGER->GetDxImg("death_soul")->render();
	}


	//골드
	if (m_pBtnGold->GetIsCheck())
	{
		DXIMG_MANAGER->GetDxImg("gold_god")->render();
	}








	//소울 렌더
	//m_pSour->render();
	m_pBtnSoul->render();

	//골드 렌더
	//m_pMoney->render();
	m_pBtnGold->render();


	//===============================================
	//미니맵 틀을 그리자.
	//===============================================
	if (m_pBtnMap->GetIsCheck() && m_pBtnMap->GetOff()->GetPosition().y == 320)
	{
		DXIMG_MANAGER->render(m_szMinimap,
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth / 4,
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fHeight / 4,
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth / 2,		//보여줄 가로길이
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fHeight / 2,		//보여줄 세로길이
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth / 2 - m_fMinimapMoveX,
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fHeight / 2 - m_fMinimapMoveY);

		DXIMG_MANAGER->GetDxImg("radar")->render(0, 0, m_fRaderAngle - 180);
		DXIMG_MANAGER->render("minimap_player");
		m_pMiniMap->render();
	}
	m_pBtnMap->render();

	

	//===============================================
	// 인벤토리를 그리자.
	//===============================================
	if (m_isInven)
	{
		_inven->render();
		_playerItem->render();
	}


	//===============================================
	// 스킬창을 그리자.
	//===============================================
	//if(DXIMGANI_MANAGER->getDxAniST("skillbook01").nAniType == 1)
	//{
	//	if(DXIMGANI_MANAGER->getDxAniST("skillbook01").isReverse && 
	//	   DXIMGANI_MANAGER->getDxAniST("skillbook01").nAniIndex==8)
	//	{
	//		if(m_nSkillBookCount++ > 30)
	//		{
	//			m_nSkillBookCount = 0;
	//			DXIMGANI_MANAGER->setDxAniType("skillbook01", 0);
	//		}
	//	}
	//	DXIMGANI_MANAGER->render("skillbook01");
	//}
	m_pSkillBook->render();


	//=================================================================================
	// 스킬
	//=================================================================================
	for (int i=0; i<m_vecUISkill.size(); i++)
	{
		m_vecUISkill[i]->render();
	}



	//===============================================
	// 월드맵 버튼 클릭시 관련 렌더
	//===============================================
	if (m_isWorldMap)
	{
		m_vecWorldmap[m_nMapNum]->render();

		float width = m_vecWorldmap[m_nMapNum]->GetUI()->GetSize().fWidth;
		float height = m_vecWorldmap[m_nMapNum]->GetUI()->GetSize().fHeight;

		float px = width * (m_fPlayerPosX - m_fTerrainSizeX / 2) / m_fTerrainSizeX;
		float py = height * (m_fPlayerPosY - m_fTerrainSizeX / 2) / m_fTerrainSizeX;

		DXIMG_MANAGER->GetDxImg("worldmap_point")->SetPosition(
			D3DXVECTOR3(px + m_vecWorldmap[m_nMapNum]->GetUI()->GetPosition().x,
						-py + m_vecWorldmap[m_nMapNum]->GetUI()->GetPosition().y,
						0));
		DXIMG_MANAGER->GetDxImg("worldmap_point")->SetCenterDraw(true);
		DXIMG_MANAGER->GetDxImg("worldmap_point")->render();
		DXIMG_MANAGER->GetDxImg("worldmap_cover")->render();
	}


	FONTMANAGER->fontOut("%f", DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth / 2 - m_fMinimapMoveX, 100,100, WHITE);

	m_pYouDied->render();
}

void cUIPlayer::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pChat->WndProc(hWnd, message, wParam, lParam);
}

void cUIPlayer::linkMinimapPlayerAngle(float angle)
{
	m_fRaderAngle = angle + 180;
}

void cUIPlayer::linkMinimapPlayerMove(float posX, float posY, float terrainSizeX)
{
	m_fPlayerPosX = posX;
	m_fPlayerPosY = posY;
	m_fTerrainSizeX = terrainSizeX;
}
