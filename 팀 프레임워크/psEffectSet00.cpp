#include "stdafx.h"
#include "psEffectSet00.h"

HRESULT psEffectSet00::init()
{
	//파티클 이름이 잘 보이게 일부러 이름 넣는 인자값을 준다.
	this->EffectSet00("스턴");
	this->EffectSet01("먼지");
	this->EffectSet02("피격");

	this->EffectSet03("날기_먼지");

	return S_OK;
}

void psEffectSet00::release()
{
	dxParticleSystemSet::release();
}


void psEffectSet00::EffectSet00(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/star.png", 1, 1.0f, 1);

	_boardEMT->InitRandomSize(0.4f, 0.4f);

	_boardEMT->InitRandomPositionY(1.0f, 1.0f);
	_boardEMT->InitCircleRadiusY(1.0f, 1.0f);
	_boardEMT->InitCircleAngleSpeedY(360.0f, 360.0f);
	_boardEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_boardEMT);

	//
	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/star.png", 1, 1.0f, 1);

	_boardEMT->InitRandomSize(0.4f, 0.4f);

	_boardEMT->InitRandomPositionY(1.0f, 1.0f);

	_boardEMT->InitCircleStartAngleY(120.0f,120.0f);
	_boardEMT->InitCircleRadiusY(1.0f, 1.0f);
	_boardEMT->InitCircleAngleSpeedY(360.0f, 360.0f);
	_boardEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_boardEMT);

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/star.png", 1, 1.0f, 1);

	_boardEMT->InitRandomSize(0.4f, 0.4f);

	_boardEMT->InitRandomPositionY(1.0f, 1.0f);

	_boardEMT->InitCircleStartAngleY(240.0f, 240.0f);
	_boardEMT->InitCircleRadiusY(1.0f, 1.0f);
	_boardEMT->InitCircleAngleSpeedY(360.0f, 360.0f);
	_boardEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_boardEMT);


	PSM->addPS(psName, _PS, true);

}

void psEffectSet00::EffectSet01(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/smoke02_frame4x4.png", 1, 0.4f, 20);
	//_pointEMT->InitConstSize(2.4f);

	_boardEMT->InitRandomSize(0.0f, 0.2f);
	_boardEMT->InitRandomSizeEnd(1.0f, 1.2f);
	//_pointEMT->addSizeGraph(0.5f, 2.8f, 2.8f);
	//_pointEMT->addSizeGraph(1.0f, 2.2f, 2.2f);

	//_boardEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_boardEMT->InitRandomPositionY(-0.5f, 0.5f);
	_boardEMT->InitRandomPositionZ(-0.2f, 0.5f);

	//_boardEMT->InitRandomVelocityX(-3.0f, 3.0f);
	_boardEMT->InitRandomVelocityY(0.5f, 0.8f);
	_boardEMT->InitRandomVelocityZ(2.0f, 2.0f);

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

	_boardEMT->InitRandomAlpha(0.1f, 0.1f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.2f, 0.2f);
	//_pointEMT->InitRandomAlphaFade(0.2f, 0.2f);
	_boardEMT->InitAnimation(4, 4);
	//_boardEMT->InitConstAniReactivateNum(2);
	//_boardEMT->InitRandomColorR(0.5f,0.5f);
	//_boardEMT->InitRandomColorG(0.2f,0.2f);
	//_boardEMT->InitRandomColorB(0.0f,0.0f);
	//_planeEMT->InitRandomColorFadeR(1.0f,1.0f);
	//_planeEMT->InitRandomColorFadeG(0.0f, 0.0f);
	//_planeEMT->InitRandomColorFadeB(1.0f, 1.0f);

	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	//_boardEMT->InitRotateAngleSpeedZ(100.0f,100.0f);

	//D3DXCOLOR color;
	//color.r = color_
	//_boardEMT->InitRotateStartAngleZ(10.0f)

	/*_boardEMT->InitCircleStartAngleZ(0.0f, 360.0f);
	_boardEMT->InitCircleRadiusZ(0.0f, 0.0f);
	_boardEMT->InitCircleRadiusEndZ(5.0f, 5.0f);*/
	//_boardEMT->InitRandomRadiusZ(5.0f, 5.0f);

	//_boardEMT->
	//_boardEMT->InitCircleAngleSpeedZ(100.0f, 120.0f);

	_boardEMT->InitRandomLifeTime(0.7f, 1.2f);

	_PS->addEmitter(_boardEMT);


	PSM->addPS(psName, _PS, true);
}

