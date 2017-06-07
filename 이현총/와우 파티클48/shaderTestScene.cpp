#include "stdafx.h"
#include "shaderTestScene.h"

HRESULT shaderTestScene::init(void)
{
	//카메라 조정
	_mainCamera.SetLocalPosition(-1, 2, -10);

	//큐브생성
	this->CreateCube();

	//쉐이더 로딩시 컴파일 에러가 나면 에러의 내용을 받아올 Error버퍼
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;

	//fx파일로 부터 이펙트 객체를 로딩한다
	D3DXCreateEffectFromFile(
		_device,				//디바이스
		"HLSL_LambertLighting.fx",	//파일이름
		NULL,					//세이더를 컴파일할때 추가로 사용할 #define정의
		NULL,					//세이더를 컴파일할때 #include지시문 처리할때 사용할 인터페이스 플래그
		shaderFlag,				//세이더 컴파일 플래그
		NULL,					//세이더 매개변수를 공유할 메모리 풀
		&_effect,				//로딩될 세이더 이펙트 포인터
		&error);				//세이더 로딩하고 컴파일 할때 컴파일에 문제가 생기면 헤더버퍼에 에러메세지가 들어간다

	//문제가 있다면
	if (error != NULL)
	{
		//에러버퍼 릴리즈
		SAFE_RELEASE(error);
		return E_FAIL;
	}

	//쉐이더 로딩이 잘 되었으니 핸들을 받아온다
	_hTechnique = _effect->GetTechniqueByName("MyShader");

	//전역변수 핸들
	_hMatWorld = _effect->GetParameterByName(NULL, "matWorld");
	_hMatView = _effect->GetParameterByName(NULL, "matView");
	_hMatProjection = _effect->GetParameterByName(NULL, "matProjection");
	_hColor = _effect->GetParameterByName(NULL, "vColor");

	return S_OK;
}

void shaderTestScene::release(void)
{
	SAFE_RELEASE(this->_vb);
	SAFE_RELEASE(this->_ib);

	//이펙트 해제
	SAFE_RELEASE(_effect);
}

void shaderTestScene::update(void)
{
	//큐브트렌스 업데이트
	//_cubeTrans.DefaultMyControl(_timeDelta);
	_lightTrans.DefaultMyControl(_timeDelta);

	//카메라 디폴트컨트롤
	_mainCamera.DefaultControl(_timeDelta);
	//카메라 업데이트
	_mainCamera.updateCamToDevice();
}

void shaderTestScene::render(void)
{
	//이펙트에 전역변수 값을 세팅하기
	D3DXMATRIXA16 matWorld = _cubeTrans.GetFinalMatrix();
	//월드행렬세팅
	_effect->SetMatrix(_hMatWorld, &matWorld);
	//디바이스로부터 세팅된 뷰행렬과 투영행렬을 얻기
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProjection;
	_device->GetTransform(D3DTS_VIEW, &matView);
	_device->GetTransform(D3DTS_PROJECTION, &matProjection);

	//뷰행렬 세팅
	_effect->SetMatrix(_hMatView, &matView);
	//투영행렬 세팅
	_effect->SetMatrix(_hMatProjection, &matProjection);
	//컬러벡터 세팅(주의사항 세팅되는 벡터는 모두 벡터4로 대동단결)
	D3DXVECTOR4 color(1, 0, 1, 1); //RGBA
	_effect->SetVector(_hColor, &color);


	//광원의 방향
	D3DXVECTOR4 lightDir(_lightTrans.GetForward(), 1);
	_effect->SetVector("vLightDir", &lightDir);
	//월드 역행렬전달
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);
	_effect->SetMatrix("matInvWorld", &matInvWorld);



	//테크닉세팅
	_effect->SetTechnique(_hTechnique);

	//쉐이더로 큐브렌더
	UINT iPassNum = 0;

	//이펙트로 렌더링시작
	_effect->Begin(&iPassNum, 0);

	//패스 수대로 for문으로 돌린다
	for (UINT i = 0; i < iPassNum; i++)
	{
		_effect->BeginPass(i);

		//렌더
		this->RenderCube();

		_effect->EndPass();
	}

	_effect->End();

	_lightTrans.RenderGimozo();

}

void shaderTestScene::CreateCube()
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

void shaderTestScene::RenderCube()
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
