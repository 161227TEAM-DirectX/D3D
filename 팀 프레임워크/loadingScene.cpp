#include "stdafx.h"
#include "loadingScene.h"

bool loadingScene::m_isChange = false;
bool loadingScene::m_isChangeScene1 = false;
bool loadingScene::m_isChangeScene2 = false;
bool loadingScene::m_isChangeScene3 = false;
bool loadingScene::m_isChangeScene4 = false;

loadingScene::loadingScene()
{
	
}


loadingScene::~loadingScene()
{

}

HRESULT loadingScene::init()
{
	UILoading();
	AniLoading();
	
	FILEPATH_MANAGER->AddFilepath("로딩", "Resource/Sound/로딩.mp3");
	SOUNDMANAGER->addSound("로딩", FILEPATH_MANAGER->GetFilepath("로딩"), true, true);
	SOUNDMANAGER->play("로딩", 0.5f);

	m_pLoadingBar = new cDxImgBar("loadingbar_cover", "loadingbar_back", "loadingbar_move",
								  D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2 + 400), true);
	InitializeCriticalSection(&_cs);

	DWORD dwThID[6];
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadInit, this, NULL, &dwThID[1]));//로딩씬
	
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadInitScene1, this, NULL, &dwThID[2]));
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadInitScene2, this, NULL, &dwThID[3]));
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadInitScene3, this, NULL, &dwThID[4]));
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadInitScene4, this, NULL, &dwThID[5]));

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(m_pLoadingBar);
}

void loadingScene::update()
{
	m_pLoadingBar->updateLoading();
}

void loadingScene::render()
{
	EnterCriticalSection(&_cs);

	DXIMG_MANAGER->GetDxImg("로딩화면")->render();
	m_pLoadingBar->render();

	if (m_isChange
		&& m_isChangeScene1
		&& m_isChangeScene2 
		&& m_isChangeScene3 
		&& m_isChangeScene4
		&& m_pLoadingBar->IsFullBar()
		)
	{
		SOUNDMANAGER->stop("로딩");
		//SCENEMANAGER->changeScene("test");

		//g_isMaptool = true;
		//SCENEMANAGER->changeScene("maptool");

		SCENEMANAGER->changeScene("start");			
		//SCENEMANAGER->changeScene("EndingScene");		
		//ENEMANAGER->changeScene("gameSceneOne");		//gameSceneOne
		//SCENEMANAGER->changeScene("gameSceneTwo");	//gameSceneTwo
		//SCENEMANAGER->changeScene("gameSceneThree");	//gameSceneThree
		//SCENEMANAGER->changeScene("gameSceneFour");	//gameSceneFour
		//SCENEMANAGER->changeScene("EndingScene");		//gameSceneTwo
		//SCENEMANAGER->changeScene("kims");			//kims
		//SCENEMANAGER->changeScene("AItest");			//AItest
		
	}
	LeaveCriticalSection(&_cs);
}

HRESULT loadingScene::ThreadInit(LPVOID lpVod)
{
	//맵툴모드이면 스테틱메쉬를 로드하자...
	if (g_eSelectMode == E_MAPTOOL)
	{
		XMeshStaticLoading();
	}

	XMeshSkinnedLoading();
	PtcLoading();
	SoundLoading();

	m_isChange = true;

	return S_OK;
}

HRESULT loadingScene::ThreadInitScene1(LPVOID lpVod)
{
	ex_pStage1->loadingStage();
	m_isChangeScene1 = true;
	return S_OK;
}

HRESULT loadingScene::ThreadInitScene2(LPVOID lpVod)
{
	ex_pStage2->loadingScene();
	m_isChangeScene2 = true;
	return S_OK;
}

HRESULT loadingScene::ThreadInitScene3(LPVOID lpVod)
{
	ex_pStage3->loadingStage();
	m_isChangeScene3 = true;
	return S_OK;
}

HRESULT loadingScene::ThreadInitScene4(LPVOID lpVod)
{
	ex_pStage4->loadingStage();
	m_isChangeScene4 = true;
	return S_OK;
}



