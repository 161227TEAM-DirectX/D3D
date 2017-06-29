#pragma once
#include "dxModule.h"
#include "dxPositionModule.h"
#include "dxVelocityModule.h"
#include "dxAccelerationModule.h"
#include "dxColorModule.h"
#include "dxSizeModule.h"
#include "dxLifeTimeModule.h"
#include "dxCircleModule.h"

#include "dxRotationModule.h"
#include "dxUVModule.h"

//모듈을 모으자!!
class dxModuleKit
{
private:
	dxPositionModule*		_posMD;		//위치
	dxVelocityModule*		_velMD;		//속도
	dxAccelerationModule*	_accelMD;	//가속도
	dxColorModule*			_colorMD;	//색깔
	dxSizeModule*			_sizeMD;	//사이즈
	dxLifeTimeModule*		_lifeMD;	//생명시간
	dxCircleModule*			_circleMD;	//원회전
	dxRotationModule*		_rotateMD;	//회전
	dxUVModule*				_uvMD;

private:
	bool _realTimeTrackingOn;

public:
	virtual void setRealTimeTrackingOn(void) { _realTimeTrackingOn = true; };

public:
	virtual HRESULT init();
	virtual void relese();
	/*virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);*/

	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:	//=======================================================================================================================
	//위치 타입 세팅
	void SetPositionType(PTC_POSITION_TYPE posType) { _posMD->SetPositionType(posType); }
	void InitRandomPosSphereRadius(float min, float max) { _posMD->InitRandomPosSphereRadius(min, max); }

	//구 방향 세팅
	void InitDirSphere(float dirX, float dirY, float dirZ) { _posMD->InitDirSphere(dirX, dirY, dirZ); }

	//위치
	void InitRandomPositionX(float min, float max) { _posMD->InitRandomPositionX(min, max);}
	void InitRandomPositionY(float min, float max) { _posMD->InitRandomPositionY(min, max);}
	void InitRandomPositionZ(float min, float max) { _posMD->InitRandomPositionZ(min, max);}

public:	//=======================================================================================================================
	//위치에서 폭파
	void InitRandomPosExplosionVel(float min, float max) { _posMD->InitRandomPosExplosionVel(min, max); }

	//위치폭파 그래프 세팅
	void addPosExplosionVelGraph(float point, float min, float max) { _posMD->addPosExplosionVelGraph(point, min, max); };

public:	//=======================================================================================================================
	//위치 중심 회전
	void InitRandomPosRotAngleSpeedX(float min, float max) { _posMD->InitRandomPosRotAngleSpeedX(min, max); }
	void InitRandomPosRotAngleSpeedY(float min, float max) { _posMD->InitRandomPosRotAngleSpeedY(min, max); }
	void InitRandomPosRotAngleSpeedZ(float min, float max) { _posMD->InitRandomPosRotAngleSpeedZ(min, max); }

public:	//=======================================================================================================================
	//끌림 고정
	void InitConstAttractCenter(float x, float y, float z) { _posMD->InitConstAttractCenter( x, y, z); }
	//끌림 랜덤
	void InitAttractCenterX(float min, float max) { _posMD->InitAttractCenterX(min, max); }
	void InitAttractCenterY(float min, float max) { _posMD->InitAttractCenterY(min, max); }
	void InitAttractCenterZ(float min, float max) { _posMD->InitAttractCenterZ(min, max); }


public:	//=======================================================================================================================
	//속도
	void InitRandomVelocityX(float min, float max) { _velMD->InitRandomVelocityX(min, max); }
	void InitRandomVelocityY(float min, float max) { _velMD->InitRandomVelocityY(min, max); }
	void InitRandomVelocityZ(float min, float max) { _velMD->InitRandomVelocityZ(min, max); }

	//속도 그래프 세팅
	void addVelocityGraphX(float point, float min, float max) { _velMD->addVelocityGraphX(point, min, max); }
	void addVelocityGraphY(float point, float min, float max) { _velMD->addVelocityGraphY(point, min, max); }
	void addVelocityGraphZ(float point, float min, float max) { _velMD->addVelocityGraphZ(point, min, max); }


public:	//=======================================================================================================================

	//가속도
	void InitRandomAccelerationX(float min, float max) { _accelMD->InitRandomAccelerationX(min, max); }
	void InitRandomAccelerationY(float min, float max) { _accelMD->InitRandomAccelerationY(min, max); }
	void InitRandomAccelerationZ(float min, float max) { _accelMD->InitRandomAccelerationZ(min, max); }


public:	//=======================================================================================================================
	//초기색
	void InitRandomColorR(float min, float max) { _colorMD->InitRandomColorR(min, max); }
	void InitRandomColorG(float min, float max) { _colorMD->InitRandomColorG(min, max); }
	void InitRandomColorB(float min, float max) { _colorMD->InitRandomColorB(min, max); }

	//색 소멸
	void InitRandomColorFadeR(float min, float max) { _colorMD->InitRandomColorFadeR(min, max); }
	void InitRandomColorFadeG(float min, float max) { _colorMD->InitRandomColorFadeG(min, max); }
	void InitRandomColorFadeB(float min, float max) { _colorMD->InitRandomColorFadeB(min, max); }

