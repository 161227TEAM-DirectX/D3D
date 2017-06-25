#include "stdafx.h"
#include "psPlayerSet00.h"

HRESULT psPlayerSet00::init()
{
	//파티클 이름이 잘 보이게 일부러 이름 넣는 인자값을 준다.
	//매직슈터
	this->MagicShootSet00("마법진");
	this->MagicShootSet01("구체");
	this->MagicShootSet02("폭발");
	this->MagicShootSet03("타겟팅");

	//힐
	this->HealSet00("힐_마법진");
	//this->HealSet01("");

	//this->set00_02("");

	return S_OK;
}

void psPlayerSet00::release()
{
	dxParticleSystemSet::release();
}

void psPlayerSet00::MagicShootSet00(string psName)
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



	//
	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light09.png", 30, 0.2f, 30);
	//_pointEMT->setRealtimeTrackingPosOn();
	//_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_pointEMT->InitRandomPositionY(-0.5f, 0.5f);

	_pointEMT->InitConstAttractCenter(0.0f, 3.0f, 0.0f);

	_pointEMT->SetPositionType(PTC_SPHERE);
	_pointEMT->InitRandomPosSphereRadius(1.5f,2.0f);
	_pointEMT->InitDirSphere(1.0f,0.0f,1.0f);

	_pointEMT->InitRandomColorR(0.0f, 0.0f);
	_pointEMT->InitRandomColorFadeR(1.0f, 1.0f);


	_pointEMT->InitRandomSize(2.0f, 2.0f);
	_pointEMT->InitRandomSizeEnd(1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(1.0f, 1.0f);
	//_pointEMT->InitRandomPositionZ(2.0f, 2.0f);
	//_pointEMT->InitRandomPositionY(-2.0f, 2.0f);
	//_pointEMT->InitRandomPositionZ(-2.0f, 2.0f);
	_pointEMT->InitRandomLifeTime(1.0f,1.0f);
	//_pointEMT->SetActiveLimitTime(1.0f);

	_PS->addEmitter(_pointEMT);




	_boardEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/default.png", 1, 1.0f, 1);

	//_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	//_pointEMT->InitConstAttractCenter(0.0f, 1.0f, 2.0f);
	//_pointEMT->SetPositionType(PTC_SPHERE);
	//_pointEMT->InitRandomPosSphereRadius(3.0f, 3.0f);
	//_pointEMT->InitDirSphere(1.0f, 1.0f, 0.0f);
	//_pointEMT->setRealtimeTrackingPosOn();
	_pointEMT->InitRandomSize(1.2f, 1.2f);
	_pointEMT->addSizeGraph(0.5f, 2.0f,2.0f);
	_pointEMT->addSizeGraph(1.0f, 1.0f, 1.0f);
	//_pointEMT->InitRandomSizeEnd(1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(3.0f, 3.0f);
	//_pointEMT->InitRandomPositionZ(2.0f, 2.0f);
	//_pointEMT->InitRandomPositionY(-2.0f, 2.0f);
	//_pointEMT->InitRandomPositionZ(-2.0f, 2.0f);
	_pointEMT->InitRandomColorR(1.0f, 1.0f);
	_pointEMT->InitRandomColorG(1.0f, 1.0f);
	_pointEMT->InitRandomColorB(1.0f, 1.0f);

	_pointEMT->InitRandomColorFadeR(1.0f, 1.0f);
	//_pointEMT->InitRandomColorG(1.0f, 1.0f);
	//_pointEMT->InitRandomColorB(1.0f, 1.0f);

	_pointEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_pointEMT);


	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::MagicShootSet01(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/explosion.png", 1, 1.0f, 1);
	//_pointEMT->InitConstSize(2.4f);

	_pointEMT->InitRandomSize(1.6f, 1.6f);
	_pointEMT->addSizeGraph(0.5f, 2.2f, 2.2f);
	_pointEMT->addSizeGraph(1.0f, 1.6f, 1.6f);

	/*_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	_pointEMT->InitRandomPositionZ(-1.0f, 1.0f);*/

	//_pointEMT->InitRandomVelocityX(-3.0f, 3.0f);
	_pointEMT->InitRandomVelocityY(0.0f, 0.0f);
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

	_pointEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light02.png", 1, 0.5f, 1);
	//_pointEMT->InitConstSize(3.5f);
	_pointEMT->InitRandomSize(1.5f, 1.5f);
	_pointEMT->addSizeGraph(0.5f, 3.5f, 3.5f);
	_pointEMT->addSizeGraph(1.0f, 1.5f, 1.5f);
	//	_pointEMT->addSizeGraph();
	//_pointEMT->addSizeGraph(2.);

	/*_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	_pointEMT->InitRandomPositionZ(-1.0f, 1.0f);*/

	//_pointEMT->InitRandomVelocityX(-3.0f, 3.0f);
	_pointEMT->InitRandomVelocityY(0.0f, 0.0f);
	//_pointEMT->InitRandomVelocityZ(-3.0f, 3.0f);

	_pointEMT->InitRandomVelocityX(0.0f, 0.0f);
	_pointEMT->InitRandomVelocityY(0.0f, 0.0f);
	_pointEMT->InitRandomVelocityZ(0.0f, 0.0f);

	//_pointEMT->InitRandomAccelerationX(0.0f,0.0f);
	//_pointEMT->InitRandomAccelerationY(200.0f, 200.0f);
	//_pointEMT->InitRandomAccelerationZ(0.0f,0.0f);

	_pointEMT->InitRandomColorR(0.8f, 0.8f);
	_pointEMT->InitRandomColorG(0.0f, 0.0f);
	_pointEMT->InitRandomColorB(0.0f, 0.0f);

	/*_pointEMT->InitRandomColorFadeR(1.0f, 1.0f);
	_pointEMT->InitRandomColorFadeG(1.0f, 1.0f);
	_pointEMT->InitRandomColorFadeB(1.0f, 1.0f);*/

	_pointEMT->InitRandomAlpha(0.8f, 0.8f);
	_pointEMT->addAlphaGraph(0.5, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	//_pointEMT->InitRandomAlphaFade(0.3f, 0.3f);

	_pointEMT->InitRandomLifeTime(0.5f, 0.5f);

	/*_pointEMT->InitRandomLifeTime(1.0f, 1.0f);
	_pointEMT->InitRandomLifeTime(0.5f, 0.5f);*/

	_PS->addEmitter(_pointEMT);

	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::MagicShootSet02(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light06.png", 1, 1.0f, 1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);

	_pointEMT->InitRandomSize(2.5f, 2.5f);
	_pointEMT->InitRandomSizeEnd(7.0f, 7.0f);

	_pointEMT->InitRandomAlpha(0.4f, 0.4f);
	_pointEMT->addAlphaGraph(0.8, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.7f, 0.7f);
	//	_pointEMT->InitRandomAlphaFade(.0f, 10.0f);
	//_pointEMT->addSizeGraph(0.5f, 3.5f, 3.5f);
	//_pointEMT->addSizeGraph(1.0f, 2.5f, 2.5f);


	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/explosion.png", 1, 1.0f, 1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	_pointEMT->InitRandomSize(2.2f, 2.2f);
	_pointEMT->addSizeGraph(0.5f, 4.5f, 4.5f);
	_pointEMT->addSizeGraph(1.0f, 1.5f, 1.5f);
	_pointEMT->InitRandomAlpha(1.0f, 1.0f);
	_pointEMT->addAlphaGraph(0.6, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.3f, 0.3f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light02.png", 1, 1.0f, 1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	_pointEMT->InitRandomSize(2.0f, 2.0f);
	_pointEMT->addSizeGraph(0.7f, 2.5f, 2.5f);
	_pointEMT->addSizeGraph(1.0f, 7.5f, 7.5f);
	_pointEMT->InitRandomAlpha(0.2f, 0.2f);
	_pointEMT->addAlphaGraph(0.7, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_PS->addEmitter(_pointEMT);


	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::MagicShootSet03(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("PaticleResources/Texture/targeting.png", 1, 1.0f, 1);
	_boardEMT->InitRandomSize(5.0f,5.0f);
	_boardEMT->InitRandomSizeEnd(1.0f, 1.0f);
	_boardEMT->SetActiveLimitTime(1.0f);
	_boardEMT->InitRandomAlpha(0.1f, 0.1f);
	_boardEMT->InitRandomAlphaFade(0.8f, 0.8f);
	_boardEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_boardEMT);

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("PaticleResources/Texture/targeting.png", 1, 0.8f, 2);
	_boardEMT->InitRandomSize(1.0f, 1.0f);
	_boardEMT->addSizeGraph(0.5f, 1.2f, 1.2f);
	_boardEMT->addSizeGraph(1.0f, 1.0f, 1.0f);
	_boardEMT->SetStartLimitTime(0.2f);
	_boardEMT->InitRandomAlpha(0.6f, 0.6f);
	_boardEMT->addAlphaGraph(0.5f, 0.4f, 0.4f);
	_boardEMT->addAlphaGraph(1.0f, 0.6f, 0.6f);
	_boardEMT->InitRandomLifeTime(0.8f,0.8f);
	/*_boardEMT->InitRandomColorR(1.0f, 1.0f);
	_boardEMT->InitRandomColorG(1.0f, 1.0f);
	_boardEMT->InitRandomColorB(1.0f, 1.0f);

	_boardEMT->InitRandomColorFadeR(0.5f, 0.5f);
	_boardEMT->InitRandomColorFadeG(0.0f, 0.0f);
	_boardEMT->InitRandomColorFadeB(0.0f, 0.0f);*/


	_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::HealSet00(string psName)
{
	dxParticleSystemSet::init();
	
	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("PaticleResources/Texture/HealMagicCircle_f5x4.png", 1, 1.0f, 1);

	_planeEMT->InitRandomSize(2.5f, 2.5f);
	_planeEMT->addSizeGraph(0.5f,3.0f,3.0f);
	_planeEMT->addSizeGraph(1.0f, 2.5f, 2.5f);

	//_planeEMT->InitRandomSizeEnd(3.0f, 3.0f);
	_planeEMT->InitAnimation(5,4);
	//_planeEMT->InitStartDelayTime(1.0f);
	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	_planeEMT->InitRandomLifeTime(1.0f, 1.0f);


	_planeEMT->SetActiveLimitTime(1.0f);

	_PS->addEmitter(_planeEMT);

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("PaticleResources/Texture/HealMagicHead_5x7.png", 1, 2.0f, 1);

	_boardEMT->InitRandomSize(1.6f, 1.6f);
	_boardEMT->InitAnimation(5, 7);

	_boardEMT->InitRandomPositionY(3.0f,3.0f);

	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);

	_boardEMT->SetActiveLimitTime(2.0f);

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("PaticleResources/Texture/HealParticle_f5x5.png", 20, 0.5f, 360);

	_boardEMT->InitRandomSize(0.1f, 0.2f);
	_boardEMT->InitAnimation(5, 5);
	_boardEMT->InitConstAniReactivateNum(3);

	_boardEMT->SetPositionType(PTC_SPHERE);

	_boardEMT->InitRandomPositionY(0.0f, 1.2f);
	_boardEMT->InitRandomPosSphereRadius(0.3f,1.0f);
	_boardEMT->InitDirSphere(1.0f,0.0f,1.0f);
	_boardEMT->InitRandomVelocityY(1.2f,2.0f);
	
	//_boardEMT->InitRandomPositionX(3.0f, 3.0f);
	//_boardEMT->InitRandomPositionY(3.0f, 3.0f);
	//_boardEMT->InitRandomPositionZ(3.0f, 3.0f);

	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	_boardEMT->InitRandomLifeTime(1.6f, 2.0f);

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("PaticleResources/Texture/HealExplosion_f5x6.png", 1, 1.5f, 1);

	_boardEMT->InitRandomSize(2.5f, 2.5f);
	_boardEMT->addSizeGraph(0.5f, 3.0f, 3.0f);
	_boardEMT->addSizeGraph(1.0f, 2.5f, 2.5f);
	

	_boardEMT->InitRandomPositionY(3.0f,3.0f);
	//_planeEMT->InitRandomSizeEnd(3.0f, 3.0f);
	_boardEMT->InitAnimation(5, 6);
	_boardEMT->SetStartLimitTime(0.4f);
	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	_boardEMT->InitRandomLifeTime(1.5f, 1.5f);

	_boardEMT->SetActiveLimitTime(3.3f);

	_PS->addEmitter(_boardEMT);




	PSM->addPS(psName, _PS);
}

void psPlayerSet00::HealSet01(string psName)
{
}

void psPlayerSet00::HealSet02(string psName)
{
}
