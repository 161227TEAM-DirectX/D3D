#pragma once
#include "dxParticle.h"
#include "dxModule.h"
#include "dxModuleKit.h"

enum EMITTER_TYPE
{
	ET_POINT,
	ET_PLANE,
	ET_BOARD,
	ET_MESH
};
#define ET_POINT	ET_POINT
#define ET_PLANE	ET_PLANE
#define ET_BOARD	ET_BOARD
#define ET_MESH		ET_MESH

class dxEmitter
{
protected:
	//파티클 속성들
	//list<tagDxAttribute> _ptcList;
	vector<tagDxAttribute> _ptcList;
	dxModuleKit* _module;

	//파티클 타입
	EMITTER_TYPE _EmitterType;

	dx::transform* _trans;
	
	LPDIRECT3DTEXTURE9		_texture;			//텍스쳐

	//D3DXVECTOR3             _origin;		

	//BoundingBox			 _boundingBox;	//경계상자는 파티클이 이동할 수 있는 부피를 제한하는 데 이용된다.

	//float   _size;			//시스템 내 모든 파티클의 크기
	//LPDIRECT3DVERTEXBUFFER9 _vb;				//버텍스버퍼
	//WORD _vbSize;			// 버텍스버퍼가 한번에 보관할 수 있는 파티클의 수.
							// 이 값은 파티클 시스템이 가질 수 있는 파티클의 수와는 독립적이다.
	float _constPaticleSize;

protected:
	//파티클 개수 및 시간 관련
	int		_onePtcNum;					//스폰할 때마다 한번에 뿜어내는 파티클 개수
	DWORD	_totalPtcNum;				//총 파티클 개수

	bool	_startDelayTimeOn;			//처음 시작 딜레이 사용여부
	float	_startDelayTime;			//처음 시작 딜레이 한계시간 설정
	float	_currentDelayTime;			//처음 시작 딜레이 현재시간

	float	_spawnTime;					//스폰
	float	_spawnCurrentTime;			//스폰타임

	int		_drawPtcNum;				//그릴 파티클 개수	


public:		//함수

	//순수 가상함수
	//virtual HRESULT init(string textureFileName, int particleNumber) = 0;
	virtual HRESULT init(string textureFileName, int OneTimePaticleNum, float spawnTime, int totalParticlenum) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	//virtual void reset() = 0;

public:	//해제
	virtual void release();
	//virtual void CopyInit() = 0;

public:
	dxModuleKit* Module(void) { return _module; };
	dx::transform*	Transform() { return _trans; }

public:
	//초기 지연작동시간 세팅
	void InitStartDelayTime(float time) { _startDelayTime = time; _spawnCurrentTime = 0.0f; _startDelayTimeOn = true; }
	//위치에 따른 방향성 속도
	void InitRandomPosDirectionVelocity(float min, float max) { _module->InitRandomPosDirectionVelocity(min, max); }

public: //=======================================================================================================================
		//위치 타입 세팅
	void SetPositionType(PTC_POSITION_TYPE posType) { _module->SetPositionType(posType); }
	void InitRandomPosSphereRadius(float min, float max) { _module->InitRandomPosSphereRadius(min, max); }

	//위치
	void InitRandomPositionX(float min, float max) { _module->InitRandomPositionX(min, max); }
	void InitRandomPositionY(float min, float max) { _module->InitRandomPositionY(min, max); }
	void InitRandomPositionZ(float min, float max) { _module->InitRandomPositionZ(min, max); }

	//위치에 따른 방향성 속도 그래프 세팅
	void addPosDirectVelGraph(float point, float min, float max) { _module->addPosDirectVelGraph(point, min, max); }

public:  //=======================================================================================================================
		 //속도
	void InitRandomVelocityX(float min, float max) { _module->InitRandomVelocityX(min, max); }
	void InitRandomVelocityY(float min, float max) { _module->InitRandomVelocityY(min, max); }
	void InitRandomVelocityZ(float min, float max) { _module->InitRandomVelocityZ(min, max); }

	//속도 그래프
	void addVelocityGraphX(float point, float min, float max) { _module->addVelocityGraphX(point, min, max); }
	void addVelocityGraphY(float point, float min, float max) { _module->addVelocityGraphY(point, min, max); }
	void addVelocityGraphZ(float point, float min, float max) { _module->addVelocityGraphZ(point, min, max); }

public:  //=======================================================================================================================
		 //가속도
	void InitRandomAccelerationX(float min, float max) { _module->InitRandomAccelerationX(min, max); }
	void InitRandomAccelerationY(float min, float max) { _module->InitRandomAccelerationY(min, max); }
	void InitRandomAccelerationZ(float min, float max) { _module->InitRandomAccelerationZ(min, max); }

public:  //=======================================================================================================================
		 //색
	void InitRandomColorR(float min, float max) { _module->InitRandomColorR(min, max); }
	void InitRandomColorG(float min, float max) { _module->InitRandomColorG(min, max); }
	void InitRandomColorB(float min, float max) { _module->InitRandomColorB(min, max); }

