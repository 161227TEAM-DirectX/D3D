#include "stdafx.h"
#include "mainGame.h"
//==================================================================
//		## 초기화 ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	gameNode::init();

	//씬추가
	SCENEMANAGER->addScene("스킨드애니메이션", new skinnedAniTest);
	SCENEMANAGER->addScene("파티클 테스트", new particleTest);
	SCENEMANAGER->addScene("파티클 테스트2", new particleTest02);
	SCENEMANAGER->addScene("파티클 테스트3", new particleTest03);
	SCENEMANAGER->addScene("파티클 테스트4", new particleTest04);
	SCENEMANAGER->addScene("파티클 테스트5", new particleTest05);
	SCENEMANAGER->addScene("파티클 테스트6", new particleTest06);
	SCENEMANAGER->addScene("파티클 테스트7", new particleTest07);
	SCENEMANAGER->addScene("파티클 테스트8", new particleTest08);
	SCENEMANAGER->addScene("파티클 테스트9", new particleTest09);
	SCENEMANAGER->addScene("파티클 테스트10", new particleTest10);
	SCENEMANAGER->addScene("파티클3", new _3quadParticleEmitter);
	SCENEMANAGER->addScene("메쉬", new useXMeshClass);

	//씬초기화
	//SCENEMANAGER->changeScene("파티클3");
	//SCENEMANAGER->changeScene("파티클 테스트10");
	SCENEMANAGER->changeScene("메쉬");

	return S_OK;
}

//==================================================================
//		## 해제 ## release(void)
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
}

//==================================================================
//		## 업데이트 ## update(void)
//==================================================================
void mainGame::update(void)
{
	//씬매니져 업데이트
	SCENEMANAGER->update();
}

//==================================================================
//		## 렌더 ## render(void)
//==================================================================
void mainGame::render(void)
{
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

		//씬매니져 렌더
		SCENEMANAGER->render();

		//월드그리드 렌더
		GIZMOMANAGER->WorldGrid(1, 10);

		//타임매니져 렌더
		TIMEMANAGER->render();

		//디바이스 렌더 종료
		_device->EndScene();

		//렌더링된 버퍼내용을 화면에 전송
		_device->Present(0, 0, 0, 0);
	}
}