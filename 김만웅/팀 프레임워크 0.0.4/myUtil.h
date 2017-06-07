#pragma once

#define EPSILON		0.0001f		//float 비교 할때 이값 이하의 오차는 같다고 판단한다
//c = 0.0001f
//a = 10.00001f
//b = 10.00008f
//(abs(a - b) < c) => 같다

//a 와 b 가 같냐?
#define FLOATEQUAL(a, b) (abs((a) - (b)) < EPSILON)
//거의 0값과 같냐?
#define FLOATZERO(a) (abs(a) < EPSILON)
//제로 벡터냐?
#define VECTORZERO(v) (FLOATZERO((v).x) && FLOATZERO((v).y) && FLOATZERO((v).z))

//레이 구조체
typedef struct tagRay
{
	tagRay() { this->origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f); this->direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	tagRay(D3DXVECTOR3& origin, D3DXVECTOR3& direction) { this->origin = origin; this->direction = direction; }
	D3DXVECTOR3 origin;		//직선의 시작위치
	D3DXVECTOR3	direction;	//직선의 방향(정규화 되어 있어야 함)
}Ray, *LPRay;

namespace myUtil
{
	//이방성 필터링 최대단계
	extern DWORD maxAnisotropic;
	//진짜 중요함, 이 디바이스로 모든걸 다 진행한다고 생각하면됨!!!
	//이놈의 파워는 HDC와는 비교불가
	extern LPDIRECT3DDEVICE9 device;	//디바이스 (외부에서 사용가능)

	HRESULT CreateDevice();				//디바이스 생성함수
	void ReleaseDevice();				//디바이스 해제함수

	POINT GetMousePos();				//마우스 위치
	void SetMousePos(int x, int y);		//마우스 위치 세팅

	float Clamp(float value, float min, float max);	//value값을 min max사이로 맞추기
	float Clamp01(float value);			//value값을 0 ~ 1 사이로 맞추기
	float ClampMinusOnePlusOne(float value); //value값을 -1 ~ 0 사이로 맞추기

	//float 선형보간
	//(t는 0 ~ 1 사이의 값을 받는데..)
	//(t가 0일 수록 from 가까운 값이 리턴되고)
	//(t가 1일 수록 to 가까운 값이 리턴된다)
	float Lerp(float from, float to, float t);

	//float 선형보간 반대
	//value 값이 head와 rear사이에 어느정도 위치에 있는지
	//0 ~ 1사이의 값으로 리턴한다
	float InverseLerp(float head, float rear, float value);
	//벡터 선형보간
	D3DXVECTOR3 VecLerp(D3DXVECTOR3& from, D3DXVECTOR3& to, float t);

	//Random
	void SetRandomSeed();
	float RandomFloatRange(float min, float max);
	int RandomIntRange(int min, int max);

	//정점의 노말을 계산해주는 함수
	void ComputeNormal(
		D3DXVECTOR3* pNorams,			//결과로 받을 노말백터 배열 포인터 ( 노말벡터의 배열의 수는 정점 배열의 수와 같다 )
		const D3DXVECTOR3* pVertices,	//계산에 사용된 정점위치 배열 포인터
		int verticesNum,				//정점 갯수
		const DWORD* pIndices,			//인덱스 배열포인터 ( 일단 인덱스는 DWORD 로 대동단결 )
		int indicesNum					//인덱스 배열포인터 갯수
	);

	//탄젠트와 바이노말 계산
	void ComputeTangentBinormal(
		D3DXVECTOR3* outTangets,			//결과 Tangent 배열
		D3DXVECTOR3* outBinormals,			//결과 Binormal 배열
		const D3DXVECTOR3* pPositions,		//정점 위치 배열
		const D3DXVECTOR3* pNormals,		//정점 노말 배열
		const D3DXVECTOR2* pUVs,			//정점의 UV 배열
		const DWORD* pIndices,				//인덱스 배열
		DWORD NumTris,						//삼각형 갯수		
		DWORD NumVertices 					//정점 갯수
	);

	//플룻의 비트값을 손실하지 않은체 DWORD 형으로 변환
	DWORD FloatToDWORD(float f);
}

