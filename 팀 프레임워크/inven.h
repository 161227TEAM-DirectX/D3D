#pragma once
#include "iGameNode.h"
#include "item.h"

class force;
class shop;
class playerItem;
class medicineShop;

class inven : public iGameNode
{
private:
	force* _force;
	shop* _shop;
	playerItem* _playerItem;
	medicineShop* _medicineShop;
private:
	//인벤바탕
	ITEMIMAGE _inven;
	ITEMIMAGE _temp;
	ITEMIMAGE _invenButton[2];

	ITEMIMAGE _invenItemInformation;

	//인벤아이템렌더벡터
	vector<ITEMIMAGE> _vinvenItemRender;

	//인벤아이템정보
	vector<ITEMINFOMATION> _vinvenItem;
	ITEMINFOMATION _tempInformation;
	ITEMINFOMATION _tempNumber;        //정보값 숫자
	bool _tempNumberBool[18];

	pair <bool, POINT> _pick;
	int _tempItem;                                   //팔떄 필요한 변수
	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void invenPickUpdate();
	void invenButtonUpdate();
    
	void removeInvenItem(int num);
	void removeInvenItemInformation(int num);

	void setShopLink(shop* shop) { _shop = shop; }
	void setForceLink(force* force) { _force = force; }
	void setPlayerItemLink(playerItem* playerItem) { _playerItem = playerItem; }
	void setmedicineShopLink(medicineShop* medicineShop) { _medicineShop = medicineShop; }

	void setPick(pair<bool, POINT>& temp) { this->_pick = temp; }

	pair<bool, POINT> getPick(void) { return _pick; }
	int getTempItem(void) { return _tempItem; }

	ITEMIMAGE getInvenBack() { return _inven; }

	ITEMINFOMATION getTempInformation() { return _tempInformation; }
	void setTempInformation(ITEMINFOMATION& tempInformation) { _tempInformation = tempInformation; }

	ITEMIMAGE getTempRender() { return _temp; }
	void setTempRender(ITEMIMAGE& temp) { _temp = temp; }

	vector<ITEMIMAGE> getVinvenitemRender() { return _vinvenItemRender; }
	void setVinvenItemRender(ITEMIMAGE& invenItemRender) { _vinvenItemRender.push_back(invenItemRender); }

	vector<ITEMINFOMATION> getVinvenitem() { return _vinvenItem; }
	void setVinvenItem(ITEMINFOMATION& invenItem) { _vinvenItem.push_back(invenItem); }



	inven() {}
	~inven() {}
};

