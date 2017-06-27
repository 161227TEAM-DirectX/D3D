#include "stdafx.h"
#include "particleTest05.h"


HRESULT particleTest05::init(void)
{
	_player = new dx::transform;
	_target = new dx::transform;

	_testSkill = new skill00;
	_testSkill->setPlayer(_player);
	_testSkill->setTarget(_target);
	_testSkill->init();
	
	_testSkill02 = new skill00_02;
	_testSkill02->setPlayer(_player);
	_testSkill02->init();

	//_set00 = new particleSet00;
	//_set00->init();
	
	_mainCamera = new camera;

	//PSM->initPS(_testPS, "터짐");
	//D3DXMatrixIdentity()
	//시스템 초기화
	//_testPS = new dxParticleSystem;
	//_testPS = PSM->findPS("구슬");
	//_testPS = _set00->getPS();
	
	//_testPS->init();
	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("ParticleResources/Texture/Light02.png", 1, 1.5f);


	return S_OK;
}

void particleTest05::release(void)
{
	SAFE_DELETE(_testPS);
}

void particleTest05::update(void)
{

	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();_mainCamera->updateCamToDevice();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_testSkill02->Start();
		//_testSkill->Start();
	}

	//_target->DefaultMyControl(_timeDelta);
	_player->DefaultMyControl(_timeDelta);

	_testSkill02->update();
	//_testSkill->update();
	
	//_testPS->update();
}

void particleTest05::render(void)
{
	//_testSkill->render();
	//_target->RenderGimozo();
	_player->RenderGimozo();
	_testSkill02->render();
	
	//_testPS->render();
}
