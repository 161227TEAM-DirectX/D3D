#include "stdafx.h"
#include "boundSphere.h"

//월드단위의 센터와 반지름을 얻는다
void boundSphere::getWorldCenterRadius(dx::transform * trans, D3DXVECTOR3 * center, float * raius)
{
	//최종행렬 가져오기
	D3DXMATRIXA16 matFinal = trans->GetFinalMatrix();

	//월드 센터로 이동(벡터와 행렬 연산으로 벡턱값 뽑을때 사용하는 함수)
	D3DXVec3TransformCoord(center, &_localCenter, &matFinal);
	
	//스케일값 가져오기
	D3DXVECTOR3 scale = trans->GetScale();

	//구의 길이
	D3DXVECTOR3 halfSize;
	halfSize.x = _halfSize.x * scale.x;
	halfSize.y = _halfSize.y * scale.y;
	halfSize.z = _halfSize.z * scale.z;

	*raius = D3DXVec3Length(&halfSize);
}


//월드 단위로 그리기
void boundSphere::renderGizmo(dx::transform * trans)
{
	D3DXVECTOR3 worldCenter;
	float radius;
	this->getWorldCenterRadius(trans, &worldCenter, &radius);
	GIZMOMANAGER->WireSphere(worldCenter, radius, 0xffffff00);
}

//바운드 세팅하기
void boundSphere::setBound(D3DXVECTOR3 * center, D3DXVECTOR3 * halfSize)
{
	_localCenter = *center;
	_halfSize = *halfSize;
	_radius = D3DXVec3Length(halfSize);
}

