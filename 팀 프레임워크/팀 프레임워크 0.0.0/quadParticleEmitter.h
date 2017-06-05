#pragma once
#include "baseObject.h"
#include "particleQuad.h"

class quadParticleEmitter : public baseObject
{
private:
	DWORD					_PaticleNum;			//������ �ѷ�
	particleQuad*			_pPaticles;				//��ƼŬ �迭
	particleQuad**			_pSortArray;			//��ƼŬ ��Ʈ�� Array
	LPPARTICLEQUAD_VERTEX	_ParticleVerticles;		//��ƼŬ ���ؽ�
	DWORD*					_ParticleIndex;			//��ƼŬ �ε���
	float					_fEmissionPerSec;		//�ʴ� �߻���
	DWORD					_dwParticleCount;		//Ȱ��ȭ ����
	VEC_COLOR				_Colors;				//��ƼŬ �÷� �迭
	VEC_SCALE				_Scales;				//��ƼŬ ������ �迭
	transform*				_pCameraTransform;		//ī�޶� Ʈ������
	bool					_bCameraSort;			//ī�޶� �Ÿ��� ��Ʈ�Ҳ���?
	
	//��ƼŬ ���̺� Ÿ�� �ִ� �ּ�
	float					_fStartLiveTimeMin;		
	float					_fStartLiveTimeMax;		

	//��ƼŬ ���� �ӵ� �ִ� �ּ�
	D3DXVECTOR3				_StartVelocityMin;
	D3DXVECTOR3				_StartVelocityMax;

	//��ƼŬ ���� ���� �ִ� �ּ�
	D3DXVECTOR3				_StartAccelateMin;
	D3DXVECTOR3				_StartAccelateMax;

	//��ƼŬ �����Ҷ� ȸ�� ���۰� �ִ� �ּ�
	D3DXVECTOR3				_StartSetRotateMin;
	D3DXVECTOR3				_StartSetRotateMax;

	//��ƼŬ ���� ȸ�� �ִ� �ּ�
	D3DXVECTOR3				_StartRotateMin;
	D3DXVECTOR3				_StartRotateMax;

	//��ƼŬ ȸ�� ���� �ִ� �ּ�
	D3DXVECTOR3				_StartRotateAccelateMin;
	D3DXVECTOR3				_StartRotateAccelateMax;

	//��ƼŬ ���� ������ �ִ� �ּ�
	float					_fStartScaleMin;
	float					_fStartScaleMax;

	bool					_bEmission;				//���� �������̴�?
	float					_fEmisionIntervalTime;	//���� ���� �ð�
	float					_fEmisionDeltaTime;		//�ϳ� �����ϱ� �����ð�

	LPDIRECT3DTEXTURE9		_pTex;					//��ƼŬ �ؽ���
	bool					_bLocal;

public:
	quadParticleEmitter() : _pCameraTransform(NULL), _bCameraSort(false) {}
	~quadParticleEmitter() {}

	HRESULT init(
		DWORD partcleNum,						//�� ��ƼŬ ��
		float emission,							//�ʴ� �߻���
		float liveTimeMin,
		float liveTimeMax,
		const D3DXVECTOR3& velocityMin,
		const D3DXVECTOR3& velocityMax,
		const D3DXVECTOR3& accelMin,
		const D3DXVECTOR3& accelMax,
		const D3DXVECTOR3& startRotateMin,		//�����Ҷ� ȸ�� �ּҰ� 
		const D3DXVECTOR3& startRotateMax,		//�����Ҷ� ȸ�� �ִ밪
		const D3DXVECTOR3& rotateMin,			//�����ӿ����� ȸ�� �ּҷ�
		const D3DXVECTOR3& rotateMax,			//�����ӿ����� ȸ�� �ִ뷮
		const D3DXVECTOR3& rotateAccelMin,		//������ ���ӿ����� ȸ�� �ּҷ�
		const D3DXVECTOR3& rotateAccelMax,		//������ ���ӿ����� ȸ�� �ִ뷮
		const VEC_COLOR& colors,
		const VEC_SCALE& scales,
		float scaleMin,
		float scaleMax,
		LPDIRECT3DTEXTURE9 pTex,
		bool bLocal = false
	);

	void release();

	virtual void baseObjectUpdate() override;	//BaseObject �� Update �� ����
	virtual void baseObjectRender() override;

	void StartEmission();			//��ƼŬ ���� ����
	void StopEmission();			//��ƼŬ ���� ����

	//ī�޶� ������ �Ҳ���?
	void setCameraSort(transform* pCameraTrans, bool bSort);

	void SetRenderLocal(bool bLocal) { _bLocal = bLocal; }

private:
	void StartOneParticle();		//��ƼŬ �ϳ� ����
};

