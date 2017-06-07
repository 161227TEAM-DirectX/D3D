#pragma once
#include "dxEmitter.h"


class dxPointEmitter : public dxEmitter
{
private:
	//dxModule* _module;

	D3DXMATRIX _matWorld;

	//tagDxParticle* ptcVtx;

	string _textureFileName;

	

	int _vbMaxStep;
	
	

	int limitCycle;
	int currentCycle;
	bool cycleOn;
	 
	tagDxParticle* _ptcVtx;
	tagDxParticle* _drawVtx;


public:
	virtual HRESULT init(string textureFileName, int OneTimePaticleNum = 10, float spawnTime = 1.0f, int totalPaticleNum = 0);
	//vietual HRESULT init(string textureFileName, int OneTimePaticleNum = 10, float spawnTime = 1.0f, int allPaticleNum = 200);
	virtual void relese();
	virtual void update();
	virtual void render();

//public:  
//	//초기 지연작동시간 세팅
//	void InitStartDelayTime(float time) { _startDelayTime = time; _spawnCurrentTime = 0.0f; _startDelayTimeOn = true; }
//	//위치에 따른 방향성 속도
//	void InitRandomPosDirectionVelocity(float min, float max) { _module->InitRandomPosDirectionVelocity(min, max); }
//
//public: //=======================================================================================================================
//	//위치 타입 세팅
//	void SetPositionType(PTC_POSITION_TYPE posType) { _module->SetPositionType(posType); }
//	void InitRandomPosSphereRadius(float min, float max) { _module->InitRandomPosSphereRadius(min, max); }
//
//	//위치
//	void InitRandomPositionX(float min, float max) { _module->InitRandomPositionX(min, max); }
//	void InitRandomPositionY(float min, float max) { _module->InitRandomPositionY(min, max); }
//	void InitRandomPositionZ(float min, float max) { _module->InitRandomPositionZ(min, max); }
//
//	//위치에 따른 방향성 속도 그래프 세팅
//	void addPosDirectVelGraph(float point, float min, float max) { _module->addPosDirectVelGraph(point, min, max); }
//
//public:  //=======================================================================================================================
//	//속도
//	void InitRandomVelocityX(float min, float max) { _module->InitRandomVelocityX(min, max); }
//	void InitRandomVelocityY(float min, float max) { _module->InitRandomVelocityY(min, max); }
//	void InitRandomVelocityZ(float min, float max) { _module->InitRandomVelocityZ(min, max); }
//
//	//속도 그래프
//	void addVelocityGraphX(float point, float min, float max) { _module->addVelocityGraphX(point, min, max); }
//	void addVelocityGraphY(float point, float min, float max) { _module->addVelocityGraphY(point, min, max); }
//	void addVelocityGraphZ(float point, float min, float max) { _module->addVelocityGraphZ(point, min, max); }
//
//public:  //=======================================================================================================================
//	//가속도
//	void InitRandomAccelerationX(float min, float max) { _module->InitRandomAccelerationX(min, max); }
//	void InitRandomAccelerationY(float min, float max) { _module->InitRandomAccelerationY(min, max); }
//	void InitRandomAccelerationZ(float min, float max) { _module->InitRandomAccelerationZ(min, max); }
//
//public:  //=======================================================================================================================
//	//색
//	void InitRandomColorR(float min, float max) { _module->InitRandomColorR(min, max); }
//	void InitRandomColorG(float min, float max) { _module->InitRandomColorG(min, max); }
//	void InitRandomColorB(float min, float max) { _module->InitRandomColorB(min, max); }
//
//	//색 소멸
//	void InitRandomColorFadeR(float min, float max) { _module->InitRandomColorFadeR(min, max); }
//	void InitRandomColorFadeG(float min, float max) { _module->InitRandomColorFadeG(min, max); }
//	void InitRandomColorFadeB(float min, float max) { _module->InitRandomColorFadeB(min, max); }
//
//	//알파
//	void InitRandomAlpha(float min, float max) { _module->InitRandomAlpha(min, max); }
//	void InitRandomAlphaFade(float min, float max) { _module->InitRandomAlphaFade(min, max); }
//
//	//알파 그래프
//	void addAlphaGraph(float point, float min, float max) { _module->addAlphaGraph(point, min, max); };
//
//public:
//	//생명
//	void InitRandomLifeTime(float min, float max) { _module->InitRandomLiftTime(min, max); }
//
//public:	//=======================================================================================================================
//	//사이즈 세팅
//	void InitRandomSize(float min, float max) { _module->InitRandomSize(min, max); }
//	void InitRandomSizeEnd(float min, float max) { _module->InitRandomSizeEnd(min, max); }
//
//	//사이즈 그래프 세팅
//	void InitConstSize(float size) { _constPaticleSize = size; }
//	
//	void addSizeGraph(float point, float min, float max) { _module->addSizeGraph(point, min, max); };
//	
//	
//public:	//=======================================================================================================================
//	//원 회전 반지름 초기화
//	void InitRandomRadiusX(float min, float max) { _module->InitRandomRadiusX(min, max); }
//	void InitRandomRadiusY(float min, float max) { _module->InitRandomRadiusY(min, max); }
//	void InitRandomRadiusZ(float min, float max) { _module->InitRandomRadiusZ(min, max); }
//	//원 회전 스피드
//	void InitRandomAngleSpeedX(float min, float max) { _module->InitRandomAngleSpeedX(min, max); }
//	void InitRandomAngleSpeedY(float min, float max) { _module->InitRandomAngleSpeedY(min, max); }
//	void InitRandomAngleSpeedZ(float min, float max) { _module->InitRandomAngleSpeedZ(min, max); }
//	//원 회전 시작각도								  
//	void InitRandomStartAngleX(float min, float max) { _module->InitRandomStartAngleX(min, max); }
//	void InitRandomStartAngleY(float min, float max) { _module->InitRandomStartAngleY(min, max); }
//	void InitRandomStartAngleZ(float min, float max) { _module->InitRandomStartAngleZ(min, max); }
//	//원회전 반지름 마지막
//	void InitRandomRadiusEndX(float min, float max) { _module->InitRandomRadiusEndX(min, max); }
//	void InitRandomRadiusEndY(float min, float max) { _module->InitRandomRadiusEndY(min, max); }
//	void InitRandomRadiusEndZ(float min, float max) { _module->InitRandomRadiusEndZ(min, max); }
//
//
//	//void InitRandomSpawnTime(float min, float max) { init(_textureFileName, _onePtcNum, RandomFloatRange(min, max)); }
//	//void InitRandomDirectionVelocity(float min, float max) { _module->InitRandomDirectionVelocity(min, max); }
//	

public:
	////리셋
	//void reset()
	//{
	//	_ptcList.clear();
	//	_ptcList.resize(_totalPtcNum);
	//	_currentDelayTime = 0.0f;
	//	//_spawnCurrentTime = _spawnTime;
	//	if (_startDelayTimeOn)
	//	{
	//		_spawnCurrentTime = 0.0f;	
	//	}
	//	else 
	//	{	
	//		_spawnCurrentTime = _spawnTime; 
	//	}
	//}
public:
	/*void CopyInit()
	{
		_ptcVtx = NULL;
		_ptcVtx = new tagDxParticle[(int)_vbSize];
		_drawVtx = NULL;
		_drawVtx = new tagDxParticle[(int)_vbSize];
	}*/

public:
	dxPointEmitter()
	{
		//모듈 초기화
		_module = new dxModuleKit;
		_trans = new transform;
		_module->init();
		//이미터 타입 설정
		_EmitterType = ET_POINT;
		//_startDelayTimeOn = false;
	};
	~dxPointEmitter() {};
	
};