	//색깔 그래프 세팅
	void addColorGraphR(float point, float min, float max) { _colorMD->addColorGraphR(point,min, max); }
	void addColorGraphG(float point, float min, float max) { _colorMD->addColorGraphG(point,min, max); }
	void addColorGraphB(float point, float min, float max) { _colorMD->addColorGraphB(point,min, max); }

	//알파
	void InitRandomAlpha(float min, float max) { _colorMD->InitRandomAlpha(min, max); }
	void InitRandomAlphaFade(float min, float max) { _colorMD->InitRandomAlphaFade(min, max); }

	//알파 그래프 세팅
	void addAlphaGraph(float point, float min, float max) { _colorMD->addAlphaGraph(point, min, max); }


public:	//=======================================================================================================================
	//사이즈 세팅
	void InitRandomSize(float min, float max) { _sizeMD->InitRandomSize(min, max); }
	void InitRandomSizeEnd(float min, float max) { _sizeMD->InitRandomSizeEnd(min, max); }
	//사이즈 그래프 세팅
	void addSizeGraph(float point, float min, float max) { _sizeMD->addSizeGraph(point, min, max); }


public:	//=======================================================================================================================
	//라이프 세팅
	void InitRandomLiftTime(float min, float max) { _lifeMD->InitRandomLiftTime(min, max); }
	

public:	//=======================================================================================================================

	//반지름 그래프 세팅
	void addRadiusGraph(float point, float min, float max) { _circleMD->addRadiusGraph(point, min, max); }


	//반지름
	void InitCircleRadiusX(float min, float max) { _circleMD->InitCircleRadiusX(min, max); }
	void InitCircleRadiusY(float min, float max) { _circleMD->InitCircleRadiusY(min, max); }
	void InitCircleRadiusZ(float min, float max) { _circleMD->InitCircleRadiusY(min, max); }

	//각도 스피드
	void InitCircleAngleSpeedX(float min, float max) { _circleMD->InitCircleAngleSpeedX(min, max); }
	void InitCircleAngleSpeedY(float min, float max) { _circleMD->InitCircleAngleSpeedY(min, max); }
	void InitCircleAngleSpeedZ(float min, float max) { _circleMD->InitCircleAngleSpeedZ(min, max); }

	//시작 각도
	void InitCircleStartAngleX(float min, float max) { _circleMD->InitCircleStartAngleX(min, max); }
	void InitCircleStartAngleY(float min, float max) { _circleMD->InitCircleStartAngleY(min, max); }
	void InitCircleStartAngleZ(float min, float max) { _circleMD->InitCircleStartAngleZ(min, max); }

	//반지름 마지막
	void InitCircleRadiusEndX(float min, float max) { _circleMD->InitCircleRadiusEndX(min, max); }
	void InitCircleRadiusEndY(float min, float max) { _circleMD->InitCircleRadiusEndY(min, max); }
	void InitCircleRadiusEndZ(float min, float max) { _circleMD->InitCircleRadiusEndZ(min, max); }
	
public:	//=======================================================================================================================
	//회전시작 각도
	void InitRotateStartAngleX(float min, float max) { _rotateMD->InitRotateStartAngleX(min, max); }
	void InitRotateStartAngleY(float min, float max) { _rotateMD->InitRotateStartAngleY(min, max); }
	void InitRotateStartAngleZ(float min, float max) { _rotateMD->InitRotateStartAngleZ(min, max); }

	//회전각도 스피드
	void InitRotateAngleSpeedX(float min, float max) { _rotateMD->InitRotateAngleSpeedX(min, max); }
	void InitRotateAngleSpeedY(float min, float max) { _rotateMD->InitRotateAngleSpeedY(min, max); }
	void InitRotateAngleSpeedZ(float min, float max) { _rotateMD->InitRotateAngleSpeedZ(min, max); }

public:	//=======================================================================================================================
	//가로세로
	void InitConstHV(float horizontal, float vertical) { _sizeMD->InitConstHV(horizontal, vertical); }

	//면 상에서 중심 위치를 세팅
	void InitCenterPointHV(float pointH, float pointV) { _sizeMD->InitCenterPointHV(pointH, pointV); }

public:	//=======================================================================================================================
	//UV애니메이션
	void InitAnimation(int inFrameMaxX, int inFrameMaxY, int inTotalFrame) { _uvMD->InitAnimation(inFrameMaxX, inFrameMaxY, inTotalFrame); }
	//애니메이션 재생수
	void InitConstAniReactivateNum(int inReactiveateNum) { _uvMD->InitConstAniReactivateNum(inReactiveateNum); }
	//애니매이션 시작지점과 끝지점 지정가능
	void InitAniPlaySection(int inStartFrameNum, int inEndFrameNum) { _uvMD->InitAniPlaySection(inStartFrameNum, inEndFrameNum); }

	//UV이미지 반전
	void uvReverseImgU() { _uvMD->uvReverseImgU(); }
	void uvReverseImgV() { _uvMD->uvReverseImgV(); }


public:
	dxModuleKit() {};
	virtual ~dxModuleKit() {};
};

