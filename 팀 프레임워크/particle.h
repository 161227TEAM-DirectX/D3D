#pragma once

//��ƼŬ ���� ����ü
typedef struct tagPARTICLE_VERTEX 
{
	D3DXVECTOR3 pos;				//���� ��ġ
	float size;						//��ƼŬ ���� ���� ������
	DWORD color;					//���� �÷�
	enum { FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
}PARTICLE_VERTEX, *LPPARTICLE_VERTEX;

typedef vector<D3DXCOLOR>   VEC_COLOR;
typedef vector<float>		VEC_SCALE;

//���� �ϳ��� ���� ����
class particle
{
public:
	dx::transform		_transform;				//��ƼŬ�� ��ġ��

private:
	bool			_bLive;					//Ȱ��ȭ ����
	float			_fTotalLiveTime;		//�� Ȱ��ȭ �ð�
	float			_fDeltaLiveTime;		//Ȱ��ȭ ���� �ð�
	float			_fNormalizeLiveTime;	//Ȱ��ȭ ���� �ð�(0~1)
	D3DXVECTOR3		_Velocity;				//��ƼŬ�� �ӵ�����
	D3DXVECTOR3		_Accelation;			//�ʴ� �����ϴ� ���� ����
	float			_fScale;				//�⺻ �����ϰ�

public:
	void Start(
		float liveTime,						//���̺�Ÿ��
		const D3DXVECTOR3* pos,				//���� ��ġ
		const D3DXVECTOR3* velo,			//���ۼӵ�
		const D3DXVECTOR3* accel,			//���ӵ�
		float scale							//�⺻������
	);

	void Update();

	//�ڽ��� ���� ������ �������� LPPATICLE_VERTEX  �� ���� �־��ش�.
	void GetParticleVertex(
		LPPARTICLE_VERTEX pOut,
		const VEC_COLOR& colors,
		const VEC_SCALE& scales
	);

	bool isLive() { return _bLive; }

	particle() : _bLive(false) {}
	~particle() {}
};




