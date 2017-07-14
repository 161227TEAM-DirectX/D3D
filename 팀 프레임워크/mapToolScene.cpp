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
	//초기화
	_rightView = new rightView;
	_rightView->init();

	_leftViewHead = new leftViewHead;
	_leftViewHead->init();

	//화면 사이즈 들고오기 
	//화면 사이즈의 넓이 들고오기
	_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	pBackBuffer->GetDesc(&d3dsd);
	pBackBuffer->Release();

	//화면 사이즈의 넓이 , 높이 담기
	g_dwBackBufferWidth = d3dsd.Width;
	g_dwBackBufferHeight = d3dsd.Height;

	//상호참조
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
	//왼쪽뷰 설정하기
	leftViewPort.X = 0;
	leftViewPort.Y = 0;
	leftViewPort.Width = g_dwBackBufferWidth - 400;
	leftViewPort.Height = g_dwBackBufferHeight;
	leftViewPort.MinZ = 0.0f;
	leftViewPort.MaxZ = 1.0f;

	//왼쪽뷰 적용
	_device->SetViewport(&leftViewPort);

	//버퍼를 청소하자
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

		_leftViewHead->render();

		MOUSE_MANAGER->render();

		//GIZMOMANAGER->WorldGrid(1, 10);

		//타임매니져 렌더
		TIMEMANAGER->render();

		//디바이스 렌더 종료
		_device->EndScene();
	}

	//오른쪽뷰 화면설정
	rightViewPort.X = g_dwBackBufferWidth - 400;
	rightViewPort.Y = 0;
	rightViewPort.Width = g_dwBackBufferWidth - 1200;
	rightViewPort.Height = g_dwBackBufferHeight;
	rightViewPort.MinZ = 0.0f;
	rightViewPort.MaxZ = 1.0f;

	//오른쪽뷰 설정
	_device->SetViewport(&rightViewPort);

	HRESULT result2 = _device->Clear(
		0,			//청소할 영역의 D3D렉트 배열 갯수	(전체 클리어 0)
		NULL,		//청소할 영역의 D3D렉트 배열 포인터 (전체 클리어 NULL)
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, //청소될 버퍼 플래그 (컬러버퍼, 깊이버퍼, 스텐실버퍼)
		D3DCOLOR_XRGB(0, 0, 0),	//컬러버퍼를 청소하고 채워질 색상 (0xAARRGGBB)
		1.0f,		//깊이버퍼를 청소할 값 (0 ~ 1, 0이 카메라에서 제일 가깝고 1이 카메라에서 제일 멀다)
		0);			//스텐실 버퍼를 채울값

					//버퍼 청소가 성공했다면
	if (SUCCEEDED(result))
	{
		//디바이스 렌더링 시작
		_device->BeginScene();

		_rightView->render();

		MOUSE_MANAGER->render();

		//디바이스 렌더 종료
		_device->EndScene();

		//렌더링된 버퍼내용을 화면에 전송
		_device->Present(0, 0, 0, 0);
	}

}

