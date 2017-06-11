#pragma once

//파티클 정점 구조체
typedef struct tagPARTICLE_VERTEX 
{
	D3DXVECTOR3 pos;				//정점 위치
	float size;						//파티클 사용시 정점 사이즈
	DWORD color;					//정점 컬러
	enum { FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
}PARTICLE_VERTEX, *LPPARTICLE_VERTEX;

typedef vector<D3DXCOLOR>   VEC_COLOR;
typedef vector<float>		VEC_SCALE;

//입자 하나에 대한 정보
class particle
{
public:
	dx::transform		_transform;				//파티클의 위치값

private:
	bool			_bLive;					//활성화 여부
	float			_fTotalLiveTime;		//총 활성화 시간
	float			_fDeltaLiveTime;		//활성화 지난 시간
	float			_fNormalizeLiveTime;	//활성화 비율 시간(0~1)
	D3DXVECTOR3		_Velocity;				//파티클의 속도벡터
	D3DXVECTOR3		_Accelation;			//초당 증가하는 가속 벡터
	float			_fScale;				//기본 스케일값

public:
	void Start(
		float liveTime,						//라이브타임
		const D3DXVECTOR3* pos,				//시작 위치
		const D3DXVECTOR3* velo,			//시작속도
		const D3DXVECTOR3* accel,			//가속도
		float scale							//기본스케일
	);

	void Update();

	//자신의 정점 정보를 바탕으로 LPPATICLE_VERTEX  의 값을 넣어준다.
	void GetParticleVertex(
		LPPARTICLE_VERTEX pOut,
		const VEC_COLOR& colors,
		const VEC_SCALE& scales
	);

	bool isLive() { return _bLive; }

	particle() : _bLive(false) {}
	~particle() {}
};




