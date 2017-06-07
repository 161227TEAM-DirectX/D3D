#include "stdafx.h"
#include "gizmoTestScene.h"

HRESULT gizmoTestScene::init(void)
{
//====================================================================
//			## 뷰 스페이스 ##
//====================================================================
	//뷰행렬 및 뷰벡터 준비
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0위치를 바라본다
	D3DXVECTOR3 eyePos(3, 10, -20);			//카메라 눈의 위치
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
	
	return S_OK;
}

void gizmoTestScene::release(void)
{
}

void gizmoTestScene::update(void)
{
}

void gizmoTestScene::render(void)
{
	//기즈모매니져 월드렌더
	GIZMOMANAGER->WorldGrid(1, 10);
	GIZMOMANAGER->Circle(D3DXVECTOR3(0, 2, 0), 3.0f, D3DXVECTOR3(0, 0, 1), 0xff00fffff);

	//GIZMOMANAGER->WireSphere(D3DXVECTOR3(-3, 0, 1), 2, 0xffffff00);

	//GIZMOMANAGER->AABB(D3DXVECTOR3(0, 1, -5), D3DXVECTOR3(10, 8, 10), 0xffffff00);
}
