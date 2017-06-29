#pragma once
#include "iGameNode.h"
#include "medicine.h"

#define MENUMBER 4

class inven;

class medicineShop : public iGameNode
{
//클래스들
private:
	medicine* _medicine;
	inven* _inven;

//보여지는 변수들
private:
	ITEMIMAGE _medicineShop;
	ITEMIMAGE _medicineTemp;
	ITEMIMAGE _medicineButton[2];
	ITEMIMAGE _medicinePMbutton[3];
	ITEMIMAGE _medicineSellMenu;
	ITEMIMAGE _medicineSellButton[2];
	ITEMIMAGE _medicinePMSellButton[2];

	vector<ITEMINFOMATION> _vmidicine;
	ITEMINFOMATION _tempInfomation;

	ITEMINFOMATION _countTemp;
	ITEMINFOMATION _count2Temp;

//상세 정보 변수들
private:
	ITEMIMAGE _medicineRender[4];

private:
	bool _countStrart;
	bool _tempTemp;
	pair <bool, POINT> _pick;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setmedicineShopLink(inven* inven) { _inven = inven; }
	void setPick(pair<bool, POINT>& pick) { this->_pick = pick; }

	bool gettempTemp(void) { return _tempTemp; }
	void settempTemp(bool tempTemp) { _tempTemp = tempTemp; }

	medicineShop() {}
	~medicineShop() {}
};

