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
	/*testSkill00 = new skBoss_GrandMagic;
	testSkill00->setSkillPosTrans(_player);
	testSkill00->setSkillDirTrans(_player);
	testSkill00->init();*/

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

	_mainCamera->DefaultControl(_timeDelta, 0.0f);
	_mainCamera->updateCamToDevice();


	if (KEYMANAGER->isToggleKey(VK_SPACE))
	{
		_target->DefaultMyControl(_timeDelta);
	}
	else
	{
		_player->DefaultMyControl(_timeDelta);
	}
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

	
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SKM->findSK("���̾����")->setSkillPosTrans(_player);
		SKM->findSK("���̾����")->setSkillDirTrans(_player);
		SKM->findSK("���̾����")->setOneTargetTrans(_target);
		SKM->findSK("���̾����")->Start();
	}

	if (KEYMANAGER->isOnceKeyDown('4'))
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
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		SKM->findSK("��")->setSkillPosTrans(_player);
		SKM->findSK("��")->setSkillDirTrans(_player);
		SKM->findSK("��")->setOneTargetTrans(_target);
		SKM->findSK("��")->Start();

	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		SKM->findSK("����_������")->setSkillPosTrans(_player);
		SKM->findSK("����_������")->setSkillDirTrans(_player);
		SKM->findSK("����_������")->setOneTargetTrans(_target);
		SKM->findSK("����_������")->Start();
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		SKM->findSK("�븶��")->setSkillPosTrans(_player);
		SKM->findSK("�븶��")->setSkillDirTrans(_player);
		SKM->findSK("�븶��")->setOneTargetTrans(_target);
		SKM->findSK("�븶��")->Start();

	}
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		SKM->findSK("������ź")->setSkillPosTrans(_player);
		SKM->findSK("������ź")->setSkillDirTrans(_player);
		SKM->findSK("������ź")->setOneTargetTrans(_target);
		SKM->findSK("������ź")->Start();

	}

	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		EFFECT->findEffect("����_����")->setLimitTime(5.0f);
		EFFECT->findEffect("����_����")->Start(_player);
		//EFFECT->findEffect("����")->setLimitTime(2.0f);
		//EFFECT->findEffect("����")->Start(_player);
		//EFFECT->findEffect("����")->Start(_target);

	}

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		SKM->findSK("�ϴ���_���")->setSkillPosTrans(_player);
		SKM->findSK("�ϴ���_���")->setSkillDirTrans(_player);
		SKM->findSK("�ϴ���_���")->setOneTargetTrans(_target);
		SKM->findSK("�ϴ���_���")->Start();
		//EFFECT->findEffect("����")->setLimitTime(2.0f);
		//EFFECT->findEffect("����")->Start(_player);
		//EFFECT->findEffect("����")->Start(_target);

	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		/*SKM->findSK("������")->setSkillPosTrans(_player);
		SKM->findSK("������")->setSkillDirTrans(_player);
		SKM->findSK("������")->setOneTargetTrans(_target);
		SKM->findSK("������")->Start();*/

		EFFECT->findEffect("�չ����")->setLimitTime(5.0f);
		EFFECT->findEffect("�չ����")->Start(_player);

	}


	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		SKM->findSK("ȭ������")->setSkillPosTrans(_player);
		SKM->findSK("ȭ������")->setSkillDirTrans(_player);
		SKM->findSK("ȭ������")->setOneTargetTrans(_target);
		SKM->findSK("ȭ������")->Start();

		//EFFECT->findEffect("����")->setLimitTime(2.0f);
		//EFFECT->findEffect("����")->Start(_player);
		//EFFECT->findEffect("����")->Start(_target);
	}


	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		SKM->findSK("������_������")->setSkillPosTrans(_player);
		SKM->findSK("������_������")->setSkillDirTrans(_player);
		SKM->findSK("������_������")->setOneTargetTrans(_target);
		SKM->findSK("������_������")->Start();
	}

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		SKM->findSK("�Ҳɱ�")->setSkillPosTrans(_player);
		SKM->findSK("�Ҳɱ�")->setSkillDirTrans(_player);
		SKM->findSK("�Ҳɱ�")->setOneTargetTrans(_target);
		SKM->findSK("�Ҳɱ�")->Start();
	}

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		SKM->findSK("�극��")->setSkillPosTrans(_player);
		SKM->findSK("�극��")->setSkillDirTrans(_player);
		//SKM->findSK("�Ҳɱ�")->setOneTargetTrans(_target);
		SKM->findSK("�극��")->Start();
	}

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		SKM->findSK("������")->setSkillPosTrans(_player);
		SKM->findSK("������")->setSkillDirTrans(_player);
		//SKM->findSK("�Ҳɱ�")->setOneTargetTrans(_target);
		SKM->findSK("������")->Start();
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		SKM->findSK("����")->setSkillPosTrans(_player);
		SKM->findSK("����")->setSkillDirTrans(_player);
		SKM->findSK("����")->Start();
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		SKM->findSK("���ۺ���")->setSkillPosTrans(_player);
		SKM->findSK("���ۺ���")->setSkillDirTrans(_player);
		SKM->findSK("���ۺ���")->Start();
	}

	//if (KEYMANAGER->isOnceKeyDown('P'))
	//{
	//	SCENEMANAGER->changeScene("gameSceneOne");//gameSceneTwo
	//}
	//if (KEYMANAGER->isOnceKeyDown('L'))
	//{
	//	SCENEMANAGER->changeScene("gameSceneTwo");//gameSceneTwo
	//}

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

