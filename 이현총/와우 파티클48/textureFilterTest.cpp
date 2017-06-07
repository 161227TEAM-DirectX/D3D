#include "stdafx.h"
#include "textureFilterTest.h"

HRESULT textureFilterTest::init(void)
{
	//쿼드생성
	this->CreateQuad();

	//쿼드 스케일
	_quadTrans.SetScale(100, 100, 100);
	//위로보게 만들기
	_quadTrans.RotateLocal(D3DXToRadian(90), 0, 0);

	/*
	//텍스쳐로딩
	//디폴트로 밉맵체인이 만들어진다
	//D3DXCreateTextureFromFile(디바이스, 파일이름, 텍스쳐포인터)
	D3DXCreateTextureFromFile(_device, "Sample1.png", &_texture);
	*/
	
	//밉맵체인없이 로딩
	D3DXCreateTextureFromFileEx(
	_device,
	"Sample1.png",
	256,
	256,
	0,
	0,
	D3DFMT_UNKNOWN,
	D3DPOOL_MANAGED,
	D3DX_FILTER_NONE,
	D3DX_FILTER_NONE,
	0,
	0,
	0,
	&_texture);
	

	//라이트 오프
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

void textureFilterTest::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
	SAFE_RELEASE(_texture);
}

void textureFilterTest::update(void)
{
	_quadTrans.DefaultMyControl(_timeDelta);
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();

	//필터모드 세팅
	//_device->SetSamplerState(스테이지번호, 어떤거 필터 세팅할꺼냐, 필터옵션);
	//D3DSAMP_MINFILTER 기존 Sample 된거보다 작게 나오는경우에 대한 필터링 방법
	//D3DSAMP_MAGFILTER 기존 Sample 된거보다 크게 나오는경우에 대한 필터링 방법
	//D3DSAMP_MIPFILTER 밉맵체인의 경계에서 어떻게 필터링할건지

	//필터옵션
	//D3DTEXF_LINEAR 주변필셀을 선형보간
	//D3DTEXF_ANISOTROPIC 이방성필터링을 통한 보간
	//D3DTEXF_POINT 한픽셀만 본다

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		//텍스쳐의 필터모드
		_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		//텍스쳐의 필터모드
		_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

		//이방성 필터링은 레벨을 조정할수 있다.
		//D3DTEXF_ANISOTROPIC 단계를 설정
		//Device->SetSamplerState( 0, D3DSAMP_MAXANISOTROPY, 16 );  //16 단계 까지의 픽셀보간

		//그래픽카드마다 최대 지원될수 있는 D3DTEXF_ANISOTROPIC 단계 는 다르다.
		//그래서 D3DCAP9 을 통해 확인할수 있다
		_device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, maxAnisotropic);
	}
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		//텍스쳐의 필터모드
		_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	}
}

void textureFilterTest::render(void)
{
	//디바이스를 통해 트렌스폼을 월드에 세팅
	_quadTrans.SetDeviceWorld();

	//그리기 전에 로딩된 텍스쳐를 세팅하기
	_device->SetTexture(0, _texture);

	//정점 그리기
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));
	_device->SetFVF(MYVERTEX::FVF);
	_device->SetIndices(_ib);
	_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//텍스쳐 세팅해제
	_device->SetTexture(0, NULL);
}

void textureFilterTest::CreateQuad()
{
	//정점 버퍼 생성
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 4,
		D3DUSAGE_WRITEONLY,
		MYVERTEX::FVF,
		D3DPOOL_DEFAULT,
		&_vb,
		NULL);

	// 1---2    UV좌표계는 윈도우 좌표계와 똑같다 
	// |  /|	왼쪽상단이 0,0 우측상단 1,0 왼쪽하단 0,1 우측하단 1,1
	// | / |								
	// 0---3								
	LPMYVERTEX pVertices = NULL;
	_vb->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].pos = D3DXVECTOR3(-3.5, -3.5, 0);
	pVertices[1].pos = D3DXVECTOR3(-3.5, 3.5, 0);
	pVertices[2].pos = D3DXVECTOR3(3.5, 3.5, 0);
	pVertices[3].pos = D3DXVECTOR3(3.5, -3.5, 0);

	pVertices[0].uv = D3DXVECTOR2(0, 100);
	pVertices[1].uv = D3DXVECTOR2(0, 0);
	pVertices[2].uv = D3DXVECTOR2(100, 0);
	pVertices[3].uv = D3DXVECTOR2(100, 100);

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
