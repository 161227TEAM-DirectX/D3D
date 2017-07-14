#include "stdafx.h"
#include "mapToolScene.h"
//
#include "rightView.h"
#include "leftViewHead.h"

mapToolScene::mapToolScene()
{
}


mapToolScene::~mapToolScene()
{
}

HRESULT mapToolScene::init()
{
	//�ʱ�ȭ
	_rightView = new rightView;
	_rightView->init();

	_leftViewHead = new leftViewHead;
	_leftViewHead->init();

	//ȭ�� ������ ������ 
	//ȭ�� �������� ���� ������
	_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	pBackBuffer->GetDesc(&d3dsd);
	pBackBuffer->Release();

	//ȭ�� �������� ���� , ���� ���
	g_dwBackBufferWidth = d3dsd.Width;
	g_dwBackBufferHeight = d3dsd.Height;

	//��ȣ����
	_leftViewHead->setLink(_rightView);

	return S_OK;
}

void mapToolScene::release()
{
	_leftViewHead->release();
	_rightView->release();
}

void mapToolScene::update()
{
	_leftViewHead->update();
	_rightView->update();
}

void mapToolScene::render()
{
	//���ʺ� �����ϱ�
	leftViewPort.X = 0;
	leftViewPort.Y = 0;
	leftViewPort.Width = g_dwBackBufferWidth - 400;
	leftViewPort.Height = g_dwBackBufferHeight;
	leftViewPort.MinZ = 0.0f;
	leftViewPort.MaxZ = 1.0f;

	//���ʺ� ����
	_device->SetViewport(&leftViewPort);

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

		_leftViewHead->render();

		MOUSE_MANAGER->render();

		//GIZMOMANAGER->WorldGrid(1, 10);

		//Ÿ�ӸŴ��� ����
		TIMEMANAGER->render();

		//����̽� ���� ����
		_device->EndScene();
	}

	//�����ʺ� ȭ�鼳��
	rightViewPort.X = g_dwBackBufferWidth - 400;
	rightViewPort.Y = 0;
	rightViewPort.Width = g_dwBackBufferWidth - 1200;
	rightViewPort.Height = g_dwBackBufferHeight;
	rightViewPort.MinZ = 0.0f;
	rightViewPort.MaxZ = 1.0f;

	//�����ʺ� ����
	_device->SetViewport(&rightViewPort);

	HRESULT result2 = _device->Clear(
		0,			//û���� ������ D3D��Ʈ �迭 ����	(��ü Ŭ���� 0)
		NULL,		//û���� ������ D3D��Ʈ �迭 ������ (��ü Ŭ���� NULL)
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, //û�ҵ� ���� �÷��� (�÷�����, ���̹���, ���ٽǹ���)
		D3DCOLOR_XRGB(0, 0, 0),	//�÷����۸� û���ϰ� ä���� ���� (0xAARRGGBB)
		1.0f,		//���̹��۸� û���� �� (0 ~ 1, 0�� ī�޶󿡼� ���� ������ 1�� ī�޶󿡼� ���� �ִ�)
		0);			//���ٽ� ���۸� ä�ﰪ

					//���� û�Ұ� �����ߴٸ�
	if (SUCCEEDED(result))
	{
		//����̽� ������ ����
		_device->BeginScene();

		_rightView->render();

		MOUSE_MANAGER->render();

		//����̽� ���� ����
		_device->EndScene();

		//�������� ���۳����� ȭ�鿡 ����
		_device->Present(0, 0, 0, 0);
	}

}

