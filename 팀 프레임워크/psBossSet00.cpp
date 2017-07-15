#include "stdafx.h"
#include "psBossSet00.h"

HRESULT psBossSet00::init()
{
	//파티클 이름이 잘 보이게 일부러 이름 넣는 인자값을 준다.
	this->BreathSet00("브레스");
	this->ShoutingSet00("샤우팅");

	this->GrandMagic00("대마법진");
	this->GrandMagic01("대규모마법");

	this->EnergyBullet00("에너지탄_준비");
	this->EnergyBullet01("에너지탄");
	this->EnergyBullet02("에너지탄_폭발");

	this->FireField00("불꽃퍼짐");

	this->Scratch00("불꽃할퀴기");
	this->FirePath00("불꽃길");

	

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
	_boardEMT->init("ParticleResources/Texture/fire06_frame4x4.png", 18, 0.1f, 1000);
	//_pointEMT->InitConstSize(2.4f);
	_boardEMT->InitRandomSize(2.0f, 2.5f);
	_boardEMT->InitRandomSizeEnd(8.3f, 10.8f);
	//_pointEMT->addSizeGraph(0.5f, 2.8f, 2.8f);
	//_pointEMT->addSizeGraph(1.0f, 2.2f, 2.2f);
	_boardEMT->setInitActiveLimitTime(8.5f);
	//_boardEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_boardEMT->InitRandomPositionY(-0.5f, 0.5f);
	//_boardEMT->InitRandomPositionZ(0.0f, 0.5f);

	//_boardEMT->InitRandomVelocityX(-3.0f, 3.0f);
	//_boardEMT->InitRandomVelocityY(-1.0f, 1.0f);
	_boardEMT->InitRandomVelocityZ(15.0f, 25.0f);
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

	_boardEMT->InitRandomAlpha(1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8,0.8f, 0.8f);
	_boardEMT->addAlphaGraph(1.0, 0.0f, 0.0f);

	//_pointEMT->InitRandomAlphaFade(0.1f, 0.1f);
	_boardEMT->InitAnimation(4,4);
	_boardEMT->InitConstAniReactivateNum(6);

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
	_boardEMT->InitCircleRadiusEndZ(12.0f, 15.0f);
	_boardEMT->InitRotateStartAngleZ(0.0f,360.0f);

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
	_planeEMT->init("ParticleResources/Texture/shoutingCircle01.png", 4, 0.2f, 50);
	
	_planeEMT->InitRandomSize(1.0f,1.0f);
	_planeEMT->InitRandomSizeEnd(38.0f, 52.0f);


	//시작시간 조절!!!!!!!!!!!
	_planeEMT->SetStartLimitTime(1.0f);

	_planeEMT->SetPositionType();
	//_planeEMT->InitDirSphere(1.0f,1.0f,0.0f);
	//_planeEMT->InitRandomPosSphereRadius(1.0f,1.0f);
	//_planeEMT->InitRandomPosExplosionVel(5.0f,5.0f);

	_planeEMT->InitRotateStartAngleX(0.0f, 360.0f);
	_planeEMT->InitRotateStartAngleY(0.0f, 360.0f);
	_planeEMT->InitRotateStartAngleZ(0.0f, 360.0f);

	_planeEMT->InitRandomLifeTime(0.7f, 0.7f);

	_planeEMT->InitRandomAlpha(0.1f, 0.2f);
	_planeEMT->addAlphaGraph(0.8f, 0.3f, 0.4f);
	_planeEMT->addAlphaGraph(1.0f, 0.0f, 0.0f);


	_PS->addEmitter(_planeEMT);

	//_boardEMT = NULL;
	//_boardEMT = new dxBoardEmitter;
	//_boardEMT->init("ParticleResources/Texture/OneSmoke00.png", 10, 0.1f, 50);
	//
	//_boardEMT->InitRandomSize(4.0f,4.0f);
	//_planeEMT->InitRandomSizeEnd(20.0f, 20.0f);

	//_boardEMT->SetPositionType();
	//_boardEMT->InitDirSphere(1.0f,1.0f,0.0f);
	//_boardEMT->InitRandomPosSphereRadius(1.0f,1.0f);
	//_boardEMT->InitRandomPosExplosionVel(5.0f,5.0f);

	//_boardEMT->InitRotateStartAngleZ(0.0f, 360.0f);

	//_boardEMT->InitRandomLifeTime(0.5f, 0.5f);

	//_PS->addEmitter(_boardEMT);

	//PSM->addPS(psName, _PS);

	//_boardEMT = NULL;
	//_boardEMT = new dxBoardEmitter;
	//_boardEMT->init("ParticleResources/Texture/OneSmoke01.png", 10, 0.5f, 50);

	//_boardEMT->InitRandomSize(1.0f, 1.0f);
	////_planeEMT->InitRandomSizeEnd(20.0f, 20.0f);

	//_boardEMT->SetPositionType();
	//_boardEMT->InitDirSphere(1.0f, 1.0f, 0.0f);
	//_boardEMT->InitRandomPosSphereRadius(1.0f, 1.0f);
	//_boardEMT->InitRandomPosExplosionVel(5.0f, 5.0f);

	//_boardEMT->InitRandomLifeTime(0.5f, 0.5f);

	//_boardEMT->InitRotateStartAngleZ(0.0f,360.0f);

	//_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS);
}

