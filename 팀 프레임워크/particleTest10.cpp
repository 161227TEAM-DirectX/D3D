#include "stdafx.h"
#include "particleTest10.h"


HRESULT particleTest10::init(void)
{
	_player = new dx::transform;
	_target = new dx::transform;

	_mineCamera = new camera;

	_testPS = new dxParticleSystem;

	_testEmitter = NULL;
	_testEmitter = new dxMeshEmitter;
	//_testEmitter->init("ParticleResources/Texture/magicCircle.png",1,1.0f,1);
	//_testEmitter->init("ParticleResources/Texture/fire00_frame7x7.png", 20, 0.1f, 100);
	//_testEmitter->init("ParticleResources/Mesh/stone.x", 20, 0.1f, 100);
	//_testEmitter->init("Resources/Meshes/Elementalist/Elementalist.x", 20, 0.1f, 100);
	_testEmitter->init("Resources/Meshes/GunShip/GunShip.x", 1, 0.1f, 1);
	
	_testEmitter->InitRandomPositionX(-10.0f, 10.0f);
	_testEmitter->InitRandomPositionZ(-10.0f, 10.0f);
	//_testEmitter->InitRandomVelocityY(23.5f,38.5f);
	
	//_testEmitter->InitRandomSize(1.0f,3.0f);
	//_testEmitter->InitRandomSizeEnd(12.0f, 22.0f);
	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	_testEmitter->InitRandomAlphaFade(0.1f, 0.1f);

	_testEmitter->InitAnimation(5,4);
	//_testEmitter->InitConstAniReactivateNum(12);
	
	_testEmitter->InitRandomLifeTime(0.8f,1.2f);
	_testEmitter->InitRotateStartAngleY(0.0f, 120.0f);
	_testEmitter->InitRotateAngleSpeedY(6.0f, 6.0f);
	

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
	//_testEmitter->init("ParticleResources/Texture/Light02.png", 1, 1.5f);

	rotateY = 0.0f;

	return S_OK;
}

void particleTest10::release(void)
{
	SAFE_DELETE(_testPS);
}

void particleTest10::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		
	}

	//_target->DefaultMyControl(_timeDelta);
	//_player->DefaultMyControl(_timeDelta);

	//rotateY += D3DXToRadian(10.0f)*_timeDelta;

	rotateY += D3DXToRadian(1.0f);
	//wave = rotateY*4;

	//Lerp(D3DX_PI/rotateY,,);


	//D3DXVECTOR3 LookPos = _player->GetWorldPosition();
	//LookPos.y = 10.0f;

	//_mineCamera->LookPosition(LookPos);

	//_mineCamera->SetWorldPosition(LookPos.x+cos(rotateY)*10.0f, LookPos.y + 5.0f, LookPos.z + sin(rotateY)*10.0f);
	//_mineCamera->SetWorldPosition(LookPos.x, LookPos.y + 10.0f,- 10.0f);
	//_mainCamera->SetRotateWorld(0.0f,rotateY,0.0f);


	//_mineCamera->updateCamToDevice();

	_testEmitter->update();
	//_testPS->update();
}

void particleTest10::render(void)
{
	//_testSkill->render();
	//_target->RenderGimozo();
	
	//_player->RenderGimozo();

	_testEmitter->render();

	//_testPS->render();
}
