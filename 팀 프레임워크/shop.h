#pragma once
#include "iGameNode.h"
#include "armor.h"
#include "weapon.h"

#define NUMBER 18

class inven;
class playerItem;

class shop : public iGameNode
{
//������ Ŭ����
private:
	armor* _armor;
	weapon* _weapon;
	inven* _inven;
	playerItem* _playerItem;

//SHOP ������
private:
	ITEMIMAGE _SHOP;                                 //�������UI
	ITEMIMAGE _ShopWeaponRender[5];                 //�������������
	ITEMIMAGE _ShopArmorRender[5];                  //������������
	ITEMIMAGE _ShopButton[2];                        //���,�ȱ� ��ư
	ITEMIMAGE _temp;                                 //�������͸� ���� ����


	//������ ������ ����� �ִ� ����
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