//대규모 마법
void psBossSet00::GrandMagic00(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/Lightning08_f27x1.png", 10, 0.2f, 200);

	_boardEMT->InitRandomLifeTime(1.0f,1.2f);
	_boardEMT->SetStartLimitTime(0.8f);


	_boardEMT->InitCenterPointHV(0.5f, 0.0f);
	
	_boardEMT->InitConstHV(1.0f,7.0f);
	_boardEMT->InitRandomSize(3.6f,3.6f);

	/*_planeEMT->InitRotateStartAngleY(-90.0f, -90.0f);

	_planeEMT->InitRotateStartAngleZ(-90.0f, -90.0f);

	_planeEMT->InitRotateStartAngleX(0.0f, 360.0f);*/

	_boardEMT->SettingBillBoardY();


	_boardEMT->InitRandomPositionY(-7.0f, -7.0f);
	_boardEMT->InitAnimation(27,1);


	_boardEMT->SetPositionType(PTC_SPHERE);
	_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	_boardEMT->InitRandomPosSphereRadius(15.0f, 32.5f);


	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/smoke04_frame4x4.png", 50, 0.4f, 300);
	//_pointEMT->InitConstSize(2.4f);

	_boardEMT->InitRandomLifeTime(3.6f, 3.6f);
	//_boardEMT->SetStartLimitTime(0.6f);
	_boardEMT->SetActiveLimitTime(4.4f);

	_boardEMT->InitRandomSize(9.0f, 11.0f);
	_boardEMT->addSizeGraph(0.3f, 17.0f, 23.0f);
	_boardEMT->addSizeGraph(1.0f, 13.0f, 15.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 18.2f);

	_boardEMT->SetPositionType(PTC_SPHERE);
	_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);


	_boardEMT->InitRandomPosSphereRadius(0.7f, 3.8f);
	//_boardEMT->InitRandomPosExplosionVel(10.0f, 10.0f);
	_boardEMT->InitRandomPosExplosionVel(0.0f, 0.0f);
	_boardEMT->addPosExplosionVelGraph(0.4f, 1.0f, 24.0f);
	_boardEMT->addPosExplosionVelGraph(0.5f, 0.0f, 0.0f);
	_boardEMT->addPosExplosionVelGraph(1.0f, 0.0f, 0.0f);

	_boardEMT->InitRandomPosRotAngleSpeedY(100.0f, 200.0f);

	//	_boardEMT->InitAllRotateSpeed(0.0f,50.0f,0.0f);

	_boardEMT->InitRandomVelocityY(0.0f, 0.0f);
	//_boardEMT->addVelocityGraphY(0.5f, 0.0f, 0.0f);
	//_boardEMT->addVelocityGraphY(1.0f, 5.0f, 10.0f);


	_boardEMT->InitRandomAlpha(0.3f, 0.3f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.0f, 0.0f);
	//_pointEMT->InitRandomAlphaFade(0.2f, 0.2f);
	_boardEMT->InitAnimation(4, 4);
	_boardEMT->InitConstAniReactivateNum(8);
	

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/smoke04_frame4x4.png", 50, 0.5f, 250);
	//_pointEMT->InitConstSize(2.4f);

	_boardEMT->InitRandomLifeTime(3.5f, 3.5f);
	_boardEMT->SetStartLimitTime(2.2f);
	//_boardEMT->SetActiveLimitTime(5.4f);

	_boardEMT->InitRandomSize(9.0f, 11.0f);
	_boardEMT->addSizeGraph(0.3f, 17.0f, 23.0f);
	_boardEMT->addSizeGraph(1.0f, 13.0f, 15.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 18.2f);

	_boardEMT->SetPositionType(PTC_SPHERE);
	_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);

	//테스트용
	//_boardEMT->InitRandomPosSphereRadius(10.5f, 10.5f);

	_boardEMT->InitRandomPosSphereRadius(1.0f, 22.0f);
	//_boardEMT->InitRandomPosExplosionVel(10.0f, 10.0f);
	//_boardEMT->InitRandomPosExplosionVel(0.0f, 0.0f);
	//_boardEMT->addPosExplosionVelGraph(0.3f, 0.8f, 12.0f);
	//_boardEMT->addPosExplosionVelGraph(0.5f, 0.0f, 0.0f);
	//_boardEMT->addPosExplosionVelGraph(1.0f, 0.0f, 0.0f);

	_boardEMT->InitRandomPosRotAngleSpeedY(100.0f, 200.0f);

	//	_boardEMT->InitAllRotateSpeed(0.0f,50.0f,0.0f);

	_boardEMT->InitRandomVelocityY(0.0f, 0.0f);
	//_boardEMT->addVelocityGraphY(0.5f, 0.0f, 0.0f);
	//_boardEMT->addVelocityGraphY(1.0f, 5.0f, 10.0f);



	_boardEMT->InitRandomAlpha(0.3f, 0.3f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.8f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.0f, 0.0f);
	//_pointEMT->InitRandomAlphaFade(0.2f, 0.2f);
	_boardEMT->InitAnimation(4, 4);
	_boardEMT->InitConstAniReactivateNum(8);


	_PS->addEmitter(_boardEMT);




	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/tornado_f32x1.png", 1, 2.0f, 1);
	//_boardEMT->setGrayScaleAlphaOn();
	_boardEMT->InitAnimation(32, 1);
	//_boardEMT->InitAnimation(5, 3, 13);
	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);
	_boardEMT->InitRandomSize(10.0f, 10.0f);
	//_boardEMT->InitRandomSizeEnd(1.0f, 1.0f);
	//_boardEMT->InitRandomAlpha(0.1f, 0.1f);

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/crystal_f15x3.png", 1, 2.0f, 1);
	//_boardEMT->setGrayScaleAlphaOn();
	_boardEMT->InitAnimation(15, 3);
	//_boardEMT->InitAnimation(5, 3, 13);
	_boardEMT->InitRandomLifeTime(2.0f, 2.0f);
	_boardEMT->InitRandomSize(5.0f, 5.0f);
	//_boardEMT->InitRandomSizeEnd(1.0f, 1.0f);
	//_boardEMT->InitRandomAlpha(0.1f, 0.1f);

	_PS->addEmitter(_boardEMT);

	


	PSM->addPS(psName, _PS,true);
}

