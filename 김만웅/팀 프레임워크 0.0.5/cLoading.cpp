#include "stdafx.h"
#include "cLoading.h"


cLoading::cLoading()
{
	SetRandomSeed();					//�����õ� �ʱ�ȭ
	CreateDevice();						//����̽� �ʱ�ȭ
	KEYMANAGER->init();					//Ű�Ŵ��� �ʱ�ȭ
	TIMEMANAGER->init();				//Ÿ�ӸŴ��� �ʱ�ȭ
	SCENEMANAGER->init();				//���Ŵ��� �ʱ�ȭ
	FONTMANAGER->init();				//��Ʈ�Ŵ��� �ʱ�ȭ
	GIZMOMANAGER->init();				//�����Ŵ��� �ʱ�ȭ
	RM_TEXTURE->init();					//RM�ؽ��� �ʱ�ȭ
	RM_SHADERFX->init();				//RM���̴�FX �ʱ�ȭ
	RM_XMESH->init();					//RM����ƽX�޽� �ʱ�ȭ
	RM_SKINNED->init();					//RM��Ų��X�޽� �ʱ�ȭ
	PHYSICSMANAGER->init();				//�������Ŵ��� �ʱ�ȭ
	SPRITEMANAGER->init();				//��������Ʈ�Ŵ��� �ʱ�ȭ
	PSM->ParticleSystemSetInit();		//��ƼŬ�ý��۸Ŵ��� �ʱ�ȭ
}


cLoading::~cLoading()
{
	//Ű�Ŵ��� �̱��� ����
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	//Ÿ�ӸŴ��� �̱��� ����
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	//���Ŵ��� �̱��� ����
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	//��Ʈ�Ŵ��� �̱��� ����
	FONTMANAGER->release();
	FONTMANAGER->releaseSingleton();
	//�����Ŵ��� �̱��� ����
	GIZMOMANAGER->release();
	GIZMOMANAGER->releaseSingleton();
	//���ҽ��Ŵ��� �̱��� ����
	RM_TEXTURE->clearResource();
	RM_TEXTURE->releaseSingleton();
	RM_SHADERFX->clearResource();
	RM_SHADERFX->releaseSingleton();
	RM_XMESH->clearResource();
	RM_XMESH->releaseSingleton();
	RM_SKINNED->clearResource();
	RM_SKINNED->releaseSingleton();
	//�������Ŵ��� �̱��� ����
	PHYSICSMANAGER->release();
	PHYSICSMANAGER->releaseSingleton();
	//��������Ʈ�Ŵ��� �̱��� ����
	SPRITEMANAGER->release();
	SPRITEMANAGER->releaseSingleton();
	//��ƼŬ�ý��۸Ŵ��� �̱��� ����
	PSM->ParticleSystemSetRelease();
	PSM->releaseSingleton();

	//����̽� ����
	ReleaseDevice();
}
