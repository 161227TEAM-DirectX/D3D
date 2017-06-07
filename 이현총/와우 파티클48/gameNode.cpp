#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode() : _environmentTexture(NULL), _environmemtSphereMesh(NULL)
{
	//환경구 이펙트 초기화
	_environmentEffect = RM_SHADERFX->getResource("Resources/Shaders/EnvironmentCube.fx");
	//메인카메라 초기화
	_mainCamera = new camera;
}

gameNode::~gameNode()
{
	//환경텍스쳐, 메시 해제
	SAFE_RELEASE(_environmentTexture);
	SAFE_RELEASE(_environmemtSphereMesh);
	//메인카메라 해제
	SAFE_DELETE(_mainCamera);
}

HRESULT gameNode::init(void)
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

	PSM->ParticleSystemSetInit();

	return S_OK;
}

void gameNode::release(void)
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

	PSM->ParticleSystemSetRelease();
	PSM->releaseSingleton();
	
	
	//디바이스 해제
	ReleaseDevice();
}

void gameNode::update(void)
{
}

void gameNode::render(void)
{
}

//씬매니져에서 처리
void gameNode::renderEnvironment(void)
{
	//환경 맵 로딩된게 없다면 리턴해라
	if (_environmentTexture == NULL) return;

	//환경 이펙트 세팅
	_environmentEffect->SetTexture("MyCube_Tex", _environmentTexture);

	//WVP 매트릭스
	D3DXMATRIXA16 matWorld = _mainCamera->GetFinalMatrix();
	D3DXMATRIXA16 matViewProj = _mainCamera->getViewProjectionMatrix();
	D3DXMATRIXA16 matWVP = matWorld * matViewProj;

	//이펙트 세팅
	_environmentEffect->SetMatrix("matWVP", &matWVP);
	_environmentEffect->SetMatrix("matWorld", &matWorld);

	//셰이더 그려라
	UINT numPass;
	_environmentEffect->Begin(&numPass, 0);		//셰이더로 그린다는 것을 알리고 pass 수를 얻는다.
	for (UINT i = 0; i < numPass; i++)			//공정 수대로 돈다.
	{
		_environmentEffect->BeginPass(i);		//i번째 공정시작
		_environmemtSphereMesh->DrawSubset(0);	//구 그려라
		_environmentEffect->EndPass();			//i번째 공정끝
	}
	_environmentEffect->End();					//셰이더로 그리기 끝
}

void gameNode::setEnvironment(string cubeFilePath)
{
	//기존의 환경맵이 셋팅되어있을지 모르니 먼저 릴리즈해주고 시작하자
	SAFE_RELEASE(_environmentTexture);

	//환경맵 로딩
	D3DXCreateCubeTextureFromFile(_device, cubeFilePath.c_str(), &_environmentTexture);

	//환경구 로딩되어있지 않다면....
	if (_environmemtSphereMesh == NULL)
	{
		D3DXCreateSphere(_device, 3.0f, 20, 20, &_environmemtSphereMesh, NULL);
	}
}

void gameNode::updateCamera(void)
{
	//카메라 업데이트
	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
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