void psBossSet00::GrandMagic01(string psName)
{
	dxParticleSystemSet::init();

	//_boardEMT = NULL;
	//_boardEMT = new dxBoardEmitter;
	//_boardEMT->init("ParticleResources/Texture/fireballEffect_f38x1.png", 240, 0.5f, 600);

	//_boardEMT->InitRandomLifeTime(5.0f, 5.0f);
	//_boardEMT->InitAnimation(38, 1);
	//_boardEMT->InitConstAniReactivateNum(5);
	//_boardEMT->InitRandomSize(2.0f, 2.0f);
	//_boardEMT->InitRandomSizeEnd(5.0f, 5.0f);
	////_boardEMT->addSizeGraph(0.5f, 12.0f, 12.0f);
	////_boardEMT->addSizeGraph(1.0f, 5.0f, 5.0f);
	//_boardEMT->InitRandomAccelerationY(-1200.0f, -1200.0f);
	//_boardEMT->InitRandomVelocityY(10.0f,10.0f);


	//_boardEMT->SetPositionType(PTC_SPHERE);
	//_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	//_boardEMT->InitRandomPosSphereRadius(0.1f, 0.1f);
	//_boardEMT->InitRandomPosExplosionVel(16.0f, 16.0f);
	////_boardEMT->addPosExplosionVelGraph(1.0f, 5.0f, 5.0f);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/starLight_f5x6.png", 1, 1.0f, 1);

	_boardEMT->InitRandomLifeTime(10.0f, 10.0f);
	_boardEMT->InitAnimation(5, 6);
	_boardEMT->InitAniPlaySection(0,9);
	//_boardEMT->InitConstAniReactivateNum(10);

	_boardEMT->InitRandomSize(2.0f, 2.0f);
	_boardEMT->InitRandomSizeEnd(5.0f, 5.0f);
	//_boardEMT->addSizeGraph(0.5f, 12.0f, 12.0f);
	//_boardEMT->addSizeGraph(1.0f, 5.0f, 5.0f);
	_boardEMT->InitRandomAccelerationY(-1200.0f, -1200.0f);
	_boardEMT->InitRandomVelocityY(10.0f,10.0f);


	_boardEMT->SetPositionType(PTC_SPHERE);
	_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	_boardEMT->InitRandomPosSphereRadius(0.1f, 0.1f);
	_boardEMT->InitRandomPosExplosionVel(16.0f, 16.0f);
	//_boardEMT->addPosExplosionVelGraph(1.0f, 5.0f, 5.0f);

	_PS->addEmitter(_boardEMT);


	PSM->addPS(psName, _PS);
}




