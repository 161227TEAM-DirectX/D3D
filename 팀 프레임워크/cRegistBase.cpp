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
	//기본 설정 초기화
	//========================================================================
	SetRandomSeed();					//랜덤시드 초기화
	CreateDevice();						//디바이스 초기화
	


	//========================================================================
	//게임에 사용할 파일경로 등록
	//========================================================================
	FxRegist();							//Fx 경로 등록
	HeightRegist();						//높이맵 경로 등록
	TileRegist();						//타일맵 경로 등록
	SplatRegist();						//스플랫 경로 등록
	BrushRegist();						//브러쉬 경로 등록
	SoundRegist();						//사운드 경로 등록
	UIRegist();							//UI 경로 등록
	AniRegist();						//애니메이션(이미지) 경로 등록
	XMeshStaticRegist();				//X메쉬스태틱 경로 등록
	XMeshSkinnedRegist();				//X메쉬스키드 경로 등록



	//========================================================================
	//매니져 초기화
	//========================================================================
	KEYMANAGER->init();					//키매니져 초기화
	TIMEMANAGER->init();				//타임매니져 초기화
	SCENEMANAGER->init();				//씬매니져 초기화
	FONTMANAGER->init();				//폰트매니져 초기화
	GIZMOMANAGER->init();				//기즈모매니져 초기화
	RM_TEXTURE->init();					//RM텍스쳐 초기화
	RM_SHADERFX->init();				//RM셰이더FX 초기화
	RM_XMESH->init();					//RM스태틱X메쉬 초기화
	RM_SKINNED->init();					//RM스킨드X메쉬 초기화
	PHYSICSMANAGER->init();				//피직스매니져 초기화
	SPRITEMANAGER->init();				//스프라이트매니져 초기화
	PTM->LoadImgInit();					//파티클텍스쳐_매니져 초기화(순서1)
	PSM->ParticleSystemSetInit();		//파티클시스템_매니져 초기화(순서2)
	SKM->skillSetting();				//스킬 매니저 초기화(순서3)
	SOUNDMANAGER->init();				//사운드매니저초기화

	

}

void cRegistBase::Destroy()
{
	//키매니져 싱글톤 해제
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	//타임매니져 싱글톤 해제
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	//씬매니져 싱글톤 해제
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	//폰트매니져 싱글톤 해제
	FONTMANAGER->release();
	FONTMANAGER->releaseSingleton();
	//기즈모매니져 싱글톤 해제
	GIZMOMANAGER->release();
	GIZMOMANAGER->releaseSingleton();
	//리소스매니져 싱글톤 해제
	RM_TEXTURE->clearResource();
	RM_TEXTURE->releaseSingleton();
	RM_SHADERFX->clearResource();
	RM_SHADERFX->releaseSingleton();
	RM_XMESH->clearResource();
	RM_XMESH->releaseSingleton();
	RM_SKINNED->clearResource();
	RM_SKINNED->releaseSingleton();
	//피직스매니져 싱글톤 해제
	PHYSICSMANAGER->release();
	PHYSICSMANAGER->releaseSingleton();
	//스프라이트매니져 싱글톤 해제
	SPRITEMANAGER->release();
	SPRITEMANAGER->releaseSingleton();

	//스킬 매니져 싱글톤 해제(역순1)
	SKM->skillRelease();
	SKM->releaseSingleton();
	//파티클시스템매니져 싱글톤 해제(역순2)
	PSM->ParticleSystemSetRelease();
	PSM->releaseSingleton();
	//파티클시스템텍스쳐매니져 싱글톤 해제(역순3)
	PTM->releaseSingleton();
	PTM->ImgRelease();
	
	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	//디바이스 해제
	ReleaseDevice();
}



void cRegistBase::FxRegist()
{
	//FILEPATH_MANAGER->AddFilepath("FX_지형기본", "Resource/Maptool/Shaders/TerrainBase.fx");
}



