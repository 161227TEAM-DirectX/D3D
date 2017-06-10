#include "stdafx.h"
#include "lightTestScene.h"


HRESULT lightTestScene::init(void)
{
	//카메라 위치 세팅
	_mainCamera.SetLocalPosition(-1, 2, -7);

	//큐브생성
	this->CreateCube();

	//큐브 재질 정보
	//0 ~ 255 // 0.0f ~ 1.0f
	_cubeMaterial.Diffuse = D3DXCOLOR(0xffff0000);
	_cubeMaterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_cubeMaterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_cubeMaterial.Emissive = D3DXCOLOR(0, 0, 0, 0);
	_cubeMaterial.Power = 10.0f;

	//라이트
	ZeroMemory(&_light, sizeof(_light));
	_light.Type = D3DLIGHT_DIRECTIONAL;				//광원타입
	_light.Direction = D3DXVECTOR3(-1.0f, 0, 0);	//바라볼 위치
	_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//백색광
	_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//라이트 세팅
	_device->SetRenderState(D3DRS_LIGHTING, TRUE);	//광원 사용하겠다
	_device->SetLight(0, &_light);					//0번 광원 정보세팅
	_device->LightEnable(0, TRUE);					//0번 광원 활성화

	//Ambient 세팅
	_device->SetRenderState(D3DRS_AMBIENT, 0xff000000);
	//스펙큘러 세팅
	_device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	return S_OK;
}

void lightTestScene::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
}

void lightTestScene::update(void)
{
	float deltaMove = 3.0f * _timeDelta;
	float deltaAngle = D3DXToRadian(90) * _timeDelta;

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) == FALSE)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_lightTrans.MovePositionSelf(-deltaMove, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_lightTrans.MovePositionSelf(deltaMove, 0.0f, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_lightTrans.MovePositionSelf(0.0f, 0.0f, deltaMove);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_lightTrans.MovePositionSelf(0.0f, 0.0f, -deltaMove);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_lightTrans.RotateSelf(0.0f, -deltaAngle, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_lightTrans.RotateSelf(0.0f, deltaAngle, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_lightTrans.RotateSelf(-deltaAngle, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_lightTrans.RotateSelf(deltaAngle, 0.0f, 0.0f);
		}
	}

	//라이트 방향 새로갱신
	_light.Direction = _lightTrans.GetForward();
	//갱신된 라이트 다시 세팅
	_device->SetLight(0, &_light);

	//카메라 디폴트컨트롤
	_mainCamera.DefaultControl(_timeDelta);
	//카메라 업데이트
	_mainCamera.updateCamToDevice();
}

void lightTestScene::render(void)
{
	//큐브의 재질정보 세팅
	_device->SetMaterial(&_cubeMaterial);
	_cubeTrans.SetDeviceWorld();
	this->RenderCube();

	_lightTrans.RenderGimozo();
}

void lightTestScene::CreateCube()
{
	//정점 버퍼 만들기
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX_PN) * 24,	//만들어질 정점버퍼의 크기(삼각형은 정점 3개 필요)
		D3DUSAGE_WRITEONLY,			//만들어지는 정점버퍼의 속성(일단 writeonly가 접근이 빠르다, 후에 정점버퍼에 접근이 자주 일어난다면 다이내믹으로 변경하자)
		MYVERTEX_PN::FVF,			//FVF정보
		D3DPOOL_DEFAULT,			//메모리풀 보관방식
		&_vb,						//생성된 버텍버퍼
		NULL);						//그냥 묻지도 따지지도 말고 NULL

									//쿼드 플랜 정점
	MYVERTEX_PN quad[4];
	quad[0].pos = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	quad[1].pos = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	quad[2].pos = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	quad[3].pos = D3DXVECTOR3(0.5f, -0.5f, -0.5f);

	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(-90));

	//정점 배열 준비
	MYVERTEX_PN vertices[24];

	//앞면
	memcpy(vertices, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[0].normal = D3DXVECTOR3(0, 0, -1);
	vertices[1].normal = D3DXVECTOR3(0, 0, -1);
	vertices[2].normal = D3DXVECTOR3(0, 0, -1);
	vertices[3].normal = D3DXVECTOR3(0, 0, -1);

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//우측면 복사
	memcpy(vertices + 4, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[4].normal = D3DXVECTOR3(1, 0, 0);
	vertices[5].normal = D3DXVECTOR3(1, 0, 0);
	vertices[6].normal = D3DXVECTOR3(1, 0, 0);
	vertices[7].normal = D3DXVECTOR3(1, 0, 0);

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//뒷면 복사
	memcpy(vertices + 8, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[8].normal = D3DXVECTOR3(0, 0, 1);
	vertices[9].normal = D3DXVECTOR3(0, 0, 1);
	vertices[10].normal = D3DXVECTOR3(0, 0, 1);
	vertices[11].normal = D3DXVECTOR3(0, 0, 1);

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//좌측면 복사
	memcpy(vertices + 12, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[12].normal = D3DXVECTOR3(-1, 0, 0);
	vertices[13].normal = D3DXVECTOR3(-1, 0, 0);
	vertices[14].normal = D3DXVECTOR3(-1, 0, 0);
	vertices[15].normal = D3DXVECTOR3(-1, 0, 0);

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-90));

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//윗면 복사
	memcpy(vertices + 16, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[16].normal = D3DXVECTOR3(0, 1, 0);
	vertices[17].normal = D3DXVECTOR3(0, 1, 0);
	vertices[18].normal = D3DXVECTOR3(0, 1, 0);
	vertices[19].normal = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-180));

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//아래면 복사
	memcpy(vertices + 20, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[20].normal = D3DXVECTOR3(0, -1, 0);
	vertices[21].normal = D3DXVECTOR3(0, -1, 0);
	vertices[22].normal = D3DXVECTOR3(0, -1, 0);
	vertices[23].normal = D3DXVECTOR3(0, -1, 0);

	//정점 락
	void* pVertices = NULL;
	_vb->Lock(0, 0, &pVertices, 0);
	//메모리 복사
	memcpy(pVertices, vertices, sizeof(MYVERTEX_PN) * 24);
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

void lightTestScene::RenderCube()
{
	//SetStreamSource => 쉽게 이야기 하면 버텍스 버퍼 세팅
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX_PN));

	//인덱스버퍼 세팅
	_device->SetIndices(_ib);

	//지금 그리는 정점에 대한 정점 정보 플래그 세팅
	_device->SetFVF(MYVERTEX_PN::FVF);

	_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,	 //라인그리기			
		0,				//시작 버텍스배열 인덱스				
		0,
		24,				//정점 갯수			
		0,				//시작 인덱스배열 인덱스		
		12				//그리는 개체수 라인이 12개
	);
}
