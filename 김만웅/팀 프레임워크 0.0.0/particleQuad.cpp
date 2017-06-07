#include "stdafx.h"
#include "particleQuad.h"

void particleQuad::Start(float liveTime, const D3DXVECTOR3 * pos, const D3DXVECTOR3 * velo, const D3DXVECTOR3 * accel, const D3DXVECTOR3 * rotate, const D3DXVECTOR3 * rotateAccel, float scale)
{
	//활성화 여부
	_bLive = true;

	//라이브 타임 초기화
	_fTotalLiveTime = liveTime;
	_fDeltaLiveTime = 0.0f;

	//위치 값세팅
	_transform.SetWorldPosition(pos->x, pos->y, pos->z);

	//시작 속도
	_Velocity = *velo;

	//가속
	_Accelation = *accel;

	//회전
	_Rotate = *rotate;

	//회전 가속
	_RotateAccel = *rotateAccel;

	//기본 스케일
	_fScale = scale;
}

void particleQuad::Update()
{
	if (_bLive == false) return;

	//라이브 타임이 다되었다면...
	if (_fDeltaLiveTime > _fTotalLiveTime) { _bLive = false; }

	//활성화 시간 쌓는다.
	_fDeltaLiveTime += _timeDelta;

	//정규화된 시간값을 계산
	_fNomalizeLiveTime = _fDeltaLiveTime / _fTotalLiveTime;
	if (_fNomalizeLiveTime > 1.0f) _fNomalizeLiveTime = 1.0f;

	//파티클 월드 이동
	_transform.MovePositionWorld(
		_Velocity.x * _timeDelta,
		_Velocity.y * _timeDelta,
		_Velocity.z * _timeDelta);

	_transform.RotateSelf(
		_Rotate.x * _timeDelta,
		_Rotate.y * _timeDelta,
		_Rotate.z * _timeDelta);

	//파티클 가속
	_Velocity += _Accelation * _timeDelta;

	//파티클 회전 가속
	_Rotate += _RotateAccel * _timeDelta;
}

void particleQuad::GetParticleVertex(LPPARTICLEQUAD_VERTEX pOut, DWORD * pIndex, const VEC_COLOR & colors, const VEC_SCALE & scales, DWORD dwParticleNum)
{
	//파티클 위치 값
	D3DXVECTOR3 center = _transform.GetWorldPosition();

	DWORD dwcolor = 0;
	float scale;

	//
	// 스케일 보간
	//

	//스케일 보간 결과
	float s = 0.0f;

	//스케일 배열의 마지막 인덱스
	int lastIndex = scales.size() - 1;

	if (_fNomalizeLiveTime == 1.0f) 
	{
		dwcolor = colors[colors.size() - 1];
		scale = _fScale * scales[scales.size() - 1];
	}

	else if (_fNomalizeLiveTime == 0.0f) 
	{
		dwcolor = colors[0];
		scale = _fScale * scales[0];
	}
	else 
	{

		//스케일 인터벌
		float interval = 1.0f / lastIndex;

		//현재 라이브 타임 량에 따른 위치
		float position = _fNomalizeLiveTime / interval;

		//시작인덱스
		int startIndex = (int)position;

		//종료 인덱스
		int endIndex = startIndex + 1;

		//보간값
		float fN = position - startIndex;
		s = (scales[endIndex] - scales[startIndex]) * fN + scales[startIndex];

		//최종 스케일 값 세팅
		scale = _fScale * s;

		//
		// 컬러 보간
		//

		//컬러 배열의 마지막 인덱스
		lastIndex = colors.size() - 1;

		//컬러 인터벌
		interval = 1.0f / lastIndex;

		//현재 라이브 타임 량에 따른 위치
		position = _fNomalizeLiveTime / interval;

		//시작인덱스
		startIndex = (int)position;

		//종료 인덱스
		endIndex = startIndex + 1;

		//보간값
		fN = position - startIndex;

		//최종 컬러값
		D3DXCOLOR color;

		//컬러 선형 보간
		D3DXColorLerp(&color,			//결과
			&colors[startIndex],		//from
			&colors[endIndex],			//to
			fN);						//normalize Factor

		dwcolor = (DWORD)(color);
	}

	//스케일에 따른 halfSize;
	float halfScale = scale * 0.5f;

	//방향
	D3DXVECTOR3 x = _transform.GetRight();
	D3DXVECTOR3 y = _transform.GetUp();

	//정점 정보 대입
	(pOut + 0)->pos = center + (-x * halfScale) + (y * halfScale);
	(pOut + 1)->pos = center + (x * halfScale) + (y * halfScale);
	(pOut + 2)->pos = center + (-x * halfScale) + (-y * halfScale);
	(pOut + 3)->pos = center + (x * halfScale) + (-y * halfScale);

	(pOut + 0)->uv = D3DXVECTOR2(0, 0);
	(pOut + 1)->uv = D3DXVECTOR2(1, 0);
	(pOut + 2)->uv = D3DXVECTOR2(0, 1);
	(pOut + 3)->uv = D3DXVECTOR2(1, 1);

	(pOut + 0)->color = dwcolor;
	(pOut + 1)->color = dwcolor;
	(pOut + 2)->color = dwcolor;
	(pOut + 3)->color = dwcolor;

	//0----1
	//|   /|
	//|  / |
	//| /  |
	//|/   |
	//2----3

	//인덱스 정보 대입 ( 인덱스 넣을때 지금까지 그려지는 Quad 수만큼 점프해한 값을 넣어야 한다 )
	*(pIndex + 0) = (dwParticleNum * 4) + 0;
	*(pIndex + 1) = (dwParticleNum * 4) + 1;
	*(pIndex + 2) = (dwParticleNum * 4) + 2;
	*(pIndex + 3) = (dwParticleNum * 4) + 2;
	*(pIndex + 4) = (dwParticleNum * 4) + 1;
	*(pIndex + 5) = (dwParticleNum * 4) + 3;
}
