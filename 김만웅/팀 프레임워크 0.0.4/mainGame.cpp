#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
	//�Ŵ��� �ʱ�ȭ
	this->initManager();	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//������ ��
	//~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ", new particleTest);
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ2", new particleTest02);
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ3", new particleTest03);
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ4", new particleTest04);
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ5", new particleTest05);
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ6", new particleTest06);
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ7", new particleTest07);
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ8", new particleTest08);
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ9", new particleTest09);
	//SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ10", new particleTest10);


	//~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//������ ��
	//~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//SCENEMANAGER->addScene("test", new terrainPickingTest);


	//~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//�踸�� �� �׽�Ʈ �������
	//~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//SCENEMANAGER->addScene("test", new cLoadingBarTest);
	//SCENEMANAGER->addScene("test", new cLoadingTest);
	SCENE_MANAGER->AddScene("���׽�Ʈ", new cSceneTest);


	//~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//������ �� �׽�Ʈ �������
	//~~~~~~~~~~~~~~~~~~~~~~~~~~//


	//~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//���½� �� �׽�Ʈ �������
	//~~~~~~~~~~~~~~~~~~~~~~~~~~//


	//�� ü����
	switch(g_eSceneManager)
	{
	case eSceneManager::E_GAMENODE:
		SCENEMANAGER->changeScene("��ƼŬ �׽�Ʈ7");
		break;
	case eSceneManager::E_ISCENE:
		SCENE_MANAGER->ChangeScene("���׽�Ʈ");
		break;
	}
}



mainGame::~mainGame()
{
	SCENE_MANAGER->Destroy();

	//�Ŵ��� ����
	this->releaseManager();	
}



void mainGame::update(void)
{
	switch(g_eSceneManager)
	{
	case eSceneManager::E_GAMENODE:
		SCENEMANAGER->update();
		break;
	case eSceneManager::E_ISCENE:
		SCENE_MANAGER->Update();
		break;
	}
}



void mainGame::render(void)
{
	//���۸� û������
	HRESULT result = _device->Clear(
		0,			//û���� ������ D3D��Ʈ �迭 ����	(��ü Ŭ���� 0)
		NULL,		//û���� ������ D3D��Ʈ �迭 ������ (��ü Ŭ���� NULL)
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, //û�ҵ� ���� �÷��� (�÷�����, ���̹���, ���ٽǹ���)
		D3DCOLOR_XRGB(100,100,100),			//�÷����۸� û���ϰ� ä���� ���� (0xAARRGGBB)
		1.0f,								//���̹��۸� û���� �� (0 ~ 1, 0�� ī�޶󿡼� ���� ������ 1�� ī�޶󿡼� ���� �ִ�)
		0);									//���ٽ� ���۸� ä�ﰪ

	//���� û�Ұ� �����ߴٸ�
	if (SUCCEEDED(result))
	{
		//����̽� ������ ����
		_device->BeginScene();

		switch(g_eSceneManager)
		{
		case eSceneManager::E_GAMENODE:
			SCENEMANAGER->render();
			break;
		case eSceneManager::E_ISCENE:
			SCENE_MANAGER->Render();
			break;
		}

		//����� ��忡���� ����
#ifdef _DEBUG 
		//����׸��� ����
		GIZMOMANAGER->WorldGrid(1, 10);
		//Ÿ�ӸŴ��� ����
		TIMEMANAGER->render();
#endif	

		//����̽� ���� ����
		_device->EndScene();
		//�������� ���۳����� ȭ�鿡 ����
		_device->Present(0, 0, 0, 0);
	}
}



//==================================================================
//		## �������ν��� ## MainProc()
//==================================================================
LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(g_eSceneManager)
	{
	case eSceneManager::E_GAMENODE:
		break;
	case eSceneManager::E_ISCENE:
		SCENE_MANAGER->WndProc(hWnd, iMessage, wParam, lParam);
		break;
	}

	switch(iMessage)
	{
	case WM_KEYDOWN:
		switch(wParam)
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



//==================================================================
//		## �Ŵ��� �ʱ�ȭ ## initManager(void)
//==================================================================
void mainGame::initManager(void)
{
	SetRandomSeed();					//�����õ� �ʱ�ȭ
	CreateDevice();						//����̽� �ʱ�ȭ
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
}

//==================================================================
//		## �Ŵ��� ���� ## releaseManager(void)
//==================================================================
void mainGame::releaseManager(void)
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

	//����̽� ����
	ReleaseDevice();
}