void cRegistBase::HeightRegist()
{
	FILEPATH_MANAGER->AddFilepath("높이맵_1", "Resource/Maptool/Textures/RAW/1.png");
	FILEPATH_MANAGER->AddFilepath("높이맵_2", "Resource/Maptool/Textures/RAW/2.png");
	FILEPATH_MANAGER->AddFilepath("높이맵_3", "Resource/Maptool/Textures/RAW/3.png");
	FILEPATH_MANAGER->AddFilepath("높이맵_4", "Resource/Maptool/Textures/RAW/4.png");
	FILEPATH_MANAGER->AddFilepath("높이맵_5", "Resource/Maptool/Textures/RAW/5.png");
	FILEPATH_MANAGER->AddFilepath("높이맵_6", "Resource/Maptool/Textures/RAW/6.png");
}



void cRegistBase::TileRegist()
{
	FILEPATH_MANAGER->AddFilepath("타일맵_1", "Resource/Maptool/Textures/Tile/1.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_2", "Resource/Maptool/Textures/Tile/2.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_3", "Resource/Maptool/Textures/Tile/3.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_4", "Resource/Maptool/Textures/Tile/4.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_5", "Resource/Maptool/Textures/Tile/5.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_6", "Resource/Maptool/Textures/Tile/6.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_7", "Resource/Maptool/Textures/Tile/13.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_8", "Resource/Maptool/Textures/Tile/12.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_9", "Resource/Maptool/Textures/Tile/21.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_10", "Resource/Maptool/Textures/Tile/10.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_11", "Resource/Maptool/Textures/Tile/11.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_12", "Resource/Maptool/Textures/Tile/12.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_13", "Resource/Maptool/Textures/Tile/13.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_14", "Resource/Maptool/Textures/Tile/14.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_15", "Resource/Maptool/Textures/Tile/15.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_16", "Resource/Maptool/Textures/Tile/8.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_17", "Resource/Maptool/Textures/Tile/3.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_18", "Resource/Maptool/Textures/Tile/18.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_19", "Resource/Maptool/Textures/Tile/19.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_20", "Resource/Maptool/Textures/Tile/2.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_21", "Resource/Maptool/Textures/Tile/21.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_22", "Resource/Maptool/Textures/Tile/22.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_23", "Resource/Maptool/Textures/Tile/14.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_24", "Resource/Maptool/Textures/Tile/16.png");
	FILEPATH_MANAGER->AddFilepath("타일맵_25", "Resource/Maptool/Textures/Tile/4.png");
}



void cRegistBase::SplatRegist()
{
	FILEPATH_MANAGER->AddFilepath("스플랫_1", "Resource/Maptool/Textures/Splat/1.png");
	FILEPATH_MANAGER->AddFilepath("스플랫_2", "Resource/Maptool/Textures/Splat/2.png");
	FILEPATH_MANAGER->AddFilepath("스플랫_3", "Resource/Maptool/Textures/Splat/3.png");
	FILEPATH_MANAGER->AddFilepath("스플랫_4", "Resource/Maptool/Textures/Splat/4.png");
	FILEPATH_MANAGER->AddFilepath("스플랫_5", "Resource/Maptool/Textures/Splat/5.png");
	FILEPATH_MANAGER->AddFilepath("스플랫_6", "Resource/Maptool/Textures/Splat/6.png");
}



void cRegistBase::BrushRegist()
{
	FILEPATH_MANAGER->AddFilepath("브러쉬_brush00", "Resource/Maptool/Textures/Brush/brush00.png");
	FILEPATH_MANAGER->AddFilepath("브러쉬_brush01", "Resource/Maptool/Textures/Brush/brush01.png");
}



