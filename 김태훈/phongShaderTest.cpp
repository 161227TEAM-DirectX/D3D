#include "stdafx.h"
#include "phongShaderTest.h"

HRESULT phongShaderTest::init(void)
{
	//카메라 위치세팅
	_mainCamera.SetLocalPosition(0, 0, -10);

	//구생성
	if (FAILED(D3DXCreateSphere(_device, 3.0f, 50, 50, &_mesh, NULL))) return E_FAIL;

	//쉐이더 로딩시 컴파일 에러가 나면 에러의 내용을 받아올 Error버퍼
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;

	//fx파일로 부터 이펙트 객체를 로딩한다
	D3DXCreateEffectFromFile(
		_device,				//디바이스
		"BlinnPhong.fx",		//파일이름
		NULL,					//세이더를 컴파일할때 추가로 사용할 #define정의
		NULL,					//세이더를 컴파일할때 #include지시문 처리할때 사용할 인터페이스 플래그
		shaderFlag,				//세이더 컴파일 플래그
		NULL,					//세이더 매개변수를 공유할 메모리 풀
		&_effect,				//로딩될 세이더 이펙트 포인터
		&error);				//세이더 로딩하고 컴파일 할때 컴파일에 문제가 생기면 헤더버퍼에 에러메세지가 들어간다

								//문제가 있다면
	if (error != NULL)
	{
		//에러버퍼 릴리즈
		SAFE_RELEASE(error);
		return E_FAIL;
	}

	return S_OK;
}

void phongShaderTest::release(void)
{
	SAFE_RELEASE(_effect);
	SAFE_RELEASE(_mesh);
}

void phongShaderTest::update(void)
{
	//조명트렌스
	_lightTrans.DefaultMyControl(_timeDelta);
	//카메라
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();
}

void phongShaderTest::render(void)
{
	//이펙트에 전역변수 값을 세팅하기
	D3DXMATRIXA16 matWorld = _meshTrans.GetFinalMatrix();
	//월드행렬세팅
	_effect->SetMatrix("matWorld", &matWorld);
	
	//디바이스로부터 세팅된 뷰행렬과 투영행렬을 얻기
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProjection;
	_device->GetTransform(D3DTS_VIEW, &matView);
	_device->GetTransform(D3DTS_PROJECTION, &matProjection);

	//뷰행렬 세팅
	_effect->SetMatrix("matView", &matView);
	//투영행렬 세팅
	_effect->SetMatrix("matProjection", &matProjection);
	//컬러벡터 세팅
	D3DXVECTOR4 vMaterialDiffuseColor(1, 0, 0, 1);
	_effect->SetVector("vMaterialDiffuseColor", &vMaterialDiffuseColor);
	D3DXVECTOR4 vMaterialSpecularColor(1, 1, 1, 1);
	_effect->SetVector("vMaterialSpecularColor", &vMaterialSpecularColor);
	//파워
	_effect->SetFloat("fPower", 30.0f);


	//광원의 방향
	D3DXVECTOR4 lightDir(_lightTrans.GetForward(), 1);
	_effect->SetVector("vLightDir", &lightDir);
	D3DXVECTOR4 eyePos(_mainCamera.GetWorldPosition(), 1);
	_effect->SetVector("vEyePos", &eyePos);




	//테크닉세팅
	_effect->SetTechnique("MyShader");

	//쉐이더로 큐브렌더
	UINT iPassNum = 0;

	//이펙트로 렌더링시작
	_effect->Begin(&iPassNum, 0);

	//패스 수대로 for문으로 돌린다
	for (UINT i = 0; i < iPassNum; i++)
	{
		_effect->BeginPass(i);

		//렌더
		_mesh->DrawSubset(0);

		_effect->EndPass();
	}

	_effect->End();

	_lightTrans.RenderGimozo();
}
