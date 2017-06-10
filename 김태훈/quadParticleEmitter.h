#pragma once
#include "baseObject.h"
#include "particleQuad.h"

class quadParticleEmitter : public baseObject
{
private:
	DWORD					_PaticleNum;			//입자의 총량
	particleQuad*			_pPaticles;				//파티클 배열
	particleQuad**			_pSortArray;			//파티클 소트용 Array
	LPPARTICLEQUAD_VERTEX	_ParticleVerticles;		//파티클 버텍스
	DWORD*					_ParticleIndex;			//파티클 인덱스
	float					_fEmissionPerSec;		//초당 발생량
	DWORD					_dwParticleCount;		//활성화 순번
	VEC_COLOR				_Colors;				//파티클 컬러 배열
	VEC_SCALE				_Scales;				//파티클 사이즈 배열
	transform*				_pCameraTransform;		//카메라 트랜스폼
	bool					_bCameraSort;			//카메라 거리별 소트할꺼냐?
	
	//파티클 라이브 타임 최대 최소
	float					_fStartLiveTimeMin;		
	float					_fStartLiveTimeMax;		

	//파티클 시작 속도 최대 최소
	D3DXVECTOR3				_StartVelocityMin;
	D3DXVECTOR3				_StartVelocityMax;

	//파티클 시작 가속 최대 최소
	D3DXVECTOR3				_StartAccelateMin;
	D3DXVECTOR3				_StartAccelateMax;

	//파티클 시작할때 회전 시작값 최대 최소
	D3DXVECTOR3				_StartSetRotateMin;
	D3DXVECTOR3				_StartSetRotateMax;

	//파티클 시작 회전 최대 최소
	D3DXVECTOR3				_StartRotateMin;
	D3DXVECTOR3				_StartRotateMax;

	//파티클 회전 가속 최대 최소
	D3DXVECTOR3				_StartRotateAccelateMin;
	D3DXVECTOR3				_StartRotateAccelateMax;

	//파티클 시작 사이즈 최대 최소
	float					_fStartScaleMin;
	float					_fStartScaleMax;

	bool					_bEmission;				//현재 생성중이니?
	float					_fEmisionIntervalTime;	//생성 간격 시간
	float					_fEmisionDeltaTime;		//하나 생성하구 지난시간

	LPDIRECT3DTEXTURE9		_pTex;					//파티클 텍스쳐
	bool					_bLocal;

public:
	quadParticleEmitter() : _pCameraTransform(NULL), _bCameraSort(false) {}
	~quadParticleEmitter() {}

	HRESULT init(
		DWORD partcleNum,						//총 파티클 량
		float emission,							//초당 발생량
		float liveTimeMin,
		float liveTimeMax,
		const D3DXVECTOR3& velocityMin,
		const D3DXVECTOR3& velocityMax,
		const D3DXVECTOR3& accelMin,
		const D3DXVECTOR3& accelMax,
		const D3DXVECTOR3& startRotateMin,		//시작할때 회전 최소값 
		const D3DXVECTOR3& startRotateMax,		//시작할때 회전 최대값
		const D3DXVECTOR3& rotateMin,			//움직임에대한 회전 최소량
		const D3DXVECTOR3& rotateMax,			//움직임에대한 회전 최대량
		const D3DXVECTOR3& rotateAccelMin,		//움직임 가속에대한 회전 최소량
		const D3DXVECTOR3& rotateAccelMax,		//움직임 가속에대한 회전 최대량
		const VEC_COLOR& colors,
		const VEC_SCALE& scales,
		float scaleMin,
		float scaleMax,
		LPDIRECT3DTEXTURE9 pTex,
		bool bLocal = false
	);

	void release();

	virtual void baseObjectUpdate() override;	//BaseObject 가 Update 때 실행
	virtual void baseObjectRender() override;

	void StartEmission();			//파티클 생성 시작
	void StopEmission();			//파티클 생성 중지

	//카메라 소팅을 할꺼니?
	void setCameraSort(transform* pCameraTrans, bool bSort);

	void SetRenderLocal(bool bLocal) { _bLocal = bLocal; }

private:
	void StartOneParticle();		//파티클 하나 생성
};

