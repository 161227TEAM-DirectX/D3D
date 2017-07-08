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
	

	_target->SetWorldPosition(RandomFloatRange(-8.0f, 8.0f), RandomFloatRange(0.0f, 0.0f), RandomFloatRange(5.0f, 15.0f));

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
	_mainCamera->updateCamToDevice();

	_target->DefaultMyControl(_timeDelta);
	
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SKM->findSK("¸ÅÁ÷½¯µå")->setSkillPosTrans(_player);
		SKM->findSK("¸ÅÁ÷½¯µå")->setSkillDirTrans(_player);
		SKM->findSK("¸ÅÁ÷½¯µå")->setOneTargetTrans(_target);
		SKM->findSK("¸ÅÁ÷½¯µå")->Start();

		/*SKM->findSK("ÀÌÆåÆ®")->setSkillPosTrans(_player);
		SKM->findSK("ÀÌÆåÆ®")->setSkillDirTrans(_player);
		SKM->findSK("ÀÌÆåÆ®")->SetManyTargetTrans(_manyTarget, 10);
		SKM->findSK("ÀÌÆåÆ®")->Start();*/


		//testSkill00->SetManyTargetTrans(_target,0);
		//testSkill00->setOneTargetTrans(_target);
		//testSkill00->Start();
		
		
		/*EFFECT->findEffect("½ºÅÏ")->setLimitTime(5.0f);
		EFFECT->findEffect("½ºÅÏ")->setPositoin(&_player->GetWorldPosition());
		EFFECT->findEffect("½ºÅÏ")->setPositoin(&_target->GetWorldPosition());
		EFFECT->findEffect("½ºÅÏ")->Start();*/

		//EFFECT->findEffect("½ºÅÏ")->setLimitTime(2.0f);
		//EFFECT->findEffect("½ºÅÏ")->Start(_player);
		//EFFECT->findEffect("½ºÅÏ")->Start(_target);

	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SKM->findSK("¶óÀÌÆ®´×")->setSkillPosTrans(_player);
		SKM->findSK("¶óÀÌÆ®´×")->setSkillDirTrans(_player);
		SKM->findSK("¶óÀÌÆ®´×")->setOneTargetTrans(_target);
		SKM->findSK("¶óÀÌÆ®´×")->Start();

	
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SKM->findSK("ÆÄÀÌ¾î¸ÅÁ÷")->setSkillPosTrans(_player);
		SKM->findSK("ÆÄÀÌ¾î¸ÅÁ÷")->setSkillDirTrans(_player);
		SKM->findSK("ÆÄÀÌ¾î¸ÅÁ÷")->setOneTargetTrans(_target);
		SKM->findSK("ÆÄÀÌ¾î¸ÅÁ÷")->Start();
	}

	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		SKM->findSK("¸ÅÁ÷½´ÅÍ")->setSkillPosTrans(_player);
		SKM->findSK("¸ÅÁ÷½´ÅÍ")->setSkillDirTrans(_player);
		SKM->findSK("¸ÅÁ÷½´ÅÍ")->setOneTargetTrans(_target);
		SKM->findSK("¸ÅÁ÷½´ÅÍ")->Start();

		/*SKM->findSK("ÀÌÆåÆ®")->setSkillPosTrans(_player);
		SKM->findSK("ÀÌÆåÆ®")->setSkillDirTrans(_player);
		SKM->findSK("ÀÌÆåÆ®")->SetManyTargetTrans(_manyTarget, 10);
		SKM->findSK("ÀÌÆåÆ®")->Start();*/


		//testSkill00->SetManyTargetTrans(_target,0);
		//testSkill00->setOneTargetTrans(_target);
		//testSkill00->Start();


		/*EFFECT->findEffect("½ºÅÏ")->setLimitTime(5.0f);
		EFFECT->findEffect("½ºÅÏ")->setPositoin(&_player->GetWorldPosition());
		EFFECT->findEffect("½ºÅÏ")->setPositoin(&_target->GetWorldPosition());
		EFFECT->findEffect("½ºÅÏ")->Start();*/
		//EFFECT->findEffect("½ºÅÏ")->setLimitTime(2.0f);
		//EFFECT->findEffect("½ºÅÏ")->Start(_player);
		//EFFECT->findEffect("½ºÅÏ")->Start(_target);
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		SKM->findSK("Èú")->setSkillPosTrans(_player);
		SKM->findSK("Èú")->setSkillDirTrans(_player);
		SKM->findSK("Èú")->setOneTargetTrans(_target);
		SKM->findSK("Èú")->Start();

	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		SKM->findSK("»ûº°_¶³±¸±â")->setSkillPosTrans(_player);
		SKM->findSK("»ûº°_¶³±¸±â")->setSkillDirTrans(_player);
		SKM->findSK("»ûº°_¶³±¸±â")->setOneTargetTrans(_target);
		SKM->findSK("»ûº°_¶³±¸±â")->Start();
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		SKM->findSK("´ë¸¶¹ý")->setSkillPosTrans(_player);
		SKM->findSK("´ë¸¶¹ý")->setSkillDirTrans(_player);
		SKM->findSK("´ë¸¶¹ý")->setOneTargetTrans(_target);
		SKM->findSK("´ë¸¶¹ý")->Start();

	}
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		SKM->findSK("¿¡³ÊÁöÅº")->setSkillPosTrans(_player);
		SKM->findSK("¿¡³ÊÁöÅº")->setSkillDirTrans(_player);
		SKM->findSK("¿¡³ÊÁöÅº")->setOneTargetTrans(_target);
		SKM->findSK("¿¡³ÊÁöÅº")->Start();

	}

	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		EFFECT->findEffect("³¯±â_¸ÕÁö")->setLimitTime(5.0f);
		
		EFFECT->findEffect("³¯±â_¸ÕÁö")->Start(_player);
		//EFFECT->findEffect("½ºÅÏ")->setLimitTime(2.0f);
		//EFFECT->findEffect("½ºÅÏ")->Start(_player);
		//EFFECT->findEffect("½ºÅÏ")->Start(_target);

	}

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		SKM->findSK("ÇÏ´ÃÀÇ_´ë°Ë")->setSkillPosTrans(_player);
		SKM->findSK("ÇÏ´ÃÀÇ_´ë°Ë")->setSkillDirTrans(_player);
		SKM->findSK("ÇÏ´ÃÀÇ_´ë°Ë")->setOneTargetTrans(_target);
		SKM->findSK("ÇÏ´ÃÀÇ_´ë°Ë")->Start();
		//EFFECT->findEffect("½ºÅÏ")->setLimitTime(2.0f);
		//EFFECT->findEffect("½ºÅÏ")->Start(_player);
		//EFFECT->findEffect("½ºÅÏ")->Start(_target);

	}

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

