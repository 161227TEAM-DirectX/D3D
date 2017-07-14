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

	//��ų �Ŵ��� �̱��� ����(����1)
	SKM->skillRelease();
	SKM->releaseSingleton();
	//��ƼŬ�ý��۸Ŵ��� �̱��� ����(����2)
	PSM->ParticleSystemSetRelease();
	PSM->releaseSingleton();
	//��ƼŬ�ý��������͸Ŵ��� �̱��� ����(���� ����3)
	EFFECT->EffectRelease();
	EFFECT->releaseSingleton();
	//��ƼŬ�ý����ؽ��ĸŴ��� �̱��� ����(����3)
	PTM->ImgRelease();
	PTM->releaseSingleton();
	
	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	//����̽� ����
	ReleaseDevice();
}



void cRegistBase::FxRegist()
{
	//FILEPATH_MANAGER->AddFilepath("FX_�����⺻", "Resource/Maptool/Shaders/TerrainBase.fx");
	FILEPATH_MANAGER->AddFilepath("FX_�����⺻", "ResourceUI/test/TerrainBase.fx");
	FILEPATH_MANAGER->AddFilepath("StaticMesh", "Resource/Shaders/StaticMesh.fx");
	FILEPATH_MANAGER->AddFilepath("diffuseDefault", "Resource/Meshes/diffuseDefault.png");
	FILEPATH_MANAGER->AddFilepath("normalDefault", "Resource/Meshes/normalDefault.png");
	FILEPATH_MANAGER->AddFilepath("specularDefault", "Resource/Meshes/specularDefault.png");
	FILEPATH_MANAGER->AddFilepath("emissionDefault", "Resource/Meshes/emissionDefault.png");
}



void cRegistBase::HeightRegist()
{
	FILEPATH_MANAGER->AddFilepath("���̸�_1", "Resource/Maptool/Textures/RAW/1.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_2", "Resource/Maptool/Textures/RAW/2.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_3", "Resource/Maptool/Textures/RAW/3.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_4", "Resource/Maptool/Textures/RAW/4.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_5", "Resource/Maptool/Textures/RAW/5.png");
	FILEPATH_MANAGER->AddFilepath("���̸�_6", "Resource/Maptool/Textures/RAW/6.png");

	FILEPATH_MANAGER->AddFilepath("height_base", "ResourceUI/test/height_base.png");
	FILEPATH_MANAGER->AddFilepath("height_base16", "ResourceUI/test/height_base16.png");
	FILEPATH_MANAGER->AddFilepath("height_base32", "ResourceUI/test/height_base32.png");
	FILEPATH_MANAGER->AddFilepath("height_base64", "ResourceUI/test/height_base64.png");
	FILEPATH_MANAGER->AddFilepath("height_base128", "ResourceUI/test/height_base128.png");
	FILEPATH_MANAGER->AddFilepath("height_base256", "ResourceUI/test/height_base256.png");
	FILEPATH_MANAGER->AddFilepath("height_base512", "ResourceUI/test/height_base512.png");
	FILEPATH_MANAGER->AddFilepath("height_base1024", "ResourceUI/test/height_base1024.png");
}



void cRegistBase::TileRegist()
{
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_1", "Resource/Maptool/Textures/Tile/1.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_2", "Resource/Maptool/Textures/Tile/2.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_3", "Resource/Maptool/Textures/Tile/3.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_4", "Resource/Maptool/Textures/Tile/4.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_5", "Resource/Maptool/Textures/Tile/26.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_6", "Resource/Maptool/Textures/Tile/6.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_7", "Resource/Maptool/Textures/Tile/13.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_8", "Resource/Maptool/Textures/Tile/12.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_9", "Resource/Maptool/Textures/Tile/21.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_10", "Resource/Maptool/Textures/Tile/10.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_11", "Resource/Maptool/Textures/Tile/11.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_12", "Resource/Maptool/Textures/Tile/27.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_13", "Resource/Maptool/Textures/Tile/13.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_14", "Resource/Maptool/Textures/Tile/14.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_15", "Resource/Maptool/Textures/Tile/15.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_16", "Resource/Maptool/Textures/Tile/8.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_17", "Resource/Maptool/Textures/Tile/3.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_18", "Resource/Maptool/Textures/Tile/18.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_19", "Resource/Maptool/Textures/Tile/19.png");
	FILEPATH_MANAGER->AddFilepath("Ÿ�ϸ�_20", "Resource/Maptool/Textures/Tile/2.png");
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
	FILEPATH_MANAGER->AddFilepath("����", "Resource/Sound/����ȭ��.mp3");
	FILEPATH_MANAGER->AddFilepath("����ȭ�鼱��", "Resource/Sound/����ȭ�鼱��.ogg");

	FILEPATH_MANAGER->AddFilepath("�ʵ�", "Resource/Sound/FieldBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Resource/Sound/BossBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Resource/Sound/TownBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Resource/Sound/����1.mp3");
	FILEPATH_MANAGER->AddFilepath("����", "Resource/Sound/����1.mp3");
	FILEPATH_MANAGER->AddFilepath("�����Ҹ�", "Resource/Sound/�����Ҹ�1.mp3");
	FILEPATH_MANAGER->AddFilepath("���߱��Ҹ�", "Resource/Sound/���߱��Ҹ�1.mp3");
	FILEPATH_MANAGER->AddFilepath("Ǫ���δ�", "Resource/Sound/Ǫ���δ�.mp3");
	FILEPATH_MANAGER->AddFilepath("������", "Resource/Sound/������.mp3");

	FILEPATH_MANAGER->AddFilepath("���������Ҹ�", "Resource/Sound/deathWing/deathwing_shouting_good.mp3");
	FILEPATH_MANAGER->AddFilepath("���������Ҹ�2", "Resource/Sound/deathWing/event_deathwingattacks_roar_01.ogg");
	FILEPATH_MANAGER->AddFilepath("���������Ҹ�3", "Resource/Sound/deathWing/event_deathwingattacks_roar_03.ogg");
	FILEPATH_MANAGER->AddFilepath("���������Ҹ�4", "Resource/Sound/deathWing/event_deathwingattacks_roar_04.ogg");
	FILEPATH_MANAGER->AddFilepath("��������1", "Resource/Sound/deathWing/mon_deathwing_attack_02.ogg");
	FILEPATH_MANAGER->AddFilepath("��������2", "Resource/Sound/deathWing/mon_deathwing_attack_04.ogg");
	FILEPATH_MANAGER->AddFilepath("��������3", "Resource/Sound/deathWing/mon_deathwing_attack_10.ogg");
	FILEPATH_MANAGER->AddFilepath("��������4", "Resource/Sound/deathWing/mon_deathwing_wound_01.ogg");
	FILEPATH_MANAGER->AddFilepath("��������1", "Resource/Sound/deathWing/mon_deathwing_death_09.ogg");
	FILEPATH_MANAGER->AddFilepath("��������2", "Resource/Sound/deathWing/mon_deathwing_death_10.ogg");
	FILEPATH_MANAGER->AddFilepath("�������Ҹ�1", "Resource/Sound/deathWing/mon_deathwing_preaggro_03.ogg");
	FILEPATH_MANAGER->AddFilepath("�������Ҹ�2", "Resource/Sound/deathWing/mon_deathwing_preaggro_04.ogg");
	FILEPATH_MANAGER->AddFilepath("�����극��", "Resource/Sound/deathWing/European_Dragon_Roaring_and_breathe_fire-daniel-simon.mp3");
	FILEPATH_MANAGER->AddFilepath("�����극��2", "Resource/Sound/deathWing/flamebreath.ogg");
	FILEPATH_MANAGER->AddFilepath("��������", "Resource/Sound/deathWing/mdeathimpactcolossalgrassa.ogg");
	FILEPATH_MANAGER->AddFilepath("�ȱ�", "Resource/Sound/deathWing/mdeathimpactgiantdirta.ogg");
	FILEPATH_MANAGER->AddFilepath("���ʹ��", "Resource/Sound/monster/ancientofarcane_aggro_01.ogg");
	FILEPATH_MANAGER->AddFilepath("���Ͱ���", "Resource/Sound/monster/ancientofarcane_attack_02.ogg");
	FILEPATH_MANAGER->AddFilepath("��������", "Resource/Sound/monster/ancientofarcane_death_02.ogg");
}



