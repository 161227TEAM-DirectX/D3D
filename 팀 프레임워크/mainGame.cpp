#include "stdafx.h"
#include "mainGame.h"
//==================================================================
//		## �ʱ�ȭ ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	/*�Ŵ��� �ʱ�ȭ*/
	this->initManager();

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
	//SCENEMANAGER->addScene("test", new terrainPickingTest);
	SCENEMANAGER->addScene("test2", new kimsTestScene);

//===================================================================================
//�踸�� �� �׽�Ʈ �������
//===================================================================================
	////���߰�
	//SCENEMANAGER->addScene("test", new cLoadingBarTest);
	//SCENEMANAGER->addScene("test", new cLoadingTest);

//===================================================================================
//������ �� �׽�Ʈ �������
//===================================================================================


//===================================================================================
//���½� �� �׽�Ʈ �������
//===================================================================================


	//���ʱ�ȭ
	SCENEMANAGER->changeScene("test2");
	return S_OK;
}

//==================================================================
//		## ���� ## release(void)
//==================================================================
void mainGame::release(void)
{
	/*�Ŵ��� ����*/
	this->releaseManager();
}

//==================================================================
//		## ������Ʈ ## update(void)
//==================================================================
void mainGame::update(void)
{
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
}

//==================================================================
//		## ���� ## render(void)
//==================================================================
void mainGame::render(void)
{
	//���۸� û������
	HRESULT result = _device->Clear(
		0,			//û���� ������ D3D��Ʈ �迭 ����	(��ü Ŭ���� 0)
		NULL,		//û���� ������ D3D��Ʈ �迭 ������ (��ü Ŭ���� NULL)
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, //û�ҵ� ���� �÷��� (�÷�����, ���̹���, ���ٽǹ���)
		0xff202020,	//�÷����۸� û���ϰ� ä���� ���� (0xAARRGGBB)
		1.0f,		//���̹��۸� û���� �� (0 ~ 1, 0�� ī�޶󿡼� ���� ������ 1�� ī�޶󿡼� ���� �ִ�)
		0);			//���ٽ� ���۸� ä�ﰪ

	//���� û�Ұ� �����ߴٸ�
	if (SUCCEEDED(result))
	{
		//����̽� ������ ����
		_device->BeginScene();
		//���Ŵ��� ����
		SCENEMANAGER->render();

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

//==================================================================
//		## �������ν��� ## MainProc()
//==================================================================
LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
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
