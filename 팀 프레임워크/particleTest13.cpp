#include "stdafx.h"
#include "particleTest13.h"

HRESULT particleTest13::init()
{
	_player = new dx::transform;
	_target = new dx::transform;
	_manyTarget = new dx::transform[10];

	//testSkill00 = new skPlayer_Heal;
	//testSkill00 = new skPlayer_MagicShoot;
	//testSkill00 = new skBoss_Shouting;
	testSkill00 = new skBoss_GrandMagic;
	testSkill00->setSkillPosTrans(_player);
	testSkill00->setSkillDirTrans(_player);
	testSkill00->init();

	_mainCamera = new camera;
	

	_target->SetWorldPosition(RandomFloatRange(-5.0f, 5.0f), RandomFloatRange(0.0f, 3.0f), RandomFloatRange(5.0f, 8.0f));

	for (int i = 0; i < 10; i++)
	{
		_manyTarget[i].SetWorldPosition(RandomFloatRange(-5.0f, 5.0f), RandomFloatRange(0.0f, 3.0f), RandomFloatRange(5.0f, 8.0f));
	}



	return S_OK;

}

void particleTest13::release()
{
}

void particleTest13::update()
{

	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();_mainCamera->updateCamToDevice();

	_player->DefaultMyControl(_timeDelta);
	
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SKM->findSK("��������")->setSkillPosTrans(_player);
		SKM->findSK("��������")->setSkillDirTrans(_player);
		SKM->findSK("��������")->setOneTargetTrans(_target);
		SKM->findSK("��������")->Start();

		/*SKM->findSK("����Ʈ")->setSkillPosTrans(_player);
		SKM->findSK("����Ʈ")->setSkillDirTrans(_player);
		SKM->findSK("����Ʈ")->SetManyTargetTrans(_manyTarget, 10);
		SKM->findSK("����Ʈ")->Start();*/


		//testSkill00->SetManyTargetTrans(_target,0);
		//testSkill00->setOneTargetTrans(_target);
		//testSkill00->Start();
		
		
		/*EFFECT->findEffect("����")->setLimitTime(5.0f);
		EFFECT->findEffect("����")->setPositoin(&_player->GetWorldPosition());
		EFFECT->findEffect("����")->setPositoin(&_target->GetWorldPosition());
		EFFECT->findEffect("����")->Start();*/
		//EFFECT->findEffect("����")->setLimitTime(2.0f);
		//EFFECT->findEffect("����")->Start(_player);
		//EFFECT->findEffect("����")->Start(_target);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SKM->findSK("����Ʈ��")->setSkillPosTrans(_player);
		SKM->findSK("����Ʈ��")->setSkillDirTrans(_player);
		SKM->findSK("����Ʈ��")->setOneTargetTrans(_target);
		SKM->findSK("����Ʈ��")->Start();

		/*SKM->findSK("����Ʈ")->setSkillPosTrans(_player);
		SKM->findSK("����Ʈ")->setSkillDirTrans(_player);
		SKM->findSK("����Ʈ")->SetManyTargetTrans(_manyTarget, 10);
		SKM->findSK("����Ʈ")->Start();*/


		//testSkill00->SetManyTargetTrans(_target,0);
		//testSkill00->setOneTargetTrans(_target);
		//testSkill00->Start();


		/*EFFECT->findEffect("����")->setLimitTime(5.0f);
		EFFECT->findEffect("����")->setPositoin(&_player->GetWorldPosition());
		EFFECT->findEffect("����")->setPositoin(&_target->GetWorldPosition());
		EFFECT->findEffect("����")->Start();*/
		//EFFECT->findEffect("����")->setLimitTime(2.0f);
		//EFFECT->findEffect("����")->Start(_player);
		//EFFECT->findEffect("����")->Start(_target);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SKM->findSK("���̾����")->setSkillPosTrans(_player);
		SKM->findSK("���̾����")->setSkillDirTrans(_player);
		SKM->findSK("���̾����")->setOneTargetTrans(_target);
		SKM->findSK("���̾����")->Start();
	}

	//testSkill00->update();

}

void particleTest13::render()
{
	_player->RenderGimozo();
	_target->RenderGimozo();


	//testSkill00->render();

	for (int i = 0; i < 10; i++)
	{
		//_manyTarget[i].RenderGimozo();
	}

	
}

