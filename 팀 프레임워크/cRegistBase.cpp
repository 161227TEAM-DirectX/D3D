#include "stdafx.h"
#include "cRegistBase.h"

cRegistBase::cRegistBase()
{	
}


cRegistBase::~cRegistBase()
{	
}

void cRegistBase::Init()
{
	//========================================================================
	//�⺻ ���� �ʱ�ȭ
	//========================================================================
	SetRandomSeed();					//�����õ� �ʱ�ȭ
	CreateDevice();						//����̽� �ʱ�ȭ
	


	//========================================================================
	//���ӿ� ����� ���ϰ�� ���
	//========================================================================
	FxRegist();							//Fx ��� ���
	HeightRegist();						//���̸� ��� ���
	TileRegist();						//Ÿ�ϸ� ��� ���
	SplatRegist();						//���÷� ��� ���
	BrushRegist();						//�귯�� ��� ���
	SoundRegist();						//���� ��� ���
	UIRegist();							//UI ��� ���
	AniRegist();						//�ִϸ��̼�(�̹���) ��� ���
	XMeshStaticRegist();				//X�޽�����ƽ ��� ���
	XMeshSkinnedRegist();				//X�޽���Ű�� ��� ���



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
	PSM->ParticleSystemSetInit();		//��ƼŬ�ý���_�Ŵ��� �ʱ�ȭ
	PTM->LoadImgInit();					//��ƼŬ�ؽ���_�Ŵ��� �ʱ�ȭ
	SOUNDMANAGER->init();				//����Ŵ����ʱ�ȭ

	

}

void cRegistBase::Destroy()
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
	//��ƼŬ�ý��۸Ŵ��� �̱��� ����
	//PTM->ParticleSystemSetRelease();
	PTM->releaseSingleton();

	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	//����̽� ����
	ReleaseDevice();
}



void cRegistBase::FxRegist()
{
	FILEPATH_MANAGER->AddFilepath("FX_�����⺻", "Resource/Maptool/Shaders/TerrainBase.fx");
}



void cRegistBase::HeightRegist()
{
	FILEPATH_MANAGER->AddFilepath("���̸�_1", "Resource/Maptool/Textures/RAW/1.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_2", "Resource/Maptool/Textures/RAW/2.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_3", "Resource/Maptool/Textures/RAW/3.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_4", "Resource/Maptool/Textures/RAW/4.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_5", "Resource/Maptool/Textures/RAW/5.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_6", "Resource/Maptool/Textures/RAW/6.png");
}



void cRegistBase::TileRegist()
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



void cRegistBase::SplatRegist()
{
	FILEPATH_MANAGER->AddFilepath("���÷�_1", "Resource/Maptool/Textures/Splat/1.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_2", "Resource/Maptool/Textures/Splat/2.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_3", "Resource/Maptool/Textures/Splat/3.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_4", "Resource/Maptool/Textures/Splat/4.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_5", "Resource/Maptool/Textures/Splat/5.png");
	FILEPATH_MANAGER->AddFilepath("���÷�_6", "Resource/Maptool/Textures/Splat/6.png");
}



void cRegistBase::BrushRegist()
{
	FILEPATH_MANAGER->AddFilepath("�귯��_brush00", "Resource/Maptool/Textures/Brush/brush00.png");
	FILEPATH_MANAGER->AddFilepath("�귯��_brush01", "Resource/Maptool/Textures/Brush/brush01.png");
}



void cRegistBase::SoundRegist()
{
	FILEPATH_MANAGER->AddFilepath("�ʵ�", "Sound/FieldBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Sound/BossBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Sound/TownBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Sound/����1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Sound/����1.mp3");
	FILEPATH_MANAGER->AddFilepath("�����Ҹ�", "Sound/�����Ҹ�1.mp3");
}



