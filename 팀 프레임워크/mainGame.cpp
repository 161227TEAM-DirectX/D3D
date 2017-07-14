#include "stdafx.h"
#include "mainGame.h"

#include "startScene.h"
#include "mapToolScene.h"
//
#include "loadingScene.h"
//
#include "cTerrainTest2.h"
#include "cTerrainTest3.h"
#include "cCameraTest.h"
#include "cCutsceneTest.h"
#include "cUserInterfaceTest2.h"
#include "cCameraTest.h"
#include "cMinimapTest.h"
#include "cMinimapTest2.h"
#include "cMinimapPlayerTest.h"
//#include "cSkillBookTest.h"
//#include "cSkillTest.h"
#include "cImgPartRenderTest.h"
#include "cBossUITest.h"
//
//#include "EndingScene.h"
#include "kimsNewTest.h"

mainGame::mainGame()
{
	REGIST_SGT->Init();

	//SCENEMANAGER->addScene("kims", new kimsNewTest, false);

	//SCENEMANAGER->addScene("test", new cCutsceneTest, false);

	SCENEMANAGER->addScene("loading", new loadingScene, true);
	//SCENEMANAGER->addScene("test", new cBossUITest, false);

	//SCENEMANAGER->addScene("test", new cMinimapTest, false);
	//SCENEMANAGER->addScene("start", new startScene, false);
	//SCENEMANAGER->addScene("maptool", new mapToolScene, false);
	//SCENEMANAGER->addScene("particleTest5", new particleTest05, false);
	//SCENEMANAGER->addScene("particleTest6", new particleTest06, true);
	//SCENEMANAGER->addScene("particleTest13", new particleTest13, false);

	
	
	//SCENEMANAGER->addScene("particleTest5", new particleTest05, false);
	//SCENEMANAGER->addScene("particleTest13", new particleTest13, false);

	SCENEMANAGER->addScene("start", new startScene, false);
	SCENEMANAGER->addScene("gameSceneOne", ex_pStage1);
	SCENEMANAGER->addScene("gameSceneTwo", ex_pStage2);
	SCENEMANAGER->addScene("gameSceneThree", ex_pStage3);
	SCENEMANAGER->addScene("gameSceneFour", ex_pStage4);
	//SCENEMANAGER->addScene("EndingScene", ex_pEnding, false);

	//SCENEMANAGER->addScene("test", new cGameUITest, false);
	//SCENEMANAGER->addScene("test", new cMinimapTest, false);
	//SCENEMANAGER->addScene("AItest", new bossMonsterAITestScene);
}

mainGame::~mainGame()
{
	REGIST_SGT->Destroy();
}


HRESULT mainGame::init(void)
{
	
	return S_OK;
}



void mainGame::release(void)
{
}



void mainGame::update(void)
{
	//씬매니져 업데이트
	SCENEMANAGER->update();
	EFFECT->update();
	SKM->update();
	SOUNDMANAGER->update();
}



void mainGame::render(void)
{
	switch (g_eSelectMode)
	{
	case eSelectMode::E_GAME:
	{
		//버퍼를 청소하자
		HRESULT result = _device->Clear(
			0,			//청소할 영역의 D3D렉트 배열 갯수	(전체 클리어 0)
			NULL,		//청소할 영역의 D3D렉트 배열 포인터 (전체 클리어 NULL)
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, //청소될 버퍼 플래그 (컬러버퍼, 깊이버퍼, 스텐실버퍼)
			D3DCOLOR_XRGB(50, 50, 50),			//컬러버퍼를 청소하고 채워질 색상 (0xAARRGGBB)
			1.0f,								//깊이버퍼를 청소할 값 (0 ~ 1, 0이 카메라에서 제일 가깝고 1이 카메라에서 제일 멀다)
			0);									//스텐실 버퍼를 채울값

												//버퍼 청소가 성공했다면
		if (SUCCEEDED(result))
		{
			//디바이스 렌더링 시작
			_device->BeginScene();

			SCENEMANAGER->render();
			
			EFFECT->render();

			SKM->render();

			MOUSE_MANAGER->render();

			//디버그 모드에서만 실행
#ifdef _DEBUG 
			if (KEYMANAGER->isToggleKey(VK_F9))
			{
				//월드그리드 렌더
			GIZMOMANAGER->WorldGrid(1, 10);
			}
			if (KEYMANAGER->isToggleKey(VK_F8))
			{
				//타임매니져 렌더
				TIMEMANAGER->render();
			}
#endif	

			//디바이스 렌더 종료
			_device->EndScene();
			//렌더링된 버퍼내용을 화면에 전송
			_device->Present(0, 0, 0, 0);
		}
	}
	break;

	case eSelectMode::E_MAPTOOL:
		SCENEMANAGER->render();
		break;
	}
}

//==================================================================
//		## 메인프로시져 ## MainProc()
//==================================================================
LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	SCENEMANAGER->WndProc(hWnd, iMessage, wParam, lParam);

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
