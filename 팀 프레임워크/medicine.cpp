#include "stdafx.h"
#include "medicine.h"

medicine::medicine() { settinhItem(), settingItemRender();  }
medicine::~medicine() { }

void medicine::settinhItem()
{
	//빨간물약정보----------------------
	//빨간물약(1)
	_medicine.number = 1;
	_medicine.attack = 0;
	_medicine.armorAbility = 0;
	_medicine.hpAbility = 50;
	_medicine.mpAbility = 0;
	_medicine.medicineCount = 1;
	_medicine.price = 100;
	_medicine.type = ITEMKIND::HPMEDICINE;
	_vMedicine.push_back(_medicine);

	//빨간물약(2)
	_medicine.number = 2;
	_medicine.attack = 0;
	_medicine.armorAbility = 0;
	_medicine.hpAbility = 100;
	_medicine.mpAbility = 0;
	_medicine.medicineCount = 1;
	_medicine.price = 200;
	_medicine.type = ITEMKIND::HPMEDICINE;
	_vMedicine.push_back(_medicine);

	//파란물약정보 
	//빨간물약(1)
	_medicine.number = 3;
	_medicine.attack = 0;
	_medicine.armorAbility = 0;
	_medicine.hpAbility = 0;
	_medicine.mpAbility = 100;
	_medicine.medicineCount = 1;
	_medicine.price = 100;
	_medicine.type = ITEMKIND::MPMEDICINE;
	_vMedicine.push_back(_medicine);

	//빨간물약(2)
	_medicine.number = 4;
	_medicine.attack = 0;
	_medicine.armorAbility = 0;
	_medicine.hpAbility = 0;
	_medicine.mpAbility = 200;
	_medicine.medicineCount = 1;
	_medicine.price = 200;
	_medicine.type = ITEMKIND::MPMEDICINE;
	_vMedicine.push_back(_medicine);
}

void medicine::settingItemRender()
{
	//빨간물약렌더-------------------- -
	//빨간(1)
	_medicineRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/물약1.png");
	_medicineRender.kind = ITEMKIND::HPMEDICINE;
	_vMedicineRender.push_back(_medicineRender);

	//빨간(2)
	_medicineRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/물약2.png");
	_medicineRender.kind = ITEMKIND::HPMEDICINE;
	_vMedicineRender.push_back(_medicineRender);


	//파란물약렌더-------------------- -
	//파란(3)
	_medicineRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/물약3.png");
	_medicineRender.kind = ITEMKIND::MPMEDICINE;
	_vMedicineRender.push_back(_medicineRender);

	//파란(4)
	_medicineRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/물약4.png");
	_medicineRender.kind = ITEMKIND::MPMEDICINE;
	_vMedicineRender.push_back(_medicineRender);

}


