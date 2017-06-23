#include "stdafx.h"
#include "mainGame.h"

#include "startScene.h"
#include "loadingScene.h"
#include "mapToolScene.h"
#include "cTerrainTest.h"
#include "cImageTest.h"
#include "cButtonTest.h"

mainGame::mainGame()
{
	REGIST_SGT->Init();

	//SCENEMANAGER->addScene("loading", new loadingScene, false);

	//SCENEMANAGER->addScene("start", new startScene, false);
	//SCENEMANAGER->addScene("maptool", new mapToolScene, false);
	//SCENEMANAGER->addScene("particleTest13", new particleTest13, false);
	//SCENEMANAGER->addScene("test", new cButtonTest, false);
	//SCENEMANAGER->addScene("gameSceneOne", new stageOne, false);
	//SCENEMANAGER->addScene("gameSceneTwo", new stageTwo, false);
	//SCENEMANAGER->addScene("gameSceneThree", new stageThree, false);
}

mainGame::~mainGame()
{
	REGIST_SGT->Destroy();
}


//==================================================================
//		## 초기화 ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	//===================================================================================
	//이현총 씬 테스트 헤더파일
	//===================================================================================
		//SCENEMANAGER->addScene("test", new particleTest);
		//SCENEMANAGER->addScene("test", new particleTest02);
		//SCENEMANAGER->addScene("test", new particleTest03);
		//SCENEMANAGER->addScene("test", new particleTest04);
		//SCENEMANAGER->addScene("test", new particleTest05);
		//SCENEMANAGER->addScene("test", new particleTest06);
		//SCENEMANAGER->addScene("test", new particleTest07);
		//SCENEMANAGER->addScene("test", new particleTest08);
		//SCENEMANAGER->addScene("test", new particleTest09);
		//SCENEMANAGER->addScene("test", new particleTest10);



	//===================================================================================
	//이현수 씬 테스트 헤더파일
	//===================================================================================
		//씬추가
		SCENEMANAGER->addScene("testMON", new terrainPickingTest, false);



	//===================================================================================
	//김만웅 씬 테스트 헤더파일
	//===================================================================================
		////씬추가
		//SCENEMANAGER->addScene("test", new cLoadingBarTest);
		//SCENEMANAGER->addScene("test", new cLoadingTest);
		//SCENEMANAGER->addScene("test", new cImageTest,false);



	//===================================================================================
	//김태훈 씬 테스트 헤더파일
	//===================================================================================
		SCENEMANAGER->addScene("test", new kimsNewTest, false);
		//SCENEMANAGER->addScene("test", new cubeLight, false);



	//===================================================================================
	//김태승 씬 테스트 헤더파일
	//===================================================================================


		//씬초기화
		SCENEMANAGER->changeScene("test");
	return S_OK;
}

//==================================================================
//		## 해제 ## release(void)
//==================================================================
void mainGame::release(void)
{
}

//==================================================================
//		## 업데이트 ## update(void)
//==================================================================
void mainGame::update(void)
{
	//씬매니져 업데이트
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
}

//==================================================================
//		## 렌더 ## render(void)
//==================================================================
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
