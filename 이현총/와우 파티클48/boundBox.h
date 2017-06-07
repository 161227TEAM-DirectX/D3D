#pragma once
#include "boundSphere.h"

class boundBox : public boundSphere
{
public:
	D3DXVECTOR3		_localMinPos;
	D3DXVECTOR3		_localMaxPos;

public:
	void getWorldBox(transform* trans, D3DXVECTOR3* outBoxPos);
	void getWorldAABBMinMax(transform* trans, D3DXVECTOR3* min, D3DXVECTOR3* max);

	//���� ������ �׸���
	virtual void renderGizmo(transform* trans) override;
	//�ٿ�� �����ϱ�
	virtual void setBound(D3DXVECTOR3* center, D3DXVECTOR3* halfSize) override;

	boundBox() {}
	~boundBox() {}
};

