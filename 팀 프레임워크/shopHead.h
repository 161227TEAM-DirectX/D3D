#pragma once
#include "iGameNode.h"
#include "shop.h"
#include "inven.h"
#include "playerItem.h"
#include "medicineShop.h"
#include "force.h"

class shopHead : public iGameNode
{
private:
	shop* _shop;
	inven* _inven;
	medicineShop* _medicineShop;
	playerItem* _playerItem;
	force* _force;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	shopHead() {}
	~shopHead() {}
};

