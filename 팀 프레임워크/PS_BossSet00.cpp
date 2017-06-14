#include "stdafx.h"
#include "PS_BossSet00.h"

HRESULT PS_BossSet00::init()
{
	//파티클 이름이 잘 보이게 일부러 이름 넣는 인자값을 준다.
	this->set00_00("브레스");
	this->set00_01("타겟000");
	//this->set00_02("");

	return S_OK;
}

void PS_BossSet00::release()
{
	dxParticleSystemSet::release();
}

void PS_BossSet00::set00_00(string psName)
{
	dxParticleSystemSet::init();

	_boardEMT = NULL;
	_boardEMT = new dxBoardEmitter;
	_boardEMT->init("PaticleResources/Texture/fire01_frame5x4.png", 10, 0.1f, 3000);
	//_pointEMT->InitConstSize(2.4f);

	_boardEMT->InitRandomSize(1.0f, 1.5f);
	_boardEMT->InitRandomSizeEnd(2.3f, 2.8f);
	//_pointEMT->addSizeGraph(0.5f, 2.8f, 2.8f);
	//_pointEMT->addSizeGraph(1.0f, 2.2f, 2.2f);

	//_boardEMT->InitRandomPositionX(-1.0f, 1.0f);
	//_boardEMT->InitRandomPositionY(-0.5f, 0.5f);
	_boardEMT->InitRandomPositionZ(0.0f, 0.5f);

	//_boardEMT->InitRandomVelocityX(-3.0f, 3.0f);
	//_boardEMT->InitRandomVelocityY(-1.0f, 1.0f);
	_boardEMT->InitRandomVelocityZ(5.0f, 10.0f);

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

	_boardEMT->InitCircleStartAngleZ(0.0f,360.0f);
	_boardEMT->InitCircleRadiusZ(0.0f, 0.0f);
	_boardEMT->InitCircleRadiusEndZ(5.0f, 5.0f);
	//_boardEMT->InitRandomRadiusZ(5.0f, 5.0f);

	//_boardEMT->
	_boardEMT->InitCircleAngleSpeedZ(100.0f, 120.0f);

	_boardEMT->InitRandomLifeTime(3.0f, 5.0f);

	_PS->addEmitter(_boardEMT);

	


	PSM->addPS(psName, _PS);
}

void PS_BossSet00::set00_01(string psName)
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
