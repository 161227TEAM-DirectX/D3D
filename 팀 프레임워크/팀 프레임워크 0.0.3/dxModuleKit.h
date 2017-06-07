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

	//위치
	void InitRandomPositionX(float min, float max) { _posMD->InitRandomPositionX(min, max);}
	void InitRandomPositionY(float min, float max) { _posMD->InitRandomPositionY(min, max);}
	void InitRandomPositionZ(float min, float max) { _posMD->InitRandomPositionZ(min, max);}

	//위치에 따른 방향성 속도
	void InitRandomPosDirectionVelocity(float min, float max) { _posMD->InitRandomPosDirectionVelocity(min, max); }

	//위치에 따른 방향성 속도 그래프 세팅
	void addPosDirectVelGraph(float point, float min, float max) { _posMD->addPosDirectVelGraph(point, min, max); };


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
	void InitRandomRadiusX(float min, float max) { _circleMD->InitRandomRadiusX(min, max); }
	void InitRandomRadiusY(float min, float max) { _circleMD->InitRandomRadiusY(min, max); }
	void InitRandomRadiusZ(float min, float max) { _circleMD->InitRandomRadiusZ(min, max); }

	//각도 스피드
	void InitCircleAngleSpeedX(float min, float max) { _circleMD->InitCircleAngleSpeedX(min, max); }
	void InitCircleAngleSpeedY(float min, float max) { _circleMD->InitCircleAngleSpeedY(min, max); }
	void InitCircleAngleSpeedZ(float min, float max) { _circleMD->InitCircleAngleSpeedZ(min, max); }

	//시작 각도
	void InitCircleStartAngleX(float min, float max) { _circleMD->InitCircleStartAngleX(min, max); }
	void InitCircleStartAngleY(float min, float max) { _circleMD->InitCircleStartAngleY(min, max); }
	void InitCircleStartAngleZ(float min, float max) { _circleMD->InitCircleStartAngleZ(min, max); }

	//반지름 마지막
	void InitRandomRadiusEndX(float min, float max) { _circleMD->InitRandomRadiusEndX(min, max); }
	void InitRandomRadiusEndY(float min, float max) { _circleMD->InitRandomRadiusEndY(min, max); }
	void InitRandomRadiusEndZ(float min, float max) { _circleMD->InitRandomRadiusEndZ(min, max); }
	
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
	void InitConstVH(float vertical, float horizontal) { _sizeMD->InitConstVH(vertical, horizontal); }

public:	//=======================================================================================================================
	//UV애니메이션
	void InitAnimation(int inFrameMaxX, int inFrameMaxY, int inTotalFrame) { _uvMD->InitAnimation(inFrameMaxX, inFrameMaxY, inTotalFrame); }
	//애니메이션 재생수
	void InitConstAniReactivateNum(int inReactiveateNum) { _uvMD->InitConstAniReactivateNum(inReactiveateNum); }


public:
	dxModuleKit() {};
	virtual ~dxModuleKit() {};
};

