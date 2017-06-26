#include "stdafx.h"
#include "psBossSet00.h"

HRESULT psBossSet00::init()
{
	//파티클 이름이 잘 보이게 일부러 이름 넣는 인자값을 준다.
	this->BreathSet00("브레스");
	this->ShoutingSet00("샤우팅");

	this->GrandMagic00("대마법진");
	this->GrandMagic01("대규모");

	return S_OK;
}

void psBossSet00::release()
{
	dxParticleSystemSet::release();
}

void psBossSet00::BreathSet00(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("PaticleResources/Texture/fire02_frame5x4.png", 15, 0.1f, 800);
	//_pointEMT->InitConstSize(2.4f);
	_boardEMT->InitRandomSize(1.0f, 1.5f);
	_boardEMT->InitRandomSizeEnd(2.3f, 2.8f);
	//_pointEMT->addSizeGraph(0.5f, 2.8f, 2.8f);
	//_pointEMT->addSizeGraph(1.0f, 2.2f, 2.2f);

	//_boardEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_boardEMT->InitRandomPositionY(-0.5f, 0.5f);
	//_boardEMT->InitRandomPositionZ(0.0f, 0.5f);

	//_boardEMT->InitRandomVelocityX(-3.0f, 3.0f);
	//_boardEMT->InitRandomVelocityY(-1.0f, 1.0f);
	_boardEMT->InitRandomVelocityZ(5.0f, 10.0f);
	//_boardEMT->InitRandomVelocityZ(0.05f, 0.05f);

	//_pointEMT->InitRandomVelocityX(0.0f, 0.0f);
	//_pointEMT->InitRandomVelocityY(1.0f, 2.0f);
	//_pointEMT->InitRandomVelocityZ(0.0f, 0.0f);

	//_pointEMT->InitRandomAccelerationX(0.0f,0.0f);
	//_pointEMT->InitRandomAccelerationY(200.0f, 200.0f);
	//_pointEMT->InitRandomAccelerationZ(0.0f,0.0f);

	/*_pointEMT->InitRandomColorR(0.0f, 0.0f);
	_pointEMT->InitRandomColorG(0.6f, 0.6f);
	_pointEMT->InitRandomColorB(0.6f, 0.6f);*/

	/*_pointEMT->InitRandomColorFadeR(0.1f, 1.0f);
	_pointEMT->InitRandomColorFadeG(0.1f, 1.0f);
	_pointEMT->InitRandomColorFadeB(0.0f, 0.0f);*/

	/*_pointEMT->InitRandomAlpha(1.0f, 1.0f);
	_pointEMT->InitRandomAlphaFade(0.1f, 0.1f);*/
	_boardEMT->InitAnimation(5,4);
	//_boardEMT->InitConstAniReactivateNum(2);
	/*_planeEMT->InitRandomColorR(1.0f,1.0f);
	_planeEMT->InitRandomColorG(1.0f,1.0f);
	_planeEMT->InitRandomColorB(1.0f,1.0f);
	_planeEMT->InitRandomColorFadeR(1.0f,1.0f);*/
	//_planeEMT->InitRandomColorFadeG(0.0f, 0.0f);
	//_planeEMT->InitRandomColorFadeB(1.0f, 1.0f);

	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	//_boardEMT->InitRotateAngleSpeedZ(100.0f,100.0f);


	//_boardEMT->InitRotateStartAngleZ(10.0f)
	//_boardEMT->InitCircleStartAngleY(90.0,90.f);
	_boardEMT->InitCircleStartAngleZ(0.0f,360.0f);
	_boardEMT->InitCircleRadiusZ(0.0f, 0.0f);
	_boardEMT->InitCircleRadiusEndZ(5.0f, 5.0f);

	//_boardEMT->InitCircleAngleSpeedZ(100.0f, 120.0f);

	_boardEMT->InitRandomLifeTime(3.0f, 5.0f);

	_PS->addEmitter(_boardEMT);
	

	PSM->addPS(psName, _PS, false);
}

//샤우팅
void psBossSet00::ShoutingSet00(string psName)
{
	dxParticleSystemSet::init();

	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("PaticleResources/Texture/shouting02.png", 1, 0.5f, 1);
	
	_planeEMT->InitRandomSize(1.0f,1.0f);
	_planeEMT->InitRandomSizeEnd(20.0f, 20.0f);

	_planeEMT->InitRandomLifeTime(0.5f, 0.5f);

	_PS->addEmitter(_planeEMT);

	PSM->addPS(psName, _PS);
}

//대규모 마법
void psBossSet00::GrandMagic00(string psName)
{
	dxParticleSystemSet::init();

	/*_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("PaticleResources/Texture/cast_magiCircle02_f5x7.png", 1, 1.0f, 1);
	_planeEMT->InitAnimation(5,7);
	_planeEMT->InitRandomLifeTime(1.0f,1.0f);
	_planeEMT->InitRandomSize(5.0f, 5.0f);

	_PS->addEmitter(_planeEMT);*/

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("PaticleResources/Texture/wind_f5x3_tt13.png", 1, 1.0f, 1);
	_boardEMT->InitAnimation(5, 3, 12);
	//_boardEMT->InitAnimation(5, 3, 13);
	_boardEMT->InitRandomLifeTime(1.0f, 1.0f);
	_boardEMT->InitRandomSize(4.0f, 4.0f);
	_boardEMT->InitRandomSizeEnd(20.0f, 20.0f);
	_boardEMT->InitRandomAlpha(0.1f, 0.1f);

	_PS->addEmitter(_boardEMT);

	


	PSM->addPS(psName, _PS);
}

void psBossSet00::GrandMagic01(string psName)
{
}