void cRegistBase::UIRegist()
{
	FILEPATH_MANAGER->AddFilepath("�ε�ȭ��", "ResourceUI/loading/�ε�ȭ��.png");
	FILEPATH_MANAGER->AddFilepath("����ȭ��", "ResourceUI/loading/����ȭ��.png");
	FILEPATH_MANAGER->AddFilepath("���۹�ư_����", "ResourceUI/loading/���۹�ư_����.png");
	FILEPATH_MANAGER->AddFilepath("���۹�ư_����", "ResourceUI/loading/���۹�ư_����.png");

	FILEPATH_MANAGER->AddFilepath("loadingbar_move", "ResourceUI/loading/loadingbar_move.png");
	FILEPATH_MANAGER->AddFilepath("loadingbar_back", "ResourceUI/loading/loadingbar_back.png");
	FILEPATH_MANAGER->AddFilepath("loadingbar_cover", "ResourceUI/loading/loadingbar_cover.png");

	FILEPATH_MANAGER->AddFilepath("btn_exit_off", "ResourceUI/start/btn_exit_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_exit_over", "ResourceUI/start/btn_exit_over.png");
	FILEPATH_MANAGER->AddFilepath("btn_option_off", "ResourceUI/start/btn_option_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_option_over", "ResourceUI/start/btn_option_over.png");
	FILEPATH_MANAGER->AddFilepath("btn_gameStart_off", "ResourceUI/start/btn_gameStart_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_gameStart_over", "ResourceUI/start/btn_gameStart_over.png");
	FILEPATH_MANAGER->AddFilepath("btn_mapTool_off", "ResourceUI/start/btn_mapTool_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_mapTool_over", "ResourceUI/start/btn_mapTool_over.png");

	FILEPATH_MANAGER->AddFilepath("quickSlotUI_back", "ResourceUI/game/quickSlotUI_back.png");

	FILEPATH_MANAGER->AddFilepath("playerbar_back", "ResourceUI/game/playerbar_back.png");
	FILEPATH_MANAGER->AddFilepath("playerbarHP_cover", "ResourceUI/game/playerbarHP_cover.png");
	FILEPATH_MANAGER->AddFilepath("playerbarHP_move", "ResourceUI/game/playerbarHP_move.png");
	FILEPATH_MANAGER->AddFilepath("playerbarMP_cover", "ResourceUI/game/playerbarMP_cover.png");
	FILEPATH_MANAGER->AddFilepath("playerbarMP_move", "ResourceUI/game/playerbarMP_move.png");

	FILEPATH_MANAGER->AddFilepath("ä��â", "ResourceUI/chat/ä��â.png");

	FILEPATH_MANAGER->AddFilepath("shopSlot_back", "ResourceUI/game/shopSlot_back.png");
	FILEPATH_MANAGER->AddFilepath("shopSlot_off00", "ResourceUI/game/shopSlot_off00.png");
	FILEPATH_MANAGER->AddFilepath("shopSlot_off01", "ResourceUI/game/shopSlot_off01.png");
	FILEPATH_MANAGER->AddFilepath("shopSlot_off02", "ResourceUI/game/shopSlot_off02.png");
	FILEPATH_MANAGER->AddFilepath("shopSlot_over00", "ResourceUI/game/shopSlot_over00.png");
	FILEPATH_MANAGER->AddFilepath("shopSlot_over01", "ResourceUI/game/shopSlot_over01.png");
	FILEPATH_MANAGER->AddFilepath("shopSlot_over02", "ResourceUI/game/shopSlot_over02.png");

	FILEPATH_MANAGER->AddFilepath("minimap", "ResourceUI/game/minimap.png");
	FILEPATH_MANAGER->AddFilepath("minimap_cover", "ResourceUI/game/minimap_cover.png");
	FILEPATH_MANAGER->AddFilepath("minimap_player", "ResourceUI/game/minimap_player.png");
	FILEPATH_MANAGER->AddFilepath("btn_minimap_off", "ResourceUI/game/btn_minimap_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_minimap_on", "ResourceUI/game/btn_minimap_on.png");

	FILEPATH_MANAGER->AddFilepath("worldmap_cover", "ResourceUI/game/worldmap_cover.png");
	FILEPATH_MANAGER->AddFilepath("worldmap_point", "ResourceUI/game/worldmap_point.png");


	FILEPATH_MANAGER->AddFilepath("btn_invetory_off", "ResourceUI/game/btn_invetory_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_invetory_over", "ResourceUI/game/btn_invetory_over.png");

	FILEPATH_MANAGER->AddFilepath("btn_skillbook_off", "ResourceUI/game/btn_skillbook_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_skillbook_over", "ResourceUI/game/btn_skillbook_over.png");

	FILEPATH_MANAGER->AddFilepath("btn_worldmap_off", "ResourceUI/game/btn_worldmap_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_worldmap_over", "ResourceUI/game/btn_worldmap_over.png");

	FILEPATH_MANAGER->AddFilepath("btn_quest_off", "ResourceUI/game/btn_quest_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_quest_on", "ResourceUI/game/btn_quest_on.png");

	FILEPATH_MANAGER->AddFilepath("btn_questBox_off", "ResourceUI/game/btn_questBox_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_questBox_on", "ResourceUI/game/btn_questBox_on.png");

	FILEPATH_MANAGER->AddFilepath("numbox_money", "ResourceUI/game/numbox_money.png");
	FILEPATH_MANAGER->AddFilepath("numbox_soul", "ResourceUI/game/numbox_soul.png");

	FILEPATH_MANAGER->AddFilepath("miniQuestBox", "ResourceUI/game/miniQuestBox.png");
	FILEPATH_MANAGER->AddFilepath("questBox", "ResourceUI/game/questBox.png");

	FILEPATH_MANAGER->AddFilepath("btn_skill00_off", "ResourceUI/game/btn_skill00_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill01_off", "ResourceUI/game/btn_skill01_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill02_off", "ResourceUI/game/btn_skill02_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill03_off", "ResourceUI/game/btn_skill03_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill04_off", "ResourceUI/game/btn_skill04_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill05_off", "ResourceUI/game/btn_skill05_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill06_off", "ResourceUI/game/btn_skill06_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill07_off", "ResourceUI/game/btn_skill07_off.png");

	FILEPATH_MANAGER->AddFilepath("btn_skill00_on", "ResourceUI/game/btn_skill00_on.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill01_on", "ResourceUI/game/btn_skill01_on.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill02_on", "ResourceUI/game/btn_skill02_on.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill03_on", "ResourceUI/game/btn_skill03_on.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill04_on", "ResourceUI/game/btn_skill04_on.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill05_on", "ResourceUI/game/btn_skill05_on.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill06_on", "ResourceUI/game/btn_skill06_on.png");
	FILEPATH_MANAGER->AddFilepath("btn_skill07_on", "ResourceUI/game/btn_skill07_on.png");

	FILEPATH_MANAGER->AddFilepath("btn_gold_off", "ResourceUI/game/btn_gold_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_gold_on", "ResourceUI/game/btn_gold_on.png");

	FILEPATH_MANAGER->AddFilepath("btn_soul_off", "ResourceUI/game/btn_soul_off.png");
	FILEPATH_MANAGER->AddFilepath("btn_soul_on", "ResourceUI/game/btn_soul_on.png");






	FILEPATH_MANAGER->AddFilepath("skillbookText00", "ResourceUI/game/skillbookText00.png");
	FILEPATH_MANAGER->AddFilepath("skillbookText01", "ResourceUI/game/skillbookText01.png");
	FILEPATH_MANAGER->AddFilepath("skillbookText02", "ResourceUI/game/skillbookText02.png");
	FILEPATH_MANAGER->AddFilepath("skillbookText03", "ResourceUI/game/skillbookText03.png");
	FILEPATH_MANAGER->AddFilepath("skillbookText04", "ResourceUI/game/skillbookText04.png");
	FILEPATH_MANAGER->AddFilepath("skillbookText05", "ResourceUI/game/skillbookText05.png");
	FILEPATH_MANAGER->AddFilepath("skillbookText06", "ResourceUI/game/skillbookText06.png");
	FILEPATH_MANAGER->AddFilepath("skillbookText07", "ResourceUI/game/skillbookText07.png");

	FILEPATH_MANAGER->AddFilepath("mouseCursor", "ResourceUI/game/mouseCursor.png");

	FILEPATH_MANAGER->AddFilepath("worldmap_cover", "ResourceUI/game/worldmap_cover.png");
	FILEPATH_MANAGER->AddFilepath("worldmap", "ResourceUI/game/worldmap.png");
	FILEPATH_MANAGER->AddFilepath("worldmap2", "ResourceUI/game/worldmap2.png");
	FILEPATH_MANAGER->AddFilepath("worldmap3", "ResourceUI/game/worldmap3.png");

	FILEPATH_MANAGER->AddFilepath("worldmapTest", "ResourceUI/game/worldmapTest.png");

	FILEPATH_MANAGER->AddFilepath("chat_Icon", "ResourceUI/game/chat_Icon.png");
	FILEPATH_MANAGER->AddFilepath("map_Icon", "ResourceUI/game/map_Icon.png");
	FILEPATH_MANAGER->AddFilepath("quest_Icon", "ResourceUI/game/quest_Icon.png");
	FILEPATH_MANAGER->AddFilepath("quest", "ResourceUI/game/quest.png");

	FILEPATH_MANAGER->AddFilepath("�׾�����ȭ��", "ResourceUI/game/�׾�����ȭ��.png");
	FILEPATH_MANAGER->AddFilepath("YOU DIED", "ResourceUI/game/YOU DIED.png");

	FILEPATH_MANAGER->AddFilepath("gold_god", "ResourceUI/game/gold_god.png");
	FILEPATH_MANAGER->AddFilepath("death_soul", "ResourceUI/game/death_soul.png");

	FILEPATH_MANAGER->AddFilepath("bossbar_back", "ResourceUI/monster/bossbar_back.png");
	FILEPATH_MANAGER->AddFilepath("bossbar_cover", "ResourceUI/monster/bossbar_cover.png");
	FILEPATH_MANAGER->AddFilepath("bossbar_move", "ResourceUI/monster/bossbar_move.png");
	FILEPATH_MANAGER->AddFilepath("monsterbar_back", "ResourceUI/monster/monsterbar_back.png");
	FILEPATH_MANAGER->AddFilepath("monsterbar_cover", "ResourceUI/monster/monsterbar_cover.png");
	FILEPATH_MANAGER->AddFilepath("monsterbar_move", "ResourceUI/monster/monsterbar_move.png");


	//=============================================================================
	//test
	//=============================================================================
	FILEPATH_MANAGER->AddFilepath("minimap", "ResourceUI/test/minimap.png");
	FILEPATH_MANAGER->AddFilepath("minimap3", "ResourceUI/test/minimap3.png");
	FILEPATH_MANAGER->AddFilepath("minimapTest", "ResourceUI/test/minimapTest.png");


	FILEPATH_MANAGER->AddFilepath("tileTest0", "ResourceUI/test/tileTest0.png");
	FILEPATH_MANAGER->AddFilepath("tileTest1", "ResourceUI/test/tileTest1.png");
	FILEPATH_MANAGER->AddFilepath("tileTest2", "ResourceUI/test/tileTest2.png");
	FILEPATH_MANAGER->AddFilepath("tileTest3", "ResourceUI/test/tileTest3.png");
	FILEPATH_MANAGER->AddFilepath("tileTest4", "ResourceUI/test/tileTest4.png");
	FILEPATH_MANAGER->AddFilepath("tileTest5", "ResourceUI/test/tileTest5.png");
	FILEPATH_MANAGER->AddFilepath("tileTest6", "ResourceUI/test/tileTest6.png");
	FILEPATH_MANAGER->AddFilepath("tileTest7", "ResourceUI/test/tileTest7.png");
	FILEPATH_MANAGER->AddFilepath("tileTest8", "ResourceUI/test/tileTest8.png");
	FILEPATH_MANAGER->AddFilepath("tileTest9", "ResourceUI/test/tileTest9.png");
	FILEPATH_MANAGER->AddFilepath("tileTest10", "ResourceUI/test/tileTest10.png");
	FILEPATH_MANAGER->AddFilepath("tileTest11", "ResourceUI/test/tileTest11.png");
	FILEPATH_MANAGER->AddFilepath("tileTest12", "ResourceUI/test/tileTest12.png");


	FILEPATH_MANAGER->AddFilepath("tileTest0_mapTool", "ResourceUI/test/tileTest0_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest1_mapTool", "ResourceUI/test/tileTest1_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest2_mapTool", "ResourceUI/test/tileTest2_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest3_mapTool", "ResourceUI/test/tileTest3_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest4_mapTool", "ResourceUI/test/tileTest4_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest5_mapTool", "ResourceUI/test/tileTest5_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest6_mapTool", "ResourceUI/test/tileTest6_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest7_mapTool", "ResourceUI/test/tileTest7_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest8_mapTool", "ResourceUI/test/tileTest8_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest9_mapTool", "ResourceUI/test/tileTest9_mapTool.png");
	FILEPATH_MANAGER->AddFilepath("tileTest10_mapTool", "ResourceUI/test/tileTest10_mapTool.png");


	FILEPATH_MANAGER->AddFilepath("tileTestBase", "ResourceUI/test/tileTestBase.png");
	FILEPATH_MANAGER->AddFilepath("splat_test0", "ResourceUI/test/splat_test0.png");
	FILEPATH_MANAGER->AddFilepath("splat_test1", "ResourceUI/test/splat_test1.png");
	FILEPATH_MANAGER->AddFilepath("splat_test2", "ResourceUI/test/splat_test2.png");
	FILEPATH_MANAGER->AddFilepath("splat_test3", "ResourceUI/test/splat_test3.png");



	FILEPATH_MANAGER->AddFilepath("splat_red_base", "ResourceUI/test/splat_red_base.png");
	FILEPATH_MANAGER->AddFilepath("splat_green_base", "ResourceUI/test/splat_green_base.png");
	FILEPATH_MANAGER->AddFilepath("splat_blue_base", "ResourceUI/test/splat_blue_base.png");
	FILEPATH_MANAGER->AddFilepath("splat_black_base", "ResourceUI/test/splat_black_base.png");
	FILEPATH_MANAGER->AddFilepath("splat_base", "ResourceUI/test/splat_base.png");

	FILEPATH_MANAGER->AddFilepath("tileTest_Select", "ResourceUI/test/tileTest_Select.png");


	FILEPATH_MANAGER->AddFilepath("Test_Inven", "ResourceUI/test/Test_Inven.png");
	FILEPATH_MANAGER->AddFilepath("Test_Inven2", "ResourceUI/test/Test_Inven2.png");

	FILEPATH_MANAGER->AddFilepath("miniPlayer", "ResourceUI/test/miniPlayer.png");
	FILEPATH_MANAGER->AddFilepath("radar", "ResourceUI/test/radar.png");

	FILEPATH_MANAGER->AddFilepath("��������", "ResourceUI/test/��������.png");
	FILEPATH_MANAGER->AddFilepath("�������������", "ResourceUI/test/�������������.png");
	FILEPATH_MANAGER->AddFilepath("�������������", "ResourceUI/test/�������������.png");
	FILEPATH_MANAGER->AddFilepath("��ȭ����������", "ResourceUI/test/��ȭ����������.png");
	FILEPATH_MANAGER->AddFilepath("�κ��丮������", "ResourceUI/test/�κ��丮������.png");

	FILEPATH_MANAGER->AddFilepath("GrieverCursor", "ResourceUI/test/GrieverCursor.png");
	FILEPATH_MANAGER->AddFilepath("rangeTest00", "ResourceUI/test/rangeTest00.png");
	FILEPATH_MANAGER->AddFilepath("rangeTest01", "ResourceUI/test/rangeTest01.png");
	FILEPATH_MANAGER->AddFilepath("rangeTest02", "ResourceUI/test/rangeTest02.png");
	FILEPATH_MANAGER->AddFilepath("rangeTest03", "ResourceUI/test/rangeTest03.png");
	FILEPATH_MANAGER->AddFilepath("rangeTest04", "ResourceUI/test/rangeTest04.png");
	FILEPATH_MANAGER->AddFilepath("checkTest00", "ResourceUI/test/checkTest00.png");

	FILEPATH_MANAGER->AddFilepath("worldmapTest", "ResourceUI/test/worldmapTest.png");

	FILEPATH_MANAGER->AddFilepath("markCenter", "ResourceUI/test/markCenter.png");
	FILEPATH_MANAGER->AddFilepath("markEast", "ResourceUI/test/markEast.png");
	FILEPATH_MANAGER->AddFilepath("markWest", "ResourceUI/test/markWest.png");
	FILEPATH_MANAGER->AddFilepath("markSouth", "ResourceUI/test/markSouth.png");
	FILEPATH_MANAGER->AddFilepath("markNorth", "ResourceUI/test/markNorth.png");

	FILEPATH_MANAGER->AddFilepath("gamemapTest", "ResourceUI/test/gamemapTest.png");

	FILEPATH_MANAGER->AddFilepath("�̺�Ʈ��", "ResourceUI/test/�̺�Ʈ��.png");

	FILEPATH_MANAGER->AddFilepath("questBtn_Over", "ResourceUI/test/questBtn_Over.png");
	FILEPATH_MANAGER->AddFilepath("questBtn_Off", "ResourceUI/test/questBtn_Off.png");

	FILEPATH_MANAGER->AddFilepath("questSlot_Test", "ResourceUI/test/questSlot_Test.png");

	FILEPATH_MANAGER->AddFilepath("skill0_On", "ResourceUI/test/skill/skill0_On.png");
	FILEPATH_MANAGER->AddFilepath("skill0_Off", "ResourceUI/test/skill/skill0_Off.png");
	FILEPATH_MANAGER->AddFilepath("skill1_On", "ResourceUI/test/skill/skill1_On.png");
	FILEPATH_MANAGER->AddFilepath("skill1_Off", "ResourceUI/test/skill/skill1_Off.png");
	FILEPATH_MANAGER->AddFilepath("skill2_On", "ResourceUI/test/skill/skill2_On.png");
	FILEPATH_MANAGER->AddFilepath("skill2_Off", "ResourceUI/test/skill/skill2_Off.png");
	FILEPATH_MANAGER->AddFilepath("skill3_On", "ResourceUI/test/skill/skill3_On.png");
	FILEPATH_MANAGER->AddFilepath("skill3_Off", "ResourceUI/test/skill/skill3_Off.png");
	FILEPATH_MANAGER->AddFilepath("skill4_On", "ResourceUI/test/skill/skill4_On.png");
	FILEPATH_MANAGER->AddFilepath("skill4_Off", "ResourceUI/test/skill/skill4_Off.png");
	FILEPATH_MANAGER->AddFilepath("skill5_On", "ResourceUI/test/skill/skill5_On.png");
	FILEPATH_MANAGER->AddFilepath("skill5_Off", "ResourceUI/test/skill/skill5_Off.png");
	FILEPATH_MANAGER->AddFilepath("skill6_On", "ResourceUI/test/skill/skill6_On.png");
	FILEPATH_MANAGER->AddFilepath("skill6_Off", "ResourceUI/test/skill/skill6_Off.png");
	FILEPATH_MANAGER->AddFilepath("skill7_On", "ResourceUI/test/skill/skill7_On.png");
	FILEPATH_MANAGER->AddFilepath("skill7_Off", "ResourceUI/test/skill/skill7_Off.png");

	FILEPATH_MANAGER->AddFilepath("��Ÿ��", "ResourceUI/test/skill/��Ÿ��.png");

	FILEPATH_MANAGER->AddFilepath("��ü�ʿ�������ġ", "ResourceUI/test/��ü�ʿ�������ġ.png");
	FILEPATH_MANAGER->AddFilepath("��ü���׽�Ʈ", "ResourceUI/test/��ü���׽�Ʈ.png");
	FILEPATH_MANAGER->AddFilepath("��ų����", "ResourceUI/test/skill/��ų����.png");

	FILEPATH_MANAGER->AddFilepath("money_gold", "ResourceUI/test/money_gold.png");
	FILEPATH_MANAGER->AddFilepath("dragon_soul", "ResourceUI/test/dragon_soul.png");

	FILEPATH_MANAGER->AddFilepath("mouse", "ResourceUI/test/mouse.png");

	FILEPATH_MANAGER->AddFilepath("partTest", "ResourceUI/test/partTest.png");
}



