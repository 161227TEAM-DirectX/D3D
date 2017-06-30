#pragma once
#include "iGameNode.h"
#include "item.h"

class inven;
class shop;

class playerItem : public iGameNode
{
private:
	//인벤상호참조클래스
	inven* _inven;
	shop* _shop;

	pair<bool, POINT> _pick;

	int _tempItem;
	ITEMIMAGE _temp;
	ITEMIMAGE _statItemWeapon;
	ITEMIMAGE _statItemArmor;

	//플레이어아이템렌더벡터
	vector<ITEMIMAGE> _playerWeaponItemRender;
	vector<ITEMIMAGE> _playerArmorItemRender;

	//플레이어아이템정보렌벡터
	vector<ITEMINFOMATION> _playerWeaponItem;
	vector<ITEMINFOMATION> _playerArmorItem;

	//플레이어 정보
	ITEMINFOMATION _playerInfomation;

private:
	int playerAttack;
	int playerArmor;

public:

	int getTempItem(void) { return _tempItem; }
	ITEMIMAGE getTemp(void) { return _temp; }
	ITEMINFOMATION getTempInformation(void){ return _playerInfomation; }

	vector<ITEMIMAGE> getPlaterWeaponItemRender() { return _playerWeaponItemRender; }
	void setPlayerWeaponItem(ITEMIMAGE& PlaterWeaponItemRender) { _playerWeaponItemRender.push_back(PlaterWeaponItemRender); }

	vector<ITEMIMAGE> getplayerArmorItemRender() { return _playerArmorItemRender; }
	void setPlayerArmorItem(ITEMIMAGE& playerArmorItemRender) { _playerArmorItemRender.push_back(playerArmorItemRender); }

	vector<ITEMINFOMATION> getWeaponInfomation() { return _playerWeaponItem; }
	void setWeaponInfomation(ITEMINFOMATION& playerWeaponItem) { _playerWeaponItem.push_back(playerWeaponItem); }

	vector<ITEMINFOMATION> getArmorInformation() { return _playerArmorItem; }
	void setArmorInformation(ITEMINFOMATION& playerArmorItem) { _playerArmorItem.push_back(playerArmorItem); }
	
	void setPick(pair<bool, POINT>& temp) { this->_pick = temp; }
	pair<bool, POINT> getPick(void) { return _pick; }

	void setInvenLink(inven* inven) { _inven = inven; }
	void setShopLink(shop* shop) { _shop = shop; }

	//플레이어 스탯
	int getPlayerAttack(void) { return playerAttack; }
	int getPlayerArmor(void) { return playerArmor; }

	void setPlayerAttack(int _playerAttack) { playerAttack = _playerAttack; }
	void setPlayerArmor(int _playerArmor) { playerArmor = _playerArmor; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void removePlayerItem(int num , ITEMIMAGE temp);
	void removePlayerItemInformation(int num, ITEMINFOMATION temp);
	void removePlaterInformation(ITEMINFOMATION temp);

	void updatePlayerInfo();

	playerItem() {}
	~playerItem() {}
};

