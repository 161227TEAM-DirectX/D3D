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
		SKM->findSK("매직쉴드")->setSkillPosTrans(_player);
		SKM->findSK("매직쉴드")->setSkillDirTrans(_player);
		SKM->findSK("매직쉴드")->setOneTargetTrans(_target);
		SKM->findSK("매직쉴드")->Start();

		/*SKM->findSK("이펙트")->setSkillPosTrans(_player);
		SKM->findSK("이펙트")->setSkillDirTrans(_player);
		SKM->findSK("이펙트")->SetManyTargetTrans(_manyTarget, 10);
		SKM->findSK("이펙트")->Start();*/


		//testSkill00->SetManyTargetTrans(_target,0);
		//testSkill00->setOneTargetTrans(_target);
		//testSkill00->Start();
		
		
		/*EFFECT->findEffect("스턴")->setLimitTime(5.0f);
		EFFECT->findEffect("스턴")->setPositoin(&_player->GetWorldPosition());
		EFFECT->findEffect("스턴")->setPositoin(&_target->GetWorldPosition());
		EFFECT->findEffect("스턴")->Start();*/
		//EFFECT->findEffect("스턴")->setLimitTime(2.0f);
		//EFFECT->findEffect("스턴")->Start(_player);
		//EFFECT->findEffect("스턴")->Start(_target);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SKM->findSK("라이트닝")->setSkillPosTrans(_player);
		SKM->findSK("라이트닝")->setSkillDirTrans(_player);
		SKM->findSK("라이트닝")->setOneTargetTrans(_target);
		SKM->findSK("라이트닝")->Start();

		/*SKM->findSK("이펙트")->setSkillPosTrans(_player);
		SKM->findSK("이펙트")->setSkillDirTrans(_player);
		SKM->findSK("이펙트")->SetManyTargetTrans(_manyTarget, 10);
		SKM->findSK("이펙트")->Start();*/


		//testSkill00->SetManyTargetTrans(_target,0);
		//testSkill00->setOneTargetTrans(_target);
		//testSkill00->Start();


		/*EFFECT->findEffect("스턴")->setLimitTime(5.0f);
		EFFECT->findEffect("스턴")->setPositoin(&_player->GetWorldPosition());
		EFFECT->findEffect("스턴")->setPositoin(&_target->GetWorldPosition());
		EFFECT->findEffect("스턴")->Start();*/
		//EFFECT->findEffect("스턴")->setLimitTime(2.0f);
		//EFFECT->findEffect("스턴")->Start(_player);
		//EFFECT->findEffect("스턴")->Start(_target);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SKM->findSK("파이어매직")->setSkillPosTrans(_player);
		SKM->findSK("파이어매직")->setSkillDirTrans(_player);
		SKM->findSK("파이어매직")->setOneTargetTrans(_target);
		SKM->findSK("파이어매직")->Start();
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