void cRegistBase::SoundRegist()
{
	FILEPATH_MANAGER->AddFilepath("필드", "Resource/Sound/FieldBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("보스", "Resource/Sound/BossBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("마을", "Resource/Sound/TownBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("공격", "Resource/Sound/공격1.mp3");
	FILEPATH_MANAGER->AddFilepath("베기", "Resource/Sound/베기1.mp3");
	FILEPATH_MANAGER->AddFilepath("걸음소리", "Resource/Sound/걸음소리1.mp3");
	FILEPATH_MANAGER->AddFilepath("보스울음소리", "Resource/Sound/deathWing/deathwing_shouting_good.mp3");
	FILEPATH_MANAGER->AddFilepath("보스울음소리2", "Resource/Sound/deathWing/event_deathwingattacks_roar_01.ogg");
	FILEPATH_MANAGER->AddFilepath("보스울음소리3", "Resource/Sound/deathWing/event_deathwingattacks_roar_03.ogg");
	FILEPATH_MANAGER->AddFilepath("보스울음소리4", "Resource/Sound/deathWing/event_deathwingattacks_roar_04.ogg");
	FILEPATH_MANAGER->AddFilepath("보스공격1", "Resource/Sound/deathWing/mon_deathwing_attack_02.ogg");
	FILEPATH_MANAGER->AddFilepath("보스공격2", "Resource/Sound/deathWing/mon_deathwing_attack_04.ogg");
	FILEPATH_MANAGER->AddFilepath("보스공격3", "Resource/Sound/deathWing/mon_deathwing_attack_10.ogg");
	FILEPATH_MANAGER->AddFilepath("보스공격4", "Resource/Sound/deathWing/mon_deathwing_wound_01.ogg");
	FILEPATH_MANAGER->AddFilepath("보스죽음1", "Resource/Sound/deathWing/mon_deathwing_death_09.ogg");
	FILEPATH_MANAGER->AddFilepath("보스죽음2", "Resource/Sound/deathWing/mon_deathwing_death_10.ogg");
	FILEPATH_MANAGER->AddFilepath("보스숨소리1", "Resource/Sound/deathWing/mon_deathwing_preaggro_03.ogg");
	FILEPATH_MANAGER->AddFilepath("보스숨소리2", "Resource/Sound/deathWing/mon_deathwing_preaggro_04.ogg");
	FILEPATH_MANAGER->AddFilepath("보스브레스", "Resource/Sound/deathWing/European_Dragon_Roaring_and_breathe_fire-daniel-simon.mp3");
	FILEPATH_MANAGER->AddFilepath("보스브레스2", "Resource/Sound/deathWing/flamebreath.ogg");
	FILEPATH_MANAGER->AddFilepath("꼬리공격", "Resource/Sound/deathWing/mdeathimpactcolossalgrassa.ogg");
	FILEPATH_MANAGER->AddFilepath("걷기", "Resource/Sound/deathWing/mdeathimpactgiantdirta.ogg");
	FILEPATH_MANAGER->AddFilepath("몬스터대기", "Resource/Sound/monster/ancientofarcane_aggro_01.ogg");
	FILEPATH_MANAGER->AddFilepath("몬스터공격", "Resource/Sound/monster/ancientofarcane_attack_02.ogg");
	FILEPATH_MANAGER->AddFilepath("몬스터죽음", "Resource/Sound/monster/ancientofarcane_death_02.ogg");
}



void cRegistBase::UIRegist()
{
	FILEPATH_MANAGER->AddFilepath("로딩화면", "ResourceUI/loading/로딩화면.png");
	FILEPATH_MANAGER->AddFilepath("시작화면", "ResourceUI/loading/시작화면.png");
	FILEPATH_MANAGER->AddFilepath("시작버튼_오버", "ResourceUI/loading/시작버튼_오버.png");
	FILEPATH_MANAGER->AddFilepath("시작버튼_오프", "ResourceUI/loading/시작버튼_오프.png");
	
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

	FILEPATH_MANAGER->AddFilepath("Test_Inven", "ResourceUI/game/Test_Inven.png");
	FILEPATH_MANAGER->AddFilepath("Test_Inven2", "ResourceUI/game/Test_Inven2.png");
	FILEPATH_MANAGER->AddFilepath("quickSlotUI_back", "ResourceUI/game/quickSlotUI_back.png");

	FILEPATH_MANAGER->AddFilepath("playerbar_back", "ResourceUI/game/playerbar_back.png");
	FILEPATH_MANAGER->AddFilepath("playerbarHP_cover", "ResourceUI/game/playerbarHP_cover.png");
	FILEPATH_MANAGER->AddFilepath("playerbarHP_move", "ResourceUI/game/playerbarHP_move.png");
	FILEPATH_MANAGER->AddFilepath("playerbarMP_cover", "ResourceUI/game/playerbarMP_cover.png");
	FILEPATH_MANAGER->AddFilepath("playerbarMP_move", "ResourceUI/game/playerbarMP_move.png");

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

	FILEPATH_MANAGER->AddFilepath("splat_red_base", "ResourceUI/test/splat_red_base.png");
	FILEPATH_MANAGER->AddFilepath("splat_green_base", "ResourceUI/test/splat_green_base.png");
	FILEPATH_MANAGER->AddFilepath("splat_blue_base", "ResourceUI/test/splat_blue_base.png");
	FILEPATH_MANAGER->AddFilepath("splat_black_base", "ResourceUI/test/splat_black_base.png");

	FILEPATH_MANAGER->AddFilepath("miniPlayer", "ResourceUI/test/miniPlayer.png");
	FILEPATH_MANAGER->AddFilepath("radar", "ResourceUI/test/radar.png");

	FILEPATH_MANAGER->AddFilepath("height_base", "ResourceUI/test/height_base.png");

	FILEPATH_MANAGER->AddFilepath("StaticMesh", "ResourceUI/test/fx/StaticMesh.fx");
	FILEPATH_MANAGER->AddFilepath("diffuseDefault", "ResourceUI/test/meshTx/diffuseDefault.png");
	FILEPATH_MANAGER->AddFilepath("normalDefault", "ResourceUI/test/meshTx/normalDefault.png");
	FILEPATH_MANAGER->AddFilepath("specularDefault", "ResourceUI/test/meshTx/specularDefault.png");
	FILEPATH_MANAGER->AddFilepath("emissionDefault", "ResourceUI/test/meshTx/emissionDefault.png");

	FILEPATH_MANAGER->AddFilepath("FX_지형기본", "ResourceUI/test/fx/TerrainBase.fx");

}



void cRegistBase::AniRegist()
{
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
	FILEPATH_MANAGER->AddFilepath("몬스터_골렘", "Resource/Meshes/monster/arcanegolem_ok/x/golem2.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_개", "Resource/Meshes/monster/Beargod_ok/x/beargod.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_멧돼지", "Resource/Meshes/monster/boar_ok/x/boar.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_나무짐승", "Resource/Meshes/monster/bogbeast_ok/x/bogbeast.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_브루탈루스", "Resource/Meshes/monster/Brutallus_ok/x/brutallus.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_히드라", "Resource/Meshes/monster/chimerabeast_ok/x/chimerabeast.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_새", "Resource/Meshes/monster/cockatriceelite_ok/x/cockatriceelite.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_악어", "Resource/Meshes/monster/crocodile_ok/x/crocodile.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_곰", "Resource/Meshes/monster/direfurbolg_ok/x/direfurbolg.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_둠가드", "Resource/Meshes/monster/doomguard_ok/x/doomguard.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_하피", "Resource/Meshes/monster/harpy_ok/x/harpy.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_랩터", "Resource/Meshes/monster/raptor_ok/x/raptor.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_전갈", "Resource/Meshes/monster/scorpion_ok/x/scorpion.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_도마뱀", "Resource/Meshes/monster/thunderlizard_ok/x/thunderlizard.x");
	FILEPATH_MANAGER->AddFilepath("몬스터_데스윙", "Resource/Meshes/BossMonster/deathwing_ok/x/deathWing.x");
}
