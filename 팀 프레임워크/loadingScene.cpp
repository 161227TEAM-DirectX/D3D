#include "stdafx.h"
#include "loadingScene.h"

bool loadingScene::m_isChange = false;

loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	//로딩씬에 필요한 이미지들은 미리 로딩해둔다.
	DXIMG_MANAGER->AddDxImg("로딩화면", new cDxImg(FILEPATH_MANAGER->GetFilepath("로딩화면")));
	DXIMG_MANAGER->AddDxImg("loadingbar_move", new cDxImg(FILEPATH_MANAGER->GetFilepath("loadingbar_move")));
	DXIMG_MANAGER->AddDxImg("loadingbar_back", new cDxImg(FILEPATH_MANAGER->GetFilepath("loadingbar_back")));
	DXIMG_MANAGER->AddDxImg("loadingbar_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("loadingbar_cover")));


	m_pLoadingBar = new cDxImgBar("loadingbar_cover", "loadingbar_back", "loadingbar_move",
								  D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2 + 400), true);

	InitializeCriticalSection(&_cs);

	DWORD dwThID[2];
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadInit, this, NULL, &dwThID[1]));
	
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

	if (m_isChange /*&& m_pLoadingBar->IsFullBar()*/)
	{
		SCENEMANAGER->changeScene("gameSceneTwo");
	}

	LeaveCriticalSection(&_cs);
}

HRESULT loadingScene::ThreadInit(LPVOID lpVod)
{
	SoundLoading();
	XMeshStaticLoading();
	XMeshSkinnedLoading();
	UILoading();
	AniLoading();

	m_isChange = true;

	return S_OK;
}

void loadingScene::UILoading()
{
	DXIMG_MANAGER->AddDxImg("시작화면", new cDxImg(FILEPATH_MANAGER->GetFilepath("시작화면")));

	DXIMG_MANAGER->AddDxImg("btn_exit_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_exit_off")));
	DXIMG_MANAGER->AddDxImg("btn_exit_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_exit_over")));
	DXIMG_MANAGER->AddDxImg("btn_option_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_option_off")));
	DXIMG_MANAGER->AddDxImg("btn_option_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_option_over")));
	DXIMG_MANAGER->AddDxImg("btn_gameStart_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_gameStart_off")));
	DXIMG_MANAGER->AddDxImg("btn_gameStart_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_gameStart_over")));
	DXIMG_MANAGER->AddDxImg("btn_mapTool_off", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_mapTool_off")));
	DXIMG_MANAGER->AddDxImg("btn_mapTool_over", new cDxImg(FILEPATH_MANAGER->GetFilepath("btn_mapTool_over")));

	DXIMG_MANAGER->AddDxImg("Test_Inven", new cDxImg(FILEPATH_MANAGER->GetFilepath("Test_Inven")));
	DXIMG_MANAGER->AddDxImg("Test_Inven2", new cDxImg(FILEPATH_MANAGER->GetFilepath("Test_Inven2")));
	DXIMG_MANAGER->AddDxImg("quickSlotUI_back", new cDxImg(FILEPATH_MANAGER->GetFilepath("quickSlotUI_back")));

	DXIMG_MANAGER->AddDxImg("playerbar_back", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbar_back")));
	DXIMG_MANAGER->AddDxImg("playerbarHP_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbarHP_cover")));
	DXIMG_MANAGER->AddDxImg("playerbarHP_move", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbarHP_move")));
	DXIMG_MANAGER->AddDxImg("playerbarMP_cover", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbarMP_cover")));
	DXIMG_MANAGER->AddDxImg("playerbarMP_move", new cDxImg(FILEPATH_MANAGER->GetFilepath("playerbarMP_move")));

	//=======================================================================
	//test
	//=======================================================================
	DXIMG_MANAGER->AddDxImg("minimap", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimap")));
	DXIMG_MANAGER->AddDxImg("minimap2", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimap")));
	DXIMG_MANAGER->AddDxImg("minimap3", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimap3")));
	DXIMG_MANAGER->AddDxImg("minimapTest", new cDxImg(FILEPATH_MANAGER->GetFilepath("minimapTest")));

	DXIMG_MANAGER->AddDxImg("tileTest0", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest0")));
	DXIMG_MANAGER->AddDxImg("tileTest1", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest1")));
	DXIMG_MANAGER->AddDxImg("tileTest2", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest2")));
	DXIMG_MANAGER->AddDxImg("tileTest3", new cDxImg(FILEPATH_MANAGER->GetFilepath("tileTest3")));

	DXIMG_MANAGER->AddDxImg("splat_red_base", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_red_base")));
	DXIMG_MANAGER->AddDxImg("splat_green_base", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_green_base")));
	DXIMG_MANAGER->AddDxImg("splat_blue_base", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_blue_base")));
	DXIMG_MANAGER->AddDxImg("splat_black_base", new cDxImg(FILEPATH_MANAGER->GetFilepath("splat_black_base")));

	DXIMG_MANAGER->AddDxImg("miniPlayer", new cDxImg(FILEPATH_MANAGER->GetFilepath("miniPlayer")));
	DXIMG_MANAGER->AddDxImg("radar", new cDxImg(FILEPATH_MANAGER->GetFilepath("radar")));

}

void loadingScene::AniLoading()
{
	vector<cDxImg*> temp;

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
	XMESH_MANAGER->AddXmeshSkinned("도마뱀", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_도마뱀"), matRotate));
	XMESH_MANAGER->AddXmeshSkinned("데스윙", RM_SKINNED->getResource(FILEPATH_MANAGER->GetFilepath("몬스터_데스윙"), matRotate));
}

void loadingScene::SoundLoading()
{
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
	SOUNDMANAGER->addSound("몬스터대기", FILEPATH_MANAGER->GetFilepath("몬스터대기"));
	SOUNDMANAGER->addSound("몬스터공격", FILEPATH_MANAGER->GetFilepath("몬스터공격"));
	SOUNDMANAGER->addSound("몬스터죽음", FILEPATH_MANAGER->GetFilepath("몬스터죽음"));
}