void loadingScene::UILoading()
{
	//로딩씬에 필요한 이미지
	DXIMG_MANAGER->AddDxImg("로딩화면", new cDxImg(FILEPATH_MANAGER->GetFilepath("로딩화면")));
	DXIMG_MANAGER->AddDxImg("loadingbar_move", new cDxImg(FILEPATH_MANAGER->GetFilepath("loadingbar_move")));
	DXIMG_MANAGER->AddDxImg("loadingbar_back", new cDxImg(FILEPATH_MANAGER->GetFilepath("loadingbar_back")));
	DXIMG_MANAGER->AddDxImg("loadingbar_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("loadingbar_cover")));

	DXIMG_MANAGER->AddDxImg("시작화면", new cDxImg(FILEPATH_MANAGER->GetFilepath("시작화면")));

	DXIMG_MANAGER->AddDxImg("btn_exit_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_exit_off")));
	DXIMG_MANAGER->AddDxImg("btn_exit_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_exit_over")));
	DXIMG_MANAGER->AddDxImg("btn_option_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_option_off")));
	DXIMG_MANAGER->AddDxImg("btn_option_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_option_over")));
	DXIMG_MANAGER->AddDxImg("btn_gameStart_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_gameStart_off")));
	DXIMG_MANAGER->AddDxImg("btn_gameStart_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_gameStart_over")));
	DXIMG_MANAGER->AddDxImg("btn_mapTool_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_mapTool_off")));
	DXIMG_MANAGER->AddDxImg("btn_mapTool_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_mapTool_over")));

	DXIMG_MANAGER->AddDxImg("quickSlotUI_back", new cDxImg(FILEPATH_MANAGER->GetFilepath("quickSlotUI_back")));

	DXIMG_MANAGER->AddDxImg("playerbar_back", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbar_back")));
	DXIMG_MANAGER->AddDxImg("playerbarHP_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbarHP_cover")));
	DXIMG_MANAGER->AddDxImg("playerbarHP_move", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbarHP_move")));
	DXIMG_MANAGER->AddDxImg("playerbarMP_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbarMP_cover")));
	DXIMG_MANAGER->AddDxImg("playerbarMP_move", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbarMP_move")));

	DXIMG_MANAGER->AddDxImg("채팅창", new cDxImg(FILEPATH_MANAGER->GetFilepath("채팅창")));

	DXIMG_MANAGER->AddDxImg("shopSlot_back", new cDxImg(FILEPATH_MANAGER->GetFilepath("shopSlot_back")));
	DXIMG_MANAGER->AddDxImg("shopSlot_off00", new cDxImg(FILEPATH_MANAGER->GetFilepath("shopSlot_off00")));
	DXIMG_MANAGER->AddDxImg("shopSlot_off01", new cDxImg(FILEPATH_MANAGER->GetFilepath("shopSlot_off01")));
	DXIMG_MANAGER->AddDxImg("shopSlot_off02", new cDxImg(FILEPATH_MANAGER->GetFilepath("shopSlot_off02")));
	DXIMG_MANAGER->AddDxImg("shopSlot_over00", new cDxImg(FILEPATH_MANAGER->GetFilepath("shopSlot_over00")));
	DXIMG_MANAGER->AddDxImg("shopSlot_over01", new cDxImg(FILEPATH_MANAGER->GetFilepath("shopSlot_over01")));
	DXIMG_MANAGER->AddDxImg("shopSlot_over02", new cDxImg(FILEPATH_MANAGER->GetFilepath("shopSlot_over02")));

	DXIMG_MANAGER->AddDxImg("minimap", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimap")));
	DXIMG_MANAGER->AddDxImg("minimap_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimap_cover")));
	DXIMG_MANAGER->AddDxImg("minimap_player", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimap_player")));
	DXIMG_MANAGER->AddDxImg("btn_minimap_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_minimap_off")));
	DXIMG_MANAGER->AddDxImg("btn_minimap_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_minimap_on")));

	DXIMG_MANAGER->AddDxImg("worldmap_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap_cover")));
	DXIMG_MANAGER->AddDxImg("worldmap_point", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap_point")));


	DXIMG_MANAGER->AddDxImg("btn_invetory_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_invetory_off")));
	DXIMG_MANAGER->AddDxImg("btn_invetory_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_invetory_over")));

	DXIMG_MANAGER->AddDxImg("btn_skillbook_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skillbook_off")));
	DXIMG_MANAGER->AddDxImg("btn_skillbook_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skillbook_over")));

	DXIMG_MANAGER->AddDxImg("btn_worldmap_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_worldmap_off")));
	DXIMG_MANAGER->AddDxImg("btn_worldmap_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_worldmap_over")));

	DXIMG_MANAGER->AddDxImg("btn_quest_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_quest_off")));
	DXIMG_MANAGER->AddDxImg("btn_quest_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_quest_on")));

	DXIMG_MANAGER->AddDxImg("btn_questBox_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_questBox_off")));
	DXIMG_MANAGER->AddDxImg("btn_questBox_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_questBox_on")));

	DXIMG_MANAGER->AddDxImg("numbox_money", new cDxImg(FILEPATH_MANAGER->GetFilepath("numbox_money")));
	DXIMG_MANAGER->AddDxImg("numbox_soul", new cDxImg(FILEPATH_MANAGER->GetFilepath("numbox_soul")));

	DXIMG_MANAGER->AddDxImg("miniQuestBox", new cDxImg(FILEPATH_MANAGER->GetFilepath("miniQuestBox")));
	DXIMG_MANAGER->AddDxImg("questBox", new cDxImg(FILEPATH_MANAGER->GetFilepath("questBox")));

	DXIMG_MANAGER->AddDxImg("btn_skill00_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill00_off")));
	DXIMG_MANAGER->AddDxImg("btn_skill01_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill01_off")));
	DXIMG_MANAGER->AddDxImg("btn_skill02_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill02_off")));
	DXIMG_MANAGER->AddDxImg("btn_skill03_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill03_off")));
	DXIMG_MANAGER->AddDxImg("btn_skill04_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill04_off")));
	DXIMG_MANAGER->AddDxImg("btn_skill05_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill05_off")));
	DXIMG_MANAGER->AddDxImg("btn_skill06_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill06_off")));
	DXIMG_MANAGER->AddDxImg("btn_skill07_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill07_off")));

	DXIMG_MANAGER->AddDxImg("btn_skill00_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill00_on")));
	DXIMG_MANAGER->AddDxImg("btn_skill01_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill01_on")));
	DXIMG_MANAGER->AddDxImg("btn_skill02_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill02_on")));
	DXIMG_MANAGER->AddDxImg("btn_skill03_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill03_on")));
	DXIMG_MANAGER->AddDxImg("btn_skill04_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill04_on")));
	DXIMG_MANAGER->AddDxImg("btn_skill05_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill05_on")));
	DXIMG_MANAGER->AddDxImg("btn_skill06_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill06_on")));
	DXIMG_MANAGER->AddDxImg("btn_skill07_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_skill07_on")));

	DXIMG_MANAGER->AddDxImg("btn_gold_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_gold_off")));
	DXIMG_MANAGER->AddDxImg("btn_gold_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_gold_on")));

	DXIMG_MANAGER->AddDxImg("btn_soul_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_soul_off")));
	DXIMG_MANAGER->AddDxImg("btn_soul_on", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_soul_on")));





	DXIMG_MANAGER->AddDxImg("skillbookText00", new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbookText00")));
	DXIMG_MANAGER->AddDxImg("skillbookText01", new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbookText01")));
	DXIMG_MANAGER->AddDxImg("skillbookText02", new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbookText02")));
	DXIMG_MANAGER->AddDxImg("skillbookText03", new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbookText03")));
	DXIMG_MANAGER->AddDxImg("skillbookText04", new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbookText04")));
	DXIMG_MANAGER->AddDxImg("skillbookText05", new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbookText05")));
	DXIMG_MANAGER->AddDxImg("skillbookText06", new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbookText06")));
	DXIMG_MANAGER->AddDxImg("skillbookText07", new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbookText07")));

	DXIMG_MANAGER->AddDxImg("mouseCursor", new cDxImg(FILEPATH_MANAGER->GetFilepath("mouseCursor")));


	DXIMG_MANAGER->AddDxImg("이벤트씬_위", new cDxImg(FILEPATH_MANAGER->GetFilepath("이벤트씬")));
	DXIMG_MANAGER->AddDxImg("이벤트씬_아래", new cDxImg(FILEPATH_MANAGER->GetFilepath("이벤트씬")));

	
	DXIMG_MANAGER->AddDxImg("worldmap_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap_cover")));
	DXIMG_MANAGER->AddDxImg("worldmap", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap")));
	DXIMG_MANAGER->AddDxImg("worldmap2", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap2")));
	DXIMG_MANAGER->AddDxImg("worldmap3", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap3")));

	DXIMG_MANAGER->AddDxImg("worldmapView", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap")));
	DXIMG_MANAGER->AddDxImg("worldmap2View", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap2")));
	DXIMG_MANAGER->AddDxImg("worldmap3View", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap3")));

	DXIMG_MANAGER->AddDxImg("Miniworldmap", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmap")));

	DXIMG_MANAGER->AddDxImg("worldmapTest", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmapTest")));

	DXIMG_MANAGER->AddDxImg("chat_Icon", new cDxImg(FILEPATH_MANAGER->GetFilepath("chat_Icon")));
	DXIMG_MANAGER->AddDxImg("map_Icon", new cDxImg(FILEPATH_MANAGER->GetFilepath("map_Icon")));
	DXIMG_MANAGER->AddDxImg("quest_Icon", new cDxImg(FILEPATH_MANAGER->GetFilepath("quest_Icon")));
	DXIMG_MANAGER->AddDxImg("quest", new cDxImg(FILEPATH_MANAGER->GetFilepath("quest")));

	DXIMG_MANAGER->AddDxImg("gold_god", new cDxImg(FILEPATH_MANAGER->GetFilepath("gold_god")));
	DXIMG_MANAGER->AddDxImg("death_soul", new cDxImg(FILEPATH_MANAGER->GetFilepath("death_soul")));

	DXIMG_MANAGER->AddDxImg("bossbar_back", new cDxImg(FILEPATH_MANAGER->GetFilepath("bossbar_back")));
	DXIMG_MANAGER->AddDxImg("bossbar_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("bossbar_cover")));
	DXIMG_MANAGER->AddDxImg("bossbar_move", new cDxImg(FILEPATH_MANAGER->GetFilepath("bossbar_move")));
	DXIMG_MANAGER->AddDxImg("monsterbar_back", new cDxImg(FILEPATH_MANAGER->GetFilepath("monsterbar_back")));
	DXIMG_MANAGER->AddDxImg("monsterbar_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("monsterbar_cover")));
	DXIMG_MANAGER->AddDxImg("monsterbar_move", new cDxImg(FILEPATH_MANAGER->GetFilepath("monsterbar_move")));






	//=======================================================================
	// Test
	//=======================================================================
	
	// DXIMG
	DXIMG_MANAGER->AddDxImg("minimap", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimap")));
	DXIMG_MANAGER->AddDxImg("minimap2", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimap")));
	DXIMG_MANAGER->AddDxImg("minimap3", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimap3")));
	DXIMG_MANAGER->AddDxImg("minimapTest", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimapTest")));

	DXIMG_MANAGER->AddDxImg("tileTest0", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest0")));
	DXIMG_MANAGER->AddDxImg("tileTest1", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest1")));
	DXIMG_MANAGER->AddDxImg("tileTest2", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest2")));
	DXIMG_MANAGER->AddDxImg("tileTest3", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest3")));
	DXIMG_MANAGER->AddDxImg("tileTest4", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest4")));
	DXIMG_MANAGER->AddDxImg("tileTest5", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest5")));
	DXIMG_MANAGER->AddDxImg("tileTest6", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest6")));
	DXIMG_MANAGER->AddDxImg("tileTest7", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest7")));
	DXIMG_MANAGER->AddDxImg("tileTest8", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest8")));
	DXIMG_MANAGER->AddDxImg("tileTest9", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest9")));
	DXIMG_MANAGER->AddDxImg("tileTest10", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest10")));
	DXIMG_MANAGER->AddDxImg("tileTest11", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest11")));
	DXIMG_MANAGER->AddDxImg("tileTest12", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest12")));


	DXIMG_MANAGER->AddDxImg("tileTest0_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest0_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest1_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest1_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest2_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest2_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest3_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest3_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest4_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest4_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest5_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest5_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest6_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest6_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest7_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest7_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest8_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest8_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest9_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest9_mapTool")));
	DXIMG_MANAGER->AddDxImg("tileTest10_mapTool", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest10_mapTool")));


	DXIMG_MANAGER->AddDxImg("tileTestBase", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTestBase")));
	DXIMG_MANAGER->AddDxImg("splat_test0", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_test0")));
	DXIMG_MANAGER->AddDxImg("splat_test1", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_test1")));
	DXIMG_MANAGER->AddDxImg("splat_test2", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_test2")));
	DXIMG_MANAGER->AddDxImg("splat_test3", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_test3")));



	DXIMG_MANAGER->AddDxImg("splat_red_base", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_red_base")));
	DXIMG_MANAGER->AddDxImg("splat_green_base", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_green_base")));
	DXIMG_MANAGER->AddDxImg("splat_blue_base", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_blue_base")));
	DXIMG_MANAGER->AddDxImg("splat_black_base", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_black_base")));
	DXIMG_MANAGER->AddDxImg("splat_base", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_base")));


	DXIMG_MANAGER->AddDxImg("tileTest_Select", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest_Select")));


	DXIMG_MANAGER->AddDxImg("Test_Inven", new cDxImg(FILEPATH_MANAGER->GetFilepath("Test_Inven")));
	DXIMG_MANAGER->AddDxImg("Test_Inven2", new cDxImg(FILEPATH_MANAGER->GetFilepath("Test_Inven2")));

	DXIMG_MANAGER->AddDxImg("miniPlayer", new cDxImg(FILEPATH_MANAGER->GetFilepath("miniPlayer")));
	DXIMG_MANAGER->AddDxImg("radar", new cDxImg(FILEPATH_MANAGER->GetFilepath("radar")));

	DXIMG_MANAGER->AddDxImg("상점슬롯", new cDxImg(FILEPATH_MANAGER->GetFilepath("상점슬롯")));
	DXIMG_MANAGER->AddDxImg("무기상점아이콘", new cDxImg(FILEPATH_MANAGER->GetFilepath("무기상점아이콘")));
	DXIMG_MANAGER->AddDxImg("물약상점아이콘", new cDxImg(FILEPATH_MANAGER->GetFilepath("물약상점아이콘")));
	DXIMG_MANAGER->AddDxImg("강화상점아이콘", new cDxImg(FILEPATH_MANAGER->GetFilepath("강화상점아이콘")));
	DXIMG_MANAGER->AddDxImg("인벤토리아이콘", new cDxImg(FILEPATH_MANAGER->GetFilepath("인벤토리아이콘")));

	DXIMG_MANAGER->AddDxImg("GrieverCursor", new cDxImg(FILEPATH_MANAGER->GetFilepath("GrieverCursor")));
	DXIMG_MANAGER->AddDxImg("rangeTest00", new cDxImg(FILEPATH_MANAGER->GetFilepath("rangeTest00")));
	DXIMG_MANAGER->AddDxImg("rangeTest01", new cDxImg(FILEPATH_MANAGER->GetFilepath("rangeTest01")));
	DXIMG_MANAGER->AddDxImg("rangeTest02", new cDxImg(FILEPATH_MANAGER->GetFilepath("rangeTest02")));
	DXIMG_MANAGER->AddDxImg("rangeTest03", new cDxImg(FILEPATH_MANAGER->GetFilepath("rangeTest03")));
	DXIMG_MANAGER->AddDxImg("rangeTest04", new cDxImg(FILEPATH_MANAGER->GetFilepath("rangeTest04")));
	DXIMG_MANAGER->AddDxImg("checkTest00", new cDxImg(FILEPATH_MANAGER->GetFilepath("checkTest00")));

	DXIMG_MANAGER->AddDxImg("worldmapTest", new cDxImg(FILEPATH_MANAGER->GetFilepath("worldmapTest")));

	DXIMG_MANAGER->AddDxImg("markCenter", new cDxImg(FILEPATH_MANAGER->GetFilepath("markCenter")));
	DXIMG_MANAGER->AddDxImg("markEast", new cDxImg(FILEPATH_MANAGER->GetFilepath("markEast")));
	DXIMG_MANAGER->AddDxImg("markNorth", new cDxImg(FILEPATH_MANAGER->GetFilepath("markNorth")));
	DXIMG_MANAGER->AddDxImg("markSouth", new cDxImg(FILEPATH_MANAGER->GetFilepath("markSouth")));
	DXIMG_MANAGER->AddDxImg("markWest", new cDxImg(FILEPATH_MANAGER->GetFilepath("markWest")));

	DXIMG_MANAGER->AddDxImg("gamemapTest", new cDxImg(FILEPATH_MANAGER->GetFilepath("gamemapTest")));

	DXIMG_MANAGER->AddDxImg("questBtn_Off", new cDxImg(FILEPATH_MANAGER->GetFilepath("questBtn_Off")));
	DXIMG_MANAGER->AddDxImg("questBtn_Over", new cDxImg(FILEPATH_MANAGER->GetFilepath("questBtn_Over")));
	DXIMG_MANAGER->AddDxImg("questSlot_Test", new cDxImg(FILEPATH_MANAGER->GetFilepath("questSlot_Test")));

	DXIMG_MANAGER->AddDxImg("skill0_On", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill0_On")));
	DXIMG_MANAGER->AddDxImg("skill1_On", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill1_On")));
	DXIMG_MANAGER->AddDxImg("skill2_On", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill2_On")));
	DXIMG_MANAGER->AddDxImg("skill3_On", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill3_On")));
	DXIMG_MANAGER->AddDxImg("skill4_On", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill4_On")));
	DXIMG_MANAGER->AddDxImg("skill5_On", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill5_On")));
	DXIMG_MANAGER->AddDxImg("skill6_On", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill6_On")));
	DXIMG_MANAGER->AddDxImg("skill7_On", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill7_On")));

	DXIMG_MANAGER->AddDxImg("skill0_Off", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill0_Off")));
	DXIMG_MANAGER->AddDxImg("skill1_Off", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill1_Off")));
	DXIMG_MANAGER->AddDxImg("skill2_Off", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill2_Off")));
	DXIMG_MANAGER->AddDxImg("skill3_Off", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill3_Off")));
	DXIMG_MANAGER->AddDxImg("skill4_Off", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill4_Off")));
	DXIMG_MANAGER->AddDxImg("skill5_Off", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill5_Off")));
	DXIMG_MANAGER->AddDxImg("skill6_Off", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill6_Off")));
	DXIMG_MANAGER->AddDxImg("skill7_Off", new cDxImg(FILEPATH_MANAGER->GetFilepath("skill7_Off")));

	DXIMG_MANAGER->AddDxImg("쿨타임0", new cDxImg(FILEPATH_MANAGER->GetFilepath("쿨타임")));
	DXIMG_MANAGER->AddDxImg("쿨타임1", new cDxImg(FILEPATH_MANAGER->GetFilepath("쿨타임")));
	DXIMG_MANAGER->AddDxImg("쿨타임2", new cDxImg(FILEPATH_MANAGER->GetFilepath("쿨타임")));
	DXIMG_MANAGER->AddDxImg("쿨타임3", new cDxImg(FILEPATH_MANAGER->GetFilepath("쿨타임")));
	DXIMG_MANAGER->AddDxImg("쿨타임4", new cDxImg(FILEPATH_MANAGER->GetFilepath("쿨타임")));
	DXIMG_MANAGER->AddDxImg("쿨타임5", new cDxImg(FILEPATH_MANAGER->GetFilepath("쿨타임")));
	DXIMG_MANAGER->AddDxImg("쿨타임6", new cDxImg(FILEPATH_MANAGER->GetFilepath("쿨타임")));
	DXIMG_MANAGER->AddDxImg("쿨타임7", new cDxImg(FILEPATH_MANAGER->GetFilepath("쿨타임")));

	DXIMG_MANAGER->AddDxImg("전체맵에서의위치", new cDxImg(FILEPATH_MANAGER->GetFilepath("전체맵에서의위치")));
	DXIMG_MANAGER->AddDxImg("전체맵테스트", new cDxImg(FILEPATH_MANAGER->GetFilepath("전체맵테스트")));

	DXIMG_MANAGER->AddDxImg("스킬설명0", new cDxImg(FILEPATH_MANAGER->GetFilepath("스킬설명")));
	DXIMG_MANAGER->AddDxImg("스킬설명1", new cDxImg(FILEPATH_MANAGER->GetFilepath("스킬설명")));
	DXIMG_MANAGER->AddDxImg("스킬설명2", new cDxImg(FILEPATH_MANAGER->GetFilepath("스킬설명")));
	DXIMG_MANAGER->AddDxImg("스킬설명3", new cDxImg(FILEPATH_MANAGER->GetFilepath("스킬설명")));
	DXIMG_MANAGER->AddDxImg("스킬설명4", new cDxImg(FILEPATH_MANAGER->GetFilepath("스킬설명")));
	DXIMG_MANAGER->AddDxImg("스킬설명5", new cDxImg(FILEPATH_MANAGER->GetFilepath("스킬설명")));
	DXIMG_MANAGER->AddDxImg("스킬설명6", new cDxImg(FILEPATH_MANAGER->GetFilepath("스킬설명")));
	DXIMG_MANAGER->AddDxImg("스킬설명7", new cDxImg(FILEPATH_MANAGER->GetFilepath("스킬설명")));

	DXIMG_MANAGER->AddDxImg("죽었을때화면", new cDxImg(FILEPATH_MANAGER->GetFilepath("죽었을때화면")));
	DXIMG_MANAGER->AddDxImg("YOU DIED", new cDxImg(FILEPATH_MANAGER->GetFilepath("YOU DIED")));

	DXIMG_MANAGER->AddDxImg("dragon_soul", new cDxImg(FILEPATH_MANAGER->GetFilepath("dragon_soul")));
	DXIMG_MANAGER->AddDxImg("money_gold", new cDxImg(FILEPATH_MANAGER->GetFilepath("money_gold")));

	DXIMG_MANAGER->AddDxImg("mouse", new cDxImg(FILEPATH_MANAGER->GetFilepath("mouse")));

	DXIMG_MANAGER->AddDxImg("partTest", new cDxImg(FILEPATH_MANAGER->GetFilepath("partTest")));


	//텍스쳐를 저장하자.
	TEXTURE_MANAGER->GetTexture(FILEPATH_MANAGER->GetFilepath("splat_base"));


	//스테틱메쉬를 저장하자.
	//MESHSTATIC_MANAGER->AddMeshStatic("GunShip", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("GunShip")));

}


void loadingScene::AniLoading()
{
	vector<cDxImg*> temp;

	//======================================================================================================
	//  Skill Book
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 38; i++)
	{
		if (i < 10)
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbook0" + to_string(i))));
		}
		else	//11~99까지
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("skillbook" + to_string(i))));
		}
	}
	DXIMGANI_MANAGER->AddDxImgAni("skillbook01", temp, ST_DXIMGANI(3));




	//======================================================================================================
	//  force
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 53; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("force_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("force", temp, ST_DXIMGANI(2));

	temp.clear();
	for (int i = 1; i <= 53; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("force2_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("force2", temp, ST_DXIMGANI(2));
	//======================================================================================================
	//  Sword1
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <=20; i++)
	{
		if (i < 10)
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword1_0" + to_string(i))));
		}
		else	//11~99까지
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword1_" + to_string(i))));
		}
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Sword1", temp, ST_DXIMGANI(2));

	//======================================================================================================
	//  Sword2
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 20; i++)
	{
		if (i < 10)
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword2_0" + to_string(i))));
		}
		else	//11~99까지
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword2_" + to_string(i))));
		}
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Sword2", temp, ST_DXIMGANI(2));

	//======================================================================================================
	//  Sword3
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 20; i++)
	{
		if (i < 10)
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword3_0" + to_string(i))));
		}
		else	//11~99까지
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword3_" + to_string(i))));
		}
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Sword3", temp, ST_DXIMGANI(2));

	//======================================================================================================
	//  Sword4
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 20; i++)
	{
		if (i < 10)
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword4_0" + to_string(i))));
		}
		else	//11~99까지
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword4_" + to_string(i))));
		}
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Sword4", temp, ST_DXIMGANI(2));

	//======================================================================================================
	//  Sword5
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 20; i++)
	{
		if (i < 10)
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword5_0" + to_string(i))));
		}
		else	//11~99까지
		{
			temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Sword5_" + to_string(i))));
		}
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Sword5", temp, ST_DXIMGANI(2));

	//======================================================================================================
	//  NPC김태승
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 3; i++)
	{	
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("김태승_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("김태승", temp, ST_DXIMGANI(100));
	//======================================================================================================
	//  NPC이현총
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 3; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("이현총_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("이현총", temp, ST_DXIMGANI(100));
	//======================================================================================================
	//  NPC김만웅1
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 3; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("김만웅_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("김만웅", temp, ST_DXIMGANI(100));
	//======================================================================================================
	//  NPC이현수
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 3; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("이현수_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("이현수", temp, ST_DXIMGANI(100));
	//======================================================================================================
	//  NPC김태승
	//======================================================================================================
	temp.clear();
	for (int i = 1; i <= 3; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("김태훈_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("김태훈", temp, ST_DXIMGANI(100));



	//======================================================================================================
	//  Fire01
	//======================================================================================================
	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_0", temp, ST_DXIMGANI(1));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");


	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_1", temp, ST_DXIMGANI(2));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");


	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_2", temp, ST_DXIMGANI(3));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_3", temp, ST_DXIMGANI(4));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_4", temp, ST_DXIMGANI(5));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_5", temp, ST_DXIMGANI(6));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_6", temp, ST_DXIMGANI(7));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_7", temp, ST_DXIMGANI(8));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_8", temp, ST_DXIMGANI(9));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_9", temp, ST_DXIMGANI(1));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_10", temp, ST_DXIMGANI(2));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_11", temp, ST_DXIMGANI(3));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_12", temp, ST_DXIMGANI(4));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_13", temp, ST_DXIMGANI(5));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_14", temp, ST_DXIMGANI(6));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_15", temp, ST_DXIMGANI(7));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_16", temp, ST_DXIMGANI(8));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_17", temp, ST_DXIMGANI(9));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_18", temp, ST_DXIMGANI(1));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_19", temp, ST_DXIMGANI(2));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_20", temp, ST_DXIMGANI(3));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_21", temp, ST_DXIMGANI(4));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_22", temp, ST_DXIMGANI(5));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_23", temp, ST_DXIMGANI(6));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_24", temp, ST_DXIMGANI(7));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_25", temp, ST_DXIMGANI(8));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_26", temp, ST_DXIMGANI(9));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_27", temp, ST_DXIMGANI(1));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_28", temp, ST_DXIMGANI(2));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_29", temp, ST_DXIMGANI(3));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");

	temp.clear();
	for (int i = 0; i < 10; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_0" + to_string(i))));
	}
	for (int i = 10; i < 33; i++)
	{
		temp.push_back(new cDxImg(FILEPATH_MANAGER->GetFilepath("Ani_Fire01_" + to_string(i))));
	}
	DXIMGANI_MANAGER->AddDxImgAni("Ani_Fire01_30", temp, ST_DXIMGANI(4));
	DXIMGANI_MANAGER->setAniOverlap("Ani_Fire01");
}


void loadingScene::PtcLoading()
{
	PTM->LoadImgInit();					//파티클텍스쳐_매니져 초기화(순서1)
	PSM->ParticleSystemSetInit();		//파티클시스템_매니져 초기화(순서2)
	SKM->skillSetting();				//스킬 매니저 초기화(순서3)
	EFFECT->EffectSetting();			//이펙트 매니저 초기화(똑같이 순서3)

}


void loadingScene::XMeshStaticLoading()
{
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 0.5f, 0.5f, 0.5f);

	XMESH_MANAGER->AddXmeshStatic("ob000", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob000"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob001", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob001"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob002", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob002"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob003", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob003"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob004", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob004"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob005", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob005"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob006", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob006"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob007", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob007"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob008", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob008"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob009", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob009"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob010", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob010"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob011", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob011"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob012", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob012"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob013", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob013"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob014", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob014"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob015", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob015"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob017", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob017"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob018", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob018"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob019", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob019"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob020", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob020"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob021", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob021"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob022", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob022"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob023", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob023"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob024", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob024"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob025", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob025"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob026", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob026"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob027", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob027"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob028", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob028"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob029", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob029"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob030", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob030"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob031", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob031"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob032", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob032"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob034", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob034"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob035", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob035"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob036", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob036"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob037", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob037"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob038", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob038"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob039", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob039"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob040", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob040"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob041", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob041"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob042", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob042"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob043", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob043"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob044", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob044"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob045", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob045"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob046", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob046"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob047", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob047"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob048", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob048"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob050", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob050"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob051", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob051"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob052", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob052"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob053", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob053"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob054", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob054"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob055", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob055"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob056", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob056"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob057", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob057"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob058", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob058"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob059", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob059"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob060", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob060"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob061", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob061"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob062", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob062"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob063", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob063"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob064", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob064"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob065", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob065"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob066", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob066"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob067", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob067"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob068", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob068"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob069", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob069"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob070", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob070"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob071", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob071"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob072", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob072"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob073", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob073"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob074", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob074"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob075", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob075"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob076", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob076"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob077", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob077"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob078", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob078"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob079", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob079"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob080", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob080"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob081", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob081"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob082", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob082"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob083", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob083"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob084", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob084"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob085", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob085"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob086", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob086"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob087", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob087"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob088", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob088"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob089", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob089"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob090", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob090"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob091", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob091"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob092", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob092"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob093", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob093"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob094", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob094"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob095", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob095"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob096", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob096"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob097", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob097"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob098", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob098"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob099", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob099"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob100", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob100"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob101", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob101"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob102", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob102"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob103", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob103"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob104", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob104"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob105", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob105"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob106", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob106"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob107", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob107"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob108", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob108"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob109", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob109"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob110", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob110"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob111", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob111"), scale));
	
	XMESH_MANAGER->AddXmeshStatic("ob112", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob112"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob113", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob113"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob114", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob114"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob115", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob115"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob116", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob116"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob117", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob117"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob118", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob118"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob119", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob119"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob120", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob120"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob121", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob121"), scale));
	
	XMESH_MANAGER->AddXmeshStatic("ob122", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob122"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob123", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob123"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob124", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob124"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob125", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob125"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob126", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob126"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob127", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob127"), scale));
	
	XMESH_MANAGER->AddXmeshStatic("ob128", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob128"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob129", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob129"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob130", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob130"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob131", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob131"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob132", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob132"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob133", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob133"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob134", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob134"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob135", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob135"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob136", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob136"), scale));
	
	XMESH_MANAGER->AddXmeshStatic("ob137", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob137"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob138", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob138"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob139", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob139"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob140", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob140"), scale));
	
	XMESH_MANAGER->AddXmeshStatic("ob141", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob141"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob142", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob142"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob143", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob143"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob144", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob144"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob145", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob145"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob146", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob146"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob147", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob147"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob148", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob148"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob149", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob149"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob150", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob150"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob151", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob151"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob152", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob152"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob153", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob153"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob154", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob154"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob155", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob155"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob156", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob156"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob157", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob157"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob158", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob158"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob159", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob159"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob160", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob160"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob161", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob161"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob162", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob162"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob163", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob163"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob164", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob164"), scale));
	
	XMESH_MANAGER->AddXmeshStatic("ob165", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob165"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob166", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob166"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob167", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob167"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob168", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob168"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob169", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob169"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob170", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob170"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob171", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob171"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob172", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob172"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob173", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob173"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob174", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob174"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob175", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob175"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob176", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob176"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob177", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob177"), scale));
	
	XMESH_MANAGER->AddXmeshStatic("ob178", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob178"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob179", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob179"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob180", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob180"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob181", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob181"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob182", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob182"), scale));
	
	XMESH_MANAGER->AddXmeshStatic("ob183", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob183"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob184", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob184"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob185", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob185"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob186", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob186"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob187", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob187"), scale));

	//포탈--------------------------------------------------------------------------------------------------------------
	XMESH_MANAGER->AddXmeshStatic("portal1", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal1"), scale));
	XMESH_MANAGER->AddXmeshStatic("portal2", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal2"), scale));
	XMESH_MANAGER->AddXmeshStatic("portal3", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal3"), scale));
	XMESH_MANAGER->AddXmeshStatic("portal4", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal4"), scale));
}

void loadingScene::XMeshSkinnedLoading()
{
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

	XMESH_MANAGER->AddXmeshSkinned("골렘", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_골렘"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("개", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_개"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("멧돼지", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_멧돼지"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("나무짐승", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_나무짐승"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("브루탈루스", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_브루탈루스"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("히드라", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_히드라"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("새", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_새"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("악어", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_악어"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("곰", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_곰"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("둠가드", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_둠가드"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("하피", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_하피"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("랩터", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_랩터"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("전갈", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_전갈"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("도마뱀", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_도마뱀"),matRotate));
	XMESH_MANAGER->AddXmeshSkinned("데스윙", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_데스윙"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc1", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_1"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc2", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_2"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc3", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_3"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc4", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_4"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc5", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_5"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc6", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_6"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc7", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_7"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc8", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_8"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc9", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_9"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("npc10", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("NPC_10"), matRotate));
}

void loadingScene::SoundLoading()
{
	//시작화면
	SOUNDMANAGER->addSound("시작", FILEPATH_MANAGER->GetFilepath("시작"), true, true);
	//SOUNDMANAGER->addSound("시작화면선택", FILEPATH_MANAGER->GetFilepath("시작화면선택"), false, false);

	//플레이어/마을
	SOUNDMANAGER->addSound("마을1", FILEPATH_MANAGER->GetFilepath("마을"), true, true);
	SOUNDMANAGER->addSound("필드1", FILEPATH_MANAGER->GetFilepath("필드"), true, true);
	SOUNDMANAGER->addSound("보스1", FILEPATH_MANAGER->GetFilepath("보스"), true, true);
	SOUNDMANAGER->addSound("공격1", FILEPATH_MANAGER->GetFilepath("공격"), false, false);
	SOUNDMANAGER->addSound("베기1", FILEPATH_MANAGER->GetFilepath("베기"), false, false);
	SOUNDMANAGER->addSound("걸음소리1", FILEPATH_MANAGER->GetFilepath("걸음소리"), false, true);
	SOUNDMANAGER->addSound("걸음소리1one", FILEPATH_MANAGER->GetFilepath("걸음소리"), false, false);
	SOUNDMANAGER->addSound("말발굽소리1", FILEPATH_MANAGER->GetFilepath("말발굽소리"), false, true);
	SOUNDMANAGER->addSound("푸스로다!", FILEPATH_MANAGER->GetFilepath("푸스로다"), false, false);
	SOUNDMANAGER->addSound("휠윈드", FILEPATH_MANAGER->GetFilepath("휠윈드"), false, false);
	SOUNDMANAGER->addSound("불꽃", FILEPATH_MANAGER->GetFilepath("불꽃"), false, true);
	SOUNDMANAGER->addSound("힐링", FILEPATH_MANAGER->GetFilepath("힐링"), false, false);

	SOUNDMANAGER->addSound("천검폭파", FILEPATH_MANAGER->GetFilepath("천검폭파"), false, false);
	SOUNDMANAGER->addSound("천검후폭풍", FILEPATH_MANAGER->GetFilepath("천검후폭풍"), false, false);

	SOUNDMANAGER->addSound("쉴드1", FILEPATH_MANAGER->GetFilepath("쉴드1"), false, false);
	SOUNDMANAGER->addSound("쉴드2", FILEPATH_MANAGER->GetFilepath("쉴드2"), false, false);
	SOUNDMANAGER->addSound("매직슈터", FILEPATH_MANAGER->GetFilepath("매직슈터"), false, false);
	SOUNDMANAGER->addSound("번개", FILEPATH_MANAGER->GetFilepath("번개"), false, false);
	SOUNDMANAGER->addSound("별빛", FILEPATH_MANAGER->GetFilepath("별빛"), false, false);

	//몬스터/보스
	SOUNDMANAGER->addSound("샤우팅", FILEPATH_MANAGER->GetFilepath("보스울음소리"), false, false);
	SOUNDMANAGER->addSound("샤우팅2", FILEPATH_MANAGER->GetFilepath("보스울음소리2"), false, false);
	SOUNDMANAGER->addSound("샤우팅3", FILEPATH_MANAGER->GetFilepath("보스울음소리3"), false, false);
	SOUNDMANAGER->addSound("샤우팅4", FILEPATH_MANAGER->GetFilepath("보스울음소리4"), false, false);
	SOUNDMANAGER->addSound("보스공격1", FILEPATH_MANAGER->GetFilepath("보스공격1"));
	SOUNDMANAGER->addSound("보스공격2", FILEPATH_MANAGER->GetFilepath("보스공격2"));
	SOUNDMANAGER->addSound("보스공격3", FILEPATH_MANAGER->GetFilepath("보스공격3"));
	SOUNDMANAGER->addSound("보스공격4", FILEPATH_MANAGER->GetFilepath("보스공격4"));
	SOUNDMANAGER->addSound("보스죽음1", FILEPATH_MANAGER->GetFilepath("보스죽음1"));
	SOUNDMANAGER->addSound("보스죽음2", FILEPATH_MANAGER->GetFilepath("보스죽음2"));
	SOUNDMANAGER->addSound("보스숨소리1", FILEPATH_MANAGER->GetFilepath("보스숨소리1"), false, true);
	SOUNDMANAGER->addSound("보스숨소리2", FILEPATH_MANAGER->GetFilepath("보스숨소리2"), false, true);
	SOUNDMANAGER->addSound("브레스1", FILEPATH_MANAGER->GetFilepath("보스브레스"));
	SOUNDMANAGER->addSound("브레스2", FILEPATH_MANAGER->GetFilepath("보스브레스2"));
	SOUNDMANAGER->addSound("꼬리공격", FILEPATH_MANAGER->GetFilepath("꼬리공격"));
	SOUNDMANAGER->addSound("걷기", FILEPATH_MANAGER->GetFilepath("걷기"), false, true);
	SOUNDMANAGER->addSound("몬스터대기", FILEPATH_MANAGER->GetFilepath("몬스터대기"), false, true);
	SOUNDMANAGER->addSound("몬스터공격", FILEPATH_MANAGER->GetFilepath("몬스터공격"));
	SOUNDMANAGER->addSound("몬스터죽음", FILEPATH_MANAGER->GetFilepath("몬스터죽음"));
	SOUNDMANAGER->addSound("보스날기시작", FILEPATH_MANAGER->GetFilepath("보스날기시작"));
	SOUNDMANAGER->addSound("보스날기중", FILEPATH_MANAGER->GetFilepath("보스날기중"), false, true);
	SOUNDMANAGER->addSound("보스날기대기중", FILEPATH_MANAGER->GetFilepath("보스날기시작"), false, true);
	SOUNDMANAGER->addSound("파이어", FILEPATH_MANAGER->GetFilepath("파이어"), false, true);
	SOUNDMANAGER->addSound("파이어폭발", FILEPATH_MANAGER->GetFilepath("파이어폭발"));
	SOUNDMANAGER->addSound("플레임", FILEPATH_MANAGER->GetFilepath("플레임"), false, true);

	//맵툴배경, 엔딩배경
	SOUNDMANAGER->addSound("맵툴배경1", FILEPATH_MANAGER->GetFilepath("맵툴배경"), true, true);
	SOUNDMANAGER->addSound("엔딩배경1", FILEPATH_MANAGER->GetFilepath("엔딩배경"), true, true);
	SOUNDMANAGER->addSound("최종엔딩배경1", FILEPATH_MANAGER->GetFilepath("최종엔딩배경"), true, false);
}

