#include "stdafx.h"
#include "hierarchyScene1.h"

HRESULT hierarchyScene1::init(void)
{
	//큐브생성
	this->CreateCube();

	//자식붙인다
	_cubeTrans.AddChild(&_childCubeTrans);

	//손자 위치
	_grandChildCubeTrans.SetWorldPosition(-3, 0, 5);

	//라이트 오프
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

void hierarchyScene1::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
}

void hierarchyScene1::update(void)
{
	//자식각도
	static float childAngle = 0.0f;

	//초당 90도 증가
	childAngle += D3DXToRadian(90) * _timeDelta;

	_childCubeTrans.SetLocalPosition(cosf(childAngle) * 1, sinf(childAngle) * 1, 0.0f);

	//바라보기
	D3DXVECTOR3 targetPos = _cubeTrans.GetWorldPosition();

	_grandChildCubeTrans.LookPosition(targetPos, D3DXVECTOR3(1, 0, 0));


	float deltaMove = 3.0f * _timeDelta;
	float deltaAngle = D3DXToRadian(90) * _timeDelta;

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) == FALSE)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_cubeTrans.MovePositionSelf(-deltaMove, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_cubeTrans.MovePositionSelf(deltaMove, 0.0f, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_cubeTrans.MovePositionSelf(0.0f, 0.0f, deltaMove);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_cubeTrans.MovePositionSelf(0.0f, 0.0f, -deltaMove);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_cubeTrans.RotateSelf(0.0f, -deltaAngle, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_cubeTrans.RotateSelf(0.0f, deltaAngle, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_cubeTrans.RotateSelf(-deltaAngle, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_cubeTrans.RotateSelf(deltaAngle, 0.0f, 0.0f);
		}
	}

	//카메라 디폴트컨트롤
	_mainCamera.DefaultControl(_timeDelta);
	//카메라 업데이트
	_mainCamera.updateCamToDevice();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_childCubeTrans.SetWorldPosition(0, 0, 10.0f);
	}
}

void hierarchyScene1::render(void)
{
	//큐브 월드 행렬 세팅
	_cubeTrans.SetDeviceWorld();
	RenderCube();

	//자식큐브 월드 행렬 세팅
	_childCubeTrans.SetDeviceWorld();
	RenderCube();

	//손자큐브 월드 행렬 세팅
	_grandChildCubeTrans.SetDeviceWorld();
	RenderCube();

}

void hierarchyScene1::CreateCube()
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

void hierarchyScene1::RenderCube()
{
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
}
