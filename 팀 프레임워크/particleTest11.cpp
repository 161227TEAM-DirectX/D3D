#include "stdafx.h"
#include "particleTest11.h"

void particleTest11::Setup()
{
	_player = new dx::transform;
	_target = new dx::transform;

	_mainCamera = new camera;

	_testPS = new dxParticleSystem;

	_testEmitter = NULL;
	_testEmitter = new dxMeshEmitter;
	//_testEmitter->init("PaticleResources/Texture/magicCircle.png",1,1.0f,1);
	//_testEmitter->init("PaticleResources/Texture/fire00_frame7x7.png", 20, 0.1f, 100);
	_testEmitter->init("PaticleResources/Mesh/stone.x", 30, 5.0f, 60);
	//_testEmitter->init("Resources/Meshes/GunShip/GunShip.x", 5, 1.0f, 10);

	//_testEmitter->InitRandomPositionX(-10.0f, 10.0f);
	//_testEmitter->InitRandomPositionZ(-10.0f, 10.0f);
	_testEmitter->InitRandomVelocityX(-8.0f, 8.0f);
	_testEmitter->InitRandomVelocityZ(-8.0f, 8.0f);
	_testEmitter->InitRandomVelocityY(18.0f, 26.0f);

	_testEmitter->InitRandomAccelerationY(-980.0f,-980.0f);

	_testEmitter->InitRandomSize(0.005f, 0.008f);
	//_testEmitter->InitRandomSizeEnd(0.01f, 0.01f);
	//_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->InitRandomAlphaFade(0.1f, 0.1f);

	//_testEmitter->InitAnimation(5, 4);
	//_testEmitter->InitConstAniReactivateNum(12);

	//_testEmitter->InitRandomLifeTime(0.8f, 1.2f);
	_testEmitter->InitRotateStartAngleX(-10.0f, 10.0f);
	_testEmitter->InitRotateAngleSpeedX(-3.0f, 3.0f);

	_testEmitter->InitRotateStartAngleY(-10.0f, 10.0f);
	_testEmitter->InitRotateAngleSpeedY(-3.0f, 3.0f);

	_testEmitter->InitRotateStartAngleZ(-10.0f, 10.0f);
	_testEmitter->InitRotateAngleSpeedZ(-3.0f, 3.0f);

	_testEmitter->InitRandomLifeTime(5.0f,5.0f);


	//_testEmitter->InitConstVH(4.0f,1.0f);


	//_set00 = new particleSet00;
	//_set00->init();



	//PSM->initPS(_testPS, "터짐");
	//D3DXMatrixIdentity()
	//시스템 초기화
	//_testPS = new dxParticleSystem;
	//_testPS = PSM->findPS("구슬");
	//_testPS = _set00->getPS();

	//_testPS->init();
	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("PaticleResources/Texture/Light02.png", 1, 1.5f);

	rotateY = 0.0f;
}

void particleTest11::Update()
{
	
	_testEmitter->update();
	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();
}

void particleTest11::Render()
{
	_testEmitter->render();
}