void cRegistBase::AniRegist()
{
	//SkillBook
	FILEPATH_MANAGER->AddFilepath("skillbook01", "ResourceUI/animation/skillbook/skillbook01.png");
	FILEPATH_MANAGER->AddFilepath("skillbook02", "ResourceUI/animation/skillbook/skillbook02.png");
	FILEPATH_MANAGER->AddFilepath("skillbook03", "ResourceUI/animation/skillbook/skillbook03.png");
	FILEPATH_MANAGER->AddFilepath("skillbook04", "ResourceUI/animation/skillbook/skillbook04.png");
	FILEPATH_MANAGER->AddFilepath("skillbook05", "ResourceUI/animation/skillbook/skillbook05.png");
	FILEPATH_MANAGER->AddFilepath("skillbook06", "ResourceUI/animation/skillbook/skillbook06.png");
	FILEPATH_MANAGER->AddFilepath("skillbook07", "ResourceUI/animation/skillbook/skillbook07.png");
	FILEPATH_MANAGER->AddFilepath("skillbook08", "ResourceUI/animation/skillbook/skillbook08.png");
	FILEPATH_MANAGER->AddFilepath("skillbook09", "ResourceUI/animation/skillbook/skillbook09.png");
	FILEPATH_MANAGER->AddFilepath("skillbook10", "ResourceUI/animation/skillbook/skillbook10.png");
	FILEPATH_MANAGER->AddFilepath("skillbook11", "ResourceUI/animation/skillbook/skillbook11.png");
	FILEPATH_MANAGER->AddFilepath("skillbook12", "ResourceUI/animation/skillbook/skillbook12.png");
	FILEPATH_MANAGER->AddFilepath("skillbook13", "ResourceUI/animation/skillbook/skillbook13.png");
	FILEPATH_MANAGER->AddFilepath("skillbook14", "ResourceUI/animation/skillbook/skillbook14.png");
	FILEPATH_MANAGER->AddFilepath("skillbook15", "ResourceUI/animation/skillbook/skillbook15.png");
	FILEPATH_MANAGER->AddFilepath("skillbook16", "ResourceUI/animation/skillbook/skillbook16.png");
	FILEPATH_MANAGER->AddFilepath("skillbook17", "ResourceUI/animation/skillbook/skillbook17.png");
	FILEPATH_MANAGER->AddFilepath("skillbook18", "ResourceUI/animation/skillbook/skillbook18.png");
	FILEPATH_MANAGER->AddFilepath("skillbook19", "ResourceUI/animation/skillbook/skillbook19.png");
	FILEPATH_MANAGER->AddFilepath("skillbook20", "ResourceUI/animation/skillbook/skillbook20.png");
	FILEPATH_MANAGER->AddFilepath("skillbook21", "ResourceUI/animation/skillbook/skillbook21.png");
	FILEPATH_MANAGER->AddFilepath("skillbook22", "ResourceUI/animation/skillbook/skillbook22.png");
	FILEPATH_MANAGER->AddFilepath("skillbook23", "ResourceUI/animation/skillbook/skillbook23.png");
	FILEPATH_MANAGER->AddFilepath("skillbook24", "ResourceUI/animation/skillbook/skillbook24.png");
	FILEPATH_MANAGER->AddFilepath("skillbook25", "ResourceUI/animation/skillbook/skillbook25.png");
	FILEPATH_MANAGER->AddFilepath("skillbook26", "ResourceUI/animation/skillbook/skillbook26.png");
	FILEPATH_MANAGER->AddFilepath("skillbook27", "ResourceUI/animation/skillbook/skillbook27.png");
	FILEPATH_MANAGER->AddFilepath("skillbook28", "ResourceUI/animation/skillbook/skillbook28.png");
	FILEPATH_MANAGER->AddFilepath("skillbook29", "ResourceUI/animation/skillbook/skillbook29.png");
	FILEPATH_MANAGER->AddFilepath("skillbook30", "ResourceUI/animation/skillbook/skillbook30.png");
	FILEPATH_MANAGER->AddFilepath("skillbook31", "ResourceUI/animation/skillbook/skillbook31.png");
	FILEPATH_MANAGER->AddFilepath("skillbook32", "ResourceUI/animation/skillbook/skillbook32.png");
	FILEPATH_MANAGER->AddFilepath("skillbook33", "ResourceUI/animation/skillbook/skillbook33.png");
	FILEPATH_MANAGER->AddFilepath("skillbook34", "ResourceUI/animation/skillbook/skillbook34.png");
	FILEPATH_MANAGER->AddFilepath("skillbook35", "ResourceUI/animation/skillbook/skillbook35.png");
	FILEPATH_MANAGER->AddFilepath("skillbook36", "ResourceUI/animation/skillbook/skillbook36.png");
	FILEPATH_MANAGER->AddFilepath("skillbook37", "ResourceUI/animation/skillbook/skillbook37.png");
	FILEPATH_MANAGER->AddFilepath("skillbook38", "ResourceUI/animation/skillbook/skillbook38.png");



	//Fire01
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_00", "ResourceUI/animation/Fire01/output-00.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_01", "ResourceUI/animation/Fire01/output-01.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_02", "ResourceUI/animation/Fire01/output-02.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_03", "ResourceUI/animation/Fire01/output-03.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_04", "ResourceUI/animation/Fire01/output-04.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_05", "ResourceUI/animation/Fire01/output-05.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_06", "ResourceUI/animation/Fire01/output-06.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_07", "ResourceUI/animation/Fire01/output-07.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_08", "ResourceUI/animation/Fire01/output-08.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_09", "ResourceUI/animation/Fire01/output-09.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_10", "ResourceUI/animation/Fire01/output-10.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_11", "ResourceUI/animation/Fire01/output-11.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_12", "ResourceUI/animation/Fire01/output-12.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_13", "ResourceUI/animation/Fire01/output-13.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_14", "ResourceUI/animation/Fire01/output-14.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_15", "ResourceUI/animation/Fire01/output-15.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_16", "ResourceUI/animation/Fire01/output-16.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_17", "ResourceUI/animation/Fire01/output-17.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_18", "ResourceUI/animation/Fire01/output-18.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_19", "ResourceUI/animation/Fire01/output-19.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_20", "ResourceUI/animation/Fire01/output-20.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_21", "ResourceUI/animation/Fire01/output-21.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_22", "ResourceUI/animation/Fire01/output-22.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_23", "ResourceUI/animation/Fire01/output-23.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_24", "ResourceUI/animation/Fire01/output-24.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_25", "ResourceUI/animation/Fire01/output-25.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_26", "ResourceUI/animation/Fire01/output-26.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_27", "ResourceUI/animation/Fire01/output-27.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_28", "ResourceUI/animation/Fire01/output-28.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_29", "ResourceUI/animation/Fire01/output-29.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_30", "ResourceUI/animation/Fire01/output-30.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_31", "ResourceUI/animation/Fire01/output-31.png");
	FILEPATH_MANAGER->AddFilepath("Ani_Fire01_32", "ResourceUI/animation/Fire01/output-32.png");
	
	
	
	//============================================================================================
	//���尣 ���� 
	//============================================================================================
	FILEPATH_MANAGER->AddFilepath("Sword1_01", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (1).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_02", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (2).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_03", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (3).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_04", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (4).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_05", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (5).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_06", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (6).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_07", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (7).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_08", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (8).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_09", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (9).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_10", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (10).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_11", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (11).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_12", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (12).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_13", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (13).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_14", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (14).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_15", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (15).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_16", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (16).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_17", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (17).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_18", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (18).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_19", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (19).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword1_20", "Resource/Maptool/sword/�ҵ�1/�ҵ�1 (20).jpg");

	FILEPATH_MANAGER->AddFilepath("Sword2_01", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (1).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_02", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (2).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_03", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (3).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_04", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (4).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_05", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (5).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_06", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (6).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_07", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (7).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_08", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (8).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_09", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (9).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_10", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (10).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_11", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (11).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_12", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (12).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_13", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (13).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_14", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (14).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_15", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (15).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_16", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (16).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_17", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (17).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_18", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (18).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_19", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (19).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword2_20", "Resource/Maptool/sword/�ҵ�2/�ҵ�2 (20).jpg");

	FILEPATH_MANAGER->AddFilepath("Sword3_01", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (1).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_02", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (2).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_03", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (3).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_04", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (4).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_05", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (5).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_06", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (6).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_07", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (7).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_08", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (8).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_09", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (9).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_10", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (10).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_11", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (11).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_12", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (12).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_13", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (13).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_14", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (14).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_15", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (15).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_16", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (16).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_17", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (17).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_18", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (18).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_19", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (19).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword3_20", "Resource/Maptool/sword/�ҵ�3/�ҵ�3 (20).jpg");

	FILEPATH_MANAGER->AddFilepath("Sword4_01", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (1).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_02", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (2).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_03", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (3).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_04", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (4).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_05", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (5).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_06", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (6).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_07", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (7).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_08", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (8).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_09", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (9).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_10", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (10).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_11", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (11).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_12", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (12).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_13", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (13).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_14", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (14).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_15", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (15).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_16", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (16).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_17", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (17).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_18", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (18).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_19", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (19).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword4_20", "Resource/Maptool/sword/�ҵ�4/�ҵ�4 (20).jpg");

	FILEPATH_MANAGER->AddFilepath("Sword5_01", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (1).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_02", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (2).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_03", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (3).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_04", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (4).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_05", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (5).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_06", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (6).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_07", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (7).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_08", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (8).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_09", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (9).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_10", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (10).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_11", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (11).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_12", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (12).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_13", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (13).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_14", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (14).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_15", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (15).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_16", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (16).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_17", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (17).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_18", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (18).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_19", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (19).jpg");
	FILEPATH_MANAGER->AddFilepath("Sword5_20", "Resource/Maptool/sword/�ҵ�5/�ҵ�5 (20).jpg");

	//��ȭ �ִ�
	FILEPATH_MANAGER->AddFilepath("force_1", "ResourceUI/inven/��ȭ/1.png");
	FILEPATH_MANAGER->AddFilepath("force_2", "ResourceUI/inven/��ȭ/2.png");
	FILEPATH_MANAGER->AddFilepath("force_3", "ResourceUI/inven/��ȭ/3.png");
	FILEPATH_MANAGER->AddFilepath("force_4", "ResourceUI/inven/��ȭ/4.png");
	FILEPATH_MANAGER->AddFilepath("force_5", "ResourceUI/inven/��ȭ/5.png");
	FILEPATH_MANAGER->AddFilepath("force_6", "ResourceUI/inven/��ȭ/6.png");
	FILEPATH_MANAGER->AddFilepath("force_7", "ResourceUI/inven/��ȭ/7.png");
	FILEPATH_MANAGER->AddFilepath("force_8", "ResourceUI/inven/��ȭ/8.png");
	FILEPATH_MANAGER->AddFilepath("force_9", "ResourceUI/inven/��ȭ/9.png");
	FILEPATH_MANAGER->AddFilepath("force_10", "ResourceUI/inven/��ȭ/10.png");
	FILEPATH_MANAGER->AddFilepath("force_11", "ResourceUI/inven/��ȭ/11.png");
	FILEPATH_MANAGER->AddFilepath("force_12", "ResourceUI/inven/��ȭ/12.png");
	FILEPATH_MANAGER->AddFilepath("force_13", "ResourceUI/inven/��ȭ/13.png");
	FILEPATH_MANAGER->AddFilepath("force_14", "ResourceUI/inven/��ȭ/14.png");
	FILEPATH_MANAGER->AddFilepath("force_15", "ResourceUI/inven/��ȭ/15.png");
	FILEPATH_MANAGER->AddFilepath("force_16", "ResourceUI/inven/��ȭ/16.png");
	FILEPATH_MANAGER->AddFilepath("force_17", "ResourceUI/inven/��ȭ/17.png");
	FILEPATH_MANAGER->AddFilepath("force_18", "ResourceUI/inven/��ȭ/18.png");
	FILEPATH_MANAGER->AddFilepath("force_19", "ResourceUI/inven/��ȭ/19.png");
	FILEPATH_MANAGER->AddFilepath("force_20", "ResourceUI/inven/��ȭ/20.png");
	FILEPATH_MANAGER->AddFilepath("force_21", "ResourceUI/inven/��ȭ/21.png");
	FILEPATH_MANAGER->AddFilepath("force_22", "ResourceUI/inven/��ȭ/22.png");
	FILEPATH_MANAGER->AddFilepath("force_23", "ResourceUI/inven/��ȭ/23.png");
	FILEPATH_MANAGER->AddFilepath("force_24", "ResourceUI/inven/��ȭ/24.png");
	FILEPATH_MANAGER->AddFilepath("force_25", "ResourceUI/inven/��ȭ/25.png");
	FILEPATH_MANAGER->AddFilepath("force_26", "ResourceUI/inven/��ȭ/26.png");
	FILEPATH_MANAGER->AddFilepath("force_27", "ResourceUI/inven/��ȭ/27.png");
	FILEPATH_MANAGER->AddFilepath("force_28", "ResourceUI/inven/��ȭ/28.png");
	FILEPATH_MANAGER->AddFilepath("force_29", "ResourceUI/inven/��ȭ/29.png");
	FILEPATH_MANAGER->AddFilepath("force_30", "ResourceUI/inven/��ȭ/30.png");
	FILEPATH_MANAGER->AddFilepath("force_31", "ResourceUI/inven/��ȭ/31.png");
	FILEPATH_MANAGER->AddFilepath("force_32", "ResourceUI/inven/��ȭ/32.png");
	FILEPATH_MANAGER->AddFilepath("force_33", "ResourceUI/inven/��ȭ/33.png");
	FILEPATH_MANAGER->AddFilepath("force_34", "ResourceUI/inven/��ȭ/34.png");
	FILEPATH_MANAGER->AddFilepath("force_35", "ResourceUI/inven/��ȭ/35.png");
	FILEPATH_MANAGER->AddFilepath("force_36", "ResourceUI/inven/��ȭ/36.png");
	FILEPATH_MANAGER->AddFilepath("force_37", "ResourceUI/inven/��ȭ/37.png");
	FILEPATH_MANAGER->AddFilepath("force_38", "ResourceUI/inven/��ȭ/38.png");
	FILEPATH_MANAGER->AddFilepath("force_39", "ResourceUI/inven/��ȭ/39.png");
	FILEPATH_MANAGER->AddFilepath("force_40", "ResourceUI/inven/��ȭ/40.png");
	FILEPATH_MANAGER->AddFilepath("force_41", "ResourceUI/inven/��ȭ/41.png");
	FILEPATH_MANAGER->AddFilepath("force_42", "ResourceUI/inven/��ȭ/42.png");
	FILEPATH_MANAGER->AddFilepath("force_43", "ResourceUI/inven/��ȭ/43.png");
	FILEPATH_MANAGER->AddFilepath("force_44", "ResourceUI/inven/��ȭ/44.png");
	FILEPATH_MANAGER->AddFilepath("force_45", "ResourceUI/inven/��ȭ/45.png");
	FILEPATH_MANAGER->AddFilepath("force_46", "ResourceUI/inven/��ȭ/46.png");
	FILEPATH_MANAGER->AddFilepath("force_47", "ResourceUI/inven/��ȭ/47.png");
	FILEPATH_MANAGER->AddFilepath("force_48", "ResourceUI/inven/��ȭ/48.png");
	FILEPATH_MANAGER->AddFilepath("force_49", "ResourceUI/inven/��ȭ/49.png");
	FILEPATH_MANAGER->AddFilepath("force_50", "ResourceUI/inven/��ȭ/50.png");
	FILEPATH_MANAGER->AddFilepath("force_51", "ResourceUI/inven/��ȭ/51.png");
	FILEPATH_MANAGER->AddFilepath("force_52", "ResourceUI/inven/��ȭ/52.png");
	FILEPATH_MANAGER->AddFilepath("force_53", "ResourceUI/inven/��ȭ/53.png");

	FILEPATH_MANAGER->AddFilepath("force2_1", "ResourceUI/inven/��ȭ2/1.png");
	FILEPATH_MANAGER->AddFilepath("force2_2", "ResourceUI/inven/��ȭ2/2.png");
	FILEPATH_MANAGER->AddFilepath("force2_3", "ResourceUI/inven/��ȭ2/3.png");
	FILEPATH_MANAGER->AddFilepath("force2_4", "ResourceUI/inven/��ȭ2/4.png");
	FILEPATH_MANAGER->AddFilepath("force2_5", "ResourceUI/inven/��ȭ2/5.png");
	FILEPATH_MANAGER->AddFilepath("force2_6", "ResourceUI/inven/��ȭ2/6.png");
	FILEPATH_MANAGER->AddFilepath("force2_7", "ResourceUI/inven/��ȭ2/7.png");
	FILEPATH_MANAGER->AddFilepath("force2_8", "ResourceUI/inven/��ȭ2/8.png");
	FILEPATH_MANAGER->AddFilepath("force2_9", "ResourceUI/inven/��ȭ2/9.png");
	FILEPATH_MANAGER->AddFilepath("force2_10", "ResourceUI/inven/��ȭ2/10.png");
	FILEPATH_MANAGER->AddFilepath("force2_11", "ResourceUI/inven/��ȭ2/11.png");
	FILEPATH_MANAGER->AddFilepath("force2_12", "ResourceUI/inven/��ȭ2/12.png");
	FILEPATH_MANAGER->AddFilepath("force2_13", "ResourceUI/inven/��ȭ2/13.png");
	FILEPATH_MANAGER->AddFilepath("force2_14", "ResourceUI/inven/��ȭ2/14.png");
	FILEPATH_MANAGER->AddFilepath("force2_15", "ResourceUI/inven/��ȭ2/15.png");
	FILEPATH_MANAGER->AddFilepath("force2_16", "ResourceUI/inven/��ȭ2/16.png");
	FILEPATH_MANAGER->AddFilepath("force2_17", "ResourceUI/inven/��ȭ2/17.png");
	FILEPATH_MANAGER->AddFilepath("force2_18", "ResourceUI/inven/��ȭ2/18.png");
	FILEPATH_MANAGER->AddFilepath("force2_19", "ResourceUI/inven/��ȭ2/19.png");
	FILEPATH_MANAGER->AddFilepath("force2_20", "ResourceUI/inven/��ȭ2/20.png");
	FILEPATH_MANAGER->AddFilepath("force2_21", "ResourceUI/inven/��ȭ2/21.png");
	FILEPATH_MANAGER->AddFilepath("force2_22", "ResourceUI/inven/��ȭ2/22.png");
	FILEPATH_MANAGER->AddFilepath("force2_23", "ResourceUI/inven/��ȭ2/23.png");
	FILEPATH_MANAGER->AddFilepath("force2_24", "ResourceUI/inven/��ȭ2/24.png");
	FILEPATH_MANAGER->AddFilepath("force2_25", "ResourceUI/inven/��ȭ2/25.png");
	FILEPATH_MANAGER->AddFilepath("force2_26", "ResourceUI/inven/��ȭ2/26.png");
	FILEPATH_MANAGER->AddFilepath("force2_27", "ResourceUI/inven/��ȭ2/27.png");
	FILEPATH_MANAGER->AddFilepath("force2_28", "ResourceUI/inven/��ȭ2/28.png");
	FILEPATH_MANAGER->AddFilepath("force2_29", "ResourceUI/inven/��ȭ2/29.png");
	FILEPATH_MANAGER->AddFilepath("force2_30", "ResourceUI/inven/��ȭ2/30.png");
	FILEPATH_MANAGER->AddFilepath("force2_31", "ResourceUI/inven/��ȭ2/31.png");
	FILEPATH_MANAGER->AddFilepath("force2_32", "ResourceUI/inven/��ȭ2/32.png");
	FILEPATH_MANAGER->AddFilepath("force2_33", "ResourceUI/inven/��ȭ2/33.png");
	FILEPATH_MANAGER->AddFilepath("force2_34", "ResourceUI/inven/��ȭ2/34.png");
	FILEPATH_MANAGER->AddFilepath("force2_35", "ResourceUI/inven/��ȭ2/35.png");
	FILEPATH_MANAGER->AddFilepath("force2_36", "ResourceUI/inven/��ȭ2/36.png");
	FILEPATH_MANAGER->AddFilepath("force2_37", "ResourceUI/inven/��ȭ2/37.png");
	FILEPATH_MANAGER->AddFilepath("force2_38", "ResourceUI/inven/��ȭ2/38.png");
	FILEPATH_MANAGER->AddFilepath("force2_39", "ResourceUI/inven/��ȭ2/39.png");
	FILEPATH_MANAGER->AddFilepath("force2_40", "ResourceUI/inven/��ȭ2/40.png");
	FILEPATH_MANAGER->AddFilepath("force2_41", "ResourceUI/inven/��ȭ2/41.png");
	FILEPATH_MANAGER->AddFilepath("force2_42", "ResourceUI/inven/��ȭ2/42.png");
	FILEPATH_MANAGER->AddFilepath("force2_43", "ResourceUI/inven/��ȭ2/43.png");
	FILEPATH_MANAGER->AddFilepath("force2_44", "ResourceUI/inven/��ȭ2/44.png");
	FILEPATH_MANAGER->AddFilepath("force2_45", "ResourceUI/inven/��ȭ2/45.png");
	FILEPATH_MANAGER->AddFilepath("force2_46", "ResourceUI/inven/��ȭ2/46.png");
	FILEPATH_MANAGER->AddFilepath("force2_47", "ResourceUI/inven/��ȭ2/47.png");
	FILEPATH_MANAGER->AddFilepath("force2_48", "ResourceUI/inven/��ȭ2/48.png");
	FILEPATH_MANAGER->AddFilepath("force2_49", "ResourceUI/inven/��ȭ2/49.png");
	FILEPATH_MANAGER->AddFilepath("force2_50", "ResourceUI/inven/��ȭ2/50.png");
	FILEPATH_MANAGER->AddFilepath("force2_51", "ResourceUI/inven/��ȭ2/51.png");
	FILEPATH_MANAGER->AddFilepath("force2_52", "ResourceUI/inven/��ȭ2/52.png");
	FILEPATH_MANAGER->AddFilepath("force2_53", "ResourceUI/inven/��ȭ2/53.png");
	
	//UI��ȭâ(1)
	FILEPATH_MANAGER->AddFilepath("���½�_1", "Resource/endingtexture/���½�/1.png");
	FILEPATH_MANAGER->AddFilepath("���½�_2", "Resource/endingtexture/���½�/2.png");
	FILEPATH_MANAGER->AddFilepath("���½�_3", "Resource/endingtexture/���½�/3.png");
	//UI��ȭâ(2)
	FILEPATH_MANAGER->AddFilepath("������_1", "Resource/endingtexture/������/1.png");
	FILEPATH_MANAGER->AddFilepath("������_2", "Resource/endingtexture/������/2.png");
	FILEPATH_MANAGER->AddFilepath("������_3", "Resource/endingtexture/������/3.png");
	//UI��ȭâ(3)
	FILEPATH_MANAGER->AddFilepath("�踸��_1", "Resource/endingtexture/�踸��/1.png");
	FILEPATH_MANAGER->AddFilepath("�踸��_2", "Resource/endingtexture/�踸��/2.png");
	FILEPATH_MANAGER->AddFilepath("�踸��_3", "Resource/endingtexture/�踸��/3.png");
	//UI��ȭâ(4)
	FILEPATH_MANAGER->AddFilepath("������_1", "Resource/endingtexture/������/1.png");
	FILEPATH_MANAGER->AddFilepath("������_2", "Resource/endingtexture/������/2.png");
	FILEPATH_MANAGER->AddFilepath("������_3", "Resource/endingtexture/������/3.png");
	//UI��ȭâ(5)
	FILEPATH_MANAGER->AddFilepath("������_1", "Resource/endingtexture/������/1.png");
	FILEPATH_MANAGER->AddFilepath("������_2", "Resource/endingtexture/������/2.png");
	FILEPATH_MANAGER->AddFilepath("������_3", "Resource/endingtexture/������/3.png");

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

	//��Ż-----------------------------------------------------------------------------------------------------
	FILEPATH_MANAGER->AddFilepath("Xmesh_portal1", "Resource/Maptool/Meshes/portal/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_portal2", "Resource/Maptool/Meshes/portal/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_portal3", "Resource/Maptool/Meshes/portal/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_portal4", "Resource/Maptool/Meshes/portal/4/4.X");
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
	FILEPATH_MANAGER->AddFilepath("����_������", "Resource/Meshes/BossMonster/deathwing_ok/newX/deathWing.x");
	FILEPATH_MANAGER->AddFilepath("emergency", "Resource/Meshes/emergency.png");

	//===========================================================================================================
	//NPC
	//===========================================================================================================
	FILEPATH_MANAGER->AddFilepath("NPC_1", "Resource/Meshes/NPC/1/bandbloodelfmale.x");
	FILEPATH_MANAGER->AddFilepath("NPC_2", "Resource/Meshes/NPC/2/bandorcmale.x");
	FILEPATH_MANAGER->AddFilepath("NPC_3", "Resource/Meshes/NPC/3/bandtaurenmale.x");
	FILEPATH_MANAGER->AddFilepath("NPC_4", "Resource/Meshes/NPC/4/bandtrollmale.x");
	FILEPATH_MANAGER->AddFilepath("NPC_5", "Resource/Meshes/NPC/5/bandundeadmale.x");
	FILEPATH_MANAGER->AddFilepath("NPC_6", "Resource/Meshes/NPC/6/6.x");
	FILEPATH_MANAGER->AddFilepath("NPC_7", "Resource/Meshes/NPC/7/snowman.x");
	FILEPATH_MANAGER->AddFilepath("NPC_8", "Resource/Meshes/NPC/8/8.x");
	FILEPATH_MANAGER->AddFilepath("NPC_9", "Resource/Meshes/NPC/9/tauren_mountedcanoe.x");
	FILEPATH_MANAGER->AddFilepath("NPC_10","Resource/Meshes/NPC/10/arthas.x");


}
