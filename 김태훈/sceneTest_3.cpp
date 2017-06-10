#include "stdafx.h"
#include "sceneTest_3.h"

HRESULT sceneTest_3::init(void)
{
	//정점데이터
	_vertex[0].pos = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	_vertex[1].pos = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	_vertex[2].pos = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	_vertex[3].pos = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	_vertex[0].color = D3DCOLOR_XRGB(255, 255, 0);
	_vertex[1].color = D3DCOLOR_XRGB(255, 255, 0);
	_vertex[2].color = D3DCOLOR_XRGB(255, 0, 0);
	_vertex[3].color = D3DCOLOR_XRGB(255, 0, 0);

	//인덱스데이터
	_index[0] = 0;
	_index[1] = 1;
	_index[2] = 2;
	_index[3] = 0;
	_index[4] = 2;
	_index[5] = 3;

	//정점의 컬러 정보를 출력하기 위해서는 디바이스의 기본 라이트 기능을 해제해야 한다
	//당분간 라이트 기능을 사용할 일이 없으니 꺼두자
	_device->SetRenderState(
		D3DRS_LIGHTING,			//뭘세팅할꺼냐?
		FALSE					//세팅값은 어떻게 되냐?
	);

	//백페이스 컬링(은면제거)
	//_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);	//시계방향 안그리겠다(반시계방향 그려진다)
	//_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//반시계방항 안그리겠다 (시계방향 그려진다) => 디폴트
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//컬링안함 (양방향 모두 그려진다)
	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //와이어프레임
	//각도초기화
	_angle = 0.0f;
	
	return S_OK;
}

void sceneTest_3::release(void)
{
}

void sceneTest_3::update(void)
{
	//초당 90도 회전
	_angle += D3DXToRadian(90) * _timeDelta;

	//각각 축에대한 회전행렬
	D3DXMATRIXA16 matRotation;
	//D3DXMatrixRotationX(&matRotation, _angle);	//x축 기준으로 회전행렬
	D3DXMatrixRotationY(&matRotation, _angle);		//y축 기준으로 회전행렬
	//D3DXMatrixRotationZ(&matRotation, _angle);	//z축 기준으로 회전행렬
	//임의의 축에 대한 회전행렬
	//D3DXMatrixRotationAxis(&matRotation, &D3DXVECTOR3(0, 1, 0), _angle);

	//월드행렬
	_matWorld = matRotation;
}

void sceneTest_3::render(void)
{
//====================================================================
//			## 월드 스페이스 ##
//====================================================================
	//특정물체를 그리기전에 물체에 해당되는 월드행렬을 세팅하고 그릴것!!!
	_device->SetTransform(D3DTS_WORLD, &_matWorld);

//====================================================================
//			## 뷰 스페이스 ##
//====================================================================
	//뷰행렬 및 뷰벡터 준비
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0위치를 바라본다
	D3DXVECTOR3 eyePos(0, 1, -5);			//카메라 눈의 위치
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
		0.001f,				//근거리 평면 거리(0일때 뎁스가 꼬인다)
		100.0f);			//원거리 평면 거리

							//투영행렬 세팅
	_device->SetTransform(D3DTS_PROJECTION, &matProjection);

//============================================================================

	//지금 그리는 정점에 대한 정점 정보 플래그 세팅
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,				//그리는것 삼각형
		0,								//최소 인덱스 시작점
		4,								//정점 갯수
		2,								//삼각형 갯수
		_index,							//인덱스 배열
		D3DFMT_INDEX32,					//포맷32비트
		_vertex,						//정점 배열
		sizeof(MYVERTEX));				//정점구조체 크기

}
