#include "stdafx.h"
#include "PS_Set00.h"

HRESULT PS_Set00::init()
{
	//파티클 이름이 잘 보이게 일부러 이름 넣는 인자값을 준다.
	this->set00_00("구슬");
	this->set00_01("터짐");

	this->set01_00("구슬2");
	this->set01_01("터짐2");

	return S_OK;
}

void PS_Set00::release()
{
	dxParticleSystemSet::release();
}

void PS_Set00::set00_00(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/explosion.png", 1, 1.0f, 1);
	//_pointEMT->InitConstSize(2.4f);
	_pointEMT->setRealtimeTrackingPosOn();

	_pointEMT->InitRandomSize(2.2f, 2.2f);
	_pointEMT->addSizeGraph(0.5f, 2.8f, 2.8f);
	_pointEMT->addSizeGraph(1.0f, 2.2f, 2.2f);

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
	_pointEMT->init("PaticleResources/Texture/Light02.png", 1, 0.5f,1);
	//_pointEMT->InitConstSize(3.5f);
	_pointEMT->InitRandomSize(2.5f,2.5f);
	_pointEMT->addSizeGraph(0.5f, 4.5f,4.5f);
	_pointEMT->addSizeGraph(1.0f, 2.5f,2.5f);
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
	_pointEMT->addAlphaGraph(0.5,1.0f,1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	//_pointEMT->InitRandomAlphaFade(0.3f, 0.3f);

	_pointEMT->InitRandomLifeTime(0.5f, 0.5f);

	/*_pointEMT->InitRandomLifeTime(1.0f, 1.0f);
	_pointEMT->InitRandomLifeTime(0.5f, 0.5f);*/

	_PS->addEmitter(_pointEMT);

	PSM->addPS(psName, _PS);
}

void PS_Set00::set00_01(string psName)
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

void PS_Set00::set01_00(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light.png", 1, 0.1f, 200);
	//_pointEMT->InitConstSize(1.0f);

	//_pointEMT->InitRandomPositionX(-1.0f, -1.0f);
	//_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	//_pointEMT->InitRandomPositionZ(-1.0f, 1.0f);

	//_pointEMT->InitRandomVelocityX(-1.5f, -1.5f);
	_pointEMT->InitRandomVelocityY(1.5f, 1.5f);
	_pointEMT->InitRandomVelocityX(-0.1f, 0.1f);
	_pointEMT->InitRandomVelocityZ(-0.1f, 0.1f);
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
	_pointEMT->init("PaticleResources/Texture/Light05.png", 1, 0.1f, 200);
	_pointEMT->InitConstSize(1.2f);
	/*_pointEMT->InitRandomPositionX(-1.0f, 1.0f);
	_pointEMT->InitRandomPositionY(-0.5f, 0.5f);
	_pointEMT->InitRandomPositionZ(-1.0f, 1.0f);*/

	//_pointEMT->InitRandomVelocityY(-0.2f, 0.2f);
	//_pointEMT->InitRandomVelocityY(-1.0f, -1.0f);

	_pointEMT->InitRandomVelocityY(1.0f, 1.0f);
	_pointEMT->InitRandomVelocityX(-0.1f, 0.1f);
	_pointEMT->InitRandomVelocityZ(-0.1f, 0.1f);
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
	_pointEMT->init("PaticleResources/Texture/explosion.png", 1, 1.0f, 1);
	//_pointEMT->InitConstSize(2.4f);

	_pointEMT->InitRandomSize(2.2f, 2.2f);
	_pointEMT->addSizeGraph(0.5f, 2.8f, 2.8f);
	_pointEMT->addSizeGraph(1.0f, 2.2f, 2.2f);

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
	_pointEMT->InitRandomSize(2.5f, 2.5f);
	_pointEMT->addSizeGraph(0.5f, 4.5f, 4.5f);
	_pointEMT->addSizeGraph(1.0f, 2.5f, 2.5f);
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

	PSM->addPS(psName, _PS);
}

void PS_Set00::set01_01(string psName)
{
	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light08.png", 1, 1.0f , 2);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	
	_pointEMT->InitRandomSize(3.5f, 3.5f);
	_pointEMT->InitRandomSizeEnd(8.0f,8.0f);

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
