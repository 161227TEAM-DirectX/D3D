#include "stdafx.h"
#include "particleQuad.h"

void particleQuad::Start(float liveTime, const D3DXVECTOR3 * pos, const D3DXVECTOR3 * velo, const D3DXVECTOR3 * accel, const D3DXVECTOR3 * rotate, const D3DXVECTOR3 * rotateAccel, float scale)
{
	//Ȱ��ȭ ����
	_bLive = true;

	//���̺� Ÿ�� �ʱ�ȭ
	_fTotalLiveTime = liveTime;
	_fDeltaLiveTime = 0.0f;

	//��ġ ������
	_transform.SetWorldPosition(pos->x, pos->y, pos->z);

	//���� �ӵ�
	_Velocity = *velo;

	//����
	_Accelation = *accel;

	//ȸ��
	_Rotate = *rotate;

	//ȸ�� ����
	_RotateAccel = *rotateAccel;

	//�⺻ ������
	_fScale = scale;
}

void particleQuad::Update()
{
	if (_bLive == false) return;

	//���̺� Ÿ���� �ٵǾ��ٸ�...
	if (_fDeltaLiveTime > _fTotalLiveTime) { _bLive = false; }

	//Ȱ��ȭ �ð� �״´�.
	_fDeltaLiveTime += _timeDelta;

	//����ȭ�� �ð����� ���
	_fNomalizeLiveTime = _fDeltaLiveTime / _fTotalLiveTime;
	if (_fNomalizeLiveTime > 1.0f) _fNomalizeLiveTime = 1.0f;

	//��ƼŬ ���� �̵�
	_transform.MovePositionWorld(
		_Velocity.x * _timeDelta,
		_Velocity.y * _timeDelta,
		_Velocity.z * _timeDelta);

	_transform.RotateSelf(
		_Rotate.x * _timeDelta,
		_Rotate.y * _timeDelta,
		_Rotate.z * _timeDelta);

	//��ƼŬ ����
	_Velocity += _Accelation * _timeDelta;

	//��ƼŬ ȸ�� ����
	_Rotate += _RotateAccel * _timeDelta;
}

void particleQuad::GetParticleVertex(LPPARTICLEQUAD_VERTEX pOut, DWORD * pIndex, const VEC_COLOR & colors, const VEC_SCALE & scales, DWORD dwParticleNum)
{
	//��ƼŬ ��ġ ��
	D3DXVECTOR3 center = _transform.GetWorldPosition();

	DWORD dwcolor = 0;
	float scale;

	//
	// ������ ����
	//

	//������ ���� ���
	float s = 0.0f;

	//������ �迭�� ������ �ε���
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

		//������ ���͹�
		float interval = 1.0f / lastIndex;

		//���� ���̺� Ÿ�� ���� ���� ��ġ
		float position = _fNomalizeLiveTime / interval;

		//�����ε���
		int startIndex = (int)position;

		//���� �ε���
		int endIndex = startIndex + 1;

		//������
		float fN = position - startIndex;
		s = (scales[endIndex] - scales[startIndex]) * fN + scales[startIndex];

		//���� ������ �� ����
		scale = _fScale * s;

		//
		// �÷� ����
		//

		//�÷� �迭�� ������ �ε���
		lastIndex = colors.size() - 1;

		//�÷� ���͹�
		interval = 1.0f / lastIndex;

		//���� ���̺� Ÿ�� ���� ���� ��ġ
		position = _fNomalizeLiveTime / interval;

		//�����ε���
		startIndex = (int)position;

		//���� �ε���
		endIndex = startIndex + 1;

		//������
		fN = position - startIndex;

		//���� �÷���
		D3DXCOLOR color;

		//�÷� ���� ����
		D3DXColorLerp(&color,			//���
			&colors[startIndex],		//from
			&colors[endIndex],			//to
			fN);						//normalize Factor

		dwcolor = (DWORD)(color);
	}

	//�����Ͽ� ���� halfSize;
	float halfScale = scale * 0.5f;

	//����
	D3DXVECTOR3 x = _transform.GetRight();
	D3DXVECTOR3 y = _transform.GetUp();

	//���� ���� ����
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

	//�ε��� ���� ���� ( �ε��� ������ ���ݱ��� �׷����� Quad ����ŭ �������� ���� �־�� �Ѵ� )
	*(pIndex + 0) = (dwParticleNum * 4) + 0;
	*(pIndex + 1) = (dwParticleNum * 4) + 1;
	*(pIndex + 2) = (dwParticleNum * 4) + 2;
	*(pIndex + 3) = (dwParticleNum * 4) + 2;
	*(pIndex + 4) = (dwParticleNum * 4) + 1;
	*(pIndex + 5) = (dwParticleNum * 4) + 3;
}
