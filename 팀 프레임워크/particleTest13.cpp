#include "stdafx.h"
#include "particleTest13.h"

void particleTest13::Setup()
{
	_player = new dx::transform;
	_target = new dx::transform[5];

	testSkill00 = new SK_Effect00;
	testSkill00->setPlayer(_player);
	testSkill00->init();

	_mainCamera = new camera;

	for (int i = 0; i < 5; i++)
	{
		_target[i].SetWorldPosition(RandomFloatRange(-5.0f, 5.0f), RandomFloatRange(0.0f, 3.0f), RandomFloatRange(4.0f, 6.0f));
	}

	testSkill00->setPlayer(_player);
	//testSkill00->setAllTar(_target);


	//_skm = new dxSkillManager;
	//_skm->addSK("스킬00", testSkill00);

	//_skm->findSK("스킬00")->

}

void particleTest13::Update()
{

	//_mainCamera->DefaultControl(_timeDelta);
	//_mainCamera->updateCamToDevice();_mainCamera->updateCamToDevice();

	_player->DefaultMyControl(_timeDelta);
	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		testSkill00->Start();
	}



	testSkill00->update();

}

void particleTest13::Render()
{
	_player->RenderGimozo();

	testSkill00->render();

	for (int i = 0; i < 5; i++)
	{
		_target[i].RenderGimozo();
	}

}
