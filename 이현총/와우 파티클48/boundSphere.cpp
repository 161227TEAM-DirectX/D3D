#include "stdafx.h"
#include "boundSphere.h"

//��������� ���Ϳ� �������� ��´�
void boundSphere::getWorldCenterRadius(transform * trans, D3DXVECTOR3 * center, float * raius)
{
	//������� ��������
	D3DXMATRIXA16 matFinal = trans->GetFinalMatrix();
	//�����ϰ� ��������
	D3DXVECTOR3 scale = trans->GetScale();

	//���� ���ͷ� �̵�(���Ϳ� ��� �������� ���ΰ� ������ ����ϴ� �Լ�)
	D3DXVec3TransformCoord(center, &_localCenter, &matFinal);
	
	//���� ����
	D3DXVECTOR3 halfSize;
	halfSize.x = _halfSize.x * scale.x;
	halfSize.y = _halfSize.y * scale.y;
	halfSize.z = _halfSize.z * scale.z;

	*raius = D3DXVec3Length(&halfSize);
}


//���� ������ �׸���
void boundSphere::renderGizmo(transform * trans)
{
	D3DXVECTOR3 worldCenter;
	float radius;
	this->getWorldCenterRadius(trans, &worldCenter, &radius);
	GIZMOMANAGER->WireSphere(worldCenter, radius, 0xffffff00);
}

//�ٿ�� �����ϱ�
void boundSphere::setBound(D3DXVECTOR3 * center, D3DXVECTOR3 * halfSize)
{
	_localCenter = *center;
	_halfSize = *halfSize;
	_radius = D3DXVec3Length(halfSize);
}

