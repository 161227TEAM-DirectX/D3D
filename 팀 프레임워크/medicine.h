#pragma once
#include "item.h"
class medicine : public item
{
private:
	//������ ����
	ITEMINFOMATION _medicine;
	vector<ITEMINFOMATION> _vMedicine;
	//������ ����
	ITEMIMAGE _medicineRender;
	vector<ITEMIMAGE> _vMedicineRender;

public:

	void settinhItem();
	void settingItemRender();

	//�����۷���  get
	vector<ITEMIMAGE> getVmedicineRender() { return _vMedicineRender; }
	vector<ITEMINFOMATION> getVmedicene() { return _vMedicine; }

	medicine();
	~medicine();
};

