#include "stdafx.h"
#include "particle.h"

void particle::Start(float liveTime, const D3DXVECTOR3 * pos, const D3DXVECTOR3 * velo, const D3DXVECTOR3 * accel, float scale)
{
	//Ȱ��ȭ ����
	_bLive = true;

	//liveTime �ʱ�ȭ
	_fTotalLiveTime = liveTime;
	_fDeltaLiveTime = 0.0f;
	_fNormalizeLiveTime = 0.0f;

	//��ġ�� setting
	_transform.SetWorldPosition(pos->x, pos->y, pos->z);

	//���� �ӵ�
	_Velocity = *velo;

	//����
	_Accelation = *accel;

	//�⺻������
	_fScale = scale;
}

void particle::Update()
{
	if (_bLive == false) return;

	//���̺� Ÿ���� �� �Ǿ��ٸ�!
	if (_fDeltaLiveTime >= _fTotalLiveTime)
	{
		_bLive = false;
	}

	//Ȱ��ȭ �ð��� ���δ�.
	_fDeltaLiveTime += _timeDelta;

	//����ȭ �� �ð� �� ���
	_fNormalizeLiveTime = _fDeltaLiveTime / _fTotalLiveTime;
	if (_fNormalizeLiveTime > 1.0f)
		_fNormalizeLiveTime = 1.0f;

	//��ƼŬ�� ���� �̵�
	_transform.MovePositionWorld(
		_Velocity.x * _timeDelta,
		_Velocity.y * _timeDelta,
		_Velocity.z * _timeDelta);

	//��ƼŬ ����
	_Velocity += _Accelation * _timeDelta;
}

void particle::GetParticleVertex(LPPARTICLE_VERTEX pOut, const VEC_COLOR & colors, const VEC_SCALE & scales)
{
	//��ƼŬ�� ��ġ��
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
	//������ ����
	//

	//������ ���� ���
	float s = 0.0f;

	//������ �迭�� ������ �ε���
	int lastIndex = scales.size() - 1;

	//������ ���͹�
	float interval = 1.0f / lastIndex;

	//���� ���̺� Ÿ�� ���� ���� ��ġ
	float position = _fNormalizeLiveTime / interval;
	//postion �� ���� �����κ��� ���Ǵ� �迭���ε����� �Ǵ°��̰�,
	//�Ҽ����κ��� ���� �迭 �������� ���� ���� �ȴ�.

	//���� �ε���
	int startIndex = (int)position;

	// ���� ���ؽ�
	int endIndex = startIndex + 1;

	//���� ��
	float fN = position - startIndex;
	s = Lerp(scales[startIndex], scales[endIndex], fN);

	//���� ������ �� ����
	pOut->size = _fScale*s;

	//
	//�÷�����
	//
	
	//�÷� �迭�� ������ �ε���
	lastIndex = colors.size() - 1;

	//�÷� ���͹�
	interval = 1.0f / lastIndex;

	//���� ���̺� Ÿ�ӷ��� ������ġ
	position = _fNormalizeLiveTime / interval;

	//�����ε���
	startIndex = (int)position;

	//�����ε���
	endIndex = startIndex + 1;

	//���� ��
	fN = position - startIndex;

	//���� �÷� ��
	D3DXCOLOR color;

	//color ��������
	D3DXColorLerp(
		&color,					//��� ������ ����
		&colors[startIndex],	//From
		&colors[endIndex],		//To
		fN);					//Normalize Factor

	//���� �÷��� ����
	pOut->color = (DWORD)(color);
}
