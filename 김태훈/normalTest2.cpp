#include "stdafx.h"
#include "normalTest2.h"

HRESULT normalTest2::init(void)
{
	//쿼드생성
	this->CreateQuad();

	//정점의 형태를 알려주는 배열
	D3DVERTEXELEMENT9	vertElement[6];				//배열을 정점정보 개수 + 1
    
	//위치
	vertElement[0].Stream = 0;						//일단 0	
	vertElement[0].Offset = 0;						//메모리 시작 바이트 단위
	vertElement[0].Type = D3DDECLTYPE_FLOAT3;		//자료타입
	vertElement[0].Method = D3DDECLMETHOD_DEFAULT;	//그냥 디폴트
	vertElement[0].Usage = D3DDECLUSAGE_POSITION;	//정보타입은 위치
	vertElement[0].UsageIndex = 0;					//일단 0

	//UV
	vertElement[1].Stream = 0;						//일단 0	
	vertElement[1].Offset = 12;						//메모리 시작 바이트 단위
	vertElement[1].Type = D3DDECLTYPE_FLOAT2;		//자료타입
	vertElement[1].Method = D3DDECLMETHOD_DEFAULT;	//그냥 디폴트
	vertElement[1].Usage = D3DDECLUSAGE_TEXCOORD;	//정보타입은 텍스쳐
	vertElement[1].UsageIndex = 0;					//일단 0

	//normal
	vertElement[2].Stream = 0;						//일단 0
	vertElement[2].Offset = 20;						//메모리 시작 바이트 단위
	vertElement[2].Type = D3DDECLTYPE_FLOAT3;		//자료타입
	vertElement[2].Method = D3DDECLMETHOD_DEFAULT;	//그냥 디폴트
	vertElement[2].Usage = D3DDECLUSAGE_NORMAL;		//정보타입은 노말
	vertElement[2].UsageIndex = 0;					//일단 0

	//binormal
	vertElement[3].Stream = 0;						//Stream 은 0
	vertElement[3].Offset = 32;						//메모리의 시작 Byte 단위 0
	vertElement[3].Type = D3DDECLTYPE_FLOAT3;		//자료의 타입
	vertElement[3].Method = D3DDECLMETHOD_DEFAULT;	//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[3].Usage = D3DDECLUSAGE_BINORMAL;	//정보 타입
	vertElement[3].UsageIndex = 0;					//UsageIndex 일단 0

	//Tangent
	vertElement[4].Stream = 0;						//Stream 은 0
	vertElement[4].Offset = 44;						//메모리의 시작 Byte 단위 0
	vertElement[4].Type = D3DDECLTYPE_FLOAT3;		//자료의 타입
	vertElement[4].Method = D3DDECLMETHOD_DEFAULT;	//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[4].Usage = D3DDECLUSAGE_TANGENT;	//정보 타입
	vertElement[4].UsageIndex = 0;					//UsageIndex 일단 0

	//더이상 없으니 선언종료
	D3DVERTEXELEMENT9 end = D3DDECL_END(); //{0xFF,0,D3DDECLTYPE_UNUSED,0,0,0}
	vertElement[5] = end;

	_device->CreateVertexDeclaration(
		vertElement,
		&_vDeclation);

	//텍스쳐 로딩
	D3DXCreateTextureFromFile(_device, "terrain4.png", &_diffuseTex);
	D3DXCreateTextureFromFile(_device, "Stone-normal.png", &_normalTex);

	//셰이더 로딩
	//쉐이더 로딩시 컴파일 에러가 나면 에러의 내용을 받아올 Error버퍼
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;
	//fxFile 로 부터 Effect 객체 로딩
	D3DXCreateEffectFromFile(
		_device,				//디바이스
		"TextureNormal2.fx",	//불러올 셰이더 코드 파일이름
		NULL, 					//셰이더를 컴파일할때 추가로 사용할 #define 정의 ( 일단 NULL )
		NULL, 					//셰이더를 컴파일할때 #include 지시문을 처리할때 사용할 인터페이스 플레그 ( 일단 NULL )
		shaderFlag,				//셰이더 컴파일 플레그
		NULL, 					//셰이더 매개변수를 공유할 메모리풀 ( 일단 NULL )
		&_effect,				//로딩될 셰이더 Effect 포인터
		&error 					//셰이더를 로딩하고 컴파일할때 문제가 생기면 해당 버퍼에 에러메시지가 들어간다 ( 성공적으로 로딩되면 NULL 이 참조된다 )
	);

	//로딩에 문제가 있다면....
	if (error != NULL)
	{
		//Error 버퍼 Release
		SAFE_RELEASE(error);
		return E_FAIL;
	}

	return S_OK;
}

