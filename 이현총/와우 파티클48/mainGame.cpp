#include "stdafx.h"
#include "mainGame.h"
//==================================================================
//		## �ʱ�ȭ ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	gameNode::init();

	//���߰�
	SCENEMANAGER->addScene("��Ų��ִϸ��̼�", new skinnedAniTest);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ", new particleTest);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ2", new particleTest02);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ3", new particleTest03);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ4", new particleTest04);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ5", new particleTest05);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ6", new particleTest06);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ7", new particleTest07);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ8", new particleTest08);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ9", new particleTest09);
	SCENEMANAGER->addScene("��ƼŬ �׽�Ʈ10", new particleTest10);
	SCENEMANAGER->addScene("��ƼŬ3", new _3quadParticleEmitter);
	SCENEMANAGER->addScene("�޽�", new useXMeshClass);

	//���ʱ�ȭ
	//SCENEMANAGER->changeScene("��ƼŬ3");
	//SCENEMANAGER->changeScene("��ƼŬ �׽�Ʈ10");
	SCENEMANAGER->changeScene("�޽�");

	return S_OK;
}

//==================================================================
//		## ���� ## release(void)
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
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

		//����׸��� ����
		GIZMOMANAGER->WorldGrid(1, 10);

		//Ÿ�ӸŴ��� ����
		TIMEMANAGER->render();

		//����̽� ���� ����
		_device->EndScene();

		//�������� ���۳����� ȭ�鿡 ����
		_device->Present(0, 0, 0, 0);
	}
}