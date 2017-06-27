#include "stdafx.h"
#include "particleTest07.h"


HRESULT particleTest07::init(void)
{
	_player = new dx::transform;
	_target = new dx::transform;

	_testPS = new dxParticleSystem;

	_testEmitter = NULL;
	_testEmitter = new dxPlaneEmitter;
	//_testEmitter->init("ParticleResources/Texture/magicCircle.png",1,1.0f,1);
	_testEmitter->init("ParticleResources/Texture/fire00_frame7x7.png", 50, 0.1f, 50);
	
	_testEmitter->InitRandomPositionX(-10.0f, 10.0f);
	_testEmitter->InitRandomPositionZ(-10.0f, 10.0f);
	_testEmitter->InitRandomVelocityY(2.5f,2.5f);
	
	_testEmitter->InitRandomSize(1.0f,3.0f);
	_testEmitter->InitRandomSizeEnd(8.0f, 12.0f);
	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	_testEmitter->InitRandomAlphaFade(0.1f, 0.1f);

	_testEmitter->InitAnimation(7,7);
	_testEmitter->InitRandomLifeTime(0.8f,1.2f);
	_testEmitter->InitRotateStartAngleY(0.0f, 120.0f);
	//_testEmitter->InitRotateAngleSpeedY(6.0f, 6.0f);

	//_testEmitter->InitConstVH(4.0f,1.0f);


	//_set00 = new particleSet00;
	//_set00->init();
	


	//PSM->initPS(_testPS, "����");
	//D3DXMatrixIdentity()
	//�ý��� �ʱ�ȭ
	//_testPS = new dxParticleSystem;
	//_testPS = PSM->findPS("����");
	//_testPS = _set00->getPS();
	
	//_testPS->init();
	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("ParticleResources/Texture/Light02.png", 1, 1.5f);

	

	return S_OK;
}

void particleTest07::release(void)
{
	SAFE_DELETE(_testPS);
}

void particleTest07::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		
	}

	//_target->DefaultMyControl(_timeDelta);
	//_player->DefaultMyControl(_timeDelta);

	_testEmitter->update();
	//_testPS->update();
}

void particleTest07::render(void)
{
	//_testSkill->render();
	//_target->RenderGimozo();
	
	_testEmitter->render();

	//_testPS->render();
}
