#include "stdafx.h"
#include "sceneTest_0.h"

HRESULT sceneTest_0::init(void)
{
	//정점 정보를 채워 넣기
	_vertices[0].pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_vertices[0].color = 0xffff0000;
	_vertices[1].pos = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_vertices[1].color = 0xff00ff00;
	_vertices[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vertices[2].color = 0xff0000ff;

	//정점의 컬러 정보를 출력하기 위해서는 디바이스의 기본 라이트 기능을 해제해야 한다
	//당분간 라이트 기능을 사용할 일이 없으니 꺼두자
	_device->SetRenderState(
		D3DRS_LIGHTING,			//뭘세팅할꺼냐?
		FALSE					//세팅값은 어떻게 되냐?
	);

	return S_OK;
}

void sceneTest_0::release(void)
{
}

void sceneTest_0::update(void)
{
}

void sceneTest_0::render(void)
{
	//정점데이터의 정보로 삼각형 그리기
	
	//지금 그리는 정점에 대한 정보 FVF 플래그 값을 넣어주자
	//_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	//_device->SetFVF(FVF);
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,		//그리는 것은 삼각형이다
		1,						//그려지는 개체수는 몇개냐?
		_vertices,				//정점 구조체
		sizeof(MYVERTEX)		//정점 구조체 한개의 크기
	);
}
