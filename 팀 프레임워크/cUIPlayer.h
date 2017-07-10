#pragma once
#include "iGameNode.h"

class cUIShopSlot;
//
class inven;
class shop;
class playerItem;
class medicineShop;
class force;
class medicinePlayer;


class cUIPlayer : public iGameNode
{
private:
	cDxImgUI*	 m_pPlBar;
	cDxImgBar*	 m_pBar;
	cDxImgBar*	 m_pBar2;
	cDxImgUI*	 m_pQuick;
	cUIchatting* m_pChat;

	cUIShopSlot* m_pShopSlot;

	cDxImgButton* m_pBtnWeapon;
	cDxImgButton* m_pBtnPotion;
	cDxImgButton* m_pBtnReinforce;

	D3DXVECTOR2   m_vBtnWeaponPos;
	D3DXVECTOR2   m_vBtnPotionPos;
	D3DXVECTOR2   m_vBtnReinforcePos;

	cDxImgButton* m_pBtnInven;
	cDxImgButton* m_pBtnSkillBook;
	cDxImgButton* m_pBtnWorldMap;

	bool m_isInven = false;
	bool m_isSkillBook = false;
	bool m_isWorldMap = false;

	cDxImgUI*	  m_pSour;
	cDxImgUI*	  m_pMoney;
	cDxImgUI*	  m_pMiniMap;



private:
	shop*		  _shop;
	inven*		  _inven;
	medicineShop* _medicineShop;
	playerItem*	  _playerItem;
	force*		  _force;
	medicinePlayer* _medicinePlayer;

	enum eShopType
	{
		E_NONE_SHOP,
		E_WEAPON_SHOP,
		E_POTION_SHOP,
		E_REINFORCE_SHOP
	};
	eShopType m_eShopType = E_NONE_SHOP;

public:
	cUIPlayer();
	virtual ~cUIPlayer();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

