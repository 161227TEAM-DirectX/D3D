#pragma once

class boundSphere
{
public:
	D3DXVECTOR3		_localCenter;	//���� ������ǥ
	D3DXVECTOR3		_halfSize;		//���� ������
	float			_radius;		//������

public:
	//��������� ���Ϳ� �������� ��´�
	void getWorldCenterRadius(transform* trans, D3DXVECTOR3* center, float* raius);
	//���� ������ �׸���
	virtual void renderGizmo(transform* trans);
	//�ٿ�� �����ϱ�
	virtual void setBound(D3DXVECTOR3* center, D3DXVECTOR3* halfSize);

	boundSphere() {}
	~boundSphere() {}
};

