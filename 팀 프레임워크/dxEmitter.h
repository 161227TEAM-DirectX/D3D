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

	//파티클 시스템용 트랜스폼
	dx::transform* _psTrans;

	dx::transform* _psBoardTrans;	//빌보드용

	dx::transform* _trans;

	LPDIRECT3DTEXTURE9	_texture;			//텍스쳐

	float _constPaticleSize;

	//이미터 개수(시간 맞춤용)
	int _emitterNum;

	bool _realtimeTrackingPosOn;

protected:
	//전체 회전용
	D3DXVECTOR3 _allRotate;

	D3DXVECTOR3 _allRotateSpeed;

protected:
	//파티클 개수 및 시간 관련
	int		_onePtcNum;					//스폰할 때마다 한번에 뿜어내는 파티클 개수
	DWORD	_totalPtcNum;				//총 파티클 개수

	float	_spawnTime;					//스폰
	float	_spawnCurrentTime;			//스폰타임

	int		_drawPtcNum;				//그릴 파티클 개수	



	bool _InitActiveStop;
	bool _initActiveTimeOn;

	float _initActiveLimitTime;
	float _initActiveCurrentTime;

protected:
	//활성시간 정도
	bool	_activeTimeCheckOn;
	float	_activeCurrentTime;
	float	_activeLimitTime;

	bool	_activeRenderControlOn;
	bool	_activeRenderOn;

	//시작시간 정도
	bool	_startTimeCheckOn;
	float	_startLimitTime;			//처음 시작 한계 시간
	float	_startCurrentTime;			//처음 시작 현재시간

	bool	_startRenderOn;

protected:
	//미리 업데이트 부분 관련
	int _preInitPtcCurrentNum;
	int _oneFramePtcCurrentNum;
	int _oneFramePtcNum;

	//누적시간 관련
	float _accrueTime;
	float _preLimitTime;

	bool _preUpdateOn;
	bool _preOneSettingOn;
protected:
	//빌보드 관련
	bool _billBoardY_On;

public:		//함수

	//순수 가상함수
	//virtual HRESULT init(string textureFileName, int particleNumber) = 0;
	virtual HRESULT init(string, int OneTimePaticleNum, float spawnTime, int totalParticlenum) = 0;
	virtual void preUpdate();	//계획은 창대했지만 결국 실패했다.
	virtual void update() = 0;
	virtual void render() = 0;
	//virtual void reset() = 0;

public:	//해제
	virtual void release();
	//virtual void CopyInit() = 0;

public:
	dxModuleKit* Module(void) { return _module; };
	dx::transform*	Transform() { return _trans; }

public: //=======================================================================================================================
	//회전 시작지점
	void InitAllStartRotate(float startX, float startY, float startZ) { _allRotate = D3DXVECTOR3(startX, startY, startZ); };

	//회전 스피드
	void InitAllRotateSpeed(float speedX, float speedY, float speedZ) { _allRotateSpeed = D3DXVECTOR3(speedX, speedY, speedZ); };


public: //=======================================================================================================================
	//위치 타입 세팅
	void SetPositionType(PTC_POSITION_TYPE posType = PTC_SPHERE) { _module->SetPositionType(posType); }
	void InitRandomPosSphereRadius(float min, float max) { _module->InitRandomPosSphereRadius(min, max); }

	//구 방향
	void InitDirSphere(float dirX, float dirY, float dirZ) { _module->InitDirSphere(dirX, dirY, dirZ); }

	//위치
	void InitRandomPositionX(float min, float max) { _module->InitRandomPositionX(min, max); }
	void InitRandomPositionY(float min, float max) { _module->InitRandomPositionY(min, max); }
	void InitRandomPositionZ(float min, float max) { _module->InitRandomPositionZ(min, max); }


