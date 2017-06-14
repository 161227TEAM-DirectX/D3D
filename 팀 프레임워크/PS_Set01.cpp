#include "stdafx.h"
#include "PS_Set00.h"

HRESULT PS_Set01::init()
{
	//파티클 이름이 잘 보이게 일부러 이름 넣는 인자값을 준다.
	this->set00_00("마법진");
	this->set00_01("타겟");
	//this->set00_02("");

	return S_OK;
}

void PS_Set01::release()
{
	dxParticleSystemSet::release();
}

void PS_Set01::set00_00(string psName)
{
	dxParticleSystemSet::init();

	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("PaticleResources/Texture/magicCircle02.png", 1, 1.0f, 1);
	//_pointEMT->InitConstSize(2.4f);

	_planeEMT->InitRandomSize(2.4f, 2.4f);
	//_pointEMT->addSizeGraph(0.5f, 2.8f, 2.8f);
	//_pointEMT->addSizeGraph(1.0f, 2.2f, 2.2f);

	/*_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	_pointEMT->InitRandomPositionZ(-1.0f, 1.0f);*/

	//_pointEMT->InitRandomVelocityX(-3.0f, 3.0f);
	//_pointEMT->InitRandomVelocityY(0.0f, 0.0f);
	//_pointEMT->InitRandomVelocityZ(-3.0f, 3.0f);

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

	_planeEMT->InitRandomColorR(1.0f,1.0f);
	_planeEMT->InitRandomColorG(1.0f,1.0f);
	_planeEMT->InitRandomColorB(1.0f,1.0f);
	_planeEMT->InitRandomColorFadeR(1.0f,1.0f);
	//_planeEMT->InitRandomColorFadeG(0.0f, 0.0f);
	//_planeEMT->InitRandomColorFadeB(1.0f, 1.0f);

	_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	_planeEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_planeEMT);

	//_planeEMT = NULL;
	//_planeEMT = new dxPlaneEmitter;
	//_planeEMT->init("PaticleResources/Texture/magicCircle01.png", 1, 10.0f, 1);
	////_pointEMT->InitConstSize(2.4f);

	//_planeEMT->InitRandomSize(1.2f, 1.2f);
	//
	//_planeEMT->InitRandomPositionY(1.0f, 1.0f);
	//_planeEMT->InitRandomPositionZ(1.2f, 1.2f);

	//_planeEMT->InitRandomColorR(0.0f,0.0f);
	//_planeEMT->InitRandomColorG(0.8f,0.8f);
	//_planeEMT->InitRandomColorB(1.0f,1.0f);
	////_planeEMT->InitRandomColorFadeR(1.0f,1.0f);
	////_planeEMT->InitRandomColorFadeG(1.0f, 0.5f);
	////_planeEMT->InitRandomColorFadeB(1.0f, 1.0f);

	//_planeEMT->InitRotateStartAngleX(90.0f,90.0f);
	//_planeEMT->InitRotateAngleSpeedY(24.0f,24.0f);

	//_planeEMT->InitRandomLifeTime(10.0f, 10.0f);

	//_PS->addEmitter(_planeEMT);


	//_boardEMT = NULL;
	//_boardEMT = new dxBoardEmitter;
	//_boardEMT->init("PaticleResources/Texture/rune00_frame7x4_tt15.png", 1, 0.05f, 20);

	//_boardEMT->InitRandomPositionY(0.8f,0.8f);
	//_boardEMT->InitRandomSize(0.3f, 0.3f);
	//_boardEMT->InitRandomRadiusY(1.4f,1.4f);
	////_boardEMT->InitCircleStartAngleY(0.0f,0.0f);
	//_boardEMT->InitCircleAngleSpeedY(720.0f,720.0f);
	//_boardEMT->InitRandomLifeTime(0.65f, 0.65f);
	//_boardEMT->InitAnimation(7,4,15);

	//_boardEMT->InitRandomColorR(0.0f, 0.0f);
	//_boardEMT->InitRandomColorG(0.4f, 1.0f);
	//_boardEMT->InitRandomColorB(1.0f, 1.0f);

	//_PS->addEmitter(_boardEMT);

	//_boardEMT = NULL;
	//_boardEMT = new dxBoardEmitter;
	//_boardEMT->init("PaticleResources/Texture/rune00_frame7x4_tt15.png", 1, 0.05f, 20);

	//_boardEMT->InitRandomPositionY(1.5f, 1.5f);
	//_boardEMT->InitRandomSize(0.3f, 0.3f);
	//_boardEMT->InitRandomRadiusY(1.0f, 1.0f);
	////_boardEMT->InitCircleStartAngleY(0.0f,0.0f);
	//_boardEMT->InitCircleAngleSpeedY(-720.0f, -720.0f);
	//_boardEMT->InitRandomLifeTime(0.65f, 0.65f);
	//_boardEMT->InitAnimation(7, 4, 15);

	//_boardEMT->InitRandomColorR(0.0f, 0.0f);
	//_boardEMT->InitRandomColorG(1.0f, 1.0f);
	//_boardEMT->InitRandomColorB(0.4f, 1.0f);

	//_PS->addEmitter(_boardEMT);


	//
	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light09.png", 30, 0.3f, 30);

	//_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	_pointEMT->InitConstAttractCenter(0.0f, 1.0f, 2.0f);
	_pointEMT->SetPositionType(PTC_SPHERE);
	_pointEMT->InitRandomPosSphereRadius(1.5f,2.0f);
	_pointEMT->InitDirSphere(1.0f,1.0f,0.0f);

	_pointEMT->InitRandomColorR(0.0f, 0.0f);
	_pointEMT->InitRandomColorFadeR(1.0f, 1.0f);


	_pointEMT->InitRandomSize(2.0f, 2.0f);
	_pointEMT->InitRandomSizeEnd(1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(1.0f, 1.0f);
	_pointEMT->InitRandomPositionZ(2.0f, 2.0f);
	//_pointEMT->InitRandomPositionY(-2.0f, 2.0f);
	//_pointEMT->InitRandomPositionZ(-2.0f, 2.0f);
	_pointEMT->InitRandomLifeTime(0.1f,0.3f);
	//_pointEMT->SetActiveLimitTime(1.0f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/default.png", 1, 0.8f, 1);

	//_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	//_pointEMT->InitConstAttractCenter(0.0f, 1.0f, 2.0f);
	//_pointEMT->SetPositionType(PTC_SPHERE);
	//_pointEMT->InitRandomPosSphereRadius(3.0f, 3.0f);
	//_pointEMT->InitDirSphere(1.0f, 1.0f, 0.0f);

	_pointEMT->InitRandomSize(1.2f, 1.2f);
	_pointEMT->addSizeGraph(0.5f, 2.0f,2.0f);
	_pointEMT->addSizeGraph(1.0f, 1.0f, 1.0f);
	//_pointEMT->InitRandomSizeEnd(1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(1.0f, 1.0f);
	_pointEMT->InitRandomPositionZ(2.0f, 2.0f);
	//_pointEMT->InitRandomPositionY(-2.0f, 2.0f);
	//_pointEMT->InitRandomPositionZ(-2.0f, 2.0f);
	_pointEMT->InitRandomColorR(1.0f, 1.0f);
	_pointEMT->InitRandomColorG(1.0f, 1.0f);
	_pointEMT->InitRandomColorB(1.0f, 1.0f);

	_pointEMT->InitRandomColorFadeR(1.0f, 1.0f);
	//_pointEMT->InitRandomColorG(1.0f, 1.0f);
	//_pointEMT->InitRandomColorB(1.0f, 1.0f);

	_pointEMT->InitRandomLifeTime(0.8f, 0.8f);

	_PS->addEmitter(_pointEMT);


	PSM->addPS(psName, _PS);
}

