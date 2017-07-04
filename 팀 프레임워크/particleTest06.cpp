#include "stdafx.h"
#include "particleTest06.h"


HRESULT particleTest06::init(void)
{
	_mainCamera = new camera;

	_player = new dx::transform;
	_target = new dx::transform;

	_testSkill = new skill00;
	_testSkill->setPlayer(_player);
	_testSkill->setTarget(_target);
	_testSkill->init();
	

	_testSkill03 = new skill00_03;
	_testSkill03->setPlayer(_player);
	_testSkill03->init();

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


	return S_OK;
}

void particleTest06::release(void)
{
	SAFE_DELETE(_testPS);
}

void particleTest06::update(void)
{
	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();


	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_testSkill03->Start();
		//_testSkill->Start();
	}

	//_target->DefaultMyControl(_timeDelta);
	_player->DefaultMyControl(_timeDelta);

	_testSkill03->update();
	//_testSkill->update();
	
	//_testPS->update();
}

void particleTest06::render(void)
{
	//_testSkill->render();
	//_target->RenderGimozo();
	_player->RenderGimozo();
	_testSkill03->render();
	
	//_testPS->render();
}