//////////////////////////////////
void psBossSet00::EnergyBullet00(string psName)
{
	dxParticleSystemSet::init();


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fireballEffect_f38x1.png", 1, 3.0f, 1);

	_boardEMT->InitRandomLifeTime(3.0f, 3.0f);
	_boardEMT->InitAnimation(38, 1);
	_boardEMT->InitConstAniReactivateNum(3);

	_boardEMT->InitRandomSize(0.1f, 0.1f);
	_boardEMT->InitRandomSizeEnd(8.0f, 8.0f);
	//_boardEMT->addSizeGraph(0.5f, 12.0f, 12.0f);
	//_boardEMT->addSizeGraph(1.0f, 5.0f, 5.0f);



	_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS, true);
}


///////////////////////////
void psBossSet00::EnergyBullet01(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fireballEffect_f38x1.png", 1, 1.0f, 1);
	
	_boardEMT->InitRandomLifeTime(1.0f,1.0f);
	_boardEMT->InitAnimation(38,1);
	_boardEMT->InitRandomSize(8.0f, 8.0f);
	//_boardEMT->addSizeGraph(0.5f, 12.0f, 12.0f);
	//_boardEMT->addSizeGraph(1.0f, 5.0f, 5.0f);

	


	_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS, true);

}

//에너지 폭파
void psBossSet00::EnergyBullet02(string psName)
{
	dxParticleSystemSet::init();



	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/Light02.png", 1, 1.2f, 1);

	_boardEMT->InitRandomLifeTime(0.8f, 0.8f);

	_boardEMT->SetActiveLimitTime(0.8f, 0.8f);

	_boardEMT->InitRandomSize(2.0f, 2.0f);
	_boardEMT->addSizeGraph(0.6f, 100.0f, 100.0f);
	_boardEMT->addSizeGraph(1.0f, 10.0f, 10.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 18.2f);


	_boardEMT->InitRandomAlpha(0.6f, 0.6f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.7f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.0f, 0.0f);


	_PS->addEmitter(_boardEMT);

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fireballEffect_f38x1.png", 1, 1.2f, 1);

	_boardEMT->InitRandomLifeTime(0.6f, 0.6f);
	_boardEMT->InitAnimation(38, 1);

	_boardEMT->SetActiveLimitTime(0.6f, 0.6f);
	_boardEMT->InitRandomSize(8.0f, 8.0f);
	_boardEMT->addSizeGraph(0.4f, 24.0f, 24.0f);
	_boardEMT->addSizeGraph(1.0f, 1.0f, 1.0f);

	_boardEMT->InitRandomAlpha(1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.85f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.0f, 0.0f);

	_PS->addEmitter(_boardEMT);


	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fire02_frame4x4.png", 50, 0.6f, 150);
	//_pointEMT->InitConstSize(2.4f);

	_boardEMT->InitRandomLifeTime(4.6f, 4.6f);
	_boardEMT->SetStartLimitTime(0.6f);
	_boardEMT->SetActiveLimitTime(5.4f);

	_boardEMT->InitRandomSize(4.0f, 6.0f);
	_boardEMT->addSizeGraph(0.3f, 12.0f, 18.0f);
	_boardEMT->addSizeGraph(1.0f, 8.0f, 10.0f);
	//_boardEMT->InitRandomSizeEnd(8.0f, 18.2f);

	_boardEMT->SetPositionType(PTC_SPHERE);
	_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);

	//테스트용
	//_boardEMT->InitRandomPosSphereRadius(10.5f, 10.5f);

	_boardEMT->InitRandomPosSphereRadius(0.5f, 3.5f);
	//_boardEMT->InitRandomPosExplosionVel(10.0f, 10.0f);
	_boardEMT->InitRandomPosExplosionVel(0.0f, 0.0f);
	_boardEMT->addPosExplosionVelGraph(0.3f, 8.0f, 12.0f);
	_boardEMT->addPosExplosionVelGraph(0.5f, -12.0f, -16.0f);
	_boardEMT->addPosExplosionVelGraph(1.0f,0.0f,0.0f);

	_boardEMT->InitRandomPosRotAngleSpeedY(100.0f,200.0f);

