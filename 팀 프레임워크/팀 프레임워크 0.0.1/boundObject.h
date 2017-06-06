#pragma once
#include "baseObject.h"

class boundObject : public baseObject
{
private:
	D3DXVECTOR3		_center;
	D3DXVECTOR3		_halfSize;

public:
	boundObject()
	{
		_center = D3DXVECTOR3(0, 0, 0);
		_halfSize = D3DXVECTOR3(1, 1, 1);
	}
	~boundObject() {}

	virtual void baseObjectUpdate() override;
};

