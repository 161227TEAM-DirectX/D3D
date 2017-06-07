#include "stdafx.h"
#include "sceneTest_2.h"

HRESULT sceneTest_2::init(void)
{
	//정점 버퍼 만들기
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 3,		//만들어질 정점버퍼의 크기(삼각형은 정점 3개 필요)
		D3DUSAGE_WRITEONLY,			//만들어지는 정점버퍼의 속성(일단 writeonly가 접근이 빠르다, 후에 정점버퍼에 접근이 자주 일어난다면 다이내믹으로 변경하자)
		MYVERTEX::FVF,				//FVF정보
		D3DPOOL_DEFAULT,			//메모리풀 보관방식
		&_vb,						//생성된 버텍버퍼
		NULL);						//그냥 묻지도 따지지도 말고 NULL

									//정점 정보 채워넣기
	LPMYVERTEX vertices = NULL;
	//Lock걸고 정점을 채워넣을 주소를 vertices에 받아오기
	//
	_vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertices[0].color = 0xffff0000;
	vertices[1].pos = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertices[1].color = 0xff00ff00;
	vertices[2].pos = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	vertices[2].color = 0xff0000ff;

	//다 사용했으니 락해제
	_vb->Unlock();

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

	//각도초기화
	_angle = 0;
	
	return S_OK;
}

void sceneTest_2::release(void)
{
	//정점버텍버퍼해제
	SAFE_RELEASE(_vb);
}

void sceneTest_2::update(void)
{
	//초당 90도 회전
	_angle += D3DXToRadian(90) * _timeDelta;

	//각각 축에대한 회전행렬
	D3DXMATRIXA16 matRotation;
	//D3DXMatrixRotationX(&matRotation, _angle);		//x축 기준으로 회전행렬
	D3DXMatrixRotationY(&matRotation, _angle);		//y축 기준으로 회전행렬
	//D3DXMatrixRotationZ(&matRotation, _angle);		//z축 기준으로 회전행렬
	//임의의 축에 대한 회전행렬
	//D3DXMatrixRotationAxis(&matRotation, &D3DXVECTOR3(0, 1, 0), _angle);

	//월드행렬
	_matWorld = matRotation;


}

void sceneTest_2::render(void)
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
	D3DXVECTOR3 eyePos(0, 1, -10);			//카메라 눈의 위치
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

	//SetStreamSource => 쉽게 이야기 하면 버텍스 버퍼 세팅
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));

	//지금 그리는 정점에 대한 정점 정보 플래그 세팅
	_device->SetFVF(MYVERTEX::FVF);

	//그리는것은 삼각형, 0번째 정점부터, 삼각형은 1개
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