void psEffectSet00::EffectSet02(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/GlassShatter.png", 2, 0.3f, 2);
	//_pointEMT->InitConstSize(2.4f);

	_boardEMT->InitRandomSize(2.0f, 2.0f);
	_boardEMT->InitRandomSizeEnd(3.5f, 3.5f);
	//_pointEMT->addSizeGraph(0.5f, 2.8f, 2.8f);
	//_pointEMT->addSizeGraph(1.0f, 2.2f, 2.2f);

	//_boardEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_boardEMT->InitRandomPositionY(-0.5f, 0.5f);
	//_boardEMT->InitRandomPositionZ(-0.2f, 0.5f);

	//_boardEMT->InitRandomVelocityX(-3.0f, 3.0f);
	//_boardEMT->InitRandomVelocityY(0.5f, 0.8f);
	//_boardEMT->InitRandomVelocityZ(2.0f, 2.0f);

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

	_boardEMT->InitRandomAlpha(0.3f, 0.3f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.2f, 0.1f);
	//_pointEMT->InitRandomAlphaFade(0.2f, 0.2f);
	//_boardEMT->InitAnimation(4, 4);
	//_boardEMT->InitConstAniReactivateNum(2);
	_boardEMT->InitRandomColorR(0.8f, 1.0f);
	//_boardEMT->InitRandomColorG(0.2f,0.2f);
	//_boardEMT->InitRandomColorB(0.0f,0.0f);
	//_planeEMT->InitRandomColorFadeR(1.0f,1.0f);
	//_planeEMT->InitRandomColorFadeG(0.0f, 0.0f);
	//_planeEMT->InitRandomColorFadeB(1.0f, 1.0f);

	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	//_boardEMT->InitRotateAngleSpeedZ(100.0f,100.0f);

	//D3DXCOLOR color;
	//color.r = color_
	//_boardEMT->InitRotateStartAngleZ(10.0f)
	_boardEMT->InitRotateStartAngleZ(0.0f, 360.0f);

	/*_boardEMT->InitCircleStartAngleZ(0.0f, 360.0f);
	_boardEMT->InitCircleRadiusZ(0.0f, 0.0f);
	_boardEMT->InitCircleRadiusEndZ(5.0f, 5.0f);*/
	//_boardEMT->InitRandomRadiusZ(5.0f, 5.0f);

	//_boardEMT->
	//_boardEMT->InitCircleAngleSpeedZ(100.0f, 120.0f);

	_boardEMT->InitRandomLifeTime(0.3f, 0.3f);

	_PS->addEmitter(_boardEMT);

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/damage01.png", 1, 0.3f, 1);
	//_pointEMT->InitConstSize(2.4f);

	_boardEMT->InitRandomSize(1.5f, 1.5f);
	_boardEMT->InitRandomSizeEnd(3.5f, 3.5f);
	//_pointEMT->addSizeGraph(0.5f, 2.8f, 2.8f);
	//_pointEMT->addSizeGraph(1.0f, 2.2f, 2.2f);

	//_boardEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_boardEMT->InitRandomPositionY(-0.5f, 0.5f);
	//_boardEMT->InitRandomPositionZ(-0.2f, 0.5f);

	//_boardEMT->InitRandomVelocityX(-3.0f, 3.0f);
	//_boardEMT->InitRandomVelocityY(0.5f, 0.8f);
	//_boardEMT->InitRandomVelocityZ(2.0f, 2.0f);

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

	_boardEMT->InitRandomAlpha(0.3f, 0.3f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.2f, 0.1f);
	//_pointEMT->InitRandomAlphaFade(0.2f, 0.2f);
	//_boardEMT->InitAnimation(4, 4);
	//_boardEMT->InitConstAniReactivateNum(2);
	_boardEMT->InitRandomColorR(0.8f, 0.1f);
	//_boardEMT->InitRandomColorG(0.2f,0.2f);
	//_boardEMT->InitRandomColorB(0.0f,0.0f);
	//_planeEMT->InitRandomColorFadeR(1.0f,1.0f);
	//_planeEMT->InitRandomColorFadeG(0.0f, 0.0f);
	//_planeEMT->InitRandomColorFadeB(1.0f, 1.0f);

	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	//_boardEMT->InitRotateAngleSpeedZ(100.0f,100.0f);

	//D3DXCOLOR color;
	//color.r = color_
	//_boardEMT->InitRotateStartAngleZ(10.0f)
	_boardEMT->InitRotateStartAngleZ(0.0f, 360.0f);

	/*_boardEMT->InitCircleStartAngleZ(0.0f, 360.0f);
	_boardEMT->InitCircleRadiusZ(0.0f, 0.0f);
	_boardEMT->InitCircleRadiusEndZ(5.0f, 5.0f);*/
	//_boardEMT->InitRandomRadiusZ(5.0f, 5.0f);

	//_boardEMT->
	//_boardEMT->InitCircleAngleSpeedZ(100.0f, 120.0f);

	_boardEMT->InitRandomLifeTime(0.3f, 0.3f);

	//_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS, true);
}

