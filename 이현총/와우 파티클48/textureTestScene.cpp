#include "stdafx.h"
#include "textureTestScene.h"

HRESULT textureTestScene::init(void)
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

	pVertices[0].pos = D3DXVECTOR3(-5, -5, 0);
	pVertices[1].pos = D3DXVECTOR3(-5, 5, 0);
	pVertices[2].pos = D3DXVECTOR3(5, 5, 0);
	pVertices[3].pos = D3DXVECTOR3(5, -5, 0);

	pVertices[0].uv = D3DXVECTOR2(0, 3);
	pVertices[1].uv = D3DXVECTOR2(0, 0);
	pVertices[2].uv = D3DXVECTOR2(3, 0);
	pVertices[3].uv = D3DXVECTOR2(3, 3);

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

	//텍스쳐 로딩
	D3DXCreateTextureFromFile(
		_device,
		"전효성.jpg",
		&_texture);

//뷰, 투영행렬 준비
//====================================================================
//			## 뷰 스페이스 ##
//====================================================================
	//뷰행렬 및 뷰벡터 준비
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0위치를 바라본다
	D3DXVECTOR3 eyePos(0, 0, -10);			//카메라 눈의 위치
	D3DXVECTOR3 up(0, 1, 0);				//상방벡터 그냥 0,1,0

	//D3DXMatrixLookAtLH(뷰행렬, 눈위치, 바라볼위치, 업벡터)
	D3DXMatrixLookAtLH(&matView, &eyePos, &lookAtPos, &up);

	//뷰행렬 세팅
	_device->SetTransform(D3DTS_VIEW, &matView);

//====================================================================
//			## 투영 ##
//====================================================================
	//투영행렬 준비
	D3DXMATRIXA16 matProjection;

	D3DXMatrixPerspectiveFovLH(
		&matProjection,		//투영행렬
		D3DXToRadian(60),	//화각 60도
		(float)(WINSIZEX) / static_cast<float>(WINSIZEY), //화면 종횡비
		0.01f,				//근거리 평면 거리(0일때 뎁스가 꼬인다)
		100.0f);			//원거리 평면 거리

	//투영행렬 세팅
	_device->SetTransform(D3DTS_PROJECTION, &matProjection);
//============================================================================

	//라이트기능은 잠시 꺼두자
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

//====================================================================
//			## 텍스쳐 Wrap 모드 ##
//====================================================================
	//반복적으로 나온다 1 넘어가는 UV 좌표는 1을 빼서 다시 0부터 시작
	_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	////반복적으로 반전 나온다 1넘어가는 UV 좌표는 1부터 0으로 빠지고 0이하로 빠지면 다시 1을 향하여 증가
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	//
	////머리끄댕기 땡기듯 1 넘어가는 UV 좌표는 싸그리 1로 생각한다
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	//
	////머리끄댕기 땡기듯 1넘어가는 UV좌표 세팅된 보더 컬러로 칠한다
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
	////UV 좌표가 1 넘어갔을때 그릴 색상설정
	//_device->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0xffff00ff); 



	return S_OK;
}

void textureTestScene::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
	SAFE_RELEASE(_texture);
}

void textureTestScene::update(void)
{
}

void textureTestScene::render(void)
{
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
