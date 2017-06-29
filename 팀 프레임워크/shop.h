#pragma once
#include "iGameNode.h"
#include "armor.h"
#include "weapon.h"

#define NUMBER 18

class inven;
class playerItem;

class shop : public iGameNode
{
//아이템 클래스
private:
	armor* _armor;
	weapon* _weapon;
	inven* _inven;
	playerItem* _playerItem;

//SHOP 아이템
private:
	ITEMIMAGE _SHOP;                                 //상점배경UI
	ITEMIMAGE _ShopWeaponRender[5];                 //상점무기아이템
	ITEMIMAGE _ShopArmorRender[5];                  //상점방어구아이템
	ITEMIMAGE _ShopButton[2];                        //사기,팔기 버튼
	ITEMIMAGE _temp;                                 //렌더벡터를 담을 변수


	//아이템 정보가 담겨져 있는 벡터
	vector<ITEMINFOMATION> _ShopWeapon;
	vector<ITEMINFOMATION> _ShopArmor;
	ITEMINFOMATION _tempInfomation;

	pair <bool, POINT> _pick;
	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void shopPickUpdate();

	void setInvenLink(inven* inven) { _inven = inven; }
	void setPlayerItemLink(playerItem* playerItem) { _playerItem = playerItem; }
	void setPick(pair<bool, POINT>& temp) { this->_pick = temp; }
	
	shop() {}
	~shop() {}
};

