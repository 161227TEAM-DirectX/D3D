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
	this->FireMagicSet00("화염회오리");
	this->FireMagicSet01("화염궤적");

	
	//this->set00_02("");


	//방어마법
	this->MagicShieldSet00("쉴드");

	//라이트닝
	this->LightningSet00("번개");
	this->LightningSet01("번개준비");

	//샛별 떨구기
	this->ShootingStarSet00("샛별준비1");
	this->ShootingStarSet01("샛별준비2");
	this->ShootingStarSet02("샛별마법진");
	this->ShootingStarSet03("샛별");
	this->ShootingStarSet04("샛별_터짐");

	//하늘의 대검
	this->SkySwordSet00("대검");
	this->SkySwordSet01("대검_이펙트");
	this->SkySwordSet02("대검_먼지");

	this->WhirlwindSet00("빙글빙글");


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
	_planeEMT->init("ParticleResources/Texture/cast_magiCircle01_f5x4.png", 1, 1.0f, 1);
	//_pointEMT->InitConstSize(2.4f);

	_planeEMT->InitRandomPositionY(0.01f,0.01f);

	_planeEMT->InitRandomSize(3.8f, 3.8f);
	_planeEMT->InitAnimation(5,4);
	_planeEMT->InitRandomAlpha(0.5f,0.5f);

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

	/*_planeEMT->InitRandomColorR(1.0f,1.0f);
	_planeEMT->InitRandomColorG(1.0f,1.0f);
	_planeEMT->InitRandomColorB(1.0f,1.0f);
	_planeEMT->InitRandomColorFadeR(1.0f,1.0f);*/
	//_planeEMT->InitRandomColorFadeG(0.0f, 0.0f);
	//_planeEMT->InitRandomColorFadeB(1.0f, 1.0f);

	_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	_planeEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_planeEMT);



	//
	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/Light11.png", 30, 0.2f, 30);
	//_pointEMT->setRealtimeTrackingPosOn();
	//_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_pointEMT->InitRandomPositionY(-0.5f, 0.5f);

	_pointEMT->InitConstAttractCenter(0.0f, 3.0f, 0.0f);

	_pointEMT->SetPositionType(PTC_SPHERE);
	_pointEMT->InitRandomPosSphereRadius(1.5f,2.0f);
	_pointEMT->InitDirSphere(1.0f,0.0f,1.0f);

	//_pointEMT->InitRandomColorR(0.0f, 0.0f);
	//_pointEMT->InitRandomColorFadeR(1.0f, 1.0f);


	_pointEMT->InitRandomSize(2.0f, 2.0f);
	_pointEMT->InitRandomSizeEnd(1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(1.0f, 1.0f);
	//_pointEMT->InitRandomPositionZ(2.0f, 2.0f);
	//_pointEMT->InitRandomPositionY(-2.0f, 2.0f);
	//_pointEMT->InitRandomPositionZ(-2.0f, 2.0f);
	_pointEMT->InitRandomLifeTime(0.4f,0.4f);
	//_pointEMT->SetActiveLimitTime(1.0f);

	_PS->addEmitter(_pointEMT);




	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/light_f5x6.png", 1, 1.0f, 1);

	_boardEMT->InitAnimation(5,6);
	_boardEMT->InitAniPlaySection(0, 6);

	
	_boardEMT->InitRandomSize(1.0f, 1.0f);
	_boardEMT->addSizeGraph(0.5f, 3.0f,3.0f);
	_boardEMT->addSizeGraph(1.0f, 1.0f, 1.0f);
	//_pointEMT->InitRandomSizeEnd(1.0f, 1.0f);
	_boardEMT->InitRandomPositionY(3.0f, 3.0f);
	//_pointEMT->InitRandomPositionZ(2.0f, 2.0f);
	//_pointEMT->InitRandomPositionY(-2.0f, 2.0f);
	//_pointEMT->InitRandomPositionZ(-2.0f, 2.0f);
	/*_boardEMT->InitRandomColorR(1.0f, 1.0f);
	_boardEMT->InitRandomColorG(1.0f, 1.0f);
	_boardEMT->InitRandomColorB(1.0f, 1.0f);*/

	//_boardEMT->InitRandomColorFadeR(1.0f, 1.0f);
	//_pointEMT->InitRandomColorG(1.0f, 1.0f);
	//_pointEMT->InitRandomColorB(1.0f, 1.0f);

	_boardEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_boardEMT);


	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::MagicShootSet01(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/explosion.png", 1, 1.0f, 1);
	//_pointEMT->InitConstSize(2.4f);

	_pointEMT->InitRandomSize(1.8f, 1.8f);
	_pointEMT->addSizeGraph(0.5f, 2.6f, 2.6f);
	_pointEMT->addSizeGraph(1.0f, 1.8f, 1.8f);

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

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/magicSpher01_f5x5.png", 1, 0.5f, 1);
	//_pointEMT->InitConstSize(3.5f);
	_boardEMT->InitRandomSize(0.5f, 0.5f);
	_boardEMT->addSizeGraph(0.5f, 1.5f, 1.5f);
	_boardEMT->addSizeGraph(1.0f, 0.5f, 0.5f);

	_boardEMT->InitAnimation(5,5);
	//	_pointEMT->addSizeGraph();
	//_pointEMT->addSizeGraph(2.);

	/*_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	_pointEMT->InitRandomPositionZ(-1.0f, 1.0f);*/

	//_pointEMT->InitRandomVelocityX(-3.0f, 3.0f);
	_boardEMT->InitRandomVelocityY(0.0f, 0.0f);
	//_pointEMT->InitRandomVelocityZ(-3.0f, 3.0f);

	_boardEMT->InitRandomVelocityX(0.0f, 0.0f);
	_boardEMT->InitRandomVelocityY(0.0f, 0.0f);
	_boardEMT->InitRandomVelocityZ(0.0f, 0.0f);

	//_pointEMT->InitRandomAccelerationX(0.0f,0.0f);
	//_pointEMT->InitRandomAccelerationY(200.0f, 200.0f);
	//_pointEMT->InitRandomAccelerationZ(0.0f,0.0f);
	
	/*_pointEMT->InitRandomColorR(OneColorByte(255), OneColorByte(255));
	_pointEMT->InitRandomColorG(OneColorByte(255), OneColorByte(255));
	_pointEMT->InitRandomColorB(OneColorByte(140), OneColorByte(140));*/

	/*_pointEMT->InitRandomColorFadeR(1.0f, 1.0f);
	_pointEMT->InitRandomColorFadeG(1.0f, 1.0f);
	_pointEMT->InitRandomColorFadeB(1.0f, 1.0f);*/

	_boardEMT->InitRandomAlpha(0.8f, 0.8f);
	_boardEMT->addAlphaGraph(0.5, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	//_pointEMT->InitRandomAlphaFade(0.3f, 0.3f);

	_boardEMT->InitRandomLifeTime(0.5f, 0.5f);

	/*_pointEMT->InitRandomLifeTime(1.0f, 1.0f);
	_pointEMT->InitRandomLifeTime(0.5f, 0.5f);*/

	_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::MagicShootSet02(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/Light12.png", 1, 1.0f, 1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);

	_pointEMT->InitRandomSize(2.5f, 2.5f);
	_pointEMT->InitRandomSizeEnd(7.0f, 7.0f);

	_pointEMT->InitRandomAlpha(0.4f, 0.4f);
	_pointEMT->addAlphaGraph(0.8, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.7f, 0.7f);



	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/explosion01.png", 1, 1.0f, 1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	_pointEMT->InitRandomSize(2.2f, 2.2f);
	_pointEMT->addSizeGraph(0.5f, 4.5f, 4.5f);
	_pointEMT->addSizeGraph(1.0f, 1.5f, 1.5f);
	_pointEMT->InitRandomAlpha(0.7f, 0.7f);
	_pointEMT->addAlphaGraph(0.6, 0.7f, 0.7f);
	_pointEMT->addAlphaGraph(1.0, 0.3f, 0.3f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/Light02.png", 1, 1.0f, 1);
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

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/targeting.png", 1, 1.2f, 1);
	_pointEMT->InitRandomSize(5.0f,5.0f);
	_pointEMT->InitRandomSizeEnd(1.2f, 1.2f);
	_pointEMT->SetActiveLimitTime(1.2f);
	_pointEMT->InitRandomAlpha(0.1f, 0.1f);
	_pointEMT->InitRandomAlphaFade(0.7f, 0.7f);
	_pointEMT->InitRandomLifeTime(1.2f, 1.2f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/targeting.png", 1, 0.8f, 2);
	_pointEMT->InitRandomSize(1.2f, 1.2f);
	_pointEMT->addSizeGraph(0.5f, 1.5f, 1.5f);
	_pointEMT->addSizeGraph(1.0f, 1.2f, 1.2f);
	_pointEMT->SetStartLimitTime(1.2f);
	_pointEMT->InitRandomAlpha(0.6f, 0.6f);
	_pointEMT->addAlphaGraph(0.5f, 0.4f, 0.4f);
	_pointEMT->addAlphaGraph(1.0f, 0.6f, 0.6f);
	_pointEMT->InitRandomLifeTime(0.8f,0.8f);
	/*_boardEMT->InitRandomColorR(1.0f, 1.0f);
	_boardEMT->InitRandomColorG(1.0f, 1.0f);
	_boardEMT->InitRandomColorB(1.0f, 1.0f);

	_boardEMT->InitRandomColorFadeR(0.5f, 0.5f);
	_boardEMT->InitRandomColorFadeG(0.0f, 0.0f);
	_boardEMT->InitRandomColorFadeB(0.0f, 0.0f);*/


	_PS->addEmitter(_pointEMT);

	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::HealSet00(string psName)
{
	dxParticleSystemSet::init();
	
	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/HealMagicCircle_f5x4.png", 1, 1.0f, 1);

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
	_boardEMT->init("ParticleResources/Texture/HealMagicHead_5x7.png", 1, 2.0f, 1);

	_boardEMT->InitRandomSize(1.6f, 1.6f);
	_boardEMT->InitAnimation(5, 7);

	_boardEMT->InitRandomPositionY(3.0f,3.0f);

	//_planeEMT->InitRotateAngleSpeedY(6.0f,6.0f);

	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);

	_boardEMT->SetActiveLimitTime(2.0f);

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/HealParticle_f5x5.png", 20, 0.5f, 360);

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
	_boardEMT->init("ParticleResources/Texture/HealExplosion_f5x6.png", 1, 1.5f, 1);

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


//파이어 매직
void psPlayerSet00::FireMagicSet00(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fire04_frame5x4.png", 50, 0.16f, 800);
	//_boardEMT->SetStartLimitTime(0.05f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	_boardEMT->InitRandomSize(1.0f, 2.2f);
	_boardEMT->InitRandomSizeEnd(3.2f, 4.2f);

	_boardEMT->InitRandomLifeTime(2.4f, 3.2f);

	//_boardEMT->InitRandomPositionY(8.5f, 8.5f);

	_boardEMT->InitRandomPositionY(0.0f, 3.0f);
	_boardEMT->InitRandomVelocityY(4.0f,8.0f);
	_boardEMT->InitRandomAccelerationY(16.0f, 28.0f);

	_boardEMT->InitCircleStartAngleY(0.0f, 360.0f);
	_boardEMT->InitCircleRadiusY(1.0f,1.0f);
	_boardEMT->InitCircleRadiusEndY(6.2f, 8.0f);
	_boardEMT->InitCircleAngleSpeedY(180.0f,280.0f);

	_boardEMT->InitRandomPosRotAngleSpeedZ(10.0f,20.0f);

	_boardEMT->InitAnimation(5, 4);
	_boardEMT->InitConstAniReactivateNum(8);

	_boardEMT->InitRandomAlpha(0.8f,0.8f);
	_boardEMT->addAlphaGraph(0.8,1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.1f, 0.1f);


	_PS->addEmitter(_boardEMT);


	PSM->addPS(psName, _PS, true);

}

void psPlayerSet00::FireMagicSet01(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fire06_frame4x4.png", 3, 0.02f, 300);
	//_boardEMT->SetStartLimitTime(0.05f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	_boardEMT->InitRandomSize(0.6f, 1.0f);
	_boardEMT->InitRandomSizeEnd(2.4f, 3.2f);

	_boardEMT->InitRandomLifeTime(1.4f, 2.0f);

	_boardEMT->InitRandomPositionZ(-1.0f, 1.0f);

	//_boardEMT->InitRandomVelocityZ(-0.5f, -0.5f);

	/*_boardEMT->InitCircleStartAngleY(0.0f, 360.0f);
	_boardEMT->InitCircleRadiusY(0.2f, 0.2f);
	_boardEMT->InitCircleRadiusEndY(4.2f, 5.0f);
	_boardEMT->InitCircleAngleSpeedY(120.0f, 220.0f);*/

	_boardEMT->InitAnimation(4, 4);
	_boardEMT->InitConstAniReactivateNum(3);

	_boardEMT->InitRandomAlpha(0.8f, 0.8f);
	_boardEMT->addAlphaGraph(0.8, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.1f, 0.1f);


	_PS->addEmitter(_boardEMT);


	PSM->addPS(psName, _PS);
}


void psPlayerSet00::MagicShieldSet00(string psName)
{
	dxParticleSystemSet::init();


	

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/sheildEffect_f30x1.png", 1, 1.0f, 1);
	//_boardEMT->SetStartLimitTime(0.05f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	_boardEMT->InitRandomSize(1.4f, 1.4f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);

	_boardEMT->InitRandomPositionY(2.4f, 2.4f);

	//_boardEMT->InitRandomPositionX(1.0f, 1.0f);

	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);


	_boardEMT->InitAnimation(30, 1);
	_boardEMT->InitConstAniReactivateNum(3);

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/sheild_f4x4.png", 1, 2.0f, 1);
	//_boardEMT->SetStartLimitTime(0.05f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	_boardEMT->InitRandomSize(2.0f, 2.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);

	_boardEMT->InitRandomPositionY(1.3f, 1.3f);

	_boardEMT->InitRandomPositionX(1.0f, 1.0f);

	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);

	_boardEMT->InitAnimation(4, 4);
	
	_PS->addEmitter(_boardEMT);



	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/sheild_f4x4.png", 1, 2.0f, 1);
	//_boardEMT->SetStartLimitTime(0.05f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	//_boardEMT->InitRandomSize(1.0f, 1.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);

	_boardEMT->InitRandomSize(2.0f, 2.0f);

	_boardEMT->InitRandomPositionY(1.2f, 1.2f);

	_boardEMT->InitRandomPositionX(-1.0f, -1.0f);

	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);

	_boardEMT->InitAnimation(4, 4);

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/sheild_f4x4.png", 1, 2.0f, 1);
	//_boardEMT->SetStartLimitTime(0.05f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	//_boardEMT->InitRandomSize(1.0f, 1.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);

	//_boardEMT->InitRandomPositionY(8.5f, 8.5f);

	_boardEMT->InitRandomSize(3.0f, 3.0f);

	_boardEMT->InitRandomPositionY(1.2f, 1.2f);

	_boardEMT->InitRandomPositionZ(1.0f, 1.0f);

	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);

	_boardEMT->InitAnimation(4, 4);

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/sheild_f4x4.png", 1, 2.0f, 1);
	//_boardEMT->SetStartLimitTime(0.05f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	//_boardEMT->InitRandomSize(1.0f, 1.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);

	//_boardEMT->InitRandomPositionY(8.5f, 8.5f);

	_boardEMT->InitRandomSize(2.0f, 2.0f);

	_boardEMT->InitRandomPositionY(1.2f, 1.2f);

	_boardEMT->InitRandomPositionZ(-1.0f, -1.0f);

	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);

	_boardEMT->InitAnimation(4, 4);

	_PS->addEmitter(_boardEMT);


	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::LightningSet00(string psName)
{
	dxParticleSystemSet::init();

	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/magicCircleAni_f25x2.png", 1, 2.0f, 1);
	_planeEMT->SetActiveLimitTime(2.0f);

	_planeEMT->InitAnimation(25, 2);
	_planeEMT->InitRandomPositionY(5.0f,5.0f);

	//_planeEMT->InitRandomAlpha(0.8f, 0.8f);
	_planeEMT->InitRandomSize(5.0f, 5.0f);
	_planeEMT->InitRandomLifeTime(2.0f,2.0f);

	_PS->addEmitter(_planeEMT);


	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/magicCircleAni_f25x2.png", 1, 1.0f, 1);
	_planeEMT->SetStartLimitTime(2.0f);

	_planeEMT->InitAnimation(25, 2);
	_planeEMT->InitAniPlaySection(15,35);
	_planeEMT->InitRandomPositionY(5.0f, 5.0f);

	//_planeEMT->InitRandomAlpha(0.8f, 0.8f);
	_planeEMT->InitRandomSize(5.0f, 5.0f);
	_planeEMT->addSizeGraph(0.5f, 5.5f, 5.5f);
	_planeEMT->addSizeGraph(1.0f, 5.0f, 5.0f);


	_planeEMT->InitRandomLifeTime(1.0f, 1.0f);

	_PS->addEmitter(_planeEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/groundLightnimg_f22x4.png", 5, 0.8f, 40);
	_boardEMT->SetStartLimitTime(2.0f);
	//_boardEMT->SetActiveLimitTime(2.0f);

	_boardEMT->InitRandomAlpha(0.7f, 0.9f);

	_boardEMT->InitRandomSize(1.2f, 2.4f);

	_boardEMT->SetPositionType();

	_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	_boardEMT->InitRandomPosSphereRadius(0.0f, 2.0f);

	_boardEMT->SettingBillBoardY();

	//_boardEMT->Rot
	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);

	_boardEMT->InitRandomPositionY(0.1f, 0.8f);

	//_boardEMT->InitRandomPositionY(8.5f, 8.5f);

	_boardEMT->InitRotateStartAngleZ(0.0f, 360.0f);

	_boardEMT->InitRandomLifeTime(1.0f, 1.6f);

	_boardEMT->InitAnimation(22, 4);

	//_boardEMT->InitCenterPointHV(0.5f, 0.9f);


	_PS->addEmitter(_boardEMT);

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/Lightning05_f54x1.png", 2, 0.8f, 200);
	_boardEMT->SetStartLimitTime(2.0f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	_boardEMT->InitRandomAlpha(0.8f, 1.0f);

	_boardEMT->InitRandomSize(1.0f, 2.2f);

	_boardEMT->SetPositionType();

	_boardEMT->InitDirSphere(1.0f,0.0f, 1.0f);
	_boardEMT->InitRandomPosSphereRadius(0.0f, 1.5f);



	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);

	_boardEMT->InitRandomPositionY(5.0f, 5.0f);

	//_boardEMT->InitRotateStartAngleZ(-60.0f, 60.0f);

	_boardEMT->InitRandomLifeTime(1.5f, 2.2f);

	_boardEMT->InitAnimation(54, 1);

	_boardEMT->InitCenterPointHV(0.5f, 0.0f);

	_boardEMT->SettingBillBoardY();

	//_boardEMT->uvReverseImgU();

	_boardEMT->InitConstHV(0.5f, 3.0f);

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/Lightning05_f54x1.png", 2, 0.8f, 200);
	_boardEMT->SetStartLimitTime(2.0f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	_boardEMT->InitRandomAlpha(0.8f, 1.0f);

	_boardEMT->InitRandomSize(1.0f, 2.2f);

	_boardEMT->SetPositionType();

	_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	_boardEMT->InitRandomPosSphereRadius(0.0f, 1.5f);

	_boardEMT->InitRandomPositionY(5.0f, 5.0f);

	_boardEMT->InitRandomLifeTime(1.5f, 2.2f);

	_boardEMT->InitAnimation(54, 1);

	_boardEMT->InitCenterPointHV(0.5f, 0.0f);

	_boardEMT->uvReverseImgU();

	_boardEMT->SettingBillBoardY();

	_boardEMT->InitConstHV(0.3f, 3.0f);

	_PS->addEmitter(_boardEMT);

	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/LightningCircle_f43x2.png", 1, 2.0f, 1);
	_planeEMT->SetStartLimitTime(2.0f);

	_planeEMT->InitRandomAlpha(0.8f,0.8f);
	_planeEMT->InitRandomSize(4.0f, 4.0f);

	//_planeEMT->SetPositionType();

	_planeEMT->InitRandomPositionY(0.01f,0.01f);

	//_planeEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	//_planeEMT->InitRandomPosSphereRadius(0.0f, 2.0f);

	_planeEMT->InitRandomLifeTime(2.0f, 2.0f);

	_planeEMT->InitAnimation(43, 2);

	//_planeEMT->InitCenterPointHV(0.5f, 1.0f);

	//_planeEMT->uvReverseImgU();

	//_planeEMT->InitConstHV(1.0f, 3.0f);

	_PS->addEmitter(_planeEMT);

	
	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/circleEffect_f21x1.png", 1, 0.6f, 1);
	_planeEMT->SetStartLimitTime(2.0f);

	_planeEMT->InitRandomAlpha(0.8f, 0.8f);
	_planeEMT->InitRandomSize(4.0f, 4.0f);
	_planeEMT->addSizeGraph(0.5f, 3.0f, 3.0f);
	_planeEMT->addSizeGraph(1.0f, 4.0f, 4.0f);
	//_planeEMT->SetPositionType();

	_planeEMT->InitRandomPositionY(0.01f, 0.01f);

	//_planeEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	//_planeEMT->InitRandomPosSphereRadius(0.0f, 2.0f);

	_planeEMT->InitRandomLifeTime(0.6f, 0.6f);

	_planeEMT->InitAnimation(21, 1);

	//_planeEMT->InitCenterPointHV(0.5f, 1.0f);

	//_planeEMT->uvReverseImgU();

	//_planeEMT->InitConstHV(1.0f, 3.0f);

	_PS->addEmitter(_planeEMT);


	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::LightningSet01(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/LightningSphere_f38x1.png", 1, 0.3f, 20);
	//_boardEMT->SetActiveLimitTime(1.0f);

	_boardEMT->InitRandomAlpha(0.8f, 1.0f);

	_boardEMT->InitRandomSize(0.8f, 0.8f);

	//_boardEMT->SetPositionType();

	_boardEMT->InitRandomPositionY(2.5f,2.5f);

	//_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);

	//_boardEMT->InitRandomVelocityZ(10.0f,10.0f);

	//_boardEMT->InitRandomPositionZ(1.5f, 1.5f);

	//_boardEMT->InitRandomPosRotAngleSpeedY(360.0f, 360.0f);

	//_boardEMT->InitRandomPosSphereRadius(0.8f, 1.5f);

	_boardEMT->InitRandomLifeTime(3.0f, 3.0f);

	_boardEMT->InitAnimation(38, 1);

	_PS->addEmitter(_boardEMT);





	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/rune01_f22x1.png", 1, 2.0f, 1);
	//_planeEMT->SetStartLimitTime(2.0f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	_boardEMT->InitRandomAlpha(0.8f, 1.0f);

	_boardEMT->InitRandomSize(0.5f, 0.5f);

	_boardEMT->InitRandomPositionY(3.2f, 3.2f);
	//_boardEMT->InitRandomPositionZ(2.5f, 2.5f);


	//_boardEMT->InitRotateAngleSpeedY(90.0f,90.0f);

	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);



	//_planeEMT->InitCenterPointHV(0.5f,1.0f);

	_boardEMT->InitAnimation(22, 1);

	_PS->addEmitter(_boardEMT);


	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/magicCircle_part02.tga", 1, 0.5f, 10);
	//_planeEMT->SetStartLimitTime(2.0f);
	//_boardEMT->SetActiveLimitTime(1.0f);

	_planeEMT->InitRandomAlpha(0.8f, 1.0f);

	_planeEMT->InitRandomSize(2.0f, 2.0f);
	_planeEMT->InitRandomSizeEnd(4.0f, 4.0f);

	_planeEMT->InitRandomPositionY(2.5f, 2.5f);

	//_planeEMT->InitRotateAngleSpeedX(20.0f, 20.0f);
	_planeEMT->InitRotateAngleSpeedY(90.0f, 90.0f);

	_planeEMT->InitRandomVelocityY(-1.5f, -1.5f);
	//_planeEMT->InitRandomAccelerationY(-280.0f, -280.0f);

	_planeEMT->InitRandomLifeTime(1.5f, 1.5f);

	//_planeEMT->InitCenterPointHV(0.5f,1.0f);

	//_planeEMT->InitAnimation(5, 10);

	_PS->addEmitter(_planeEMT);


	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::ShootingStarSet00(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/Light01_5x5.png", 1, 0.6f, 1);
	_boardEMT->InitRandomLifeTime(0.6f, 0.6f);
	
	_boardEMT->InitRandomSize(2.0f, 2.0f);
	_boardEMT->addSizeGraph(0.5f,3.5f,3.5f);
	_boardEMT->addSizeGraph(1.0f, 2.0f, 2.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);
	
	_boardEMT->InitAnimation(5,5);
	_boardEMT->InitAniPlaySection(5,9);

	_boardEMT->InitRandomAlpha(0.8f, 0.8f);
	_boardEMT->addAlphaGraph(0.5, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0, 0.8f, 0.8f);
	


	_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS, true);

}

void psPlayerSet00::ShootingStarSet01(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/Light01_5x5.png", 1, 1.2f, 2);
	_boardEMT->InitRandomLifeTime(1.2f, 1.2f);

	_boardEMT->InitRandomSize(2.0f, 2.0f);
	_boardEMT->addSizeGraph(0.5f, 7.0f, 7.0f);
	_boardEMT->addSizeGraph(1.0f, 2.5f, 2.5f);
	//_boardEMT->InitRandomSizeEnd(4.0f, 4.0f);

	_boardEMT->InitAnimation(5, 5);
	//_boardEMT->InitAniPlaySection(0, 0);

	_boardEMT->InitRandomAlpha(0.8f, 0.8f);
	_boardEMT->addAlphaGraph(0.5, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_boardEMT->SetActiveLimitTime(1.2f);

	_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::ShootingStarSet02(string psName)
{
	dxParticleSystemSet::init();

	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/magicCircle.png", 1, 1.2f, 2);
	_planeEMT->InitRandomLifeTime(1.2f, 1.2f);

	_planeEMT->InitRandomSize(0.5f, 0.5f);
	//_planeEMT->addSizeGraph(0.5f, 4.0f, 4.0f);
	//_planeEMT->addSizeGraph(1.0f, 2.5f, 2.5f);
	_planeEMT->InitRandomSizeEnd(12.0f, 12.0f);


	_planeEMT->InitRotateStartAngleX(90.0f, 90.0f);
	//_planeEMT->InitAnimation(5, 5);
	//_planeEMT->InitAniPlaySection(0, 0);

	_planeEMT->InitRandomAlpha(0.8f, 0.8f);
	_planeEMT->addAlphaGraph(0.5, 1.0f, 1.0f);
	_planeEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_planeEMT->SetStartLimitTime(0.8f);
	_planeEMT->SetActiveLimitTime(1.2f);

	_PS->addEmitter(_planeEMT);

	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/magicCircle.png", 1, 1.2f, 2);
	_planeEMT->InitRandomLifeTime(1.2f, 1.2f);

	_planeEMT->InitRandomSize(0.5f, 0.5f);
	//_planeEMT->addSizeGraph(0.5f, 4.0f, 4.0f);
	//_planeEMT->addSizeGraph(1.0f, 2.5f, 2.5f);
	_planeEMT->InitRandomSizeEnd(6.0f, 6.0f);

	_planeEMT->InitRandomPositionZ(-2.0f, -2.0f);

	_planeEMT->InitRotateStartAngleX(90.0f, 90.0f);
	//_planeEMT->InitAnimation(5, 5);
	//_planeEMT->InitAniPlaySection(0, 0);

	_planeEMT->InitRandomAlpha(0.8f, 0.8f);
	_planeEMT->addAlphaGraph(0.5, 1.0f, 1.0f);
	_planeEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_planeEMT->SetStartLimitTime(0.8f);
	_planeEMT->SetActiveLimitTime(1.2f);

	_PS->addEmitter(_planeEMT);



	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/magicCircle.png", 1, 0.6f, 2);
	_planeEMT->InitRandomLifeTime(0.6f, 0.6f);

	_planeEMT->InitRandomSize(12.0f, 12.0f);
	//_planeEMT->addSizeGraph(0.5f, 8.0f, 8.0f);
	//_planeEMT->addSizeGraph(1.0f, 12.0f, 12.0f);
	
	_planeEMT->InitRotateStartAngleX(90.0f, 90.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);

	//_planeEMT->InitAnimation(5, 5);
	//_planeEMT->InitAniPlaySection(0, 0);



	_planeEMT->InitRandomAlpha(0.8f, 0.8f);
	_planeEMT->addAlphaGraph(0.5, 1.0f, 1.0f);
	_planeEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_planeEMT->SetStartLimitTime(2.0f);
	//_planeEMT->SetActiveLimitTime(1.2f);

	_PS->addEmitter(_planeEMT);


	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/magicCircle.png", 1, 0.6f, 2);
	_planeEMT->InitRandomLifeTime(0.6f, 0.6f);

	_planeEMT->InitRandomSize(6.0f, 6.0f);
	//_planeEMT->addSizeGraph(0.5f, 4.0f, 4.0f);
	//_planeEMT->addSizeGraph(1.0f, 6.0f, 6.0f);

	_planeEMT->InitRotateStartAngleX(90.0f, 90.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);

	//_planeEMT->InitAnimation(5, 5);
	//_planeEMT->InitAniPlaySection(0, 0);
	_planeEMT->InitRandomPositionZ(-2.0f, -2.0f);


	_planeEMT->InitRandomAlpha(0.8f, 0.8f);
	_planeEMT->addAlphaGraph(0.5, 1.0f, 1.0f);
	_planeEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_planeEMT->SetStartLimitTime(2.0f);
	//_planeEMT->SetActiveLimitTime(1.2f);

	_PS->addEmitter(_planeEMT);



	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::ShootingStarSet03(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/Light.png", 1, 0.1f, 200);
	//_pointEMT->InitConstSize(1.0f);

	//_pointEMT->InitRandomPositionX(-1.0f, -1.0f);
	//_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	//_pointEMT->InitRandomPositionZ(-1.0f, 1.0f);

	//_pointEMT->InitRandomVelocityX(-1.5f, -1.5f);
	_pointEMT->InitRandomVelocityZ(-1.5f, -1.5f);
	_pointEMT->InitRandomVelocityX(-0.1f, 0.1f);
	_pointEMT->InitRandomVelocityY(-0.1f, 0.1f);
	//_pointEMT->InitRandomVelocityZ(-3.0f, 3.0f);

	//_pointEMT->InitRandomVelocityX(0.0f, 0.0f);
	//_pointEMT->InitRandomVelocityY(1.0f, 2.0f);
	//_pointEMT->InitRandomVelocityZ(0.0f, 0.0f);

	_pointEMT->InitRandomAccelerationZ(-1.0f, -1.0f);
	//_pointEMT->InitRandomAccelerationY(50.0f, 80.0f);
	//_pointEMT->InitRandomAccelerationZ(0.0f,0.0f);


	_pointEMT->InitRandomAlpha(1.0f, 1.0f);
	_pointEMT->InitRandomAlphaFade(0.0f, 0.0f);

	_pointEMT->InitRandomLifeTime(3.0f, 3.0f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/Light05.png", 1, 0.1f, 200);
	_pointEMT->InitConstSize(1.2f);
	/*_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	_pointEMT->InitRandomPositionZ(-1.0f, 1.0f);*/

	//_pointEMT->InitRandomVelocityY(-0.2f, 0.2f);
	//_pointEMT->InitRandomVelocityY(-1.0f, -1.0f);

	_pointEMT->InitRandomVelocityZ(-1.0f, -1.0f);
	_pointEMT->InitRandomVelocityX(-0.1f, 0.1f);
	_pointEMT->InitRandomVelocityY(-0.1f, 0.1f);
	//_pointEMT->InitRandomVelocityZ(-3.0f, 3.0f);

	//_pointEMT->InitRandomVelocityX(0.0f, 0.0f);
	//_pointEMT->InitRandomVelocityY(1.0f, 2.0f);
	//_pointEMT->InitRandomVelocityZ(0.0f, 0.0f);

	_pointEMT->InitRandomAccelerationZ(-2.0f, -2.0f);

	_pointEMT->InitRandomAlpha(1.0f, 1.0f);
	_pointEMT->InitRandomAlphaFade(0.0f, 0.0f);

	_pointEMT->InitRandomLifeTime(1.5f, 1.5f);

	_PS->addEmitter(_pointEMT);


	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/explosion.png", 1, 1.0f, 1);
	//_pointEMT->InitConstSize(2.4f);

	_pointEMT->InitRandomSize(3.0f, 3.0f);
	_pointEMT->addSizeGraph(0.5f, 4.2f, 4.2f);
	_pointEMT->addSizeGraph(1.0f, 3.0f, 3.0f);

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
	_pointEMT->init("ParticleResources/Texture/Light02.png", 1, 0.5f, 1);
	//_pointEMT->InitConstSize(3.5f);
	_pointEMT->InitRandomSize(3.5f, 3.5f);
	_pointEMT->addSizeGraph(0.5f, 5.5f, 5.5f);
	_pointEMT->addSizeGraph(1.0f, 3.5f, 3.5f);
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

	/*_pointEMT->InitRandomColorR(0.0f, 0.0f);
	_pointEMT->InitRandomColorG(0.6f, 0.6f);
	_pointEMT->InitRandomColorB(0.6f, 0.6f);*/

	/*_pointEMT->InitRandomColorFadeR(0.1f, 1.0f);
	_pointEMT->InitRandomColorFadeG(0.1f, 1.0f);
	_pointEMT->InitRandomColorFadeB(0.0f, 0.0f);*/

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

void psPlayerSet00::ShootingStarSet04(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/Light08.png", 1, 1.0f, 2);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);

	_pointEMT->InitRandomSize(3.5f, 3.5f);
	_pointEMT->InitRandomSizeEnd(12.0f, 12.0f);

	_pointEMT->InitRandomAlpha(0.6f, 0.6f);
	_pointEMT->addAlphaGraph(0.8, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/explosion.png", 1, 1.0f, 1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	_pointEMT->InitRandomSize(2.2f, 2.2f);
	_pointEMT->addSizeGraph(0.5f, 5.5f, 5.5f);
	_pointEMT->addSizeGraph(1.0f, 1.5f, 1.5f);
	_pointEMT->InitRandomAlpha(1.0f, 1.0f);
	_pointEMT->addAlphaGraph(0.6, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.3f, 0.3f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("ParticleResources/Texture/Light02.png", 1, 1.0f, 1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	_pointEMT->InitRandomSize(3.0f, 3.0f);
	_pointEMT->addSizeGraph(0.7f, 4.5f, 4.5f);
	_pointEMT->addSizeGraph(1.0f, 9.5f, 9.5f);
	_pointEMT->InitRandomAlpha(0.2f, 0.2f);

	_pointEMT->addAlphaGraph(0.7, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_PS->addEmitter(_pointEMT);
	
	
	PSM->addPS(psName, _PS, true);
}


//하늘의 대검
void psPlayerSet00::SkySwordSet00(string psName)
{
	dxParticleSystemSet::init();

	

	_meshEMT = NULL;
	_meshEMT = new dxMeshEmitter;
	_meshEMT->init("ParticleResources/Mesh/skySword.x",1, 7.2f,1);

	_meshEMT->SetActiveLimitTime(7.2f);
	_meshEMT->InitRandomSize(3.0f, 3.0f);
	//_meshEMT->InitRandomSize(0.5f,0.5f);
	//_meshEMT->InitRandomSize(0.8f,0.8f);
	//_meshEMT->InitRandomLifeTime(4.2f, 4.2f);
	//_meshEMT->InitRandomPositionY(100.0f,100.0f);
	//_meshEMT->InitRandomVelocityY(0.0f,0.0f);
	//_meshEMT->addVelocityGraphY(0.5f, -40.0f, -40.0f);
	//_meshEMT->addVelocityGraphY(1.0f, 0.0f, 0.0f);

	//_meshEMT->InitRandomAccelerationY(0.0f,0.0f);
	//_meshEMT->addAccelGraphY(0.5f,-200.0f, -200.0f);
	////_meshEMT->addAccelGraphY(0.85f, -240.0f, -240.0f);
	//_meshEMT->addAccelGraphY(1.0f, 0.0f, 0.0f);

	//_meshEMT->addVelocityGraphY(0.3f,-10.0f, -10.0f);
	//_meshEMT->addVelocityGraphY(0.8f, -20.0f, -20.0f);
	//_meshEMT->addVelocityGraphY(1.0f, 0.0f, 0.0f);

	_PS->addEmitter(_meshEMT);

	//_pointEMT = NULL;
	//_pointEMT = new dxPointEmitter;
	//_pointEMT->init("ParticleResources/Texture/default.png", 20, 0.8f, 300.0f);
	//_pointEMT->InitRandomLifeTime(4.0f, 4.0f);
	//
	//_pointEMT->InitRandomPositionY(-10.0f,-10.0f);

	////_pointEMT->InitRandomColorR(OneColorByte(255), OneColorByte(255));
	////_pointEMT->InitRandomColorFadeR(OneColorByte(240), OneColorByte(240));
	//////_pointEMT->InitRandomColorFadeG(OneColorByte(240), OneColorByte(240));

	//////_pointEMT->SetPositionType(PTC_SPHERE);
	////_pointEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	////_pointEMT->InitRandomPosSphereRadius(0.0f, 2.0f);
	////_pointEMT->InitRandomPosExplosionVel(5.0f, 10.0f);



	//_PS->addEmitter(_pointEMT);

	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::SkySwordSet01(string psName)
{
	dxParticleSystemSet::init();

	//_pointEMT = NULL;
	//_pointEMT = new dxPointEmitter;
	//_pointEMT->init("ParticleResources/Texture/default.png", 70, 0.2f, 700.0f);
	//_pointEMT->InitRandomLifeTime(2.0f, 3.0f);


	//_pointEMT->InitRandomColorR(OneColorByte(250), OneColorByte(250));
	//_pointEMT->InitRandomColorG(OneColorByte(50), OneColorByte(50));
	//_pointEMT->InitRandomColorFadeR(OneColorByte(230), OneColorByte(230));
	//_pointEMT->InitRandomColorFadeG(OneColorByte(240), OneColorByte(240));

	//_pointEMT->SetPositionType(PTC_SPHERE);
	//_pointEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	//_pointEMT->InitRandomPosSphereRadius(0.0f, 2.0f);
	//_pointEMT->InitRandomPosExplosionVel(2.0f, 4.0f);
	//_pointEMT->InitRandomPosRotAngleSpeedY(100.0f, 200.0f);

	//_pointEMT->InitRandomSize(0.6f,0.6f);
	//_pointEMT->InitRandomSizeEnd(0.3f,0.3f);

	////_pointEMT->InitRandomSize(0.5f, 0.5f);
	////_pointEMT->InitRandomSize(0.8f, 0.8f);
	////_pointEMT->InitRandomLifeTime(4.2f, 4.2f);
	////_pointEMT->InitRandomPositionY(100.0f, 100.0f);
	//_pointEMT->InitRandomVelocityY(4.0f, 8.0f);
	////_pointEMT->addVelocityGraphY(0.8f, -30.0f, -30.0f);
	////_pointEMT->addVelocityGraphY(1.0f, 0.0f, 0.0f);

	//_pointEMT->InitRandomAccelerationY(10.0f, 20.0f);
	////_pointEMT->addAccelGraphY(0.75f, -116.0f, -116.0f);
	//////_meshEMT->addAccelGraphY(0.85f, -240.0f, -240.0f);
	////_pointEMT->addAccelGraphY(1.0f, 0.0f, 0.0f);

	////_meshEMT->addVelocityGraphY(0.3f,-10.0f, -10.0f);
	////_meshEMT->addVelocityGraphY(0.8f, -20.0f, -20.0f);
	////_meshEMT->addVelocityGraphY(1.0f, 0.0f, 0.0f);

	//_PS->addEmitter(_pointEMT);

	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/shoutingCircle01.png", 1, 0.2f, 50);

	_planeEMT->InitRandomSize(10.0f, 10.0f);
	_planeEMT->InitRandomSizeEnd(50.0f, 50.0f);


	//시작시간 조절!!!!!!!!!!!
	_planeEMT->SetStartLimitTime(1.0f);

	_planeEMT->SetPositionType();
	//_planeEMT->InitDirSphere(1.0f,1.0f,0.0f);
	//_planeEMT->InitRandomPosSphereRadius(1.0f,1.0f);
	//_planeEMT->InitRandomPosExplosionVel(5.0f,5.0f);

	//_planeEMT->InitRotateStartAngleX(0.0f, 360.0f);
	//_planeEMT->InitRotateStartAngleY(0.0f, 360.0f);
	//_planeEMT->InitRotateStartAngleZ(0.0f, 360.0f);

	//_planeEMT->InitRandomPositionY(100.0f, 100.0f);

	_planeEMT->InitRandomLifeTime(1.2f, 1.2f);

	_planeEMT->InitRandomAlpha(0.2f, 0.2f);
	_planeEMT->addAlphaGraph(0.8f, 0.4f, 0.4f);
	_planeEMT->addAlphaGraph(1.0f, 0.0f, 0.0f);


	_PS->addEmitter(_planeEMT);



	PSM->addPS(psName, _PS);


	

}

void psPlayerSet00::SkySwordSet02(string psName)
{
	dxParticleSystemSet::init();


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/smoke02_frame4x4.png", 70, 0.5f, 300);

	//_boardEMT->SetStartLimitTime(2.5f);

	_boardEMT->InitRandomLifeTime(2.5f, 3.2f);

	_boardEMT->InitRandomSize(0.0f, 0.2f);
	_boardEMT->InitRandomSizeEnd(8.0f, 18.2f);

	_boardEMT->SetPositionType(PTC_SPHERE);
	_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	_boardEMT->InitRandomPosSphereRadius(1.0f, 2.0f);
	_boardEMT->InitRandomPosExplosionVel(5.0f, 10.0f);
	

	_boardEMT->InitRandomAlpha(0.1f, 0.1f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.2f, 0.2f);
	//_pointEMT->InitRandomAlphaFade(0.2f, 0.2f);
	_boardEMT->InitAnimation(4, 4);

	_PS->addEmitter(_boardEMT);

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fire05_frame4x4.png", 12, 0.05f, 720);

	//_boardEMT->InitRandomLifeTime(1.0f, 1.0f);
	_boardEMT->SetStartLimitTime(0.8f);

	_boardEMT->InitAnimation(4, 4);
	_boardEMT->InitConstAniReactivateNum(3);

	_boardEMT->setInitActiveLimitTime(2.0f);

	_boardEMT->InitRandomLifeTime(0.4f, 0.6f);

	_boardEMT->InitCenterPointHV(0.5f, 1.0f);

	_boardEMT->InitRandomPositionX(-1.0, 1.0f);
	_boardEMT->InitRandomPositionZ(1.0, 5.0f);

	_boardEMT->InitRandomSize(0.3f, 0.5f);
	_boardEMT->InitRandomSizeEnd(8.0f, 14.2f);

	//_boardEMT->SetPositionType(PTC_SPHERE);
	//_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	//_boardEMT->InitRandomPosSphereRadius(1.0f, 2.0f);

	//_boardEMT->InitCircleRadiusY(3.0f, 5.0f);
	//_boardEMT->InitCircleStartAngleY(40.0f, 140.0f);
	//_boardEMT->InitRandomPosExplosionVel(5.0f, 15.0f);

	//_boardEMT->InitRandomAlpha(0.1f, 0.1f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.2f, 0.2f);


	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/smoke02_frame4x4.png", 70, 0.5f, 300);

	_boardEMT->SetStartLimitTime(0.2f);

	_boardEMT->InitRandomLifeTime(2.5f, 3.2f);

	_boardEMT->InitRandomPositionY(-3.0f, -4.0f);

	_boardEMT->InitRandomSize(0.0f, 0.2f);
	_boardEMT->InitRandomSizeEnd(8.0f, 12.0f);

	//_boardEMT->SetPositionType(PTC_SPHERE);
	//_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	_boardEMT->InitCircleStartAngleY(0.0f, 360.f);
	_boardEMT->InitCircleAngleSpeedY(100.0f, 20.f);
	_boardEMT->InitCircleRadiusY(0.0f, 5.0f);
	_boardEMT->InitCircleRadiusEndY(10.0f, 12.0f);

	_boardEMT->InitRandomVelocityY(4.0f, 10.0f);
	_boardEMT->InitRandomAccelerationY(5.0f,12.0f);

	/*_boardEMT->InitRandomPosSphereRadius(1.0f, 2.0f);
	_boardEMT->InitRandomPosExplosionVel(5.0f, 10.0f);*/

	_boardEMT->InitRandomAlpha(0.1f, 0.1f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.2f, 0.2f);
	//_pointEMT->InitRandomAlphaFade(0.2f, 0.2f);
	_boardEMT->InitAnimation(4, 4);



	_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS, true);
}

void psPlayerSet00::WhirlwindSet00(string psName)
{
	dxParticleSystemSet::init();

	_planeEMT = NULL;
	_planeEMT = new dxPlaneEmitter;
	_planeEMT->init("ParticleResources/Texture/shoutingCircle01.png", 4, 0.25f, 50);

	_planeEMT->InitRandomSize(0.6f, 0.7f);
	_planeEMT->InitRandomSizeEnd(2.2f, 3.2f);


	//시작시간 조절!!!!!!!!!!!
	//_planeEMT->SetStartLimitTime(1.0f);

	_planeEMT->setRealtimeTrackingPosOn();

	_planeEMT->SetPositionType();
	//_planeEMT->InitDirSphere(1.0f,1.0f,0.0f);
	//_planeEMT->InitRandomPosSphereRadius(1.0f,1.0f);
	//_planeEMT->InitRandomPosExplosionVel(5.0f,5.0f);

	_planeEMT->InitRotateStartAngleX(-30.0f, 30.0f);
	_planeEMT->InitRotateStartAngleY(0.0f, 360.0f);
	_planeEMT->InitRotateStartAngleZ(-30.0f, 30.0f);

	_planeEMT->InitRandomLifeTime(0.7f, 0.7f);

	_planeEMT->InitRandomAlpha(0.1f, 0.2f);
	_planeEMT->addAlphaGraph(0.8f, 0.3f, 0.4f);
	_planeEMT->addAlphaGraph(1.0f, 0.0f, 0.0f);


	_planeEMT->InitRandomPositionY(0.5f, 0.5f);

	_PS->addEmitter(_planeEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fire02_frame4x4.png", 1, 0.1f, 80);

	//_boardEMT->InitRandomLifeTime(1.0f, 1.0f);
	//_boardEMT->SetStartLimitTime(0.8f);

	_boardEMT->InitAnimation(4, 4);
	_boardEMT->InitConstAniReactivateNum(3);

	//_boardEMT->setInitActiveLimitTime(2.0f);

	_boardEMT->InitRandomLifeTime(1.4f, 1.6f);

	_boardEMT->InitCenterPointHV(0.5f, 1.0f);

	

	//_boardEMT->InitRandomPositionX(-1.0, 1.0f);
	//_boardEMT->InitRandomPositionZ(1.0,5.0f);

	_boardEMT->InitRandomSize(0.2f, 0.3f);
	_boardEMT->InitRandomSizeEnd(1.4f, 1.8f);

	//_boardEMT->SetPositionType(PTC_SPHERE);
	//_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	//_boardEMT->InitRandomPosSphereRadius(1.0f, 2.0f);

	//_boardEMT->InitCircleRadiusY(3.0f, 5.0f);
	//_boardEMT->InitCircleStartAngleY(40.0f, 140.0f);
	//_boardEMT->InitRandomPosExplosionVel(5.0f, 15.0f);

	_boardEMT->InitRandomAlpha(0.1f, 0.1f);
	_boardEMT->addAlphaGraph(0.3f, 0.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 0.6f, 0.7f);
	_boardEMT->addAlphaGraph(1.0f, 0.2f, 0.2f);

	_PS->addEmitter(_boardEMT);




	//_boardEMT = NULL;
	//_boardEMT = new dxBoardEmitter;
	//_boardEMT->init("ParticleResources/Texture/smoke02_frame4x4.png", 12, 0.5f, 360);
	////_pointEMT->InitConstSize(2.4f);

	//_boardEMT->setInitActiveLimitTime(2.0f);

	//_boardEMT->InitRandomLifeTime(2.5f, 3.2f);

	//_boardEMT->InitRandomSize(0.0f, 0.2f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 18.2f);

	//_boardEMT->SetPositionType(PTC_SPHERE);
	//_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	//_boardEMT->InitRandomPosSphereRadius(1.0f, 2.0f);
	//_boardEMT->InitRandomPosExplosionVel(5.0f, 8.0f);

	//_boardEMT->InitCenterPointHV(0.5f, 1.0f);

	//_boardEMT->InitRandomAlpha(0.1f, 0.1f);
	//_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	//_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	//_boardEMT->addAlphaGraph(1.0f, 0.2f, 0.2f);
	//
	//_boardEMT->InitAnimation(4, 4);
	



	_PS->addEmitter(_boardEMT);


	PSM->addPS(psName, _PS);

}
