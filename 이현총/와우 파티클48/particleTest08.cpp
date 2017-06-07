#include "stdafx.h"
#include "particleTest08.h"


HRESULT particleTest08::init(void)
{
	_player = new transform;
	_target = new transform;

	_testPS = new dxParticleSystem;

	_testEmitter = NULL;
	_testEmitter = new dxBoardEmitter;
	//_testEmitter->init("PaticleResources/Texture/magicCircle.png",1,1.0f,1);
	//_testEmitter->init("PaticleResources/Texture/fire00_frame7x7.png", 20, 0.1f, 100);
	_testEmitter->init("PaticleResources/Texture/fire01_frame5x4.png", 20, 0.10f, 100);
	
	_testEmitter->InitRandomPositionX(-10.0f, 10.0f);
	_testEmitter->InitRandomPositionZ(-10.0f, 10.0f);
	//_testEmitter->InitRandomVelocityY(23.5f,38.5f);
	
	_testEmitter->InitRandomSize(1.0f,3.0f);
	_testEmitter->InitRandomSizeEnd(12.0f, 22.0f);
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
	//_testEmitter->init("PaticleResources/Texture/Light02.png", 1, 1.5f);

	

	return S_OK;
}

void particleTest08::release(void)
{
	SAFE_DELETE(_testPS);
}

void particleTest08::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		
	}

	//_target->DefaultMyControl(_timeDelta);
	//_player->DefaultMyControl(_timeDelta);

	_testEmitter->update();
	//_testPS->update();
}

void particleTest08::render(void)
{
	//_testSkill->render();
	//_target->RenderGimozo();
	
	_testEmitter->render();

	//_testPS->render();
}
