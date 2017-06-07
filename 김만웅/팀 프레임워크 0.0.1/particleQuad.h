#pragma once

//��ƼŬ ���� ����ü
typedef struct tagPARTICLEQUAD_VERTEX 
{
	D3DXVECTOR3 pos;			//���� ��ġ
	DWORD color;				//���� �÷�
	D3DXVECTOR2 uv;				//���� UV
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
}PARTICLEQUAD_VERTEX, *LPPARTICLEQUAD_VERTEX;

typedef vector<D3DXCOLOR>		VEC_COLOR;
typedef vector<float>			VEC_SCALE;

class particleQuad
{
public:
	dx::transform		_transform;				//��ƼŬ�� ��ġ��

private:
	bool			_bLive;					//Ȱ��ȭ ����
	float			_fTotalLiveTime;		//�� Ȱ��ȭ �ð�
	float			_fDeltaLiveTime;		//Ȱ��ȭ ���� �ð�
	float			_fNomalizeLiveTime;		//Ȱ��ȭ ���� �ð�( 0 ~ 1 )
	D3DXVECTOR3		_Velocity;				//��ƼŬ�� �ӵ�����
	D3DXVECTOR3		_Accelation;			//�ʴ� �����ϴ� ���Ӻ���
	D3DXVECTOR3		_Rotate;				//�ʴ� ȸ�� ����
	D3DXVECTOR3		_RotateAccel;			//�ʴ� �����ϴ� ȸ������
	float			_fScale;				//�⺻ �����ϰ�

public:
	void Start(
		float liveTime,						//���̺� Ÿ��
		const D3DXVECTOR3* pos,				//���� ��ġ
		const D3DXVECTOR3* velo,			//���� �ӵ�
		const D3DXVECTOR3* accel,			//���� ��
		const D3DXVECTOR3* rotate,			//�ʴ� ȸ�� ��
		const D3DXVECTOR3* rotateAccel,		//�ʴ� ȸ�� ������
		float scale							//�⺻ ������
	);

	void Update();

	//�ڽ��� ���� ������ �������� LPPARTICLEQUAD_VERTEX �� ���� �־��ش�.
	void GetParticleVertex(
		LPPARTICLEQUAD_VERTEX pOut,
		DWORD* pIndex,
		const VEC_COLOR& colors,
		const VEC_SCALE& scales,
		DWORD dwParticleNum);

	bool isLive() { return _bLive; }

	particleQuad() {}
	~particleQuad() {}
};

