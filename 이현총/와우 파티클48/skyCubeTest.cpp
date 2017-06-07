#include "stdafx.h"
#include "skyCubeTest.h"

HRESULT skyCubeTest::init(void)
{
	//환경 이펙트(FX) 초기화
	_environmentEffect = RM_SHADERFX->loadResource("RESOURCE/FX/EnvironmentCUBE.fx");
	//환경맵 세팅
	this->setEnvironment("RESOURCE/TEXTURECUBE/GanjiCube.dds");

	return S_OK;
}

void skyCubeTest::release(void)
{
	SAFE_RELEASE(_environmentTexture);
	SAFE_RELEASE(_environmentCubeMesh);
	SAFE_RELEASE(_environmentEffect);
}

void skyCubeTest::update(void)
{
	//카메라 업데이트
	//this->updateForCamera();
}

void skyCubeTest::render(void)
{
	this->renderEnvironment();
}

void skyCubeTest::setEnvironment(string cubeFileName)
{
	//기존의 환경맵이 세팅되어 있을지 모르니 깔끔하게 지우고 시작하기
	SAFE_RELEASE(_environmentTexture);

	//환경맵 로딩
	D3DXCreateCubeTextureFromFile(_device, cubeFileName.c_str(), &_environmentTexture);

	//환경맵 로딩이 되어있지 않을시 예외처리
	if (_environmentCubeMesh == NULL)
	{
		D3DXCreateSphere(_device, 3.0f, 20, 20, &_environmentCubeMesh, NULL);
	}
}

void skyCubeTest::renderEnvironment(void)
{
	//환경맵 로딩된게 없다면 바로 리턴시키기
	if (_environmentTexture == NULL) return;

	//환경맵 이펙트 세팅
	_environmentEffect->SetTexture("MyCube_Tex", _environmentTexture);

	//WVP 행렬
	D3DXMATRIXA16 matWorld = _mainCamera->GetFinalMatrix();
	D3DXMATRIXA16 matViewProj = _mainCamera->getViewProjectionMatrix();
	D3DXMATRIXA16 matWVP = matWorld * matViewProj;

	_environmentEffect->SetMatrix("matWVP", &matWVP);
	_environmentEffect->SetMatrix("matWorld", &matWorld);

	//셰이더로 랜더
	UINT iPassNum = 0;

	//이펙트로 렌더링시작
	_environmentEffect->Begin(&iPassNum, 0);
	//패스 수대로 for문으로 돌린다
	for (UINT i = 0; i < iPassNum; i++)
	{
		_environmentEffect->BeginPass(i);
		//렌더
		_environmentCubeMesh->DrawSubset(0);
		_environmentEffect->EndPass();
	}
	_environmentEffect->End();
}