public: //=======================================================================================================================
	//위치에서 폭파
	void InitRandomPosExplosionVel(float min, float max) { _module->InitRandomPosExplosionVel(min, max); }

	//위치에서 폭파 그래프
	void addPosExplosionVelGraph(float point, float min, float max) { _module->addPosExplosionVelGraph(point, min, max); }


public:	//=======================================================================================================================
	//위치 중심 회전
	void InitRandomPosRotAngleSpeedX(float min, float max) { _module->InitRandomPosRotAngleSpeedX(min, max); }
	void InitRandomPosRotAngleSpeedY(float min, float max) { _module->InitRandomPosRotAngleSpeedY(min, max); }
	void InitRandomPosRotAngleSpeedZ(float min, float max) { _module->InitRandomPosRotAngleSpeedZ(min, max); }


public:	//=======================================================================================================================
	//끌림 고정
	void InitConstAttractCenter(float x, float y, float z) { _module->InitConstAttractCenter(x, y, z); }
	//끌림 랜덤
	void InitAttractCenterX(float min, float max) { _module->InitAttractCenterX(min, max); }
	void InitAttractCenterY(float min, float max) { _module->InitAttractCenterY(min, max); }
	void InitAttractCenterZ(float min, float max) { _module->InitAttractCenterZ(min, max); }


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

	//가속도 그래프
	void addAccelGraphX(float point, float min, float max) { _module->addAccelGraphX(point, min, max); }
	void addAccelGraphY(float point, float min, float max) { _module->addAccelGraphY(point, min, max); }
	void addAccelGraphZ(float point, float min, float max) { _module->addAccelGraphZ(point, min, max); }

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
	void InitCircleRadiusX(float min, float max) { _module->InitCircleRadiusX(min, max); }
	void InitCircleRadiusY(float min, float max) { _module->InitCircleRadiusY(min, max); }
	void InitCircleRadiusZ(float min, float max) { _module->InitCircleRadiusZ(min, max); }
	//원 회전 스피드
	void InitCircleAngleSpeedX(float min, float max) { _module->InitCircleAngleSpeedX(min, max); }
	void InitCircleAngleSpeedY(float min, float max) { _module->InitCircleAngleSpeedY(min, max); }
	void InitCircleAngleSpeedZ(float min, float max) { _module->InitCircleAngleSpeedZ(min, max); }
	//원 회전 시작각도								  
	void InitCircleStartAngleX(float min, float max) { _module->InitCircleStartAngleX(min, max); }
	void InitCircleStartAngleY(float min, float max) { _module->InitCircleStartAngleY(min, max); }
	void InitCircleStartAngleZ(float min, float max) { _module->InitCircleStartAngleZ(min, max); }
	//원회전 반지름 마지막
	void InitCircleRadiusEndX(float min, float max) { _module->InitCircleRadiusEndX(min, max); }
	void InitCircleRadiusEndY(float min, float max) { _module->InitCircleRadiusEndY(min, max); }
	void InitCircleRadiusEndZ(float min, float max) { _module->InitCircleRadiusEndZ(min, max); }


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
	void InitConstHV(float horizontal, float vertical) { _module->InitConstHV(horizontal, vertical); }

	//면 상에서 중심 위치를 세팅
	void InitCenterPointHV(float pointH, float pointV) { _module->InitCenterPointHV(pointH, pointV); }

public:	//=======================================================================================================================
	//UV애니메이션
	void InitAnimation(int inFrameMaxX, int inFrameMaxY, int inTotalFrame = 0) { _module->InitAnimation(inFrameMaxX, inFrameMaxY, inTotalFrame); }

	//애니메이션 재생수
	void InitConstAniReactivateNum(int inReactiveateNum) { _module->InitConstAniReactivateNum(inReactiveateNum); }

	//애니매이션 시작지점과 끝지점 지정가능
	void InitAniPlaySection(int inStartFrameNum, int inEndFrameNum) { _module->InitAniPlaySection(inStartFrameNum, inEndFrameNum); }

	//UV이미지 반전
	void uvReverseImgU() { _module->uvReverseImgU(); }
	void uvReverseImgV() { _module->uvReverseImgV(); }

	//void InitRandomSpawnTime(float min, float max) { init(_textureFileName, _onePtcNum, RandomFloatRange(min, max)); }
	//void InitRandomDirectionVelocity(float min, float max) { _module->InitRandomDirectionVelocity(min, max); }
