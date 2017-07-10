#include "stdafx.h"
#include "medicine.h"

medicine::medicine() { settinhItem(), settingItemRender();  }
medicine::~medicine() { }

void medicine::settinhItem()
{
	//������������----------------------
	//��������(1)
	_medicine.number = 1;
	_medicine.attack = 0;
	_medicine.armorAbility = 0;
	_medicine.hpAbility = 50;
	_medicine.mpAbility = 0;
	_medicine.medicineCount = 1;
	_medicine.price = 100;
	_medicine.type = ITEMKIND::HPMEDICINE;
	_vMedicine.push_back(_medicine);

	//��������(2)
	_medicine.number = 2;
	_medicine.attack = 0;
	_medicine.armorAbility = 0;
	_medicine.hpAbility = 100;
	_medicine.mpAbility = 0;
	_medicine.medicineCount = 1;
	_medicine.price = 200;
	_medicine.type = ITEMKIND::HPMEDICINE;
	_vMedicine.push_back(_medicine);

	//�Ķ��������� 
	//��������(1)
	_medicine.number = 3;
	_medicine.attack = 0;
	_medicine.armorAbility = 0;
	_medicine.hpAbility = 0;
	_medicine.mpAbility = 100;
	_medicine.medicineCount = 1;
	_medicine.price = 100;
	_medicine.type = ITEMKIND::MPMEDICINE;
	_vMedicine.push_back(_medicine);

	//��������(2)
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
	//�������෻��-------------------- -
	//����(1)
	_medicineRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/����1.png");
	_medicineRender.kind = ITEMKIND::HPMEDICINE;
	_vMedicineRender.push_back(_medicineRender);

	//����(2)
	_medicineRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/����2.png");
	_medicineRender.kind = ITEMKIND::HPMEDICINE;
	_vMedicineRender.push_back(_medicineRender);


	//�Ķ����෻��-------------------- -
	//�Ķ�(3)
	_medicineRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/����3.png");
	_medicineRender.kind = ITEMKIND::MPMEDICINE;
	_vMedicineRender.push_back(_medicineRender);

	//�Ķ�(4)
	_medicineRender.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/����4.png");
	_medicineRender.kind = ITEMKIND::MPMEDICINE;
	_vMedicineRender.push_back(_medicineRender);

}


