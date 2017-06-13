#include "stdafx.h"
#include "mainGame.h"
//==================================================================
//		## 초기화 ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	/*매니져 초기화*/
	this->initManager();

//===================================================================================
//이현총 씬 테스트 헤더파일
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
//이현수 씬 테스트 헤더파일
//===================================================================================
	//씬추가
	//SCENEMANAGER->addScene("test", new terrainPickingTest);
	SCENEMANAGER->addScene("test2", new kimsTestScene);

//===================================================================================
//김만웅 씬 테스트 헤더파일
//===================================================================================
	////씬추가
	//SCENEMANAGER->addScene("test", new cLoadingBarTest);
	//SCENEMANAGER->addScene("test", new cLoadingTest);

//===================================================================================
//김태훈 씬 테스트 헤더파일
//===================================================================================


//===================================================================================
//김태승 씬 테스트 헤더파일
//===================================================================================


	//씬초기화
	SCENEMANAGER->changeScene("test2");
	return S_OK;
}

//==================================================================
//		## 해제 ## release(void)
//==================================================================
void mainGame::release(void)
{
	/*매니져 해제*/
	this->releaseManager();
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

		//디버그 모드에서만 실행
#ifdef _DEBUG 
		//월드그리드 렌더
		GIZMOMANAGER->WorldGrid(1, 10);
		//타임매니져 렌더
		TIMEMANAGER->render();
#endif
		//디바이스 렌더 종료
		_device->EndScene();
		//렌더링된 버퍼내용을 화면에 전송
		_device->Present(0, 0, 0, 0);
	}
}


//==================================================================
//		## 매니져 초기화 ## initManager(void)
//==================================================================
void mainGame::initManager(void)
{
	SetRandomSeed();					//랜덤시드 초기화
	CreateDevice();						//디바이스 초기화
	KEYMANAGER->init();					//키매니져 초기화
	TIMEMANAGER->init();				//타임매니져 초기화
	SCENEMANAGER->init();				//씬매니져 초기화
	FONTMANAGER->init();				//폰트매니져 초기화
	GIZMOMANAGER->init();				//기즈모매니져 초기화
	RM_TEXTURE->init();					//RM텍스쳐 초기화
	RM_SHADERFX->init();				//RM셰이더FX 초기화
	RM_XMESH->init();					//RM스태틱X메쉬 초기화
	RM_SKINNED->init();					//RM스킨드X메쉬 초기화
	PHYSICSMANAGER->init();				//피직스매니져 초기화
	SPRITEMANAGER->init();				//스프라이트매니져 초기화
	PSM->ParticleSystemSetInit();		//파티클시스템매니져 초기화
}

//==================================================================
//		## 매니져 해제 ## releaseManager(void)
//==================================================================
void mainGame::releaseManager(void)
{
	//키매니져 싱글톤 해제
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	//타임매니져 싱글톤 해제
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	//씬매니져 싱글톤 해제
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	//폰트매니져 싱글톤 해제
	FONTMANAGER->release();
	FONTMANAGER->releaseSingleton();
	//기즈모매니져 싱글톤 해제
	GIZMOMANAGER->release();
	GIZMOMANAGER->releaseSingleton();
	//리소스매니져 싱글톤 해제
	RM_TEXTURE->clearResource();
	RM_TEXTURE->releaseSingleton();
	RM_SHADERFX->clearResource();
	RM_SHADERFX->releaseSingleton();
	RM_XMESH->clearResource();
	RM_XMESH->releaseSingleton();
	RM_SKINNED->clearResource();
	RM_SKINNED->releaseSingleton();
	//피직스매니져 싱글톤 해제
	PHYSICSMANAGER->release();
	PHYSICSMANAGER->releaseSingleton();
	//스프라이트매니져 싱글톤 해제
	SPRITEMANAGER->release();
	SPRITEMANAGER->releaseSingleton();
	//파티클시스템매니져 싱글톤 해제
	PSM->ParticleSystemSetRelease();
	PSM->releaseSingleton();

	//디바이스 해제
	ReleaseDevice();
}

//==================================================================
//		## 메인프로시져 ## MainProc()
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