void cRegistBase::UIRegist()
{
	FILEPATH_MANAGER->AddFilepath("UI_�ε�ȭ��", "Resource/UI/�ε�ȭ��.png");
	FILEPATH_MANAGER->AddFilepath("UI_����ȭ��", "Resource/UI/����ȭ��.png");
	FILEPATH_MANAGER->AddFilepath("UI_���۹�ư����", "Resource/UI/���۹�ư_����.png");
	FILEPATH_MANAGER->AddFilepath("UI_���۹�ư����", "Resource/UI/���۹�ư_����.png");
}



void cRegistBase::AniRegist()
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

void cRegistBase::XMeshStaticRegist()
{
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob000", "Resource/Maptool/Meshes/stormTown1/1.build/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob001", "Resource/Maptool/Meshes/stormTown1/1.build/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob002", "Resource/Maptool/Meshes/stormTown1/1.build/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob003", "Resource/Maptool/Meshes/stormTown1/1.build/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob004", "Resource/Maptool/Meshes/stormTown1/1.build/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob005", "Resource/Maptool/Meshes/stormTown1/1.build/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob006", "Resource/Maptool/Meshes/stormTown1/1.build/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob007", "Resource/Maptool/Meshes/stormTown1/1.build/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob008", "Resource/Maptool/Meshes/stormTown1/1.build/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob009", "Resource/Maptool/Meshes/stormTown1/1.build/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob010", "Resource/Maptool/Meshes/stormTown1/1.build/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob011", "Resource/Maptool/Meshes/stormTown1/1.build/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob012", "Resource/Maptool/Meshes/stormTown1/1.build/13/13.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob013", "Resource/Maptool/Meshes/stormTown1/1.build/14/14.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob014", "Resource/Maptool/Meshes/stormTown1/1.build/15/15.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob015", "Resource/Maptool/Meshes/stormTown1/1.build/16/16.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob017", "Resource/Maptool/Meshes/stormTown1/2.townfence/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob018", "Resource/Maptool/Meshes/stormTown1/2.townfence/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob019", "Resource/Maptool/Meshes/stormTown1/2.townfence/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob020", "Resource/Maptool/Meshes/stormTown1/2.townfence/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob021", "Resource/Maptool/Meshes/stormTown1/2.townfence/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob022", "Resource/Maptool/Meshes/stormTown1/2.townfence/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob023", "Resource/Maptool/Meshes/stormTown1/2.townfence/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob024", "Resource/Maptool/Meshes/stormTown1/2.townfence/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob025", "Resource/Maptool/Meshes/stormTown1/2.townfence/9/9.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob026", "Resource/Maptool/Meshes/stormTown1/3.tree/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob027", "Resource/Maptool/Meshes/stormTown1/3.tree/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob028", "Resource/Maptool/Meshes/stormTown1/3.tree/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob029", "Resource/Maptool/Meshes/stormTown1/3.tree/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob030", "Resource/Maptool/Meshes/stormTown1/3.tree/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob031", "Resource/Maptool/Meshes/stormTown1/3.tree/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob032", "Resource/Maptool/Meshes/stormTown1/3.tree/7/7.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob034", "Resource/Maptool/Meshes/stormTown1/4.townObject/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob035", "Resource/Maptool/Meshes/stormTown1/4.townObject/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob036", "Resource/Maptool/Meshes/stormTown1/4.townObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob037", "Resource/Maptool/Meshes/stormTown1/4.townObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob038", "Resource/Maptool/Meshes/stormTown1/4.townObject/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob039", "Resource/Maptool/Meshes/stormTown1/4.townObject/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob040", "Resource/Maptool/Meshes/stormTown1/4.townObject/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob041", "Resource/Maptool/Meshes/stormTown1/4.townObject/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob042", "Resource/Maptool/Meshes/stormTown1/4.townObject/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob043", "Resource/Maptool/Meshes/stormTown1/4.townObject/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob044", "Resource/Maptool/Meshes/stormTown1/4.townObject/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob045", "Resource/Maptool/Meshes/stormTown1/4.townObject/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob046", "Resource/Maptool/Meshes/stormTown1/4.townObject/13/13.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob047", "Resource/Maptool/Meshes/stormTown1/4.townObject/14/14.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob048", "Resource/Maptool/Meshes/stormTown1/4.townObject/15/15.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob050", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob051", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob052", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob053", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob054", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob055", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob056", "Resource/Maptool/Meshes/stormTown2/6.boxObject/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob057", "Resource/Maptool/Meshes/stormTown2/6.boxObject/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob058", "Resource/Maptool/Meshes/stormTown2/6.boxObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob059", "Resource/Maptool/Meshes/stormTown2/6.boxObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob060", "Resource/Maptool/Meshes/stormTown2/6.boxObject/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob061", "Resource/Maptool/Meshes/stormTown2/6.boxObject/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob062", "Resource/Maptool/Meshes/stormTown2/7.planterBox/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob063", "Resource/Maptool/Meshes/stormTown2/7.planterBox/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob064", "Resource/Maptool/Meshes/stormTown2/7.planterBox/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob065", "Resource/Maptool/Meshes/stormTown2/7.planterBox/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob066", "Resource/Maptool/Meshes/stormTown2/7.planterBox/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob067", "Resource/Maptool/Meshes/stormTown2/7.planterBox/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob068", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob069", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob070", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob071", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob072", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob073", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob074", "Resource/Maptool/Meshes/stormTown2/9.shopsign/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob075", "Resource/Maptool/Meshes/stormTown2/9.shopsign/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob076", "Resource/Maptool/Meshes/stormTown2/9.shopsign/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob077", "Resource/Maptool/Meshes/stormTown2/9.shopsign/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob078", "Resource/Maptool/Meshes/stormTown2/9.shopsign/5/5.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob079", "Resource/Maptool/Meshes/stormTown2/10.lowWall/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob080", "Resource/Maptool/Meshes/stormTown2/10.lowWall/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob081", "Resource/Maptool/Meshes/stormTown2/10.lowWall/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob082", "Resource/Maptool/Meshes/stormTown2/10.lowWall/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob083", "Resource/Maptool/Meshes/stormTown2/10.lowWall/5/5.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob084", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob085", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob086", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob087", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob088", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob089", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob090", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob091", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob092", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob093", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob094", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob095", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob096", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/13/13.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob097", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/14/14.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob098", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob099", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob100", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob101", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob102", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob103", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob104", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob105", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob106", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob107", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob108", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob109", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob110", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/13/13.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob111", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/14/14.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob112", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob113", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob114", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob115", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob116", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob117", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob118", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob119", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob120", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob121", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/10/10.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob122", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob123", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob124", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob125", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob126", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob127", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob128", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob129", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob130", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob131", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob132", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob133", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob134", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob135", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob136", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/9/9.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob137", "Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob138", "Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob139", "Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob140", "Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/4/4.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob141", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob142", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob143", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob144", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob145", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob146", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob147", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob148", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob149", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob150", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob151", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/11/11.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob152", "Resource/Maptool/Meshes/piramid/1.piramidBuild/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob153", "Resource/Maptool/Meshes/piramid/1.piramidBuild/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob154", "Resource/Maptool/Meshes/piramid/1.piramidBuild/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob155", "Resource/Maptool/Meshes/piramid/1.piramidBuild/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob156", "Resource/Maptool/Meshes/piramid/1.piramidBuild/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob157", "Resource/Maptool/Meshes/piramid/1.piramidBuild/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob158", "Resource/Maptool/Meshes/piramid/1.piramidBuild/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob159", "Resource/Maptool/Meshes/piramid/1.piramidBuild/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob160", "Resource/Maptool/Meshes/piramid/1.piramidBuild/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob161", "Resource/Maptool/Meshes/piramid/1.piramidBuild/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob162", "Resource/Maptool/Meshes/piramid/1.piramidBuild/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob163", "Resource/Maptool/Meshes/piramid/1.piramidBuild/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob164", "Resource/Maptool/Meshes/piramid/1.piramidBuild/13/13.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob165", "Resource/Maptool/Meshes/piramid/2.piramidObject/15/15.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob166", "Resource/Maptool/Meshes/piramid/2.piramidObject/14/14.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob167", "Resource/Maptool/Meshes/piramid/2.piramidObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob168", "Resource/Maptool/Meshes/piramid/2.piramidObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob169", "Resource/Maptool/Meshes/piramid/2.piramidObject/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob170", "Resource/Maptool/Meshes/piramid/2.piramidObject/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob171", "Resource/Maptool/Meshes/piramid/2.piramidObject/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob172", "Resource/Maptool/Meshes/piramid/2.piramidObject/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob173", "Resource/Maptool/Meshes/piramid/2.piramidObject/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob174", "Resource/Maptool/Meshes/piramid/2.piramidObject/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob175", "Resource/Maptool/Meshes/piramid/2.piramidObject/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob176", "Resource/Maptool/Meshes/piramid/2.piramidObject/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob177", "Resource/Maptool/Meshes/piramid/2.piramidObject/13/13.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob178", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob179", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob180", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob181", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob182", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/5/5.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob183", "Resource/Maptool/Meshes/piramid/4.piramidRock/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob184", "Resource/Maptool/Meshes/piramid/4.piramidRock/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob185", "Resource/Maptool/Meshes/piramid/4.piramidRock/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob186", "Resource/Maptool/Meshes/piramid/4.piramidRock/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob187", "Resource/Maptool/Meshes/piramid/4.piramidRock/5/5.X");

}

