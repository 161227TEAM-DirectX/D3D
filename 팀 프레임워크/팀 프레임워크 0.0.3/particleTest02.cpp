#include "stdafx.h"
#include "particleTest02.h"

HRESULT particleTest02::init(void)
{
	////시스템 초기화
	//_testPS = new dxPaticleSystem;


	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("PaticleResources/Texture/beam.png", 6, 0.5f);
	//_testEmitter->InitConstSize(0.5f);

	//_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	//_testEmitter->InitRandomPositionY(-0.5f, 1.0f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);

	////_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(1.2f, 1.6f);
	////_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	////_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	////_testEmitter->InitRandomVelocityY(1.0f, 2.0f);
	////_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);

	////_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	//_testEmitter->InitRandomAccelerationY(50.0f,50.0f);
	////_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	//_testEmitter->InitRandomColorR(0.0f, 0.2f);
	//_testEmitter->InitRandomColorG(0.8f, 1.0f);
	//_testEmitter->InitRandomColorB(0.0f, 0.0f);

	//_testEmitter->InitRandomColorFadeR(0.8f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.8f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);

	//_testEmitter->InitRandomAlpha(1.0f,1.0f);
	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	//_testEmitter->InitRandomLifeTime(2.0f, 3.0f);

	//_testPS->addEmitter(_testEmitter);


	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("PaticleResources/Texture/Light.png", 6, 0.5f);
	//_testEmitter->InitConstSize(0.3f);

	//_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	//_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);

	////_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(0.5f, 1.0f);
	////_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	////_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	////_testEmitter->InitRandomVelocityY(1.0f, 2.0f);
	////_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);

	////_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	//_testEmitter->InitRandomAccelerationY(50.0f, 80.0f);
	////_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	///*_testEmitter->InitRandomColorR(0.1f, 0.3f);
	//_testEmitter->InitRandomColorG(0.8f, 0.8f);
	//_testEmitter->InitRandomColorB(0.0f, 0.0f);

	//_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);*/

	//_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	//_testEmitter->InitRandomLifeTime(2.0f, 2.0f);

	//_testPS->addEmitter(_testEmitter);

	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("PaticleResources/Texture/Light02.png", 8, 0.5f);
	//_testEmitter->InitConstSize(0.5f);

	//_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	//_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);

	////_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(0.5f, 1.0f);
	////_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	////_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	////_testEmitter->InitRandomVelocityY(1.0f, 2.0f);
	////_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);

	////_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	////_testEmitter->InitRandomAccelerationY(200.0f, 200.0f);
	////_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	///*_testEmitter->InitRandomColorR(0.0f, 0.0f);
	//_testEmitter->InitRandomColorG(0.6f, 0.6f);
	//_testEmitter->InitRandomColorB(0.6f, 0.6f);*/

	///*_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);*/

	//_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	//_testEmitter->InitRandomLifeTime(2.0f, 2.0f);

	//_testPS->addEmitter(_testEmitter);


	//=====================================================
	//파티클 시스템 초기화
	_testPS = new dxParticleSystem;


	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("PaticleResources/Texture/beam.png", 6, 0.5f);
	//_testEmitter->InitConstSize(0.5f);

	//_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	//_testEmitter->InitRandomPositionY(-0.5f, 1.0f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);

	////_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(1.2f, 1.6f);
	////_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	////_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	////_testEmitter->InitRandomVelocityY(1.0f, 2.0f);
	////_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);

	////_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	//_testEmitter->InitRandomAccelerationY(50.0f,50.0f);
	////_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	//_testEmitter->InitRandomColorR(0.0f, 0.2f);
	//_testEmitter->InitRandomColorG(0.8f, 1.0f);
	//_testEmitter->InitRandomColorB(0.0f, 0.0f);

	//_testEmitter->InitRandomColorFadeR(0.8f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.8f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);

	//_testEmitter->InitRandomAlpha(1.0f,1.0f);
	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	//_testEmitter->InitRandomLifeTime(2.0f, 3.0f);

	//_testPS->addEmitter(_testEmitter);

	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/Light.png", 1, 0.05f);

	//_testEmitter->InitRandomPositionX(-1.0f, -1.0f);
	//_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);

	_testEmitter->InitRandomVelocityX(-1.5f, -1.5f);
	_testEmitter->InitRandomVelocityY(-0.1f, 0.1f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	//_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	//_testEmitter->InitRandomVelocityY(1.0f, 2.0f);
	//_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);

	_testEmitter->InitRandomAccelerationX(-1.0f,-1.0f);
	//_testEmitter->InitRandomAccelerationY(50.0f, 80.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	/*_testEmitter->InitRandomColorR(0.1f, 0.3f);
	_testEmitter->InitRandomColorG(0.8f, 0.8f);
	_testEmitter->InitRandomColorB(0.0f, 0.0f);

	_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);*/

	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	_testEmitter->InitRandomLifeTime(3.0f, 3.0f);

	_testPS->addEmitter(_testEmitter);

	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/Light05.png", 1, 0.05f);

	/*_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);*/

	_testEmitter->InitRandomVelocityX(-1.0f, -1.0f);
	_testEmitter->InitRandomVelocityY(-0.2f, 0.2f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	//_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	//_testEmitter->InitRandomVelocityY(1.0f, 2.0f);
	//_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);

	_testEmitter->InitRandomAccelerationX(-2.0f, -2.0f);
	//_testEmitter->InitRandomAccelerationY(50.0f, 80.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	/*_testEmitter->InitRandomColorR(0.1f, 0.3f);
	_testEmitter->InitRandomColorG(0.8f, 0.8f);
	_testEmitter->InitRandomColorB(0.0f, 0.0f);

	_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);*/

	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	_testEmitter->InitRandomLifeTime(1.5f, 1.5f);

	_testPS->addEmitter(_testEmitter);


	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/explosion.png", 1, 2.0f);

	/*_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);*/

	//_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	_testEmitter->InitRandomVelocityY(0.0f, 0.0f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	//_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	//_testEmitter->InitRandomVelocityY(1.0f, 2.0f);
	//_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);

	//_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	//_testEmitter->InitRandomAccelerationY(200.0f, 200.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	/*_testEmitter->InitRandomColorR(0.0f, 0.0f);
	_testEmitter->InitRandomColorG(0.6f, 0.6f);
	_testEmitter->InitRandomColorB(0.6f, 0.6f);*/

	/*_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);*/

	/*_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	_testEmitter->InitRandomAlphaFade(0.1f, 0.1f);*/

	//_testEmitter->InitRandomLifeTime(1.0f, 1.0f);

	_testPS->addEmitter(_testEmitter);

	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/Light02.png", 1, 1.5f);

	/*_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);*/

	//_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	_testEmitter->InitRandomVelocityY(0.0f, 0.0f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	_testEmitter->InitRandomVelocityY(0.0f, 0.0f);
	_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);

	//_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	//_testEmitter->InitRandomAccelerationY(200.0f, 200.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	/*_testEmitter->InitRandomColorR(0.0f, 0.0f);
	_testEmitter->InitRandomColorG(0.6f, 0.6f);
	_testEmitter->InitRandomColorB(0.6f, 0.6f);*/

	/*_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);*/

	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	_testEmitter->InitRandomAlphaFade(0.3f, 0.3f);

	/*_testEmitter->InitRandomLifeTime(1.0f, 1.0f);
	_testEmitter->InitRandomLifeTime(0.5f, 0.5f);*/

	_testPS->addEmitter(_testEmitter);


	


	return S_OK;
}

void particleTest02::release(void)
{
	//SAFE_DELETE(_testEmitter);
}

void particleTest02::update(void)
{
	_testPS->update();
}

void particleTest02::render(void)
{
	_testPS->render();
}
