#include "stdafx.h"
#include "frustum.h"
#include "baseObject.h"

frustum::frustum()
{
	//동차 좌표 정보 저장
	//					  4-------5  <-( 1, 1, 1 )
	//					 /|		 /|
	//					0-------1 |
	//					| 6-----|-7
	//					|/      |/
	//( -1, -1, 0 )->	2-------3
	_RHWPos[0] = D3DXVECTOR3( -1,  1,  0 );
	_RHWPos[1] = D3DXVECTOR3(  1,  1,  0 );
	_RHWPos[2] = D3DXVECTOR3( -1, -1,  0 );
	_RHWPos[3] = D3DXVECTOR3(  1, -1,  0 );
	_RHWPos[4] = D3DXVECTOR3( -1,  1,  1 );
	_RHWPos[5] = D3DXVECTOR3(  1,  1,  1 );
	_RHWPos[6] = D3DXVECTOR3( -1, -1,  1 );
	_RHWPos[7] = D3DXVECTOR3(  1, -1,  1 );
}

frustum::~frustum()
{
}

//프러스텀 정보 업데이트 (View * Projection 행렬을 요구한다)
void frustum::updateFrustum(D3DXMATRIXA16 * pmatViewProj)
{
	//ViewProjection 의 역행렬
	D3DXMATRIXA16	matInv;
	D3DXMatrixInverse(&matInv, NULL, pmatViewProj);

	//동차 좌표의 정점을 역행렬에 적용
	for (int i = 0; i < 8; i++) 
	{
		D3DXVec3TransformCoord(_pos + i, _RHWPos + i, &matInv);
	}

	//플랜 업데이트
	//동차 좌표 정보 저장
	//					  4-------5  <-( 1, 1, 1 )
	//					 /|		 /|
	//					0-------1 |
	//					| 6-----|-7
	//					|/      |/
	//( -1, -1, 0 )->	2-------3

	//정면 평면
	PHYSICSMANAGER->createPlane(&_plane[0], &_pos[0], &_pos[1], &_pos[2]);
	//후면
	PHYSICSMANAGER->createPlane(&_plane[1], &_pos[5], &_pos[4], &_pos[7]);
	//우측
	PHYSICSMANAGER->createPlane(&_plane[2], &_pos[1], &_pos[5], &_pos[3]);
	//좌측
	PHYSICSMANAGER->createPlane(&_plane[3], &_pos[4], &_pos[0], &_pos[6]);
	//상방
	PHYSICSMANAGER->createPlane(&_plane[4], &_pos[4], &_pos[5], &_pos[0]);
	//하단
	PHYSICSMANAGER->createPlane(&_plane[5], &_pos[2], &_pos[3], &_pos[6]);
}

//Base 오브젝트가 프러스텀 안에있는지 체크
bool frustum::isInFrustum(baseObject * pObject)
{
	//월드 구정보
	D3DXVECTOR3 worldCenter;
	float radius;

	pObject->_boundBox.getWorldCenterRadius(
		pObject->_transform,
		&worldCenter,
		&radius);

	//worldCenter가 절두체의 각 6면 안쪽에 있는지 확인
	for (int i = 1; i < 6; i++)
	{
		//면과의 거리
		float dist = PHYSICSMANAGER->planeDot(&_plane[i], &worldCenter);

		//반지름 이상 벗어나면 절두체 안에 없음....
		if (dist > radius) return false;
	}

	return true;
}

//프러스텀 기즈모를 그린다.
void frustum::renderGizmo()
{
	DWORD color = 0xff00ffff;
	//동차 좌표 정보 저장
	//					  4-------5  <-( 1, 1, 1 )
	//					 /|		 /|
	//					0-------1 |
	//					| 6-----|-7
	//					|/      |/
	//( -1, -1, 0 )->	2-------3
	
	GIZMOMANAGER->Line(_pos[0], _pos[1], color);
	GIZMOMANAGER->Line(_pos[1], _pos[3], color);
	GIZMOMANAGER->Line(_pos[3], _pos[2], color);
	GIZMOMANAGER->Line(_pos[2], _pos[0], color);

	GIZMOMANAGER->Line(_pos[4], _pos[5], color);
	GIZMOMANAGER->Line(_pos[5], _pos[7], color);
	GIZMOMANAGER->Line(_pos[7], _pos[6], color);
	GIZMOMANAGER->Line(_pos[6], _pos[4], color);

	GIZMOMANAGER->Line(_pos[0], _pos[4], color);
	GIZMOMANAGER->Line(_pos[1], _pos[5], color);
	GIZMOMANAGER->Line(_pos[3], _pos[7], color);
	GIZMOMANAGER->Line(_pos[2], _pos[6], color);
}
