#include "stdafx.h"
#include "xMeshLoadinigWithCorrectMatrix.h"

HRESULT xMeshLoadinigWithCorrectMatrix::init(void)
{
	//로딩 경로....
	string filePath = "Resources/Meshes/GunShip/gunship.x";			//X 파일 경로명
	//Texture 를 불러온다면
	//Resources/Meshes/GunShip/ 이경로에서 불러와야 한다...

	LPD3DXBUFFER	pAdjacency;		//인접 버퍼
	LPD3DXBUFFER	pMaterial;		//재질 버퍼
	DWORD			dwNumMtrl;		//재질 수 

									//XFile 로 부터 메쉬를 불러오는 함수
	D3DXLoadMeshFromX(
		filePath.c_str(),			//X 파일 로딩 경로...
		D3DXMESH_MANAGED,			//메쉬 옵션 일단 D3DXMESH_MANAGED 로....
		_device,					//디바이스
		&pAdjacency,				//얻어올 인접정보 버퍼
		&pMaterial,					//얻어올 재질정보 버퍼
		NULL,						//Effect 
		&_materialsNum,				//메쉬에서 사용되는 재질 갯수
		&_mesh						//메쉬
	);

	//로딩 경로에서 파일명만 제거하고 경로만 받는다.
	string path;
	int lastPathIndex = 0;			//마지막 \ 의 위치

									//filePath.find_first_of( 'A' ); filePath 문자열에 'A' 가 들어있는 위치 리턴 ( 앞에서 부터 검색 )
	lastPathIndex = filePath.find_last_of('/'); //뒤에서 부터 검색
	if (lastPathIndex == -1)
	{	//못찾으면 -1 을 리턴
		lastPathIndex = filePath.find_last_of('\\'); //경로 구분을 하는 / 을 못찾으면 \ 를 찾는다.
	}

	//경로 구분이 있다면...
	if (lastPathIndex != -1)
	{
		//filePath.substr( /*시작위치*/, /*갯수*/ );
		path = filePath.substr(0, lastPathIndex + 1);
	}

	//재질 정보를 얻는다
	LPD3DXMATERIAL	pMaterials = (LPD3DXMATERIAL)pMaterial->GetBufferPointer();

	//재질갯수만큼 for 문으로 돌려재낀다.
	for (DWORD i = 0; i < _materialsNum; i++) {

		//로드된 메터리얼
		D3DMATERIAL9 mtrl = pMaterials[i].MatD3D;

		//메쉬의 메터리얼에는 Ambient 정보가 없으니
		//Diffuse 정보와 동일하게 하자..
		mtrl.Ambient = mtrl.Diffuse;

		//메터리얼 정보 푸쉬
		_vecMaterials.push_back(mtrl);

		//메터리얼의 Texture 정보가 있다면..
		if (pMaterials[i].pTextureFilename != NULL) 
		{
			//파일경로 
			string texFilePath = path + pMaterials[i].pTextureFilename;
			//Texture 로딩하고 푸쉬
			_vecTextures.push_back(RM_TEXTURE->loadResource(texFilePath));
		}
		else
		{
			//없더라도 반드시 null 대입( 중요 )
			_vecTextures.push_back(NULL);
		}
	}

	//얻어온 재질 정보를 다 사용하여 재질과 Texture 를 로딩 했기때문에 
	//더이상 pMaterial 재질 버퍼는 필요 없어 꼭 메모리 해재를 해주어야 한다.
	SAFE_RELEASE(pMaterial);

	//메쉬 최적화 ( 인접 버퍼를 이용하여 메쉬를 최적화 한다 )
	_mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |		//메쉬 서브셋순서대로 정렬 ( DrawSubset 효율을 높인다 )
		D3DXMESHOPT_COMPACT |		//메쉬에서 사용되지 않는 정점과 인덱스 해제
		D3DXMESHOPT_VERTEXCACHE,	//정점 Cache 히트율 높힌다.
		(DWORD*)pAdjacency->GetBufferPointer(),		//인접버퍼 넘겨야 한다.
		NULL,			//최적화를 마지고 결과로 얻는 인접정보 ( 더이상 필요없으면 NULL )
		NULL,			//최적화된 인덱스 정보
		NULL			//최적화된 정점 버퍼 정보 
	);


	//최적화가 끝났으니 해재
	SAFE_RELEASE(pAdjacency);

	//
	// 메쉬 보정 처리
	//
	//원래 있던 매쉬에서 다음과 같은 행렬로 보정시켜 
	//모든 정보를 틀어버린다.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);

	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

	D3DXMATRIXA16 matCorrection = matScale * matRotate;
	//D3DXMATRIXA16 matCorrection;
	//D3DXMatrixIdentity(&matCorrection);

	//정점 Element 를 얻어 정점 정보를 얻자
	D3DVERTEXELEMENT9 pVerElement[MAX_FVF_DECL_SIZE];

	//pVerElement 배열에는 정점의 요소 정보가 들어가게 된다.
	_mesh->GetDeclaration(pVerElement);

	//정점 Position Offset;
	int positionOffset = -1;

	//정점 Normal Offset;
	int normalOffet = -1;

	//정점 Tangent Offset;
	int tangentOffet = -1;

	//정점 Binormal Offset;
	int binormalOffet = -1;


	//일단 돌아재낀다..
	for (DWORD i = 0; i < MAX_FVF_DECL_SIZE; i++) 
	{
		//마지막을 만났다면....
		if (pVerElement[i].Type == D3DDECLTYPE_UNUSED)
		{
			//탈출
			break;
		}

		//정점위치 정보를 만났다면....
		if (pVerElement[i].Usage == D3DDECLUSAGE_POSITION)
		{
			positionOffset = pVerElement[i].Offset;
		}

		//정점노말 정보를 만났다면...
		else if (pVerElement[i].Usage == D3DDECLUSAGE_NORMAL)
		{
			normalOffet = pVerElement[i].Offset;
		}

		//정점탄젠트 정보를 만났다면...
		else if (pVerElement[i].Usage == D3DDECLUSAGE_TANGENT)
		{
			tangentOffet = pVerElement[i].Offset;
		}

		//정점바이노말 정보를 만났다면...
		else if (pVerElement[i].Usage == D3DDECLUSAGE_BINORMAL)
		{
			binormalOffet = pVerElement[i].Offset;
		}
	}

	//버텍스 갯수
	DWORD verNum = _mesh->GetNumVertices();

	//메쉬의 정점 FVF 정보혹은 Decl 정보를 이용하여 정점하나당 크기를 알아내자.
	//DWORD verSize = D3DXGetFVFVertexSize( _mesh->GetFVF() );
	DWORD verSize = D3DXGetDeclVertexSize(pVerElement, 0);

	//메쉬의 버텍스 버퍼를 Lock 한다
	void* p = NULL;
	_mesh->LockVertexBuffer(0, &p);

	//버텍스 수만클 돌아 재낀다....
	for (DWORD i = 0; i < verNum; i++) 
	{
		//버텍스 시작 주소
		char* pVertex = ((char*)p + (i * verSize));

		//정점 위치가 있다면...
		if (positionOffset != -1) 
		{
			D3DXVECTOR3* pos = (D3DXVECTOR3*)(pVertex + positionOffset);
			D3DXVec3TransformCoord(pos, pos, &matCorrection);
		}

		//노말정보가 있다면..
		if (normalOffet != -1) 
		{
			D3DXVECTOR3* nor = (D3DXVECTOR3*)(pVertex + normalOffet);
			D3DXVec3TransformNormal(nor, nor, &matCorrection);
			D3DXVec3Normalize(nor, nor);
		}

		//tangent 정보가 있다면.
		if (tangentOffet != -1) 
		{
			D3DXVECTOR3* tangent = (D3DXVECTOR3*)(pVertex + tangentOffet);
			D3DXVec3TransformNormal(tangent, tangent, &matCorrection);
			D3DXVec3Normalize(tangent, tangent);
		}

		//binormal 정보가 있다면
		if (binormalOffet != -1) 
		{
			D3DXVECTOR3* binor = (D3DXVECTOR3*)(pVertex + binormalOffet);
			D3DXVec3TransformNormal(binor, binor, &matCorrection);
			D3DXVec3Normalize(binor, binor);
		}
	}

	_mesh->UnlockVertexBuffer();

	//라이팅 해제
	_device->SetRenderState(D3DRS_LIGHTING, false);

	//로딩시 얻어진 버퍼는 해재
	SAFE_RELEASE(pAdjacency);

	return S_OK;
}

void xMeshLoadinigWithCorrectMatrix::release(void)
{
	SAFE_RELEASE(_mesh);
}

void xMeshLoadinigWithCorrectMatrix::update(void)
{
	_meshTrans.DefaultMyControl(_timeDelta);
}

void xMeshLoadinigWithCorrectMatrix::render(void)
{
	_meshTrans.SetDeviceWorld();

	for (DWORD i = 0; i < _materialsNum; i++)
	{
		//Texture 세팅
		_device->SetTexture(0, _vecTextures[i]);

		_mesh->DrawSubset(i);
	}

	//다그리고 난후 Texture 를 해재해주는 센스
	_device->SetTexture(0, NULL);
}