void normalTest2::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
	SAFE_RELEASE(_diffuseTex);
	SAFE_RELEASE(_normalTex);
	SAFE_RELEASE(_effect);
	SAFE_RELEASE(_vDeclation);
}

void normalTest2::update(void)
{
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();

	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		_lightTrans.DefaultMyControl(_timeDelta);
	}
	else
	{
		_quadTrans.DefaultMyControl(_timeDelta);
	}
}

void normalTest2::render(void)
{
	//이펙트에 전역 변수값을 세팅한다.
	D3DXMATRIXA16 matWorld = _quadTrans.GetFinalMatrix();

	//디바이스로부터 세팅된 View 행렬과 Projection 행렬을 얻는다.
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProjection;
	_device->GetTransform(D3DTS_VIEW, &matView);
	_device->GetTransform(D3DTS_PROJECTION, &matProjection);

	//총변환 행렬
	D3DXMATRIXA16 matWVP = matWorld * matView * matProjection;
	_effect->SetMatrix("matWVP", &matWVP);

	//월드행렬
	_effect->SetMatrix("matWorld", &matWorld);

	//광원방향
	D3DXVECTOR3 lightDir = _lightTrans.GetForward();
	_effect->SetVector("vLightDir", &D3DXVECTOR4(lightDir, 1));

	//시선위치
	D3DXVECTOR3	eyePos = _mainCamera.GetWorldPosition();
	_effect->SetVector("vEyePos", &D3DXVECTOR4(eyePos, 1));

	//파워
	_effect->SetFloat("specPower", 10);

	//텍스쳐 세팅
	_effect->SetTexture("DiffuseTex", _diffuseTex);
	_effect->SetTexture("NormalTex", _normalTex);

	//테크닉세팅
	_effect->SetTechnique("MyShader");

	//셰이더로 쿼드 렌더
	UINT iPassNum = 0;

	//이펙트로 렌더링시작
	_effect->Begin(&iPassNum, 0);

	//패스 수대로 for문으로 돌린다
	for (UINT i = 0; i < iPassNum; i++)
	{
		_effect->BeginPass(i);

		//렌더
		//정점 그리기
		_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));
		_device->SetVertexDeclaration(_vDeclation);
		_device->SetIndices(_ib);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

		_effect->EndPass();
	}

	_effect->End();

	_lightTrans.RenderGimozo();
}

void normalTest2::CreateQuad()
{
	//정점위치
	D3DXVECTOR3 vertexPos[] =
	{
		D3DXVECTOR3(-3.5, -3.5, 0),
		D3DXVECTOR3(-3.5, 3.5, 0),
		D3DXVECTOR3(3.5, 3.5, 0),
		D3DXVECTOR3(3.5, -3.5, 0)
	};

	//정점UV
	D3DXVECTOR2 vertexUV[] =
	{
		D3DXVECTOR2(0, 1),
		D3DXVECTOR2(0, 0),
		D3DXVECTOR2(1, 0),
		D3DXVECTOR2(1, 1)
	};

	//정점 인덱스
	DWORD vertexIndices[] = { 0, 1, 2, 0, 2, 3 };

	//정점 노말
	D3DXVECTOR3	vertexNormal[4];
	ComputeNormal(vertexNormal, vertexPos, 4, vertexIndices, 6);

	//Tangent Binormal
	D3DXVECTOR3 vertexTangent[4];
	D3DXVECTOR3 vertexBinormal[4];
	ComputeTangentBinormal(
		vertexTangent,
		vertexBinormal,
		vertexPos,
		vertexNormal,
		vertexUV,
		vertexIndices,
		2,
		4);

	//정점 버퍼 생성
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 4,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_DEFAULT,
		&_vb,
		NULL);

	// 1---2    UV좌표계는 윈도우 좌표계와 똑같다 
	// |  /|	왼쪽상단이 0,0 우측상단 1,0 왼쪽하단 0,1 우측하단 1,1
	// | / |								
	// 0---3								
	LPMYVERTEX pVertices = NULL;
	_vb->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4; i++)
	{
		pVertices[i].pos = vertexPos[i];
		pVertices[i].uv = vertexUV[i];
		pVertices[i].normal = vertexNormal[i];
		pVertices[i].tangent = vertexTangent[i];
		pVertices[i].binormal = vertexBinormal[i];
	}

	_vb->Unlock();

	//인덱스 버퍼 생성
	_device->CreateIndexBuffer(
		sizeof(DWORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,
		&_ib,
		NULL);
	// 1---2    
	// |  /|	
	// | / |								
	// 0---3
	//DWORD idx[] = { 0, 1, 2, 0, 2, 3 };

	void* pIndices = NULL;
	_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, vertexIndices, sizeof(DWORD) * 6);
	_ib->Unlock();
}
