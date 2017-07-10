#pragma once

class boundSphere
{
public:
	D3DXVECTOR3		_localCenter;	//���� ������ǥ
	D3DXVECTOR3		_halfSize;		//���� ������
	float			_radius;		//������

public:
	//��������� ���Ϳ� �������� ��´�
	void getWorldCenterRadius(dx::transform* trans, D3DXVECTOR3* center, float* raius);
	//���� ������ �׸���
	virtual void renderGizmo(dx::transform* trans);
	virtual void renderGizmo(dx::transform* trans, D3DCOLOR color);
	//�ٿ�� �����ϱ�
	virtual void setBound(D3DXVECTOR3* center, D3DXVECTOR3* halfSize);

	inline D3DXVECTOR3& getLocalCenter(void) { return _localCenter; }
	inline D3DXVECTOR3& getHalfSize(void) { return _halfSize; }
	inline float& getRadius(void) { return _radius; }

	inline void setLocalCenter(D3DXVECTOR3& temp) { this->_localCenter = temp; }
	inline void setLocalCenter(float& x, float& y, float& z) { setLocalCenter(D3DXVECTOR3(x, y, z)); }

	inline void setHalfSize(D3DXVECTOR3& temp) { this->_halfSize = temp; }
	inline void setHalfSize(float& x, float& y, float& z) { setHalfSize(D3DXVECTOR3(x, y, z)); }

	inline void setRadius(float& temp) { this->_radius = temp; }

	boundSphere() {}
	~boundSphere() {}
};

