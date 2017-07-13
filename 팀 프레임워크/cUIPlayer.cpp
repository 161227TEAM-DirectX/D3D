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
	: m_pPlBar(nullptr)			//ü�¹� ��ü
	, m_pBar(nullptr)			//ü�¹�
	, m_pBar2(nullptr)			//������
	, m_pQuick(nullptr)			//������(��ų)
	, m_pChat(nullptr)			//ä��â
	, m_pShopSlot(nullptr)		//��������
	, m_pBtnWeapon(nullptr)		//������� ��ư
	, m_pBtnPotion(nullptr)		//���ǻ��� ��ư
	, m_pBtnReinforce(nullptr)	//���尣 ��ư
	, m_pBtnInven(nullptr)		//�κ��丮 ��ư
	, m_pBtnSkillBook(nullptr)	//��ų�� ��ư
	, m_pBtnWorldMap(nullptr)	//����� ��ư
	, m_pBtnChat(nullptr)		//ä��â ���� ��ư
	, m_isInven(false)			//�κ��丮�� ��������
	, m_isSkillBook(false)		//��ų���� ��������
	, m_isWorldMap(false)		//������� ��������
	, m_pSour(false)			//�ҿ� UI
	, m_pMoney(false)			//�Ӵ� UI
	, m_pMiniMap(false)			//�̴ϸ�Ʋ UI
	, m_pBtnMap(nullptr)		//�̴ϸ� ��ư
	, m_nMapNum(0)				//� ������� �������� ��ȣ
	, m_fRaderAngle(0)			//���̴� ����(�̴ϸ�)
	, m_fMinimapMoveX(0)		//�̴ϸ� ���� ��ǥX
	, m_fMinimapMoveY(0)		//�̴ϸ� ���� ��ǥY
	, m_fPlayerPosX(0)			//�ΰ��ӿ����� �÷��̾� ��ǥX
	, m_fPlayerPosY(0)			//�ΰ��ӿ����� �÷��̾� ��ǥY
	, m_fTerrainSizeX(0)		//������ ũ��
	, m_szMinimap(nullptr)		//� ���� �̴ϸ����� ��� ����
	, _shop(nullptr)			//���� Ŭ����
	, _inven(nullptr)			//�κ� Ŭ����
	, _medicineShop(nullptr)	//���� Ŭ����
	, _playerItem(nullptr)		//�÷��̾� ������ Ŭ����
	, _force(nullptr)			//���尣 Ŭ����
	, m_eShopType(E_NONE_SHOP)	//���� Ÿ��
{
	m_vBtnWeaponPos ={ 0.0f,0.0f };		//������� ��ư ��ġ
	m_vBtnPotionPos ={ 0.0f,0.0f };		//���ǻ��� ��ư ��ġ
	m_vBtnReinforcePos ={ 0.0f,0.0f };	//���尣 ��ư ��ġ
}


cUIPlayer::~cUIPlayer()
{
}

