#include "stdafx.h"
#include "cInvenTest.h"
//
#include "shopHead.h"
#include "forceView.h"

cInvenTest::cInvenTest()
{
}


cInvenTest::~cInvenTest()
{
}

HRESULT cInvenTest::init()
{
	_shopHead = new shopHead;
	_shopHead->init();

	_forceView = new forceView;
	_forceView->init();

	_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	pBackBuffer->GetDesc(&d3dsd);
	pBackBuffer->Release();

	//ȭ�� �������� ���� , ���� ���
	g_dwBackBufferWidth = d3dsd.Width;
	g_dwBackBufferHeight = d3dsd.Height;

	return S_OK;
}

void cInvenTest::release()
{
	SAFE_release(_shopHead);
	SAFE_release(_forceView);
}

void cInvenTest::update()
{
	_shopHead->update();
	_forceView->update();
}

void cInvenTest::render()
{
	_shopHead->render();

	//���ʺ� �����ϱ�
	smallView.X = 0;
	smallView.Y = 0;
	smallView.Width = g_dwBackBufferWidth;
	smallView.Height = g_dwBackBufferHeight;
	smallView.MinZ = 0.0f;
	smallView.MaxZ = 1.0f;

	//���ʺ� ����
	_device->SetViewport(&smallView);

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
		_shopHead->render();
		//_saveEx->render();
		//_cinematic->render();

		//����׸��� ����
		GIZMOMANAGER->WorldGrid(1, 10);

		//Ÿ�ӸŴ��� ����
		TIMEMANAGER->render();

		//����̽� ���� ����
		_device->EndScene();

		if (ViewTrue == FALSE)
		{
			//�������� ���۳����� ȭ�鿡 ����
			_device->Present(0, 0, 0, 0);
		}
	}

	if (ViewTrue == TRUE)
	{
		foceView.X = 380;
		foceView.Y = 290;
		foceView.Width = 352;
		foceView.Height = 162;
		foceView.MinZ = 0.0f;
		foceView.MaxZ = 1.0f;

		//���ʺ� ����
		_device->SetViewport(&foceView);

		HRESULT result2 = _device->Clear(
			0,			//û���� ������ D3D��Ʈ �迭 ����	(��ü Ŭ���� 0)
			NULL,		//û���� ������ D3D��Ʈ �迭 ������ (��ü Ŭ���� NULL)
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, //û�ҵ� ���� �÷��� (�÷�����, ���̹���, ���ٽǹ���)
			D3DCOLOR_XRGB(0, 0, 0),	//�÷����۸� û���ϰ� ä���� ���� (0xAARRGGBB)
			1.0f,		//���̹��۸� û���� �� (0 ~ 1, 0�� ī�޶󿡼� ���� ������ 1�� ī�޶󿡼� ���� �ִ�)
			0);			//���ٽ� ���۸� ä�ﰪ

						//���� û�Ұ� �����ߴٸ�
		if (SUCCEEDED(result2))
		{
			//����̽� ������ ����
			_device->BeginScene();

			_forceView->render();
			//����׸��� ����
			//GIZMOMANAGER->WorldGrid(1, 10);

			//Ÿ�ӸŴ��� ����
			TIMEMANAGER->render();

			//����̽� ���� ����
			_device->EndScene();

			//�������� ���۳����� ȭ�鿡 ����
			_device->Present(0, 0, 0, 0);
		}
	}
}
