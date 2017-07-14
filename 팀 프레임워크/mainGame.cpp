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
	//���Ŵ��� ������Ʈ
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
		//���۸� û������
		HRESULT result = _device->Clear(
			0,			//û���� ������ D3D��Ʈ �迭 ����	(��ü Ŭ���� 0)
			NULL,		//û���� ������ D3D��Ʈ �迭 ������ (��ü Ŭ���� NULL)
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, //û�ҵ� ���� �÷��� (�÷�����, ���̹���, ���ٽǹ���)
			D3DCOLOR_XRGB(50, 50, 50),			//�÷����۸� û���ϰ� ä���� ���� (0xAARRGGBB)
			1.0f,								//���̹��۸� û���� �� (0 ~ 1, 0�� ī�޶󿡼� ���� ������ 1�� ī�޶󿡼� ���� �ִ�)
			0);									//���ٽ� ���۸� ä�ﰪ

												//���� û�Ұ� �����ߴٸ�
		if (SUCCEEDED(result))
		{
			//����̽� ������ ����
			_device->BeginScene();

			SCENEMANAGER->render();
			
			EFFECT->render();

			SKM->render();

			MOUSE_MANAGER->render();

			//����� ��忡���� ����
#ifdef _DEBUG 
			if (KEYMANAGER->isToggleKey(VK_F9))
			{
				//����׸��� ����
			GIZMOMANAGER->WorldGrid(1, 10);
			}
			if (KEYMANAGER->isToggleKey(VK_F8))
			{
				//Ÿ�ӸŴ��� ����
				TIMEMANAGER->render();
			}
#endif	

			//����̽� ���� ����
			_device->EndScene();
			//�������� ���۳����� ȭ�鿡 ����
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
//		## �������ν��� ## MainProc()
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