	//색 소멸
	void InitRandomColorFadeR(float min, float max) { _module->InitRandomColorFadeR(min, max); }
	void InitRandomColorFadeG(float min, float max) { _module->InitRandomColorFadeG(min, max); }
	void InitRandomColorFadeB(float min, float max) { _module->InitRandomColorFadeB(min, max); }

	//알파
	void InitRandomAlpha(float min, float max) { _module->InitRandomAlpha(min, max); }
	void InitRandomAlphaFade(float min, float max) { _module->InitRandomAlphaFade(min, max); }

	//알파 그래프
	void addAlphaGraph(float point, float min, float max) { _module->addAlphaGraph(point, min, max); };

public:
	//생명
	void InitRandomLifeTime(float min, float max) { _module->InitRandomLiftTime(min, max); }

public:	//=======================================================================================================================
		//사이즈 세팅
	void InitRandomSize(float min, float max) { _module->InitRandomSize(min, max); }
	void InitRandomSizeEnd(float min, float max) { _module->InitRandomSizeEnd(min, max); }

	//사이즈 그래프 세팅
	void InitConstSize(float size) { _constPaticleSize = size; }

	void addSizeGraph(float point, float min, float max) { _module->addSizeGraph(point, min, max); };


public:	//=======================================================================================================================
		//원 회전 반지름 초기화
	void InitRandomRadiusX(float min, float max) { _module->InitRandomRadiusX(min, max); }
	void InitRandomRadiusY(float min, float max) { _module->InitRandomRadiusY(min, max); }
	void InitRandomRadiusZ(float min, float max) { _module->InitRandomRadiusZ(min, max); }
	//원 회전 스피드
	void InitCircleAngleSpeedX(float min, float max) { _module->InitCircleAngleSpeedX(min, max); }
	void InitCircleAngleSpeedY(float min, float max) { _module->InitCircleAngleSpeedY(min, max); }
	void InitCircleAngleSpeedZ(float min, float max) { _module->InitCircleAngleSpeedZ(min, max); }
	//원 회전 시작각도								  
	void InitCircleStartAngleX(float min, float max) { _module->InitCircleStartAngleX(min, max); }
	void InitCircleStartAngleY(float min, float max) { _module->InitCircleStartAngleY(min, max); }
	void InitCircleStartAngleZ(float min, float max) { _module->InitCircleStartAngleZ(min, max); }
	//원회전 반지름 마지막
	void InitRandomRadiusEndX(float min, float max) { _module->InitRandomRadiusEndX(min, max); }
	void InitRandomRadiusEndY(float min, float max) { _module->InitRandomRadiusEndY(min, max); }
	void InitRandomRadiusEndZ(float min, float max) { _module->InitRandomRadiusEndZ(min, max); }


public:	//=======================================================================================================================
	//회전시작 각도
	void InitRotateStartAngleX(float min, float max) { _module->InitRotateStartAngleX(min, max); }
	void InitRotateStartAngleY(float min, float max) { _module->InitRotateStartAngleY(min, max); }
	void InitRotateStartAngleZ(float min, float max) { _module->InitRotateStartAngleZ(min, max); }

	//회전각도 스피드
	void InitRotateAngleSpeedX(float min, float max) { _module->InitRotateAngleSpeedX(min, max); }
	void InitRotateAngleSpeedY(float min, float max) { _module->InitRotateAngleSpeedY(min, max); }
	void InitRotateAngleSpeedZ(float min, float max) { _module->InitRotateAngleSpeedZ(min, max); }

public:	//=======================================================================================================================
	//가로세로
	void InitConstVH(float vertical, float horizontal) { _module->InitConstVH(vertical, horizontal); }

public:	//=======================================================================================================================
	//UV애니메이션
	void InitAnimation(int inFrameMaxX, int inFrameMaxY, int inTotalFrame = 0) { _module->InitAnimation(inFrameMaxX, inFrameMaxY, inTotalFrame); }

	//애니메이션 재생수
	void InitConstAniReactivateNum(int inReactiveateNum) { _module->InitConstAniReactivateNum(inReactiveateNum); }

	//void InitRandomSpawnTime(float min, float max) { init(_textureFileName, _onePtcNum, RandomFloatRange(min, max)); }
	//void InitRandomDirectionVelocity(float min, float max) { _module->InitRandomDirectionVelocity(min, max); }


public:
	//특수함수
	DWORD FtoDw(float f) { return *((DWORD*)&f); }
	//타입함수
	EMITTER_TYPE GetType(void) { return this->_EmitterType; };

	public:
	//리셋
	void reset()
	{
		_ptcList.clear();
		_ptcList.resize(_totalPtcNum);
		_currentDelayTime = 0.0f;
		//_spawnCurrentTime = _spawnTime;
		if (_startDelayTimeOn)
		{
			_spawnCurrentTime = 0.0f;
		}
		else
		{
			_spawnCurrentTime = _spawnTime;
		}
	}

public:
	dxEmitter() {};
	~dxEmitter() {};

	
	
};

