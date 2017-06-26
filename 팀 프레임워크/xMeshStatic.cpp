#include "stdafx.h"
#include "xMeshStatic.h"

LPD3DXEFFECT		xMeshStatic::_staticMeshEffect = NULL;
LPDIRECT3DTEXTURE9	xMeshStatic::_defDiffuseTex = NULL;
LPDIRECT3DTEXTURE9	xMeshStatic::_defNormalTex = NULL;
LPDIRECT3DTEXTURE9	xMeshStatic::_defSpecularTex = NULL;
LPDIRECT3DTEXTURE9	xMeshStatic::_defEmissionTex = NULL;

xMeshStatic::xMeshStatic()
{
	//셰이더와 디폴트텍스쳐 초기화
	if (_staticMeshEffect == NULL)
	{
		//_staticMeshEffect = RM_SHADERFX->getResource("Resource/Shaders/StaticMesh.fx");
		//_staticMeshEffect = RM_SHADERFX->getResource("ResourceUI/test/fx/StaticMesh.fx");
		_staticMeshEffect = RM_SHADERFX->getResource(FILEPATH_MANAGER->GetFilepath("StaticMesh"));
	}
	if (_defDiffuseTex == NULL)
	{
		//_defDiffuseTex = RM_TEXTURE->getResource("ResourceUI/test/meshTx/diffuseDefault.png");
		//_defDiffuseTex = RM_TEXTURE->getResource("Resource/Meshes/diffuseDefault.png");
		_defDiffuseTex = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath("diffuseDefault"));
	}
	if (_defNormalTex == NULL)
	{
		//_defNormalTex = RM_TEXTURE->getResource("ResourceUI/test/meshTx/normalDefault.png");
		_defNormalTex = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath("normalDefault"));
	}
	if (_defSpecularTex == NULL)
	{
		//_defSpecularTex = RM_TEXTURE->getResource("ResourceUI/test/meshTx/specularDefault.png");
		_defSpecularTex = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath("specularDefault"));
	}
	if (_defEmissionTex == NULL)
	{
		//_defEmissionTex = RM_TEXTURE->getResource("ResourceUI/test/meshTx/emissionDefault.png");
		_defEmissionTex = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath("emissionDefault"));
	}
}
xMeshStatic::~xMeshStatic()
{
}

