#pragma once
#include "baseObject.h"
#include "particle.h"

enum PATICLE_EMISSION_TYPE 
{
	PZERO,					//�������� ���
	SPHERE,					//������ ���
	SPHERE_OUTLINE,			//������ ����ϴµ� �ܺ�ǥ�鿡����
	BOX						//�ڽ����� ���
};

//��ƼŬ�� ������ִ� ��
class particleEmitter : public baseObject
{
private:
	DWORD					_ParticleNum;			//������ �ѷ�
	particle*				_pParticles;			//��ƼŬ �迭
	LPPARTICLE_VERTEX		_pParticleVertices;		//��ƼŬ ���ؽ�
	float					_fEmissionPerSec;		//��ƼŬ �ʴ� �߻���
	DWORD					_dwParticleCount;		//Ȱ��ȭ ����
	VEC_COLOR				_Colors;				//��ƼŬ �÷� �迭
	VEC_SCALE				_Scales;				//��ƼŬ ������ �迭
	float					_fStartLiveTimeMin;		//��ƼŬ ���̺�Ÿ�� �ּ�
	float					_fStartLiveTimeMax;		//��ƼŬ ���̺�Ÿ�� �ִ�
	D3DXVECTOR3				_StartVelocityMin;		//��ƼŬ ���ۼӵ� �ּ� �ӵ�
	D3DXVECTOR3				_StartVelocityMax;		//��ƼŬ ���ۼӵ� �ִ� �ӵ�
	D3DXVECTOR3				_StartAccelateMin;		//��ƼŬ ���� ���� �ּ�
	D3DXVECTOR3				_StartAccelateMax;		//��ƼŬ ���� ���� �ִ�
	float					_fStartScaleMin;		//��ƼŬ ���� ������ �ּ�
	float					_fStartScaleMax;		//��ƼŬ ���� ������ �ּ�
	bool					_bEmission;				//���� �������̴�?
	float					_fEmissionIntervalTime;	//���� ���� �ð�
	float					_fEmissionDeltaTime;	//�ϳ� �����ϰ� ���� ���� �ð�
	LPDIRECT3DBASETEXTURE9	_pTex;					//��ƼŬ �ؽ���
	bool					_bLocal;				//�����̴�?

public:
	PATICLE_EMISSION_TYPE	EmissionType;			//��ƼŬ ���� Ÿ��
	//particle ���� ����
	float					MinEmissionRangeX;		//x ��������
	float					MaxEmissionRangeX;
	float					MinEmissionRangeY;		//y ��������
	float					MaxEmissionRangeY;
	float					MinEmissionRangeZ;		//z ��������
	float					MaxEmissionRangeZ;
	float					SphereEmissionRange;	//�������� ���� ������

public:
	particleEmitter() {}
	~particleEmitter() {}

	void init(
		DWORD	particleNum,						//�� ��ƼŬ ��
		float emission,								//�ʴ� �߻���
		float liveTimeMin,							//��ƼŬ �ϳ��� ����ð�
		float liveTimeMax,							//��ƼŬ �ϳ��� ����ð�
		const D3DXVECTOR3&	velocityMin,			//��ƼŬ ���� �ӵ� �ּ�
		const D3DXVECTOR3&	velocityMax,			//��ƼŬ ���� �ӵ� �ִ�
		const D3DXVECTOR3&	accelMin,				//��ƼŬ ���ӵ� �ּ�
		const D3DXVECTOR3&	accelMax,				//��ƼŬ ���ӵ� �ִ�
		const VEC_COLOR&	colors,					//��ƼŬ �÷� ���͹迭
		const VEC_SCALE&	scales,					//��ƼŬ ������ ���� �迭
		float scaleMin,								//��ƼŬ�� ������ �ּ�
		float scaleMax,								//��ƼŬ�� ������ �ִ�
		LPDIRECT3DTEXTURE9	pParticleTexture,		//��ƼŬ �ؽ���
		bool bLocal = false							//���� true �̸� ��ƼŬ�� �������� ���� Transform Local �������� �����δ�.(����)
	);

	void release();

	//BaseObject ��  Update �� ����
	virtual void baseObjectUpdate() override;	
	virtual void baseObjectRender() override;

	void StartEmission();		//��ƼŬ ���� ����
	void StopEmission();		//��ƼŬ ���� ����

	//��� �ȹ����� ���ڸ� ��Ʈ����.
	void Burst(int num, float minSpeed, float maxSpeed, float maxLife, float minLife);

	void SetRenderLocal(bool bLocal) { _bLocal = bLocal; }

private:
	//��ƼŬ �ϳ� ����
	void StartOneParticle();
	//��ƼŬ �ϳ� ����(���� �־)
	void StartOneParticle(D3DXVECTOR3 dir, float life);
};

