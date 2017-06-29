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

	//화면 사이즈의 넓이 , 높이 담기
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

	//왼쪽뷰 설정하기
	smallView.X = 0;
	smallView.Y = 0;
	smallView.Width = g_dwBackBufferWidth;
	smallView.Height = g_dwBackBufferHeight;
	smallView.MinZ = 0.0f;
	smallView.MaxZ = 1.0f;

	//왼쪽뷰 적용
	_device->SetViewport(&smallView);

	HRESULT result = _device->Clear(
		0,			//청소할 영역의 D3D렉트 배열 갯수	(전체 클리어 0)
		NULL,		//청소할 영역의 D3D렉트 배열 포인터 (전체 클리어 NULL)
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, //청소될 버퍼 플래그 (컬러버퍼, 깊이버퍼, 스텐실버퍼)
		0xff202020,	//컬러버퍼를 청소하고 채워질 색상 (0xAARRGGBB)
		1.0f,		//깊이버퍼를 청소할 값 (0 ~ 1, 0이 카메라에서 제일 가깝고 1이 카메라에서 제일 멀다)
		0);			//스텐실 버퍼를 채울값

					//버퍼 청소가 성공했다면
	if (SUCCEEDED(result))
	{
		//디바이스 렌더링 시작
		_device->BeginScene();

		//씬매니져 렌더
		_shopHead->render();
		//_saveEx->render();
		//_cinematic->render();

		//월드그리드 렌더
		GIZMOMANAGER->WorldGrid(1, 10);

		//타임매니져 렌더
		TIMEMANAGER->render();

		//디바이스 렌더 종료
		_device->EndScene();

		if (ViewTrue == FALSE)
		{
			//렌더링된 버퍼내용을 화면에 전송
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

		//왼쪽뷰 적용
		_device->SetViewport(&foceView);

		HRESULT result2 = _device->Clear(
			0,			//청소할 영역의 D3D렉트 배열 갯수	(전체 클리어 0)
			NULL,		//청소할 영역의 D3D렉트 배열 포인터 (전체 클리어 NULL)
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, //청소될 버퍼 플래그 (컬러버퍼, 깊이버퍼, 스텐실버퍼)
			D3DCOLOR_XRGB(0, 0, 0),	//컬러버퍼를 청소하고 채워질 색상 (0xAARRGGBB)
			1.0f,		//깊이버퍼를 청소할 값 (0 ~ 1, 0이 카메라에서 제일 가깝고 1이 카메라에서 제일 멀다)
			0);			//스텐실 버퍼를 채울값

						//버퍼 청소가 성공했다면
		if (SUCCEEDED(result2))
		{
			//디바이스 렌더링 시작
			_device->BeginScene();

			_forceView->render();
			//월드그리드 렌더
			//GIZMOMANAGER->WorldGrid(1, 10);

			//타임매니져 렌더
			TIMEMANAGER->render();

			//디바이스 렌더 종료
			_device->EndScene();

			//렌더링된 버퍼내용을 화면에 전송
			_device->Present(0, 0, 0, 0);
		}
	}
}