HRESULT xMeshStatic::init(string filePath, D3DXMATRIXA16 * matCorrection)
{
	this->filePath = filePath;
	LPD3DXBUFFER pAdjacency = NULL;	//인접 버퍼
	LPD3DXBUFFER pMaterial = NULL;	//재질 버퍼

	//XFile 로 부터 메쉬를 불러오는 함수
	if (FAILED(D3DXLoadMeshFromX(
		filePath.c_str(),			//X 파일 로딩 경로...
		D3DXMESH_MANAGED,			//메쉬 옵션 일단 D3DXMESH_MANAGED 로....
		_device,					//디바이스
		&pAdjacency,				//얻어올 인접정보 버퍼
		&pMaterial,					//얻어올 재질정보 버퍼
		NULL,						//Effect 
		&_materialsNum,				//메쉬에서 사용되는 재질 갯수
		&_mesh						//메쉬
	))) 
	{
		SAFE_RELEASE(pAdjacency);
		SAFE_RELEASE(pMaterial);
		return E_FAIL;
	}

	//로딩 경로에서 파일명만 제거하고 경로만 받는다.
	string path;
	int lastPathIndex = 0;		//마지막 \ 의 위치

	//filePath.find_first_of( 'A' ); filePath 문자열에 'A' 가 들어있는 위치 리턴 (앞에서 부터 검색)
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

	//Texture 로딩시 필요한 문자열들..
	string texFilePath;		//최종 경로...
	string texExp;			//파일 확장자 명
	string texFile;			//파일 명	

	//재질 정보를 얻는다
	LPD3DXMATERIAL	pMaterials = (LPD3DXMATERIAL)pMaterial->GetBufferPointer();

	//재질갯수만큼 for 문으로 돌려재낀다.
	for (DWORD i = 0; i < _materialsNum; i++) 
	{
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
			//tex 파일경로는 Mesh 파일경로 + texture 파일이름
			texFilePath = path + pMaterials[i].pTextureFilename;

			//Texture 로딩하고 푸쉬
			_vecDiffuseTex.push_back(RM_TEXTURE->getResource(texFilePath));

			//파일 이름과 확장자 위치
			int dotIndex = texFilePath.find_last_of(".");

			//파일 명과 확장자를 나눈다.
			texFile = texFilePath.substr(0, dotIndex);
			texExp = texFilePath.substr(dotIndex + 1, filePath.length());

			//
			// 노말말 맵은 _N 이 붙는다.
			//
			texFilePath = texFile + "_N." + texExp;
			LPDIRECT3DTEXTURE9 pNorTex = RM_TEXTURE->getResource(texFilePath);
			//없다면...
			if (pNorTex == NULL) _vecNormalTex.push_back(_defNormalTex);
			else _vecNormalTex.push_back(pNorTex);

			//
			// 스펙큘러 맵은 _S 이 붙는다.
			//
			texFilePath = texFile + "_S." + texExp;
			LPDIRECT3DTEXTURE9 pSpecTex = RM_TEXTURE->getResource(texFilePath);
			//없다면...
			if (pSpecTex == NULL) _vecSpecularTex.push_back(_defSpecularTex);
			else _vecSpecularTex.push_back(pSpecTex);

			//
			// 이미션 맵은 _E 이 붙는다.
			//
			texFilePath = texFile + "_E." + texExp;
			LPDIRECT3DTEXTURE9 pEmiTex = RM_TEXTURE->getResource(texFilePath);
			//없다면...
			if (pEmiTex == NULL) _vecEmissionTex.push_back(_defEmissionTex);
			else _vecEmissionTex.push_back(pEmiTex);
		}
		else
		{
			_vecDiffuseTex.push_back(_defDiffuseTex);
			_vecNormalTex.push_back(_defNormalTex);
			_vecSpecularTex.push_back(_defSpecularTex);
			_vecEmissionTex.push_back(_defEmissionTex);
		}
	}

	//얻어온 재질 정보를 다 사용하여 재질과 Texture 를 로딩 했기때문에 
	//더이상 pMaterial 재질 버퍼는 필요 없어 꼭 메모리 해제를 해주어야 한다.
	SAFE_RELEASE(pMaterial);

	//메쉬 최적화 (인접 버퍼를 이용하여 메쉬를 최적화 한다)
	_mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |		//메쉬 서브셋순서대로 정렬 (DrawSubset 효율을 높인다 
		D3DXMESHOPT_COMPACT |		//메쉬에서 사용되지 않는 정점과 인덱스 해제
		D3DXMESHOPT_VERTEXCACHE,	//정점 Cache 히트율 높힌다.
		(DWORD*)pAdjacency->GetBufferPointer(),	//인접버퍼 넘겨야 한다.
		NULL,			//최적화를 마지고 결과로 얻는 인접정보 (더이상 필요없으면 NULL)
		NULL,			//최적화된 인덱스 정보
		NULL			//최적화된 정점 버퍼 정보 
	);

	//최적화가 끝났으니 해재
	SAFE_RELEASE(pAdjacency);

	//
	// 메쉬 보정 처리
	//
	//보정행렬을 받았다면..
	if (matCorrection) 
	{
		scale = fabsf(matCorrection->_11);
		meshCorrection(matCorrection);
	}
	else 
	{
		//보정행렬이 없더라도 보정처리를해야 Bound 정보를 얻을수 있다.
		D3DXMATRIXA16 matIden;
		D3DXMatrixIdentity(&matIden);
		meshCorrection(&matIden);
	}
}

void xMeshStatic::release(void)
{
	SAFE_RELEASE(_mesh);
}

