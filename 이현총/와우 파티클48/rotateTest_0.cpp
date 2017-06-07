#include "stdafx.h"
#include "rotateTest_0.h"

HRESULT rotateTest_0::init(void)
{
	//큐브 생성
	this->CreateCube();

	//회전값 초기화
	_xAngle = 0.0f;
	_yAngle = 0.0f;
	_zAngle = 0.0f;

	//큐브 월드 행렬 초기화
	D3DXMatrixIdentity(&_matWorld);
	
//====================================================================
//			## 뷰 스페이스 ##
//====================================================================
	//뷰행렬 및 뷰벡터 준비
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0위치를 바라본다
	D3DXVECTOR3 eyePos(1, 3, -5);			//카메라 눈의 위치
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

void rotateTest_0::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
}

void rotateTest_0::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_yAngle -= 10.0f;
	}
	else if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_yAngle += 10.0f;
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_xAngle -= 10.0f;
	}
	else if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_xAngle += 10.0f;
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_zAngle -= 10.0f;
	}
	else if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_zAngle += 10.0f;
	}

	/*
	//짐벌락 현상이 발생
	D3DXMATRIXA16  matRotX, matRotY, matRotZ;
	//X축에대한 회전행렬
	D3DXMatrixRotationX(&matRotX, _xAngle * D3DXToRadian(1));
	//Y축에대한 회전행렬
	D3DXMatrixRotationY(&matRotY, _yAngle * D3DXToRadian(1));
	//Z축에대한 회전행렬
	D3DXMatrixRotationZ(&matRotZ, _zAngle * D3DXToRadian(1));

	//월드행렬
	//회전량대로 곱해버리는 오일러 회전 방식
	_matWorld = matRotX * matRotY * matRotZ;
	*/

	/*쿼터니온으로 짐벌락현상을 최소화하기*/
	//3축에 대한 회전 정보를 쿼터니온으로 얻기
	D3DXQUATERNION quat;

	//각 회전 량에 따른 회전 값으로 쿼터니온를 얻는다
	D3DXQuaternionRotationYawPitchRoll(&quat, _yAngle * D3DXToRadian(1), _xAngle * D3DXToRadian(1), _zAngle * D3DXToRadian(1));

	//회전 쿼터니온으로 회전행렬을 얻는다
	D3DXMATRIXA16 matRotation;
	D3DXMatrixRotationQuaternion(&matRotation, &quat);

	//월드행렬
	_matWorld = matRotation;

	//쿼터니온의 장점
	//1. 숫자 4개만으로 3축에 대한 회전정보를 지닐 수 있다
	//2. 숫자 4개로 구성되어 있기때문에 회전량을 다른 사원수랑 곱할때 계산량이 적다
	//3. 짐벌락 현상을 해결할 수 있다 (단 완전하게 해결해줄 수는 없다)
	//D3D에서 쿼터니온은 오직 회전관련 함수만 존재한다
}

void rotateTest_0::render(void)
{
	_device->SetTransform(D3DTS_WORLD, &_matWorld);

	//SetStreamSource => 쉽게 이야기 하면 버텍스 버퍼 세팅
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));

	//인덱스버퍼 세팅
	_device->SetIndices(_ib);

	//지금 그리는 정점에 대한 정점 정보 플래그 세팅
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,	 //라인그리기			
		0,				//시작 버텍스배열 인덱스				
		0,
		24,				//정점 갯수			
		0,				//시작 인덱스배열 인덱스		
		12				//그리는 개체수 라인이 12개
	);

	//회전값 출력
	char str[128];
	sprintf(str, "XAngle: %.2f", _xAngle);
	FONTMANAGER->fontOut(str, 0, 100, 0xffff0000);
	sprintf(str, "YAngle: %.2f", _yAngle);
	FONTMANAGER->fontOut(str, 0, 130, 0xffff0000);
	sprintf(str, "ZAngle: %.2f", _zAngle);
	FONTMANAGER->fontOut(str, 0, 160, 0xffff0000);

	GIZMOMANAGER->Circle(D3DXVECTOR3(0, 0, 0), 3.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0xffff0000);
	GIZMOMANAGER->Circle(D3DXVECTOR3(0, 0, 0), 3.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xff00ff00);
	GIZMOMANAGER->Circle(D3DXVECTOR3(0, 0, 0), 3.0f, D3DXVECTOR3(
		sin(_yAngle * D3DXToRadian(1)),
		0.0f,
		cos(_yAngle * D3DXToRadian(1))),
		0xff0000ff);
}