void psEffectSet00::EffectSet03(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/smoke02_frame4x4.png", 70, 0.5f, 500);
	//_pointEMT->InitConstSize(2.4f);

	_boardEMT->InitRandomLifeTime(2.5f, 3.2f);

	_boardEMT->InitRandomSize(0.0f, 0.2f);
	_boardEMT->InitRandomSizeEnd(8.0f, 18.2f);

	_boardEMT->SetPositionType(PTC_SPHERE);
	_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	_boardEMT->InitRandomPosSphereRadius(1.0f, 2.0f);
	_boardEMT->InitRandomPosExplosionVel(10.0f, 20.0f);


	//_boardEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_boardEMT->InitRandomPositionY(-0.5f, 0.5f);
	//_boardEMT->InitRandomPositionZ(0.2f, 0.5f);

	//_boardEMT->InitRandomVelocityX(-3.0f, 3.0f);
	//_boardEMT->InitRandomVelocityY(0.5f, 0.8f);
	//_boardEMT->InitRandomVelocityZ(2.0f, 2.0f);


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

	_boardEMT->InitRandomAlpha(0.1f, 0.1f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.2f, 0.2f);
	//_pointEMT->InitRandomAlphaFade(0.2f, 0.2f);
	_boardEMT->InitAnimation(4, 4);
	//_boardEMT->InitConstAniReactivateNum(2);
	//_boardEMT->InitRandomColorR(0.5f,0.5f);
	//_boardEMT->InitRandomColorG(0.2f,0.2f);
	//_boardEMT->InitRandomColorB(0.0f,0.0f);
	//_planeEMT->InitRandomColorFadeR(1.0f,1.0f);
	//_planeEMT->InitRandomColorFadeG(0.0f, 0.0f);
	//_planeEMT->InitRandomColorFadeB(1.0f, 1.0f);

	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	//_boardEMT->InitRotateAngleSpeedZ(100.0f,100.0f);

	//D3DXCOLOR color;
	//color.r = color_
	//_boardEMT->InitRotateStartAngleZ(10.0f)

	/*_boardEMT->InitCircleStartAngleZ(0.0f, 360.0f);
	_boardEMT->InitCircleRadiusZ(0.0f, 0.0f);
	_boardEMT->InitCircleRadiusEndZ(5.0f, 5.0f);*/
	//_boardEMT->InitRandomRadiusZ(5.0f, 5.0f);

	//_boardEMT->
	//_boardEMT->InitCircleAngleSpeedZ(100.0f, 120.0f);

	

	_PS->addEmitter(_boardEMT);


	PSM->addPS(psName, _PS);

}

void psEffectSet00::EffectSet04(string psName)
{
}