void xMeshStatic::render(dx::transform * trans)
{
	//월드행렬 세팅
	D3DXMATRIXA16 matWorld = trans->GetFinalMatrix();
	_staticMeshEffect->SetMatrix("matWorld", &matWorld);

	//광원 방향 일단...
	D3DXVECTOR4 lightDir(1, -1, 1, 1);
	_staticMeshEffect->SetVector("vLightDir", &lightDir);

	//라이트 컬러 일단 흰색
	D3DXVECTOR4 lightColor(1, 1, 1, 1);
	_staticMeshEffect->SetVector("vLightColor", &lightColor);

	//Effect 로 그리기 시작
	_staticMeshEffect->SetTechnique("Mesh");

	UINT passNum;
	_staticMeshEffect->Begin(&passNum, 0);

	for (UINT i = 0; i < passNum; i++)
	{
		_staticMeshEffect->BeginPass(i);
		//서브셋수만큼 돌아 재낀다...
		for (int m = 0; m < _materialsNum; m++) 
		{
			//텍스쳐 세팅
			_staticMeshEffect->SetTexture("Diffuse_Tex", _vecDiffuseTex[m]);
			_staticMeshEffect->SetTexture("Normal_Tex", _vecNormalTex[m]);
			_staticMeshEffect->SetTexture("Specular_Tex",_vecSpecularTex[m]);
			_staticMeshEffect->SetTexture("Emission_Tex",_vecEmissionTex[m]);
			//스펙파워
			_staticMeshEffect->SetFloat("fSpecPower", _vecMaterials[m].Power);
			//Begin 이 들어오고 난후 값이 바뀌면 다음과 같이 실행
			_staticMeshEffect->CommitChanges();
			//메쉬그린다
			_mesh->DrawSubset(m);
		}
		_staticMeshEffect->EndPass();
	}

	_staticMeshEffect->End();
}