void rotateTest_0::CreateCube(void)
{
	//정점 버퍼 만들기
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 24,		//만들어질 정점버퍼의 크기(삼각형은 정점 3개 필요)
		D3DUSAGE_WRITEONLY,			//만들어지는 정점버퍼의 속성(일단 writeonly가 접근이 빠르다, 후에 정점버퍼에 접근이 자주 일어난다면 다이내믹으로 변경하자)
		MYVERTEX::FVF,				//FVF정보
		D3DPOOL_DEFAULT,			//메모리풀 보관방식
		&_vb,						//생성된 버텍버퍼
		NULL);						//그냥 묻지도 따지지도 말고 NULL

	//쿼드 플랜 정점
	MYVERTEX quad[4];
	quad[0].pos = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	quad[1].pos = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	quad[2].pos = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	quad[3].pos = D3DXVECTOR3(0.5f, -0.5f, -0.5f);

	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(-90));

	//정점 배열 준비
	MYVERTEX vertices[24];

	//앞면
	memcpy(vertices, quad, sizeof(MYVERTEX) * 4);
	vertices[0].color = 0xffff0000;
	vertices[1].color = 0xffff0000;
	vertices[2].color = 0xffff0000;
	vertices[3].color = 0xffff0000;

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//우측면 복사
	memcpy(vertices + 4, quad, sizeof(MYVERTEX) * 4);
	vertices[4].color = 0xff00ff00;
	vertices[5].color = 0xff00ff00;
	vertices[6].color = 0xff00ff00;
	vertices[7].color = 0xff00ff00;
	
	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//뒷면 복사
	memcpy(vertices + 8, quad, sizeof(MYVERTEX) * 4);
	vertices[8].color = 0xffff0000;
	vertices[9].color = 0xffff0000;
	vertices[10].color = 0xffff0000;
	vertices[11].color = 0xffff0000;

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//좌측면 복사
	memcpy(vertices + 12, quad, sizeof(MYVERTEX) * 4);
	vertices[12].color = 0xff00ff00;
	vertices[13].color = 0xff00ff00;
	vertices[14].color = 0xff00ff00;
	vertices[15].color = 0xff00ff00;

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-90));

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}
	
	//윗면 복사
	memcpy(vertices + 16, quad, sizeof(MYVERTEX) * 4);
	vertices[16].color = 0xff0000ff;
	vertices[17].color = 0xff0000ff;
	vertices[18].color = 0xff0000ff;
	vertices[19].color = 0xff0000ff;

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-180));

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//아래면 복사
	memcpy(vertices + 20, quad, sizeof(MYVERTEX) * 4);
	vertices[20].color = 0xff0000ff;
	vertices[21].color = 0xff0000ff;
	vertices[22].color = 0xff0000ff;
	vertices[23].color = 0xff0000ff;

	//정점 락
	void* pVertices = NULL;
	_vb->Lock(0, 0, &pVertices, 0);
	//메모리 복사
	memcpy(pVertices, vertices, sizeof(MYVERTEX) * 24);
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

	WORD indices[36];
	for (int i = 0; i < 6; i++)
	{
		//정점 스타트 인덱스
		WORD vertexIndex = i * 4;
		//인덱스 배열 스타트 인덱스
		WORD indicesIndex = i * 6;

		indices[indicesIndex + 0] = vertexIndex + 0;
		indices[indicesIndex + 1] = vertexIndex + 1;
		indices[indicesIndex + 2] = vertexIndex + 2;
		indices[indicesIndex + 3] = vertexIndex + 0;
		indices[indicesIndex + 4] = vertexIndex + 2;
		indices[indicesIndex + 5] = vertexIndex + 3;
	}

	//인덱스 락
	void* pIndices = NULL;
	_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, indices, sizeof(WORD) * 36);
	_ib->Unlock();
}