HRESULT cUIPlayer::init()
{
	m_pSkillBook = new cUISkillBook("skillbook01");

	m_pYouDied = new cUIYouDied;


	//============================================================================================
	// �÷��̾� ��
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
	// ������ �κ�
	//============================================================================================

	//������
	m_pQuick = new cDxImgUI("quickSlotUI_back");
	//m_pQuick->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY - 68, 0));
	m_pQuick->GetUI()->setPos(800, 835);
	m_pQuick->GetUI()->SetCenterDraw(true);

	//�ҿ�
	m_pBtnSoul = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_soul_off"),
								  DXIMG_MANAGER->GetDxImg("btn_soul_on"),
								  D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 70,
											  m_pQuick->GetUI()->getPosY() + 26),
								  "�ҿ��ư");
	DXIMG_MANAGER->GetDxImg("death_soul")->setPos(465, 440);


	//m_pSour = new cDxImgUI("numbox_soul");
	//m_pSour->GetUI()->SetPosition(D3DXVECTOR3(1000, 858, 0));
	//m_pSour->GetUI()->setPos(m_pQuick->GetUI()->getPosX() - 70,
	//						 m_pQuick->GetUI()->getPosY() + 26);


	//���
	m_pBtnGold = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_gold_off"),
								  DXIMG_MANAGER->GetDxImg("btn_gold_on"),
								  D3DXVECTOR2(m_pQuick->GetUI()->getPosX() + 40,
											  m_pQuick->GetUI()->getPosY() + 26),
								  "����ư");
	DXIMG_MANAGER->GetDxImg("gold_god")->setPos(880, 440);

	//m_pMoney = new cDxImgUI("numbox_money");
	//m_pMoney->GetUI()->SetPosition(D3DXVECTOR3(1120, 860, 0));
	//m_pMoney->GetUI()->setPos(m_pQuick->GetUI()->getPosX() + 40,
	//						  m_pQuick->GetUI()->getPosY() + 29);

	//����Ʈ
	m_pBtnQuest = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_quest_off"),
								   DXIMG_MANAGER->GetDxImg("btn_quest_on"),
								   D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 240,
											   m_pQuick->GetUI()->getPosY() + 21),
								   "����Ʈ������");

	//�κ��丮
	m_pBtnInven = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_invetory_off"),
								   DXIMG_MANAGER->GetDxImg("btn_invetory_over"),
								   D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 200,
											   m_pQuick->GetUI()->getPosY() + 21),
								   "�κ��丮������");

	//��ų��
	m_pBtnSkillBook = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_skillbook_off"),
									   DXIMG_MANAGER->GetDxImg("btn_skillbook_over"),
									   D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 160,
												   m_pQuick->GetUI()->getPosY() + 21),
									   "��ų�Ͼ�����");

	//�����
	m_pBtnWorldMap = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_worldmap_off"),
									  DXIMG_MANAGER->GetDxImg("btn_worldmap_over"),
									  D3DXVECTOR2(m_pQuick->GetUI()->getPosX() - 120,
												  m_pQuick->GetUI()->getPosY() + 21),
									  "����ʾ�����");



	//============================================================================================
	// �����
	//============================================================================================
	cDxImgUI* temp;
	int mapX = WINSIZEX / 2;
	int mapY = WINSIZEY / 2;

	//��1
	temp = new cDxImgUI("worldmap");
	//temp = new cDxImgUI("worldmapTest");
	temp->GetUI()->SetPosition(D3DXVECTOR3(mapX, mapY, 0));
	temp->GetUI()->SetCenterDraw(true);
	m_vecWorldmap.push_back(temp);

	//��2
	temp = new cDxImgUI("worldmap2");
	temp->GetUI()->SetPosition(D3DXVECTOR3(mapX, mapY, 0));
	temp->GetUI()->SetCenterDraw(true);
	m_vecWorldmap.push_back(temp);

	//��3
	temp = new cDxImgUI("worldmap3");
	temp->GetUI()->SetPosition(D3DXVECTOR3(mapX, mapY, 0));
	temp->GetUI()->SetCenterDraw(true);
	m_vecWorldmap.push_back(temp);

	DXIMG_MANAGER->GetDxImg("worldmap_cover")->setPos(mapX, mapY);
	DXIMG_MANAGER->GetDxImg("worldmap_cover")->SetCenterDraw(true);


	//============================================================================================
	// ��ų 
	//============================================================================================

	//��ų�� �ִϸ��̼� �ݺ����� ����
	DXIMGANI_MANAGER->setDxAniIsOnce("skillbook01", true);

	//��ų ����
	cUISkill* tempSkill;

	tempSkill = new cUISkill("btn_skill00_on", "btn_skill00_off", "��Ÿ��0", '1', 1308, 761, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill01_on", "btn_skill01_off", "��Ÿ��1", '2', m_vecUISkill[0]->GetUI()->getPos().x + 64 + 10, 761, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill02_on", "btn_skill02_off", "��Ÿ��2", '3', m_vecUISkill[1]->GetUI()->getPos().x + 64 + 10, 761, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill03_on", "btn_skill03_off", "��Ÿ��3", '4', m_vecUISkill[2]->GetUI()->getPos().x + 64 + 10, 761, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill04_on", "btn_skill04_off", "��Ÿ��4", '5', 1308, 833, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill05_on", "btn_skill05_off", "��Ÿ��5", '6', m_vecUISkill[0]->GetUI()->getPos().x + 64 + 10, 833, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill06_on", "btn_skill06_off", "��Ÿ��6", '7', m_vecUISkill[1]->GetUI()->getPos().x + 64 + 10, 833, false);	m_vecUISkill.push_back(tempSkill);
	tempSkill = new cUISkill("btn_skill07_on", "btn_skill07_off", "��Ÿ��7", '8', m_vecUISkill[2]->GetUI()->getPos().x + 64 + 10, 833, false);	m_vecUISkill.push_back(tempSkill);



	//============================================================================================
	// ä��â
	//============================================================================================
	m_pChat = new cUIchatting;
	m_pBtnChat = new cDxImgButton(DXIMG_MANAGER->GetDxImg("chat_Icon"),
								  DXIMG_MANAGER->GetDxImg("chat_Icon"),
								  D3DXVECTOR2(0, WINSIZEY - 64), "ä�ù�ư");



	//============================================================================================
	// ���� ����
	//============================================================================================
	m_pShopSlot = new cUIShopSlot("shopSlot_back", 80, 50, 30, 250);
	m_pShopSlot->GetUI()->SetPosition(D3DXVECTOR3(-85, 200, 0));
	m_pShopSlot->SetCountMax(40);
	m_pShopSlot->SetBtnSpeed(2);


	m_pQuest = new cUIQuest("questBox", 127, 422, 97, 29);
	//m_pQuest->GetUI()->SetPosition(D3DXVECTOR3(800, 300, 0));
	m_pQuest->GetUI()->setPos(850, 100);



	//============================================================================================
	// ����, ����, ���尣 ��ư
	//============================================================================================
	m_vBtnWeaponPos ={ 17, 59 };
	m_pBtnWeapon = new cDxImgButton(DXIMG_MANAGER->GetDxImg("shopSlot_off00"),
									DXIMG_MANAGER->GetDxImg("shopSlot_over00"),
									D3DXVECTOR2(m_pShopSlot->GetUI()->GetPosition().x + m_vBtnWeaponPos.x,
												m_pShopSlot->GetUI()->GetPosition().y + m_vBtnWeaponPos.y),
									"�������������");

	m_vBtnPotionPos ={ 17,142 };
	m_pBtnPotion = new cDxImgButton(DXIMG_MANAGER->GetDxImg("shopSlot_off01"),
									DXIMG_MANAGER->GetDxImg("shopSlot_over01"),
									D3DXVECTOR2(m_pShopSlot->GetUI()->GetPosition().x + m_vBtnPotionPos.x,
												m_pShopSlot->GetUI()->GetPosition().y + m_vBtnPotionPos.y),
									"�������������");

	m_vBtnReinforcePos ={ 17 ,223 };
	m_pBtnReinforce = new cDxImgButton(DXIMG_MANAGER->GetDxImg("shopSlot_off02"),
									   DXIMG_MANAGER->GetDxImg("shopSlot_over02"),
									   D3DXVECTOR2(m_pShopSlot->GetUI()->GetPosition().x + m_vBtnReinforcePos.x,
												   m_pShopSlot->GetUI()->GetPosition().y + m_vBtnReinforcePos.y),
									   "��ȭ����������");




	//=============================================================================
	// �̴ϸ� ����
	//=============================================================================

	//�̴ϸ� Ʋ
	m_pMiniMap = new cDxImgUI("minimap_cover");
	m_pMiniMap->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX - m_pMiniMap->GetUI()->GetSize().fWidth,
												 0, 0));

	//�̴ϸ� ��ư
	m_pBtnMap  = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_minimap_off"),
								  DXIMG_MANAGER->GetDxImg("btn_minimap_on"),
								  D3DXVECTOR2(1390, 320),
								  "�ʾ�����");
	m_pBtnMap->SetIsCheck(true);


	//���̴�
	DXIMG_MANAGER->GetDxImg("radar")->SetCenterDraw(true);
	DXIMG_MANAGER->GetDxImg("radar")->SetImgAlpha(64);

	
	//��ʽ�
	//m_fMinimapMoveX = DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth * m_fPlayerPosX / m_fTerrainSizeX;
	//m_fMinimapMoveY = DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fHeight * (m_fTerrainSizeX - m_fPlayerPosY) / m_fTerrainSizeX;

	m_fMinimapMoveX = m_vecWorldmap[m_nMapNum]->GetUI()->GetSize().fWidth * m_fPlayerPosX / m_fTerrainSizeX;
	m_fMinimapMoveY = m_vecWorldmap[m_nMapNum]->GetUI()->GetSize().fHeight * (m_fTerrainSizeX - m_fPlayerPosY) / m_fTerrainSizeX;


	

	//������ �̴ϸ�
	DXIMG_MANAGER->GetDxImg(m_szMinimap)->SetPosition(D3DXVECTOR3(WINSIZEX - DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth / 2, 0, 0));
	DXIMG_MANAGER->GetDxImg(m_szMinimap)->SetCenterDraw(false);

	//�̴ϸ� �÷��̾� -> �̴ϸʿ����� ��ġ�� ��ʽ����� ���س���.
	DXIMG_MANAGER->GetDxImg("minimap_player")->SetPosition(D3DXVECTOR3(m_fMinimapMoveX / 2 + DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetPosition().x,
																	   m_fMinimapMoveY / 2 + DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetPosition().y,
																	   0));
	DXIMG_MANAGER->GetDxImg("minimap_player")->SetCenterDraw(true);

	//�̴ϸʿ��� ���̴��� ��ġ�� �̴ϸ��÷��̾�+�̴ϸ��� ��ǥ
	DXIMG_MANAGER->GetDxImg("radar")->SetPosition(D3DXVECTOR3(DXIMG_MANAGER->GetDxImg("minimap_player")->GetPosition().x,
															  DXIMG_MANAGER->GetDxImg("minimap_player")->GetPosition().y,
															  0));


	//=================================================================================
	// ���� ����
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
	// ü��
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

	//ü���� 0���ϰ� �ȴٸ�...
	if (m_pBar->getCursorBar() <= 0)
	{
		m_pYouDied->SetIsDied(true);
	}
	else
	{
		m_pYouDied->SetIsDied(false);
	}


	//=================================================================================
	// ����
	//=================================================================================
	m_pBar2->moveBar((float)PLAYERMANAGER->GetMp() / (float)PLAYERMANAGER->GetMaxMp() * 100);
	//m_pBar2->moveBar(0.0f);



	//=================================================================================
	// ��ų
	//=================================================================================
	for (int i=0; i<m_vecUISkill.size(); i++)
	{
		m_vecUISkill[i]->update();
	}


	//=================================================================================
	// ä�� ����
	//=================================================================================
	m_pChat->update();



	//=================================================================================
	// ���� ����
	//=================================================================================
	m_pShopSlot->update();



	//=================================================================================
	// ����,����,���尣 ��ư -> ���� ����
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
	// ����Ʈ ��ư
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
	// �̴ϸ� ��ư
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

	//���� �̴ϸ��� off���¶��
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
	// ä��â ���� ��ư
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
	// �κ� ��ư
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
	// ��ų�� ��ư
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
	// ����� ��ư
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
	// �ҿ� ��ư
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
	// ��� ��ư
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

	//ä��â�� �׸���.
	if (m_pBtnChat->GetIsCheck())
	{
		m_pChat->render();
	}
	m_pBtnChat->render();

	//ä��â ���� ��ư�� �׸���.
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

	//����Ʈ ��ư�� �׸���.
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


	//�ҿ�
	if (m_pBtnSoul->GetIsCheck())
	{
		DXIMG_MANAGER->GetDxImg("death_soul")->render();
	}


	//���
	if (m_pBtnGold->GetIsCheck())
	{
		DXIMG_MANAGER->GetDxImg("gold_god")->render();
	}








	//�ҿ� ����
	//m_pSour->render();
	m_pBtnSoul->render();

	//��� ����
	//m_pMoney->render();
	m_pBtnGold->render();


	//===============================================
	//�̴ϸ� Ʋ�� �׸���.
	//===============================================
	if (m_pBtnMap->GetIsCheck() && m_pBtnMap->GetOff()->GetPosition().y == 320)
	{
		DXIMG_MANAGER->render(m_szMinimap,
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth / 4,
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fHeight / 4,
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth / 2,		//������ ���α���
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fHeight / 2,		//������ ���α���
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fWidth / 2 - m_fMinimapMoveX,
							  DXIMG_MANAGER->GetDxImg(m_szMinimap)->GetSize().fHeight / 2 - m_fMinimapMoveY);

		DXIMG_MANAGER->GetDxImg("radar")->render(0, 0, m_fRaderAngle - 180);
		DXIMG_MANAGER->render("minimap_player");
		m_pMiniMap->render();
	}
	m_pBtnMap->render();

	

	//===============================================
	// �κ��丮�� �׸���.
	//===============================================
	if (m_isInven)
	{
		_inven->render();
		_playerItem->render();
	}


	//===============================================
	// ��ųâ�� �׸���.
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
	// ��ų
	//=================================================================================
	for (int i=0; i<m_vecUISkill.size(); i++)
	{
		m_vecUISkill[i]->render();
	}



	//===============================================
	// ����� ��ư Ŭ���� ���� ����
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