void xMeshStatic::meshCorrection(D3DXMATRIXA16 * matCorrection)
{
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
	for (DWORD i = 0; i < MAX_FVF_DECL_SIZE; i++) {

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
	//DWORD verSize = D3DXGetFVFVertexSize( pMesh->GetFVF() );
	DWORD verSize = D3DXGetDeclVertexSize(pVerElement, 0);

	//메쉬의 버텍스 버퍼를 Lock 한다
	void* p = NULL;
	_mesh->LockVertexBuffer(0, &p);

	//바운드 MinMax 계산을 위한 초기화
	_boundMin = D3DXVECTOR3(0, 0, 0);
	_boundMax = D3DXVECTOR3(0, 0, 0);

	//버텍스 수만클 돌아 재낀다
	for (DWORD i = 0; i < verNum; i++) {

		//버텍스 시작 주소
		char* pVertex = ((char*)p + (i * verSize));

		//정점 위치가 있다면
		if (positionOffset != -1) 
		{
			D3DXVECTOR3* pos = (D3DXVECTOR3*)(pVertex + positionOffset);

			D3DXVec3TransformCoord(pos, pos, matCorrection);

			//정점 최소 값갱신
			if (_boundMin.x > pos->x)		_boundMin.x = pos->x;
			if (_boundMin.y > pos->y)		_boundMin.y = pos->y;
			if (_boundMin.z > pos->z)		_boundMin.z = pos->z;

			//정점 최대 값갱신
			if (_boundMax.x < pos->x)		_boundMax.x = pos->x;
			if (_boundMax.y < pos->y)		_boundMax.y = pos->y;
			if (_boundMax.z < pos->z)		_boundMax.z = pos->z;

			//정점 위치 푸쉬
			_vertices.push_back(*pos);
		}

		//노말정보가 있다면..
		if (normalOffet != -1) 
		{
			D3DXVECTOR3* nor = (D3DXVECTOR3*)(pVertex + normalOffet);
			D3DXVec3TransformNormal(nor, nor, matCorrection);
			D3DXVec3Normalize(nor, nor);
			//정점 노말 푸쉬
			_normals.push_back(*nor);
		}

		//tangent 정보가 있다면.
		if (tangentOffet != -1) 
		{
			D3DXVECTOR3* tangent = (D3DXVECTOR3*)(pVertex + tangentOffet);
			D3DXVec3TransformNormal(tangent, tangent, matCorrection);
			D3DXVec3Normalize(tangent, tangent);
		}

		//binormal 정보가 있다면
		if (binormalOffet != -1) 
		{
			D3DXVECTOR3* binor = (D3DXVECTOR3*)(pVertex + binormalOffet);
			D3DXVec3TransformNormal(binor, binor, matCorrection);
			D3DXVec3Normalize(binor, binor);
		}
	}
	_mesh->UnlockVertexBuffer();

	//Bound 추가 계산
	_boundCenter = (_boundMin + _boundMax) * 0.5f;
	_boundSize = D3DXVECTOR3( 
		_boundMax.x - _boundMin.x,
		_boundMax.y - _boundMin.y,
		_boundMax.z - _boundMin.z);
	_boundHalfSize = _boundSize * 0.5f;
	_boundRadius = D3DXVec3Length(&(_boundCenter - _boundMin));

	//
	// 인덱스 버퍼를 얻는다
	//
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	_mesh->GetIndexBuffer(&pIndexBuffer);

	//면의 갯수
	_triNum = _mesh->GetNumFaces();

	//인덱스 버퍼에 대한 정보를 얻는다.
	D3DINDEXBUFFER_DESC desc;
	pIndexBuffer->GetDesc(&desc);

	if (desc.Format == D3DFMT_INDEX16)
	{
		WORD* p = NULL;
		pIndexBuffer->Lock(0, 0, (void**)&p, 0);
		for (DWORD i = 0; i < _triNum; i++)
		{
			_indices.push_back(p[i * 3 + 0]);
			_indices.push_back(p[i * 3 + 1]);
			_indices.push_back(p[i * 3 + 2]);
		}
		pIndexBuffer->Unlock();
	}
	else if (desc.Format == D3DFMT_INDEX32)
	{
		DWORD* p = NULL;
		pIndexBuffer->Lock(0, 0, (void**)&p, 0);
		for (DWORD i = 0; i < _triNum; i++)
		{
			_indices.push_back(p[i * 3 + 0]);
			_indices.push_back(p[i * 3 + 1]);
			_indices.push_back(p[i * 3 + 2]);
		}
		pIndexBuffer->Unlock();
	}

	//얻어온 인덱스 버퍼는 해재
	SAFE_RELEASE(pIndexBuffer);
}

void xMeshStatic::setCamera(camera * camera)
{
	D3DXMATRIXA16 matViewProj = camera->getViewProjectionMatrix();
	_staticMeshEffect->SetMatrix("matViewProjection", &matViewProj);
	D3DXVECTOR3 vEyePos = camera->GetWorldPosition();
	_staticMeshEffect->SetVector("vEyePos", &D3DXVECTOR4(vEyePos, 1));
	_staticMeshEffect->SetFloat("camFar", camera->_camFar);
	_staticMeshEffect->SetFloat("camNear", camera->_camNear);
}

void xMeshStatic::setBaseLight(lightDirection * pDirLight)
{
	_staticMeshEffect->SetMatrix("baseDirectionLight", &pDirLight->getLightMatrix());
}

//라이팅 세팅
void xMeshStatic::setLighting(light ** pLights, int lightNum)
{
	//라이트 행렬 세팅
	D3DXMATRIXA16 matLight[10];
	for (int i = 0; i < lightNum; i++)
	{
		matLight[i] = pLights[i]->getLightMatrix();
	}
	//Effect에 라이팅 세팅
	_staticMeshEffect->SetMatrixArray("matLights", matLight, 10);
	_staticMeshEffect->SetInt("LightNum", lightNum);
}

void xMeshStatic::setLighting(std::vector<light*>* pLights)
{
	//라이트 행렬 세팅
	D3DXMATRIXA16 matLight[10];
	for (int i = 0; i < pLights->size(); i++)
	{
		matLight[i] = (*(pLights))[i]->getLightMatrix();
	}
	//Effect에 라이팅 세팅
	_staticMeshEffect->SetMatrixArray("matLights", matLight, 10);
	_staticMeshEffect->SetInt("LightNum", pLights->size());
}

//technique 설정
void xMeshStatic::setTechniqueName(std::string name)
{
	_staticMeshEffect->SetTechnique(name.c_str());
}