void PS_Set01::set00_01(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light06.png", 1, 1.0f , 1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	
	_pointEMT->InitRandomSize(2.5f, 2.5f);
	_pointEMT->InitRandomSizeEnd(7.0f,7.0f);

	_pointEMT->InitRandomAlpha(0.4f, 0.4f);
	_pointEMT->addAlphaGraph(0.8, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.7f, 0.7f);
//	_pointEMT->InitRandomAlphaFade(.0f, 10.0f);
	//_pointEMT->addSizeGraph(0.5f, 3.5f, 3.5f);
	//_pointEMT->addSizeGraph(1.0f, 2.5f, 2.5f);
	

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/explosion.png", 1, 1.0f,1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	_pointEMT->InitRandomSize(2.2f,2.2f);
	_pointEMT->addSizeGraph(0.5f,4.5f,4.5f);
	_pointEMT->addSizeGraph(1.0f,1.5f,1.5f);
	_pointEMT->InitRandomAlpha(1.0f, 1.0f);
	_pointEMT->addAlphaGraph(0.6, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.3f, 0.3f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light02.png", 1, 1.0f,1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	_pointEMT->InitRandomSize(2.0f, 2.0f);
	_pointEMT->addSizeGraph(0.7f, 2.5f, 2.5f);
	_pointEMT->addSizeGraph(1.0f, 7.5f, 7.5f);
	_pointEMT->InitRandomAlpha(0.2f, 0.2f);
	_pointEMT->addAlphaGraph(0.7, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_PS->addEmitter(_pointEMT);

	PSM->addPS(psName, _PS);
}
