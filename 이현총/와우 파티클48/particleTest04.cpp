#include "stdafx.h"
#include "particleTest04.h"


HRESULT particleTest04::init(void)
{
	_player = new transform;
	_target = new transform;

	_testSkill = new skill00;
	_testSkill->setPlayer(_player);
	_testSkill->setTarget(_target);
	_testSkill->init();
	
	_testSkill01 = new skill00_01;
	_testSkill01->setPlayer(_player);
	_testSkill01->init();

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

void particleTest04::release(void)
{
	SAFE_DELETE(_testPS);
}

void particleTest04::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_testSkill01->Start();
		//_testSkill->Start();
	}

	//_target->DefaultMyControl(_timeDelta);
	_player->DefaultMyControl(_timeDelta);

	_testSkill01->update();
	//_testSkill->update();
	
	//_testPS->update();
}

void particleTest04::render(void)
{
	//_testSkill->render();
	//_target->RenderGimozo();
	_player->RenderGimozo();
	_testSkill01->render();
	
	//_testPS->render();
}
