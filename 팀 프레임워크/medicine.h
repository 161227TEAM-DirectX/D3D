#pragma once
#include "item.h"
class medicine : public item
{
private:
	//아이템 정보
	ITEMINFOMATION _medicine;
	vector<ITEMINFOMATION> _vMedicine;
	//아이템 렌더
	ITEMIMAGE _medicineRender;
	vector<ITEMIMAGE> _vMedicineRender;

public:

	void settinhItem();
	void settingItemRender();

	//아이템렌더  get
	vector<ITEMIMAGE> getVmedicineRender() { return _vMedicineRender; }
	vector<ITEMINFOMATION> getVmedicene() { return _vMedicine; }

	medicine();
	~medicine();
};

