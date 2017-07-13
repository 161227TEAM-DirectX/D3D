#pragma once
#include "iGameNode.h"

class cUIShopSlot;
class cUIQuest;
class cUISkill;
class cUISkillBook;
class cUIYouDied;
//
class inven;
class shop;
class playerItem;
class medicineShop;
class force;


class cUIPlayer : public iGameNode
{
private:
	cDxImgUI*	 m_pPlBar;
	cDxImgBar*	 m_pBar;
	cDxImgBar*	 m_pBar2;
	cDxImgUI*	 m_pQuick;

	cUIchatting* m_pChat;
	cDxImgButton* m_pBtnChat;

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

	bool m_isInven;
	bool m_isSkillBook;
	int  m_nSkillBookCount = 0;

	bool m_isWorldMap;

	cDxImgUI*	  m_pSour;
	cDxImgUI*	  m_pMoney;
	cDxImgUI*	  m_pMiniMap;

	cDxImgButton* m_pBtnSoul;
	cDxImgButton* m_pBtnGold;

	cDxImgButton* m_pBtnMap;		//¹Ì´Ï¸Ê ¹öÆ°
	cDxImgButton* m_pBtnQuest;		//Äù½ºÆ® ¹öÆ°
	cUIQuest*	  m_pQuest;			//Äù½ºÆ®

	vector<cDxImgUI*> m_vecWorldmap;
	SYNTHESIZE(int, m_nMapNum, MapNum);
	SYNTHESIZE(float, m_fRaderAngle, RaderAngle);
	SYNTHESIZE(float, m_fMinimapMoveX, MinimapMoveX);
	SYNTHESIZE(float, m_fMinimapMoveY, MinimapMoveY);
	SYNTHESIZE(float, m_fPlayerPosX, PlayerPosX);
	SYNTHESIZE(float, m_fPlayerPosY, PlayerPosY);
	SYNTHESIZE(float, m_fTerrainSizeX, TerrainSizeX);
	SYNTHESIZE(char*, m_szMinimap, Minimap);

	vector<cUISkill*>	m_vecUISkill;			//½ºÅ³ UI
	cUISkillBook*		m_pSkillBook;			//½ºÅ³ºÏ
	cUIYouDied*			m_pYouDied;				//Á×À½

private:
	shop*		  _shop;
	inven*		  _inven;
	medicineShop* _medicineShop;
	playerItem*	  _playerItem;
	force*		  _force;

	enum eShopType
	{
		E_NONE_SHOP,
		E_WEAPON_SHOP,
		E_POTION_SHOP,
		E_REINFORCE_SHOP
	};
	eShopType m_eShopType;

public:
	cUIPlayer();
	virtual ~cUIPlayer();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void linkMinimapPlayerAngle(float angle);
	void linkMinimapPlayerMove(float posX, float posY, float terrainSizeX);
};

