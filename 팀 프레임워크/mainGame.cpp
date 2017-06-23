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
//		## �ʱ�ȭ ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	//===================================================================================
	//������ �� �׽�Ʈ �������
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
	//������ �� �׽�Ʈ �������
	//===================================================================================
		//���߰�
		SCENEMANAGER->addScene("testMON", new terrainPickingTest, false);



	//===================================================================================
	//�踸�� �� �׽�Ʈ �������
	//===================================================================================
		////���߰�
		//SCENEMANAGER->addScene("test", new cLoadingBarTest);
		//SCENEMANAGER->addScene("test", new cLoadingTest);
		//SCENEMANAGER->addScene("test", new cImageTest,false);



	//===================================================================================
	//������ �� �׽�Ʈ �������
	//===================================================================================
		SCENEMANAGER->addScene("test", new kimsNewTest, false);
		//SCENEMANAGER->addScene("test", new cubeLight, false);



	//===================================================================================
	//���½� �� �׽�Ʈ �������
	//===================================================================================


		//���ʱ�ȭ
		SCENEMANAGER->changeScene("test");
	return S_OK;
}

//==================================================================
//		## ���� ## release(void)
//==================================================================
void mainGame::release(void)
{
}

//==================================================================
//		## ������Ʈ ## update(void)
//==================================================================
void mainGame::update(void)
{
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
}

//==================================================================
//		## ���� ## render(void)
//==================================================================
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
