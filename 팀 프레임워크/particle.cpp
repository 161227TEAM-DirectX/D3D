#include "stdafx.h"
#include "particle.h"

void particle::Start(float liveTime, const D3DXVECTOR3 * pos, const D3DXVECTOR3 * velo, const D3DXVECTOR3 * accel, float scale)
{
	//활성화 여부
	_bLive = true;

	//liveTime 초기화
	_fTotalLiveTime = liveTime;
	_fDeltaLiveTime = 0.0f;
	_fNormalizeLiveTime = 0.0f;

	//위치값 setting
	_transform.SetWorldPosition(pos->x, pos->y, pos->z);

	//시작 속도
	_Velocity = *velo;

	//가속
	_Accelation = *accel;

	//기본스케일
	_fScale = scale;
}

void particle::Update()
{
	if (_bLive == false) return;

	//라이브 타임이 다 되었다면!
	if (_fDeltaLiveTime >= _fTotalLiveTime)
	{
		_bLive = false;
	}

	//활성화 시간이 쌓인다.
	_fDeltaLiveTime += _timeDelta;

	//정규화 된 시간 값 계산
	_fNormalizeLiveTime = _fDeltaLiveTime / _fTotalLiveTime;
	if (_fNormalizeLiveTime > 1.0f)
		_fNormalizeLiveTime = 1.0f;

	//파티클의 월드 이동
	_transform.MovePositionWorld(
		_Velocity.x * _timeDelta,
		_Velocity.y * _timeDelta,
		_Velocity.z * _timeDelta);

	//파티클 가속
	_Velocity += _Accelation * _timeDelta;
}

void particle::GetParticleVertex(LPPARTICLE_VERTEX pOut, const VEC_COLOR & colors, const VEC_SCALE & scales)
{
	//파티클의 위치값
	pOut->pos = _transform.GetWorldPosition();

	if (_fNormalizeLiveTime == 1.0f)
	{
		pOut->color = colors[colors.size() - 1];
		pOut->size = _fScale*scales[scales.size() - 1];
		return;
	}
	else if (_fNormalizeLiveTime == 0.0f)
	{
		pOut->color = colors[0];
		pOut->size = _fScale*scales[0];
		return;
	}

	//
	//스케일 보간
	//

	//스케일 보간 결과
	float s = 0.0f;

	//스케일 배열의 마지막 인덱스
	int lastIndex = scales.size() - 1;

	//스케일 인터벌
	float interval = 1.0f / lastIndex;

	//현재 라이브 타임 량에 따른 위치
	float position = _fNormalizeLiveTime / interval;
	//postion 의 값에 정수부분이 사용되는 배열의인덱스가 되는것이고,
	//소숫점부분이 다음 배열 값까지의 보간 량이 된다.

	//시작 인덱스
	int startIndex = (int)position;

	// 종료 인텍스
	int endIndex = startIndex + 1;

	//보간 값
	float fN = position - startIndex;
	s = Lerp(scales[startIndex], scales[endIndex], fN);

	//최종 스케일 값 세팅
	pOut->size = _fScale*s;

	//
	//컬러보간
	//
	
	//컬러 배열의 마지막 인덱스
	lastIndex = colors.size() - 1;

	//컬러 인터벌
	interval = 1.0f / lastIndex;

	//현재 라이브 타임량에 따른위치
	position = _fNormalizeLiveTime / interval;

	//시작인덱스
	startIndex = (int)position;

	//종료인덱스
	endIndex = startIndex + 1;

	//보간 값
	fN = position - startIndex;

	//최종 컬러 값
	D3DXCOLOR color;

	//color 선형보간
	D3DXColorLerp(
		&color,					//결과 저장할 변수
		&colors[startIndex],	//From
		&colors[endIndex],		//To
		fN);					//Normalize Factor

	//최종 컬러값 세팅
	pOut->color = (DWORD)(color);
}
