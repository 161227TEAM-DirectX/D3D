#include "stdafx.h"
#include "particleTest.h"

HRESULT particleTest::init(void)
{
	//시스템 초기화
	_testPS = new dxParticleSystem;


	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/Light.png", 1, 0.5f);
	//_testEmitter->InitRandomPositionX(-2.0f, 2.0f);
	//_testEmitter->InitRandomPositionY(0.0f, 0.0f);
	//_testEmitter->InitRandomPositionZ(-2.0f, 2.0f);

	//_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(5.0f, 8.0f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	_testEmitter->addVelocityGraphX(0.25f, 1.0f, 1.0f);
	_testEmitter->addVelocityGraphX(0.5f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphX(0.75f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphX(1.0f, -1.0f, -1.0f);

	_testEmitter->InitRandomVelocityY(1.0f, 1.0f);

	_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	_testEmitter->addVelocityGraphZ(0.25f, 1.0f, 1.0f);
	_testEmitter->addVelocityGraphZ(0.5f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphZ(0.75f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphZ(1.0f, -1.0f, -1.0f);

	//_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	//_testEmitter->InitRandomAccelerationY(-90.0f,-90.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	//_testEmitter->InitRandomColorR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorB(0.1f, 1.0f);

	//_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.1f, 1.0f);

	_testEmitter->InitRandomAlpha(0.0f,0.0f);
	//_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	_testEmitter->addAlphaGraph(0.5f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	_testEmitter->addAlphaGraph(1.0f, 0.0f, 0.0f);

	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	_testEmitter->InitRandomLifeTime(6.0f, 6.0f);
	//_testEmitter->InitConstSize(1.0f);
	_testEmitter->InitRandomSize(1.0f,1.0f);
	//_testEmitter->addSizeGraph(0.25f, 3.0f, 3.0f);
	//_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);
	


	//_testEmitter->InitRandomSizeEnd(0.1f,2.0f);
	


	//
	_testPS->addEmitter(_testEmitter);

	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/alpha.png", 1, 0.1f);
	
	//_testEmitter->InitRandomPositionX(-3.0f, -1.0f);

	_testEmitter->InitRandomVelocityX(-3.0f, -3.0f);
	_testEmitter->InitRandomVelocityY(-0.2f, 0.2f);

	_testEmitter->InitRandomAccelerationX(1.0f,1.0f);

	_testEmitter->InitRandomColorR(0.7f, 0.7f);
	_testEmitter->InitRandomColorG(0.0f, 0.0f);
	_testEmitter->InitRandomColorB(0.0f, 0.0f);

	_testEmitter->InitRandomColorFadeR(0.5f, 0.5f);
	_testEmitter->InitRandomColorFadeG(0.5f, 0.5f);
	_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);

	_testEmitter->InitRandomAlpha(1.0f,1.0f);
	_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	_testEmitter->InitRandomLifeTime(2.0f, 2.0f);

	//_testEmitter->InitRandomSpawnTime(0.01f,0.01f);

	//_testPS->addEmitter(_testEmitter);

	//SAFE_DELETE(_testEmitter);
	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/arrow.png", 1, 2.0f);
	//_testEmitter->InitConstSize(5.0f);

	//_testEmitter->InitRandomPositionX(-3.0f, -1.0f);

	//_testEmitter->InitRandomVelocityX(-3.0f, -3.0f);
	_testEmitter->InitRandomVelocityY(0.0f, 0.0f);

	//_testEmitter->InitRandomAccelerationX(1.0f, 1.0f);

	_testEmitter->InitRandomColorR(0.7f, 0.7f);
	_testEmitter->InitRandomColorG(0.7f, 0.7f);
	_testEmitter->InitRandomColorB(0.7f, 0.7f);

	/*_testEmitter->InitRandomColorFadeR(0.5f, 0.5f);
	_testEmitter->InitRandomColorFadeG(0.5f, 0.5f);
	_testEmitter->InitRandomColorFadeB(0.0f, 0.0f);*/

	//_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	_testEmitter->InitRandomLifeTime(2.0f, 2.0f);

	//_testEmitter->InitRandomSpawnTime(1.0f,1.0f);

	//_testPS->addEmitter(_testEmitter);


	return S_OK;
}

void particleTest::release(void)
{
	//SAFE_DELETE(_testEmitter);
}

void particleTest::update(void)
{
	_testPS->update();
}

void particleTest::render(void)
{
	_testPS->render();
}