//	_boardEMT->InitAllRotateSpeed(0.0f,50.0f,0.0f);

	_boardEMT->InitRandomVelocityY(0.0f, 0.0f);
	_boardEMT->addVelocityGraphY(0.5f, 0.0f, 0.0f);
	_boardEMT->addVelocityGraphY(1.0f, 5.0f, 10.0f);

	_boardEMT->InitCenterPointHV(0.5f, 1.0f);

	

	_boardEMT->InitRandomAlpha(0.3f, 0.3f);
	_boardEMT->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(0.7f, 1.0f, 1.0f);
	_boardEMT->addAlphaGraph(1.0f, 0.0f, 0.0f);
	//_pointEMT->InitRandomAlphaFade(0.2f, 0.2f);
	_boardEMT->InitAnimation(4, 4);
	_boardEMT->InitConstAniReactivateNum(8);
	//_boardEMT->InitConstHV(2.0f, 2.0f);

	

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

void psBossSet00::FireField00(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fire05_frame4x4.png", 40, 0.3f, 400);

	//_boardEMT->InitRandomLifeTime(1.0f, 1.0f);
	_boardEMT->InitAnimation(4, 4);
	_boardEMT->InitConstAniReactivateNum(3);

	_boardEMT->setInitActiveLimitTime(2.0f);

	_boardEMT->InitRandomLifeTime(1.2f, 2.4f);

	_boardEMT->InitRandomSize(0.3f, 0.5f);
	_boardEMT->InitRandomSizeEnd(8.0f, 14.2f);

	_boardEMT->InitCenterPointHV(0.5f,1.0f);

	//_boardEMT->SetPositionType(PTC_SPHERE);
	//_boardEMT->InitDirSphere(1.0f, 0.0f, 1.0f);
	//_boardEMT->InitRandomPosSphereRadius(1.0f, 2.0f);
	
	_boardEMT->InitCircleRadiusY(3.0f, 5.0f);
	_boardEMT->InitCircleStartAngleY(20.0f, 160.0f);
	_boardEMT->InitRandomPosExplosionVel(5.0f, 15.0f);

	//_boardEMT->InitRandomVelocityX(-3.0f, 3.0f);
	//_boardEMT->InitRandomVelocityZ(2.0f,4.0f);


	//_boardEMT->InitRandomPositionY(1.0f,1.0f);

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

	_PS->addEmitter(_boardEMT);

	PSM->addPS(psName, _PS,true);

}

void psBossSet00::Scratch00(string psName)
{
	dxParticleSystemSet::init();

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
	_boardEMT->InitRandomPositionZ(1.0,5.0f);

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

	PSM->addPS(psName, _PS);

}

void psBossSet00::FirePath00(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("ParticleResources/Texture/fire05_frame4x4.png", 4, 0.2f, 5000);

	//_boardEMT->InitRandomLifeTime(1.0f, 1.5f);
	_boardEMT->InitAnimation(4, 4);
	_boardEMT->InitConstAniReactivateNum(4);

	//_boardEMT->setInitActiveLimitTime(2.0f);
	_boardEMT->InitCenterPointHV(0.5f, 1.0f);

	_boardEMT->InitRandomLifeTime(1.3f, 2.0f);

	_boardEMT->InitRandomPositionX(5.0, 5.0f);
	_boardEMT->InitRandomPositionZ(0.0, 5.0f);

	_boardEMT->InitRandomSize(1.0f, 2.5f);
	_boardEMT->InitRandomSizeEnd(10.0f, 16.2f);

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
	_boardEMT->init("ParticleResources/Texture/fire05_frame4x4.png", 4, 0.2f, 5000);

	//_boardEMT->InitRandomLifeTime(1.0f, 1.5f);
	_boardEMT->InitAnimation(4, 4);
	_boardEMT->InitConstAniReactivateNum(4);

	//_boardEMT->setInitActiveLimitTime(2.0f);
	_boardEMT->InitCenterPointHV(0.5f, 1.0f);

	_boardEMT->InitRandomLifeTime(1.3f, 2.2f);

	_boardEMT->InitRandomPositionX(-5.0, -5.0f);
	_boardEMT->InitRandomPositionZ(0.0, 5.0f);

	_boardEMT->InitRandomSize(1.0f, 2.5f);
	_boardEMT->InitRandomSizeEnd(10.0f, 16.2f);

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

	PSM->addPS(psName, _PS);
}

