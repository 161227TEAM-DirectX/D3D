#pragma once
#include "boundSphere.h"

class boundBox : public boundSphere
{
public:
	D3DXVECTOR3		_localMinPos;
	D3DXVECTOR3		_localMaxPos;

public:
	void getWorldBox(dx::transform* trans, D3DXVECTOR3* outBoxPos);
	void getWorldAABBMinMax(dx::transform* trans, D3DXVECTOR3* min, D3DXVECTOR3* max);

	//월드 단위로 그리기
	virtual void renderGizmo(dx::transform* trans) override;
	virtual void renderGizmo(dx::transform* trans, D3DCOLOR color) override;
	//바운드 세팅하기
	virtual void setBound(D3DXVECTOR3* center, D3DXVECTOR3* halfSize) override;

	boundBox() {}
	~boundBox() {}
};

