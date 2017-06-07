#include "stdafx.h"
#include "sceneTest_4.h"

HRESULT sceneTest_4::init(void)
{
	//그리드 클래스 생성 및 초기화
	_grid = new grid;
	_grid->init();

	//정점 버퍼 만들기
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 3,		//만들어질 정점버퍼의 크기(삼각형은 정점 3개 필요)
		D3DUSAGE_WRITEONLY,			//만들어지는 정점버퍼의 속성(일단 writeonly가 접근이 빠르다, 후에 정점버퍼에 접근이 자주 일어난다면 다이내믹으로 변경하자)
		MYVERTEX::FVF,				//FVF정보
		D3DPOOL_DEFAULT,			//메모리풀 보관방식
		&_vb,						//생성된 버텍버퍼
		NULL);						//그냥 묻지도 따지지도 말고 NULL

	//D3DPOOL_DEFAULT => 정점버퍼의 메모리는 시스템사양에 맞춰 알아서 저장이 되는데, 일반적으로 그래픽카드메모리에 저장이된다
	//D3DPOOl_MANAGED => 정점버퍼의 메모리는 시스템의 메모리영역에 저장이 되고 그래픽카드를 사용한다면 그래픽카드메모리에 저장이된다
	//즉 버퍼의 원본내용이 시스템메모리에 저장이 된 상태에서 그래픽카드메모리에 그거와 똑같은 사본을 만들어 사용하는 방식
	//이는 디바이스가 해제 되어도 버퍼의 내용을 다시 복구할 수 있는 여지가 있다

	//정점 배열준비
	MYVERTEX vertices[8];
	vertices[0].pos = D3DXVECTOR3(-2.3f, -2.3f, -2.3f);
	vertices[0].color = 0xffffff00;
	vertices[1].pos = D3DXVECTOR3(-2.3f, -2.3f, 2.3f);
	vertices[1].color = 0xffffff00;
	vertices[2].pos = D3DXVECTOR3(2.3f, -2.3f, 2.3f);
	vertices[2].color = 0xffffff00;
	vertices[3].pos = D3DXVECTOR3(2.3f, -2.3f, -2.3f);
	vertices[3].color = 0xffffff00;
	vertices[4].pos = D3DXVECTOR3(-2.3f, 2.3f, -2.3f);
	vertices[4].color = 0xffffff00;
	vertices[5].pos = D3DXVECTOR3(-2.3f, 2.3f, 2.3f);
	vertices[5].color = 0xffffff00;
	vertices[6].pos = D3DXVECTOR3(2.3f, 2.3f, 2.3f);
	vertices[6].color = 0xffffff00;
	vertices[7].pos = D3DXVECTOR3(2.3f, 2.3f, -2.3f);
	vertices[7].color = 0xffffff00;

	//정점 락
	void* pVertices = NULL;
	_vb->Lock(0, 0, &pVertices, 0);
	//메모리 복사
	memcpy(pVertices, vertices, sizeof(MYVERTEX) * 8);
	_vb->Unlock();

	//인덱스 버퍼 생성
	_device->CreateIndexBuffer(
		sizeof(WORD) * 36,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&_ib,
		NULL);

	//		5--------6
	//     /|       /|
	//    4--------7 |
	//    | |      | | 
	//    | 1------| 2
	//    |/       |/
	//    0--------3
	
	WORD indices[24] = {
		0, 4, 4, 7, 7, 3, 3, 0,
		1, 5, 5, 6, 6, 2, 2, 1,
		0, 1, 4, 5, 7, 6, 3, 2 };

	//인덱스 락
	void* pIndices = NULL;
	_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, indices, sizeof(WORD) * 24);
	_ib->Unlock();

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

void sceneTest_4::release(void)
{
	//그리드 클래스 해제
	SAFE_DELETE(_grid);
	//버퍼해제
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
}

void sceneTest_4::update(void)
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

void sceneTest_4::render(void)
{
	//그리드 클래스 렌더
	_grid->render();

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

	//인덱스버퍼 세팅
	_device->SetIndices(_ib);

	//지금 그리는 정점에 대한 정점 정보 플래그 세팅
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawIndexedPrimitive(
		D3DPT_LINELIST,	 //라인그리기			
		0,				//시작 버텍스배열 인덱스				
		0,							
		8,				//정점 갯수			
		0,				//시작 인덱스배열 인덱스		
		12				//그리는 개체수 라인이 12개
		);				
}
