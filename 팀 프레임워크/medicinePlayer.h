#pragma once
#include "iGameNode.h"
#include "item.h"

class inven;

class medicinePlayer : public iGameNode
{
private:
	inven* _inven;

private:
	ITEMIMAGE RHtemp;
	ITEMINFOMATION IHtemp;
	bool HB;

	ITEMIMAGE RMtemp;
	ITEMINFOMATION IMtemp;
	bool MB;

	vector<ITEMIMAGE> _vHPMedicinePlayerRender;
	vector<ITEMINFOMATION> _vHPMedicinePlayerInforMation;

	vector<ITEMIMAGE> _vMPMedicinePlayerRender;
	vector<ITEMINFOMATION> _vMPMedicinePlayerInforMation;

	int _HPdublePick;
	int _MPdublePick;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setInvenLink(inven* inven) { _inven = inven; }

	void removeInvenItem(int num);
	void removeInvenItemInformation(int num);
	void removeInvenItem2(int num);
	void removeInvenItem2Information(int num);

	vector<ITEMIMAGE> getvHPMedicinePlayerRender() { return _vHPMedicinePlayerRender; }
	void setvHPMedicinePlayerRender(ITEMIMAGE& invenItemRender) { _vHPMedicinePlayerRender.push_back(invenItemRender); }

	vector<ITEMINFOMATION> getvHPMedicinePlayerInforMation() { return _vHPMedicinePlayerInforMation; }
	void setvHPMedicinePlayerInforMation(ITEMINFOMATION& invenItem) { _vHPMedicinePlayerInforMation.push_back(invenItem); }

	vector<ITEMIMAGE> getvMPMedicinePlayerRender() { return _vMPMedicinePlayerRender; }
	void setvMPMedicinePlayerRender(ITEMIMAGE& invenItemRender) { _vMPMedicinePlayerRender.push_back(invenItemRender); }

	vector<ITEMINFOMATION> getvMPMedicinePlayerInforMation() { return _vMPMedicinePlayerInforMation; }
	void setvMPMedicinePlayerInforMation(ITEMINFOMATION& invenItem) { _vMPMedicinePlayerInforMation.push_back(invenItem); }

	medicinePlayer() {}
	~medicinePlayer() {}
};