#include "stdafx.h"
#include "billboardTest.h"

HRESULT billboardTest::init(void)
{
	//메인카메라 위치
	_mainCamera.SetLocalPosition(0, 0, -10);

	//평면생성
	this->CreateQuad();

	//텍스쳐 로딩
	D3DXCreateTextureFromFile(_device, "전효성.png", &_texture);

	//텍스쳐 필터모드
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//셰이더 로딩
	//쉐이더 로딩시 컴파일 에러가 나면 에러의 내용을 받아올 Error버퍼
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;
	//fxFile 로 부터 Effect 객체 로딩
	D3DXCreateEffectFromFile(
		_device,			//디바이스
		"TextureAlpha.fx",	//불러올 셰이더 코드 파일이름
		NULL, 				//셰이더를 컴파일할때 추가로 사용할 #define 정의 ( 일단 NULL )
		NULL, 				//셰이더를 컴파일할때 #include 지시문을 처리할때 사용할 인터페이스 플레그 ( 일단 NULL )
		shaderFlag,			//셰이더 컴파일 플레그
		NULL, 				//셰이더 매개변수를 공유할 메모리풀 ( 일단 NULL )
		&_effect,			//로딩될 셰이더 Effect 포인터
		&error 				//셰이더를 로딩하고 컴파일할때 문제가 생기면 해당 버퍼에 에러메시지가 들어간다 ( 성공적으로 로딩되면 NULL 이 참조된다 )
	);

	//로딩에 문제가 있다면....
	if (error != NULL)
	{
		//Error 버퍼 Release
		SAFE_RELEASE(error);
		return E_FAIL;
	}

	return S_OK;
}

void billboardTest::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
	SAFE_RELEASE(_texture);
	SAFE_RELEASE(_effect);
}

void billboardTest::update(void)
{
	_quadTrans.DefaultMyControl(_timeDelta);
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();

	//쿼드 빌보드 처리
	_quadTrans.LookDirection(_mainCamera.GetForward(), _mainCamera.GetUp());
}

void billboardTest::render(void)
{
	//이펙트에 전역 변수값을 세팅한다.
	D3DXMATRIXA16 matWorld = _quadTrans.GetFinalMatrix();

	//디바이스로부터 세팅된 View 행렬과 Projection 행렬을 얻는다.
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProjection;
	_device->GetTransform(D3DTS_VIEW, &matView);
	_device->GetTransform(D3DTS_PROJECTION, &matProjection);

	//총변환 행렬
	D3DXMATRIXA16 matWVP = matWorld * matView * matProjection;
	_effect->SetMatrix("matWVP", &matWVP);

	//컬러 벡터 세팅 (주의사항!! 세팅되는 벡터는 모두 Vector4 로 대동단결된다)
	D3DXVECTOR4 color(1, 1, 1, 1);
	_effect->SetVector("vColor", &color);

	//텍스쳐 세팅
	_effect->SetTexture("MyTex", _texture);

	//타일수 세팅
	_effect->SetFloat("tilingX", 1);
	_effect->SetFloat("tilingY", 1);

	//테크닉세팅
	_effect->SetTechnique("MyShader");

	//셰이더로 쿼드 렌더
	UINT iPassNum = 0;

	//이펙트로 렌더링시작
	_effect->Begin(&iPassNum, 0);

	//패스 수대로 for문으로 돌린다
	for (UINT i = 0; i < iPassNum; i++)
	{
		_effect->BeginPass(i);

		//렌더
		//정점 그리기
		_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX_PU));
		_device->SetFVF(MYVERTEX_PU::FVF);
		_device->SetIndices(_ib);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

		_effect->EndPass();
	}

	_effect->End();
}

void billboardTest::CreateQuad()
{
	//정점 버퍼 생성
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX_PU) * 4,
		D3DUSAGE_WRITEONLY,
		MYVERTEX_PU::FVF,
		D3DPOOL_DEFAULT,
		&_vb,
		NULL);

	// 1---2    UV좌표계는 윈도우 좌표계와 똑같다 
	// |  /|	왼쪽상단이 0,0 우측상단 1,0 왼쪽하단 0,1 우측하단 1,1
	// | / |								
	// 0---3								
	LPMYVERTEX_PU pVertices = NULL;
	_vb->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].pos = D3DXVECTOR3(-3.5, -3.5, 0);
	pVertices[1].pos = D3DXVECTOR3(-3.5, 3.5, 0);
	pVertices[2].pos = D3DXVECTOR3(3.5, 3.5, 0);
	pVertices[3].pos = D3DXVECTOR3(3.5, -3.5, 0);

	pVertices[0].uv = D3DXVECTOR2(0, 1);
	pVertices[1].uv = D3DXVECTOR2(0, 0);
	pVertices[2].uv = D3DXVECTOR2(1, 0);
	pVertices[3].uv = D3DXVECTOR2(1, 1);

	_vb->Unlock();

	//인덱스 버퍼 생성
	_device->CreateIndexBuffer(
		sizeof(DWORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,
		&_ib,
		NULL);
	// 1---2    
	// |  /|	
	// | / |								
	// 0---3
	DWORD idx[] = { 0, 1, 2, 0, 2, 3 };

	void* pIndices = NULL;
	_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, idx, sizeof(DWORD) * 6);
	_ib->Unlock();
}
