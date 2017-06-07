#include "stdafx.h"
#include "sceneTest_1.h"

HRESULT sceneTest_1::init(void)
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
	vertices[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertices[2].color = 0xff0000ff;

	//다 사용했으니 락해제
	_vb->Unlock();

	//정점의 컬러 정보를 출력하기 위해서는 디바이스의 기본 라이트 기능을 해제해야 한다
	//당분간 라이트 기능을 사용할 일이 없으니 꺼두자
	_device->SetRenderState(
		D3DRS_LIGHTING,			//뭘세팅할꺼냐?
		FALSE					//세팅값은 어떻게 되냐?
	);

	return S_OK;
}

void sceneTest_1::release(void)
{
	//정점버퍼해제
	SAFE_RELEASE(_vb);
}

void sceneTest_1::update(void)
{
}

void sceneTest_1::render(void)
{
	//SetStreamSource => 쉽게 이야기 하면 버텍스 버퍼 세팅
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));

	//지금 그리는 정점에 대한 정점 정보 플래그 세팅
	_device->SetFVF(MYVERTEX::FVF);

	//그리는것은 삼각형, 0번째 정점부터, 삼각형은 1개
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
