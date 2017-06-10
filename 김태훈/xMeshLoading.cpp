#include "stdafx.h"
#include "xMeshLoading.h"

HRESULT xMeshLoading::init(void)
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

	_meshTrans.SetScale(0.05f, 0.05f, 0.05f);
	_meshLocal.AttachTo(&_meshTrans);
	_meshLocal.RotateLocal(0, D3DXToRadian(180), 0);

	//라이팅 해제
	_device->SetRenderState(D3DRS_LIGHTING, false);

	//로딩시 얻어진 버퍼는 해재
	SAFE_RELEASE(pAdjacency);

	return S_OK;
}

void xMeshLoading::release(void)
{
	SAFE_RELEASE(_mesh);
}

void xMeshLoading::update(void)
{
	_meshTrans.DefaultMyControl(_timeDelta);
}

void xMeshLoading::render(void)
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
