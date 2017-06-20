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
	//���ӿ� ����� ���ϰ�� ���
	//========================================================================
	FxRegist();
	HeightRegist();
	TileRegist();
	SplatRegist();
	BrushRegist();
	SoundRegist();
	ImageRegist();
	AniRegist();
	XMeshRegist();

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
	SOUNDMANAGER->init();				//����Ŵ����ʱ�ȭ

	

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

void cLoading::SoundRegist()
{
	FILEPATH_MANAGER->AddFilepath("�ʵ�", "Sound/FieldBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Sound/BossBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Sound/TownBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Sound/����1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Sound/����1.mp3");
	FILEPATH_MANAGER->AddFilepath("�����Ҹ�", "Sound/�����Ҹ�1.mp3");
}

void cLoading::ImageRegist()
{
	FILEPATH_MANAGER->AddFilepath("�̹���_���ڸ�", "Resource/�̹���/���ڸ�.png");
	FILEPATH_MANAGER->AddFilepath("�̹���_�źϿ�", "Resource/�̹���/�źϿ�.png");
	FILEPATH_MANAGER->AddFilepath("�̹���_�̻��ز�", "Resource/�̹���/�̻��ز�.png");
}

void cLoading::AniRegist()
{
	FILEPATH_MANAGER->AddFilepath("cat", "Resource/�̹���/cat.png");

	FILEPATH_MANAGER->AddFilepath("�ƽ�00", "Resource/�̹���/�ƽ�/output-0.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�01", "Resource/�̹���/�ƽ�/output-1.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�02", "Resource/�̹���/�ƽ�/output-2.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�03", "Resource/�̹���/�ƽ�/output-3.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�04", "Resource/�̹���/�ƽ�/output-4.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�05", "Resource/�̹���/�ƽ�/output-5.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�06", "Resource/�̹���/�ƽ�/output-6.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�07", "Resource/�̹���/�ƽ�/output-7.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�08", "Resource/�̹���/�ƽ�/output-8.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�09", "Resource/�̹���/�ƽ�/output-9.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�10", "Resource/�̹���/�ƽ�/output-10.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�11", "Resource/�̹���/�ƽ�/output-11.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�12", "Resource/�̹���/�ƽ�/output-12.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�13", "Resource/�̹���/�ƽ�/output-13.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�14", "Resource/�̹���/�ƽ�/output-14.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�15", "Resource/�̹���/�ƽ�/output-15.png");

	FILEPATH_MANAGER->AddFilepath("�ƽ�00-2", "Resource/�̹���/�ƽ�2/output-0.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�01-2", "Resource/�̹���/�ƽ�2/output-1.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�02-2", "Resource/�̹���/�ƽ�2/output-2.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�03-2", "Resource/�̹���/�ƽ�2/output-3.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�04-2", "Resource/�̹���/�ƽ�2/output-4.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�05-2", "Resource/�̹���/�ƽ�2/output-5.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�06-2", "Resource/�̹���/�ƽ�2/output-6.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�07-2", "Resource/�̹���/�ƽ�2/output-7.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�08-2", "Resource/�̹���/�ƽ�2/output-8.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�09-2", "Resource/�̹���/�ƽ�2/output-9.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�10-2", "Resource/�̹���/�ƽ�2/output-10.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�11-2", "Resource/�̹���/�ƽ�2/output-11.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�12-2", "Resource/�̹���/�ƽ�2/output-12.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�13-2", "Resource/�̹���/�ƽ�2/output-13.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�14-2", "Resource/�̹���/�ƽ�2/output-14.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�15-2", "Resource/�̹���/�ƽ�2/output-15.png");

	FILEPATH_MANAGER->AddFilepath("�ƽ�00-3", "Resource/�̹���/�ƽ�3/output-0.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�01-3", "Resource/�̹���/�ƽ�3/output-1.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�02-3", "Resource/�̹���/�ƽ�3/output-2.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�03-3", "Resource/�̹���/�ƽ�3/output-3.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�04-3", "Resource/�̹���/�ƽ�3/output-4.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�05-3", "Resource/�̹���/�ƽ�3/output-5.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�06-3", "Resource/�̹���/�ƽ�3/output-6.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�07-3", "Resource/�̹���/�ƽ�3/output-7.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�08-3", "Resource/�̹���/�ƽ�3/output-8.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�09-3", "Resource/�̹���/�ƽ�3/output-9.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�10-3", "Resource/�̹���/�ƽ�3/output-10.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�11-3", "Resource/�̹���/�ƽ�3/output-11.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�12-3", "Resource/�̹���/�ƽ�3/output-12.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�13-3", "Resource/�̹���/�ƽ�3/output-13.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�14-3", "Resource/�̹���/�ƽ�3/output-14.png");
	FILEPATH_MANAGER->AddFilepath("�ƽ�15-3", "Resource/�̹���/�ƽ�3/output-15.png");
}

void cLoading::XMeshRegist()
{
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob000", "Resource/Maptool/Meshes/stormTown1/1.build/1/1.X");
}
