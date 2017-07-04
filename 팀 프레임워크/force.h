#pragma once
#include "iGameNode.h"
#include "weapon.h"

class inven;

class force : public iGameNode
{
private:
	inven* _inven;
private:
	//변화가 없는 UI
	ITEMIMAGE _forceShop;
	ITEMIMAGE _foceGage;
	ITEMIMAGE _forceS;
	ITEMIMAGE _forceF;
	ITEMIMAGE _forceV;

	//변화가 있는 UI
	ITEMIMAGE _forceButton[3];
	ITEMIMAGE _forcePlus;
	ITEMIMAGE _forceB;

private:
	vector<ITEMIMAGE> _forceRender;
	vector<ITEMINFOMATION> _forceInformation;

	int _forceMoney;
	int _forceGaege;
	int _rand;
public:

	void setForceLink(inven* inven) { _inven = inven; }
	vector<ITEMINFOMATION> getforceInformation() { return _forceInformation; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	force() {}
	~force() {}
};