public:
	//실시간 추적여부
	void setRealtimeTrackingPosOn() { _realtimeTrackingPosOn = true; }
	bool getRealtimeTrackingPosOn() { return _realtimeTrackingPosOn; }

public:
	//특수함수
	DWORD FtoDw(float f) { return *((DWORD*)&f); }
	//타입함수
	EMITTER_TYPE GetType(void) { return this->_EmitterType; };

public:
	//리셋
	void reset()
	{
		_activeRenderOn = true;
		_activeRenderControlOn = true;

		_InitActiveStop = FALSE;
		_initActiveCurrentTime = 0.0f;


		_ptcList.clear();
		_ptcList.resize(_totalPtcNum);
		_activeCurrentTime = 0.0f;
		_spawnCurrentTime = _spawnTime;
		_startCurrentTime = 0.0f;
		_activeCurrentTime = 0.0f;

		if (_startTimeCheckOn) { _startRenderOn = FALSE; }

	}
public:
	//작동 시간 설정
	void SetActiveLimitTime(float inTime, bool inRenderControlOn = true)
	{
		_activeLimitTime = inTime;
		_activeRenderControlOn = inRenderControlOn;
		_activeCurrentTime = 0.0f;
		_activeTimeCheckOn = TRUE;
	};

	void SetStartLimitTime(float inTime)
	{
		_startLimitTime = inTime;
		_startCurrentTime = 0.0f;
		_startTimeCheckOn = TRUE;
		_startRenderOn = FALSE;
	}

	//그레이스케일을 알파로
	void setGrayScaleAlphaOn(void);

	bool autoActiveTimeCheck(float timeDelta);

	bool autoStartTimeCheck(float timeDelta);

	void setParticleSystemTrans(dx::transform* inTrance) { _psTrans = inTrance; }

	void setPsBoardTrans(dx::transform* inBoardTrance) { _psBoardTrans = inBoardTrance; }

	void setEmitterNum(int num) { _emitterNum = num; };

	void setInitActiveLimitTime(float inTime) { _initActiveLimitTime = inTime; _initActiveTimeOn = TRUE; };

public:
	void EmitterInit(void)
	{
		//모듈 초기화
		_module = new dxModuleKit;
		_trans = new dx::transform;

		//트랜스 초기화
		_psTrans = NULL;
		_psBoardTrans = NULL;
		_module->init();

		//작동시간 초기화
		_activeTimeCheckOn = FALSE;
		_activeCurrentTime = 0.0f;
		_activeLimitTime = 0.0f;

		_activeRenderOn = true;
		_activeRenderControlOn = true;

		//시작시간 초기화
		_startTimeCheckOn = FALSE;
		_startLimitTime = 0.0f;
		_startCurrentTime = 0.0f;

		_startRenderOn = true;

		//이미터 개수
		_emitterNum = 1;


		_psTrans = NULL;

		_allRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_allRotateSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//미리 업데이트 초기화
		_preInitPtcCurrentNum = 0;
		_oneFramePtcCurrentNum = 0;
		_oneFramePtcNum = 0;

		_accrueTime = 0.0f;
		_preLimitTime = 0.0f;

		_preUpdateOn = true;
		_preOneSettingOn = true;

		_realtimeTrackingPosOn = false;

		_InitActiveStop = FALSE;

		_initActiveTimeOn = FALSE;

		_initActiveLimitTime = 0.0f;
		_initActiveCurrentTime = 0.0f;


		_billBoardY_On = FALSE;

	}
	dxEmitter() {};
	~dxEmitter() {};



};