void cRegistBase::XMeshSkinnedRegist()
{
	FILEPATH_MANAGER->AddFilepath("����_��", "Resource/Meshes/monster/arcanegolem_ok/x/golem2.x");
	FILEPATH_MANAGER->AddFilepath("����_��", "Resource/Meshes/monster/Beargod_ok/x/beargod.x");
	FILEPATH_MANAGER->AddFilepath("����_�����", "Resource/Meshes/monster/boar_ok/x/boar.x");
	FILEPATH_MANAGER->AddFilepath("����_��������", "Resource/Meshes/monster/bogbeast_ok/x/bogbeast.x");
	FILEPATH_MANAGER->AddFilepath("����_���Ż�罺", "Resource/Meshes/monster/Brutallus_ok/x/brutallus.x");
	FILEPATH_MANAGER->AddFilepath("����_�����", "Resource/Meshes/monster/chimerabeast_ok/x/chimerabeast.x");
	FILEPATH_MANAGER->AddFilepath("����_��", "Resource/Meshes/monster/cockatriceelite_ok/x/cockatriceelite.x");
	FILEPATH_MANAGER->AddFilepath("����_�Ǿ�", "Resource/Meshes/monster/crocodile_ok/x/crocodile.x");
	FILEPATH_MANAGER->AddFilepath("����_��", "Resource/Meshes/monster/direfurbolg_ok/x/direfurbolg.x");
	FILEPATH_MANAGER->AddFilepath("����_�Ұ���", "Resource/Meshes/monster/doomguard_ok/x/doomguard.x");
	FILEPATH_MANAGER->AddFilepath("����_����", "Resource/Meshes/monster/harpy_ok/x/harpy.x");
	FILEPATH_MANAGER->AddFilepath("����_����", "Resource/Meshes/monster/raptor_ok/x/raptor.x");
	FILEPATH_MANAGER->AddFilepath("����_����", "Resource/Meshes/monster/scorpion_ok/x/scorpion.x");
	FILEPATH_MANAGER->AddFilepath("����_������", "Resource/Meshes/monster/thunderlizard_ok/x/thunderlizard.x");
	FILEPATH_MANAGER->AddFilepath("����_������", "Resource/Meshes/BossMonster/deathwing_ok/x");
}
