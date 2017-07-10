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

	D3DXVECTOR3& getLocalMinPos(void) { return _localMinPos; }
	D3DXVECTOR3& getLocalMaxPos(void) { return _localMaxPos; }

	void setLocalMinPos(D3DXVECTOR3 temp) { this->_localMinPos = temp; }
	void setLocalMinPos(float x, float y, float z) { setLocalMinPos(D3DXVECTOR3(x, y, z)); }

	void setLocalMaxPos(D3DXVECTOR3 temp) { this->_localMaxPos = temp; }
	void setLocalMaxPos(float x, float y, float z) { setLocalMaxPos(D3DXVECTOR3(x, y, z)); }

	//���� ������ �׸���
	virtual void renderGizmo(dx::transform* trans) override;
	virtual void renderGizmo(dx::transform* trans, D3DCOLOR color) override;
	//�ٿ�� �����ϱ�
	virtual void setBound(D3DXVECTOR3* center, D3DXVECTOR3* halfSize) override;

	boundBox() {}
	~boundBox() {}
};

