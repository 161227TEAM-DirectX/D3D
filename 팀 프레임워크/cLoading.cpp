#include "stdafx.h"
#include "cLoading.h"

cLoading::cLoading()
{	
}


cLoading::~cLoading()
{	
}

void cLoading::Init()
{
	//========================================================================
	//�⺻ ���� �ʱ�ȭ
	//========================================================================
	SetRandomSeed();					//�����õ� �ʱ�ȭ
	CreateDevice();						//����̽� �ʱ�ȭ
	


	//========================================================================
	//�Ŵ��� �ʱ�ȭ
	//========================================================================
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
	SOUNDMANAGER->init();

	

	//========================================================================
	//���ӿ� ����� ���ϰ�� ���
	//========================================================================
	FxRegist();
	HeightRegist();
	TileRegist();
	SplatRegist();
	BrushRegist();
}

void cLoading::Destroy()
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

	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	//����̽� ����
	ReleaseDevice();
}




void cLoading::FxRegist()
{
	FILEPATH_MANAGER->AddFilepath("FX_�����⺻", "Resource/Maptool/Shaders/TerrainBase.fx");
}

void cLoading::HeightRegist()
{
	FILEPATH_MANAGER->AddFilepath("���̸�_1", "Resource/Maptool/Textures/RAW/1.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_2", "Resource/Maptool/Textures/RAW/2.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_3", "Resource/Maptool/Textures/RAW/3.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_4", "Resource/Maptool/Textures/RAW/4.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_5", "Resource/Maptool/Textures/RAW/5.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_6", "Resource/Maptool/Textures/RAW/6.png");
}

void cLoading::TileRegist()
{
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_1", "Resource/Maptool/Textures/Tile/1.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_2", "Resource/Maptool/Textures/Tile/2.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_3", "Resource/Maptool/Textures/Tile/3.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_4", "Resource/Maptool/Textures/Tile/4.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_5", "Resource/Maptool/Textures/Tile/5.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_6", "Resource/Maptool/Textures/Tile/6.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_7", "Resource/Maptool/Textures/Tile/13.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_8", "Resource/Maptool/Textures/Tile/12.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_9", "Resource/Maptool/Textures/Tile/21.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_10", "Resource/Maptool/Textures/Tile/10.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_11", "Resource/Maptool/Textures/Tile/11.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_12", "Resource/Maptool/Textures/Tile/12.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_13", "Resource/Maptool/Textures/Tile/13.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_14", "Resource/Maptool/Textures/Tile/14.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_15", "Resource/Maptool/Textures/Tile/15.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_16", "Resource/Maptool/Textures/Tile/8.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_17", "Resource/Maptool/Textures/Tile/3.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_18", "Resource/Maptool/Textures/Tile/18.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_19", "Resource/Maptool/Textures/Tile/19.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_20", "Resource/Maptool/Textures/Tile/20.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_21", "Resource/Maptool/Textures/Tile/21.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_22", "Resource/Maptool/Textures/Tile/22.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_23", "Resource/Maptool/Textures/Tile/14.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_24", "Resource/Maptool/Textures/Tile/16.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_25", "Resource/Maptool/Textures/Tile/4.png");
}

void cLoading::SplatRegist()
{
	FILEPATH_MANAGER->AddFilepath("���÷�_1", "Resource/Maptool/Textures/Splat/1.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_2", "Resource/Maptool/Textures/Splat/2.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_3", "Resource/Maptool/Textures/Splat/3.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_4", "Resource/Maptool/Textures/Splat/4.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_5", "Resource/Maptool/Textures/Splat/5.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_6", "Resource/Maptool/Textures/Splat/6.png");
}

void cLoading::BrushRegist()
{
	FILEPATH_MANAGER->AddFilepath("�귯��_brush00", "Resource/Maptool/Textures/Brush/brush00.png");
	FILEPATH_MANAGER->AddFilepath("�귯��_brush01", "Resource/Maptool/Textures/Brush/brush01.png");
}

