#include "stdafx.h"
#include "terrain.h"
#include "quadTree.h"

terrain::terrain()
	: _quadTree(NULL)			//쿼드 트리
	, _isQuad(false)			//쿼드 실행 여부
	, _cellScale(1.0f)			//셀 간격
	, _heightScale(200)			//높이 스케일(픽셀컬러가 255일때 높이)
	, _smoothLevel(3)			//스무싱 처리 횟수
	, _tileNum(100)				//타일링 갯수
	, _verNumX(0)				//가로 정점수(실제 그림 사이즈 보다 1개 더 많다.이해가 안되면 그림을 그려볼 것.)
	, _verNumZ(0)				//세로 정점수(실제 그림 사이즈 보다 1개 더 많다.이해가 안되면 그림을 그려볼 것.)
	, _totalVerNum(0)			//전체 정점수(가로 정점수 * 세로 정점수)
	, _cellNumX(0)				//가로 셀수(실제 그림 사이즈)
	, _cellNumZ(0)				//세로 셀수(실제 그림 사이즈)
	, _totalCellNum(0)			//전체 셀수
	, _totalTriangle(0)			//전체 삼각형수		
	, _terrainSizeX(0.f)		//지형 가로 사이즈(128,256,같은)
	, _terrainSizeZ(0.f)		//지형 세로 사이즈(128,256,같은)
	, _terrainStartX(0.f)		//지형 시작 위치X
	, _terrainStartZ(0.f)		//지형 시작 위치Z
	, _terrainEndX(0.f)			//지형 종료 위치X
	, _terrainEndZ(0.f)			//지형 종료 위치Z
	, _isVertexDraw(false)		//버텍스 지형을 그릴건지
	, _nHtChangeRange(3)		//높이값을 바꿀 범위(영역)
	, _fHtChangeValue(0.1f)		//높이값을 바꿀 값(얼마만큼 올리고 내릴건지)
	, _nHtChangeSign(1)			//높이값을 증가시킬지 감소시킬지 부호
	, _isSmoothing(true)		//스무싱을 할건지
{
	//지형 셰이더이펙트 로딩
	_terrainEffect = RM_SHADERFX->getResource(FILEPATH_MANAGER->GetFilepath("FX_지형기본"));
}

terrain::~terrain()
{
	SAFE_RELEASE(_terrainVb);
	SAFE_RELEASE(_terrainIb);
	SAFE_RELEASE(_terrainDecl);
	SAFE_DELETE_ARRAY(_terrainVertices);
	SAFE_DELETE(_quadTree);
}



HRESULT terrain::init(char * heightMapName, char * tile_0, char * tile_1, char * tile_2, char * tile_3, char * tileSplat, float cellSize, float heightScale, int smoothLevel, int tileNum)
{
	//스케일값 대입
	_heightScale = heightScale;
	_cellScale = cellSize;

	//높이맵 불러온다
	_heightMap = RM_TEXTURE->getResource(heightMapName);
	//불러오는데 실패하면 바로 종료
	if (_heightMap == NULL) return E_FAIL;

	//높이 맵에 대한 이미지 정보를 불러온다. (로딩된 Texture 정보를 얻는다)
	D3DSURFACE_DESC sd;
	//GetLevelDesc(밉맵체인 레벨, D3DSURFACE_DESC 구조체 포인터)
	_heightMap->GetLevelDesc(0, &sd);

	//가로세로 정점 수를 구한다.
	_verNumX = sd.Width + 1;	//가로 정점갯수는 높이 맵에 가로 해상도 + 1 과 같다. (이유는 쿼드트리쓰려면 정점갯수가 2의N승 + 1 이여야 하기 때문에)
	_verNumZ = sd.Height + 1;	//세로 정점잿수는 높이 맵에 세로 해상도 + 1 과 같다. (이유는 쿼드트리쓰려면 정점갯수가 2의N승 + 1 이여야 하기 때문에)
	_totalVerNum = _verNumX * _verNumZ;	//총 정점 갯수

										//가로세로 셀수
	_cellNumX = _verNumX - 1;
	_cellNumZ = _verNumZ - 1;
	_totalCellNum = _cellNumX * _cellNumZ;

	//총 삼각형수는
	_totalTriangle = _totalCellNum * 2;

	//터레인을 만든다.
	//스무싱 레벨 (이값이 클수록 지형이 부드러워진다)
	//타일 Texture 가 몇개로 나누어질건지 갯수
	if (FAILED(createTerrain(tileNum)))
	{
		return E_FAIL;
	}

	//터레인 크기
	_terrainSizeX = _cellNumX * _cellScale;
	_terrainSizeZ = _cellNumZ * _cellScale;

	//터레인 범위
	_terrainStartX = _terrainVertices[0].pos.x;
	_terrainStartZ = _terrainVertices[0].pos.z;
	_terrainEndX = _terrainVertices[_totalVerNum - 1].pos.x;
	_terrainEndZ = _terrainVertices[_totalVerNum - 1].pos.z;

	//쿼드트리를 만든다.
	_quadTree = new quadTree;
	_quadTree->init(_terrainVertices, _verNumX);

	//지형 텍스쳐 로딩
	_texTile_0 = RM_TEXTURE->getResource(tile_0);
	_texTile_1 = RM_TEXTURE->getResource(tile_1);
	_texTile_2 = RM_TEXTURE->getResource(tile_2);
	_texTile_3 = RM_TEXTURE->getResource(tile_3);
	_texSlat = RM_TEXTURE->getResource(tileSplat);

	//지형 셰이더이펙트 로딩
	_terrainEffect = RM_SHADERFX->getResource("Resource/Maptool/Shaders/TerrainBase.fx");

	dijk = new dijkstra;
}



void terrain::setting()
{
	//높이 맵에 대한 이미지 정보를 불러온다. (로딩된 Texture 정보를 얻는다)
	D3DSURFACE_DESC sd;
	//GetLevelDesc(밉맵체인 레벨, D3DSURFACE_DESC 구조체 포인터)
	_heightMap->GetLevelDesc(0, &sd);

	//가로세로 정점 수를 구한다.
	_verNumX = sd.Width + 1;	//가로 정점갯수는 높이 맵에 가로 해상도 + 1 과 같다. (이유는 쿼드트리쓰려면 정점갯수가 2의N승 + 1 이여야 하기 때문에)
	_verNumZ = sd.Height + 1;	//세로 정점잿수는 높이 맵에 세로 해상도 + 1 과 같다. (이유는 쿼드트리쓰려면 정점갯수가 2의N승 + 1 이여야 하기 때문에)
	_totalVerNum = _verNumX * _verNumZ;	//총 정점 갯수

										//가로세로 셀수
	_cellNumX = _verNumX - 1;
	_cellNumZ = _verNumZ - 1;
	_totalCellNum = _cellNumX * _cellNumZ;

	//총 삼각형수는
	_totalTriangle = _totalCellNum * 2;

	//터레인을 만든다.
	//스무싱 레벨
	createTerrain(_tileNum);


	//터레인 크기
	_terrainSizeX = _cellNumX * _cellScale;
	_terrainSizeZ = _cellNumZ * _cellScale;

	//터레인 범위
	_terrainStartX = _terrainVertices[0].pos.x;
	_terrainStartZ = _terrainVertices[0].pos.z;
	_terrainEndX = _terrainVertices[_totalVerNum - 1].pos.x;
	_terrainEndZ = _terrainVertices[_totalVerNum - 1].pos.z;

	//쿼드트리를 만든다.
	_quadTree = new quadTree;
	_quadTree->init(_terrainVertices, _verNumX);

	dijk = new dijkstra;
}



void terrain::changeHeight(int terrainX, int terrainZ)
{
	changeTerrainHt(terrainX, terrainZ);

	//쿼드트리를 생성해야할 경우만 생성하도록 처리.
	if (_isQuad)
	{
		//쿼트트리가 널이 아닐 경우 
		if (_quadTree != NULL) SAFE_DELETE(_quadTree);
		_quadTree = new quadTree;
		_quadTree->init(_terrainVertices, _verNumX);
	}
}



void terrain::render(camera * cam, lightDirection * directionLight)
{
	//월드 행렬세팅
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	//셰이더이펙트 월드행렬 세팅
	_terrainEffect->SetMatrix("matWorld", &matWorld);

	//셰이더이펙트 뷰행렬 세팅
	_terrainEffect->SetMatrix("matViewProjection", &cam->getViewProjectionMatrix());

	//셰이더이펙트 텍스쳐 세팅
	_terrainEffect->SetTexture("Terrain0_Tex", _texTile_0);
	_terrainEffect->SetTexture("Terrain1_Tex", _texTile_1);
	_terrainEffect->SetTexture("Terrain2_Tex", _texTile_2);
	_terrainEffect->SetTexture("Terrain3_Tex", _texTile_3);
	_terrainEffect->SetTexture("TerrainControl_Tex", _texSlat);

	//셰이더이펙트 광원 세팅
	D3DXVECTOR3 dirLight = -directionLight->_transform->GetUp();
	_terrainEffect->SetVector("worldLightDir", &D3DXVECTOR4(dirLight, 1));

	//셰이더 렌더
	UINT passNum = 0;
	_terrainEffect->Begin(&passNum, 0);
	for (UINT i = 0; i < passNum; i++)
	{
		_terrainEffect->BeginPass(i);
		_device->SetStreamSource(0, _terrainVb, 0, sizeof(TERRAINVERTEX));
		_device->SetVertexDeclaration(_terrainDecl);
		_device->SetIndices(_terrainIb);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _totalVerNum, 0, _totalTriangle);
		_terrainEffect->EndPass();
	}
	_terrainEffect->End();


	////정점렌더
	//if (_isVertexDraw)
	//{
	//	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//	_device->SetStreamSource(0, _terrainVb, 0, sizeof(TERRAINVERTEX));
	//	_device->SetIndices(_terrainIb);
	//	_device->SetVertexDeclaration(_terrainDecl);
	//	_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _totalVerNum, 0, _totalTriangle);
	//	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//}
}



void terrain::render(camera * cam, lightDirection * directionLight, camera * directionLightCamera)
{
	//ShadowMap 셋팅
	_terrainEffect->SetTexture("Shadow_Tex", directionLightCamera->getRenderTexture());

	//ShadowViewProjection 셋팅 
	_terrainEffect->SetMatrix("matLightViewProjection", &directionLightCamera->getViewProjectionMatrix());

	//월드 행렬셋팅
	D3DXMATRIXA16 matInd;
	D3DXMatrixIdentity(&matInd);
	_terrainEffect->SetMatrix("matWorld", &matInd);

	//뷰 행렬셋팅
	_terrainEffect->SetMatrix("matViewProjection", &cam->getViewProjectionMatrix());

	//Texture 셋팅
	_terrainEffect->SetTexture("Terrain0_Tex", _texTile_0);
	_terrainEffect->SetTexture("Terrain1_Tex", _texTile_1);
	_terrainEffect->SetTexture("Terrain2_Tex", _texTile_2);
	_terrainEffect->SetTexture("Terrain3_Tex", _texTile_3);
	_terrainEffect->SetTexture("TerrainControl_Tex", _texSlat);

	//광원 셋팅
	D3DXVECTOR3 dirLight = directionLight->_transform->GetForward();
	_terrainEffect->SetVector("worldLightDir", &D3DXVECTOR4(dirLight, 1));

	//광원 셋팅
	//_terrainEffect->SetVector( "worldLightDir", &D3DXVECTOR4(dirLight, 1));

	_terrainEffect->SetTechnique("ReciveShadow");

	UINT passNum = 0;
	_terrainEffect->Begin(&passNum, 0);
	for (UINT i = 0; i < passNum; i++)
	{
		_terrainEffect->BeginPass(i);
		_device->SetStreamSource(0, _terrainVb, 0, sizeof(TERRAINVERTEX));
		_device->SetVertexDeclaration(this->_terrainDecl);
		_device->SetIndices(_terrainIb);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _totalVerNum, 0, _totalTriangle);
		_terrainEffect->EndPass();
	}
	_terrainEffect->End();
}



void terrain::renderShadow(camera * directionLightCam)
{
	//월드 행렬셋팅
	D3DXMATRIXA16 matInd;
	D3DXMatrixIdentity(&matInd);
	_terrainEffect->SetMatrix("matWorld", &matInd);

	//뷰 행렬셋팅
	_terrainEffect->SetMatrix("matViewProjection", &directionLightCam->getViewProjectionMatrix());

	_terrainEffect->SetTechnique("CreateShadow");

	UINT passNum = 0;
	_terrainEffect->Begin(&passNum, 0);
	for (UINT i = 0; i < passNum; i++)
	{
		_terrainEffect->BeginPass(i);
		_device->SetStreamSource(0, _terrainVb, 0, sizeof(TERRAINVERTEX));
		_device->SetVertexDeclaration(this->_terrainDecl);
		_device->SetIndices(_terrainIb);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _totalVerNum, 0, _totalTriangle);
		_terrainEffect->EndPass();
	}
	_terrainEffect->End();
}



//Ray 히트 위치를 얻는다.
bool terrain::isIntersectRay(D3DXVECTOR3 * pOut, LPRay ray)
{
	vector<D3DXVECTOR3> hits;

	//최상단 쿼드 트리부터 Ray Check 들어간다.
	_quadTree->getRayHits(&hits, ray);

	//히트된게 없다
	if (hits.size() == 0) return false;

	//먼저 처음 위치와 처음 위치에대한 거리 대입
	D3DXVECTOR3 hitPos = hits[0];
	D3DXVECTOR3 dir = hitPos - ray->origin;
	float distSq = D3DXVec3LengthSq(&dir);

	for (int i = 1; i < hits.size(); ++i)
	{
		dir = hits[i] - ray->origin;
		float newDist = D3DXVec3LengthSq(&dir);

		if (newDist < distSq)
		{
			distSq = newDist;
			hitPos = hits[i];
		}
	}

	//여기까지온다면 제일 거리가 가까운 Hit 위치가 나온다
	*pOut = hitPos;

	return true;
}



//해당 X, Z 위치의 지형의 높이를 얻는다.
float terrain::getHeight(float x, float z)
{
	//터레인 범위을 넘어가면 0.0 값을 리턴한다
	if (x < _terrainStartX || x > _terrainEndX ||
		z > _terrainStartZ || z < _terrainEndZ)
	{
		return 0.0f;
	}


	//Terrain 의 좌상단 0 을 기준으로 월드 Terrain 의 상태적 위치를 찾자
	float pX = x - _terrainStartX;
	float pZ = -(z + _terrainEndZ);

	//해당 위치가 어느 셀에 포함되는지 파악
	float invCell = 1.0f / _cellScale;
	pX *= invCell;
	pZ *= invCell;

	//해당 위치의 셀 인덱스
	int idxX = static_cast<int>(pX);
	int idxZ = static_cast<int>(pZ);

	//셀의 네군데 정점을 얻는다.
	// lt-----rt
	//  |    /|
	//  |   / |
	//  |  /  |
	//  | /   |
	//  |/    |
	// lb-----rb

	D3DXVECTOR3 lt = _terrainVertices[idxZ * _verNumX + idxX].pos;
	D3DXVECTOR3 rt = _terrainVertices[idxZ * _verNumX + idxX + 1].pos;
	D3DXVECTOR3 lb = _terrainVertices[(idxZ + 1) * _verNumX + idxX].pos;
	D3DXVECTOR3 rb = _terrainVertices[(idxZ + 1) * _verNumX + idxX + 1].pos;

	//해당 셀에서의 delta 량을 구한다.
	float dX = pX - static_cast<float>(idxX);
	float dZ = pZ - static_cast<float>(idxZ);

	float height = 0.0f;

	//해당 점이 좌상단에 있니?
	if (dX < 1.0f - dZ)
	{
		float deltaU = rt.y - lt.y;		//lt 정점에서 rt 정점까지의 y 위치의 변위량
		float deltaV = lb.y - lt.y;		//lt 정점에서 lb 정점까지의 y 위치의 변위량

		height = lt.y + (deltaU * dX) + (deltaV * dZ);
	}

	//해당 점이 우하단이 있니?
	else
	{
		float deltaU = lb.y - rb.y;
		float deltaV = rt.y - rb.y;


		//우에서 좌로 하에서 상으로 보간방향이 바뀌었기 때문에
		//delta 량을 역수로 취한다.
		dX = 1.0f - dX;
		dZ = 1.0f - dZ;

		height = rb.y + (deltaU * dX) + (deltaV * dZ);
	}

	return height;
}



D3DXVECTOR2 terrain::getIdx(float x, float z)
{
	//터레인 범위을 넘어가면 0.0 값을 리턴한다
	if (x < _terrainStartX || x > _terrainEndX ||
		z > _terrainStartZ || z < _terrainEndZ)
	{
		return  D3DXVECTOR2(0.0f, 0.0f);
	}

	//Terrain 의 좌상단 0 을 기준으로 월드 Terrain 의 상태적 위치를 찾자
	float pX = x - _terrainStartX;
	float pZ = -(z + _terrainEndZ);

	//해당 위치가 어느 셀에 포함되는지 파악
	float invCell = 1.0f / _cellScale;
	pX *= invCell;
	pZ *= invCell;

	//해당 위치의 셀 인덱스
	int idxX = static_cast<int>(pX);
	int idxZ = static_cast<int>(pZ);

	return D3DXVECTOR2(idxX, idxZ);
}



//해당 X, Z 위치의 경사 벡터를 얻는다.
bool terrain::getSlant(D3DXVECTOR3 * pOut, float gravityPower, float x, float z)
{
	//터레인 범위을 넘어가면 0.0 값을 리턴한다
	if (x < _terrainStartX || x > _terrainEndX ||
		z > _terrainStartZ || z < _terrainEndZ)
	{
		return false;
	}


	//Terrain 의 좌상단 0 을 기준으로 월드 Terrain 의 상태적 위치를 찾자
	float pX = x - _terrainStartX;
	float pZ = -(z + _terrainEndZ);

	//해당 위치가 어느 셀에 포함되는지 파악
	float invCell = 1.0f / _cellScale;
	pX *= invCell;
	pZ *= invCell;


	//해당 위치의 셀 인덱스
	int idxX = static_cast<int>(pX);
	int idxZ = static_cast<int>(pZ);

	//셀의 네군데 정점을 얻는다.
	// lt-----rt
	//  |    /|
	//  |   / |
	//  |  /  |
	//  | /   |
	//  |/    |
	// lb-----rb

	D3DXVECTOR3 lt = _terrainVertices[idxZ * _verNumX + idxX].pos;
	D3DXVECTOR3 rt = _terrainVertices[idxZ * _verNumX + idxX + 1].pos;
	D3DXVECTOR3 lb = _terrainVertices[(idxZ + 1) * _verNumX + idxX].pos;
	D3DXVECTOR3 rb = _terrainVertices[(idxZ + 1) * _verNumX + idxX + 1].pos;

	//해당 셸에서의 delta 량을 구한다.
	float dX = pX - static_cast<float>(idxX);
	float dZ = pZ - static_cast<float>(idxZ);


	float fHeight = 0.0f;

	//폴리곤의 노말 벡터
	D3DXVECTOR3 normal;

	//해당 점이 좌상단에 있니?
	if (dX < 1.0f - dZ)
	{
		//해당폴리곤의 법선 벡터를 구한다.
		D3DXVECTOR3 edge1 = rt - lt;
		D3DXVECTOR3 edge2 = lb - lt;
		D3DXVec3Cross(&normal, &edge1, &edge2);
	}

	//해당 점이 우하단이 있니?
	else
	{
		//해당폴리곤의 법선 벡터를 구한다.
		D3DXVECTOR3 edge1 = rt - lb;
		D3DXVECTOR3 edge2 = rb - lb;
		D3DXVec3Cross(&normal, &edge1, &edge2);
	}

	//노말은 정규화
	D3DXVec3Normalize(&normal, &normal);


	//중력 방향
	D3DXVECTOR3 gravity(0, -gravityPower, 0);

	//경사면의 우측
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &normal, &gravity);

	//우측벡터에서 법선벡터를 외적한 결과가 경사면의 경사 방향이 된다.
	D3DXVec3Cross(pOut, &right, &normal);

	return true;
}



//지형 정점 만들기
HRESULT terrain::createTerrain(int tileNum)
{
	// 정점 위치 구한다.

	//타일링 갯수에 따른 간격 (정점당 uv 간격)
	float tileIntervalX = static_cast<float>(tileNum) / _cellNumX;
	float tileIntervalY = static_cast<float>(tileNum) / _cellNumZ;

	//지형 정점 가지고 있어야 한다.
	_terrainVertices = new TERRAINVERTEX[_totalVerNum];

	//텍스쳐의 pixel 정보를 얻기 위해 Texture 를 lock 한다.
	D3DLOCKED_RECT lockRect;
	_heightMap->LockRect(
		0,					//lock 을 할 밉맵 레벨 0
		&lockRect,			//lock 으로 얻어온 D3DLOCKED_RECT 정보 구조체
		0,					//lock 을 일부 영역만 하고 싶은 경우 사각형RECT 구조체의 포인터를 주는데 전체 할꺼면 NULL
		0					//lock 플레그 일단 0
	);

	//lockRect->Pitch	lock 을 한 영역 이미지의 가로 byte 크기 
	//(얻어온 바이트크기는 다음을 성립한다 pitch % 4 == 0 ) < 3byte 컬러시 pitch byte 구하는 공식 ( 가로 픽셀수 * 3 + 3 ) & ~3 = pitch  >
	//lockRect->pBits	이미지데이터가 시작되는 포인터 주소

	//정정위치와 정점 UV 를 계산하기
	for (int z = 0; z < _verNumZ; z++)
	{
		for (int x = 0; x < _verNumX; x++)
		{
			D3DXVECTOR3 pos;

			//정점의 x, z 위치 계산
			pos.x = (x - (_cellNumX * 0.5)) * _cellScale;
			pos.z = (-z + (_cellNumZ * 0.5)) * _cellScale;

			//가로마지막 라인이라면 (이전 왼쪽의 정점 Y 위치와 맞춘다)
			if (x == _verNumX - 1)
			{
				int idx = z * _verNumX + x - 1;
				pos.y = _terrainVertices[idx].pos.y;
			}

			//세로 마지막 라인이라면 (이전 위쪽의 정점 Y 위치와 맞춘다)
			else if (z == _verNumZ - 1)
			{
				int idx = (z - 1) * _verNumX + x;
				pos.y = _terrainVertices[idx].pos.y;
			}
			else
			{
				//해당 픽셀의 컬러 값을 얻는다.
				DWORD* pStart = (DWORD*)lockRect.pBits;	//(DWORD 형으로 형변환된 lock 된 이미지지의 시작 주소
				DWORD dwColor = *(pStart + (z * (lockRect.Pitch / 4) + x));

				//각 컬러 값을 0 ~ 1 사이의 실수로 나눈다.
				float inv = 1.0f / 255.0f;
				float r = ((dwColor & 0x00ff0000) >> 16) * inv;
				float g = ((dwColor & 0x0000ff00) >> 8) * inv;
				float b = ((dwColor & 0x000000ff)) * inv;

				//높이 맵 값
				float factor = (r + g + b) / 3.0f;

				//높이 값
				pos.y = factor * _heightScale;
			}

			//정점 UV 계산

			//Terrain Tile Splating UV
			D3DXVECTOR2 baseUV;
			baseUV.x = x / static_cast<float>(_verNumX - 1);
			baseUV.y = z / static_cast<float>(_verNumZ - 1);

			//Terrain Tile UV
			D3DXVECTOR2 tileUV;
			tileUV.x = x * tileIntervalX;
			tileUV.y = z * tileIntervalY;

			//버텍스 배열인덱스 계산
			int idx = z * _verNumX + x;

			_terrainVertices[idx].pos = pos;
			_terrainVertices[idx].normal = D3DXVECTOR3(0, 0, 0);	//아래에서 정점 노말 구할때 더해지니 일단 0 벡터로 초기화
			_terrainVertices[idx].baseUV = baseUV;
			_terrainVertices[idx].tileUV = tileUV;

			_vecPos.push_back(pos);
		}
	}

	//텍스쳐의 pixel 정보 Unlock
	_heightMap->UnlockRect(0);

	//지형 스무싱 
	if (_isSmoothing)
	{
		this->smoothTerrain();
	}

	// 정점 인덱스를 구한다
	LPTERRAINTRI pIndices = new tagTERRAINTRI[_totalTriangle];

	//인덱스 배열 인덱스
	int idx = 0;

	for (DWORD z = 0; z < _cellNumZ; z++)
	{
		for (DWORD x = 0; x < _cellNumX; x++)
		{
			// lt-----rt
			//  |    /|
			//  |   / |
			//  |  /  |
			//  | /   |
			//  |/    |
			// lb-----rb

			//해당 셀에 대한 정점 인덱스를 얻자
			DWORD lt = z * _verNumX + x;
			DWORD rt = z * _verNumX + x + 1;
			DWORD lb = ((z + 1)* _verNumX) + x;
			DWORD rb = ((z + 1)* _verNumX) + x + 1;

			//셀의 삼각형 하나
			pIndices[idx].dw0 = lt;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = lb;
			idx++;

			//셀의 삼각형 하나
			pIndices[idx].dw0 = lb;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = rb;
			idx++;
		}
	}

	// 노말이랑 Binormal 이랑 Tangent 계산하기
	D3DXVECTOR3* poses = new D3DXVECTOR3[_totalVerNum];		//정점위치
	D3DXVECTOR3* normals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* tangents = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* binormals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR2* uvs = new D3DXVECTOR2[_totalVerNum];
	DWORD* indices = (DWORD*)pIndices;

	//정점위치 및 UV 대입
	for (int i = 0; i < _totalVerNum; i++)
	{
		poses[i] = _terrainVertices[i].pos;
		uvs[i] = _terrainVertices[i].baseUV;
	}

	//노말계산
	ComputeNormal(normals, poses, _totalVerNum, indices, _totalTriangle * 3);

	//탄젠트 바이노말 계산
	ComputeTangentBinormal(
		tangents,
		binormals,
		poses,
		normals,
		uvs,
		indices,
		_totalTriangle,
		_totalVerNum);

	//계산된거 대입
	for (int i = 0; i < _totalVerNum; i++)
	{
		_terrainVertices[i].normal = normals[i];
		_terrainVertices[i].binormal = binormals[i];
		_terrainVertices[i].tangent = tangents[i];
	}

	// 버퍼 생성
	//정점버퍼 만들기
	_device->CreateVertexBuffer(
		sizeof(TERRAINVERTEX) * _totalVerNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&_terrainVb,
		0);

	//만들어진 정점 버퍼를 Lock 하여 지형 정점 값을 쓴다.
	void* p = NULL;
	_terrainVb->Lock(0, 0, &p, 0);
	memcpy(p, _terrainVertices, sizeof(TERRAINVERTEX) * _totalVerNum);
	_terrainVb->Unlock();

	//인덱스 버퍼 만들기
	_device->CreateIndexBuffer(
		sizeof(TERRAINTRI) * _totalTriangle,
		D3DUSAGE_WRITEONLY,	//D3DUSAGE_WRITEONLY 예는 락안하고 고정정으로 버퍼내용이 유지될때 최고성능을 발휘, D3DUSAGE_DYNAMIC 락 을 자주하여 버퍼 내용이 바뀌는 경우
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,	//D3DUSAGE_DYNAMIC 을 쓰려면 무조건 D3DPOOL_DEFAULT
		&_terrainIb,
		0);

	//인덱스 버퍼에 값을 쓴다.
	_terrainIb->Lock(0, 0, &p, 0);
	memcpy(p, pIndices, sizeof(TERRAINTRI) * _totalTriangle);
	_terrainIb->Unlock();

	// 정점 선언부를 만든다.
	//정점의 형태를 알려주는 배열
	D3DVERTEXELEMENT9 vertElement[7];	//배열을 정점정보 갯수 + 1

										//Position 
	vertElement[0].Stream = 0;							//Stream 은 0
	vertElement[0].Offset = 0;							//메모리의 시작 Byte 단위 0
	vertElement[0].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[0].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[0].Usage = D3DDECLUSAGE_POSITION;		//정보 타입
	vertElement[0].UsageIndex = 0;						//UsageIndex 일단 0

														//Normal
	vertElement[1].Stream = 0;							//Stream 은 0
	vertElement[1].Offset = 12;							//메모리의 시작 Byte 단위 0
	vertElement[1].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[1].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[1].Usage = D3DDECLUSAGE_NORMAL;			//정보 타입
	vertElement[1].UsageIndex = 0;						//UsageIndex 일단 0

														//BiNormal
	vertElement[2].Stream = 0;							//Stream 은 0
	vertElement[2].Offset = 24;							//메모리의 시작 Byte 단위 0
	vertElement[2].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[2].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[2].Usage = D3DDECLUSAGE_BINORMAL;		//정보 타입
	vertElement[2].UsageIndex = 0;						//UsageIndex 일단 0

														//Tangent
	vertElement[3].Stream = 0;							//Stream 은 0
	vertElement[3].Offset = 36;							//메모리의 시작 Byte 단위 0
	vertElement[3].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[3].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[3].Usage = D3DDECLUSAGE_TANGENT;		//정보 타입
	vertElement[3].UsageIndex = 0;						//UsageIndex 일단 0

														//BaseUV
	vertElement[4].Stream = 0;							//Stream 은 0
	vertElement[4].Offset = 48;							//메모리의 시작 Byte 단위 0
	vertElement[4].Type = D3DDECLTYPE_FLOAT2;			//자료의 타입
	vertElement[4].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[4].Usage = D3DDECLUSAGE_TEXCOORD;		//정보 타입
	vertElement[4].UsageIndex = 0;						//UsageIndex 일단 0


														//tileUV
	vertElement[5].Stream = 0;							//Stream 은 0
	vertElement[5].Offset = 56;							//메모리의 시작 Byte 단위 0
	vertElement[5].Type = D3DDECLTYPE_FLOAT2;			//자료의 타입
	vertElement[5].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[5].Usage = D3DDECLUSAGE_TEXCOORD;		//정보 타입
	vertElement[5].UsageIndex = 1;						//UsageIndex 두번째 UV 1 

														//더이상 없으니 종료
	D3DVERTEXELEMENT9 end = D3DDECL_END(); //{0xFF,0,D3DDECLTYPE_UNUSED,0,0,0}
	vertElement[6] = end;



	// LPDIRECT3DVERTEXDECLARATION9 생성
	_device->CreateVertexDeclaration(
		vertElement,			//앞에서 만든 D3DVERTEXELEMENT9 배열 포인터
		&_terrainDecl			//얻어올 LPDIRECT3DVERTEXDECLARATION9 포인터
	);

	SAFE_DELETE_ARRAY(poses);
	SAFE_DELETE_ARRAY(normals);
	SAFE_DELETE_ARRAY(tangents);
	SAFE_DELETE_ARRAY(binormals);
	SAFE_DELETE_ARRAY(uvs);
	SAFE_DELETE_ARRAY(indices);

	return S_OK;
}

HRESULT terrain::changeTerrainHt(int terrainX, int terrainZ)
{
	for (int z = terrainZ - _nHtChangeRange; z <= terrainZ + _nHtChangeRange; z++)
	{
		for (int x = terrainX - _nHtChangeRange; x <= terrainX + _nHtChangeRange; x++)
		{
			if (x >= 0 && x < _verNumX && z >= 0 && z < _verNumZ)
			{
				int vidx = z * _verNumX + x;

				if (vidx >= 0 && vidx < _vecPos.size())
				{
					D3DXVECTOR3 pos = _vecPos[vidx];
					pos.y = _vecPos[vidx].y + _fHtChangeValue * _nHtChangeSign;
					_terrainVertices[vidx].pos = pos;
					_vecPos[vidx] = pos;
				}
			}
		}
	}

	//지형 스무싱
	if (_isSmoothing)
	{
		smoothChangeTerrainHt(terrainX, terrainZ);
	}

	//버퍼에 쓸 void형 함수 선언.
	void* pVertices = NULL;

	//버텍스 버퍼를 락을 하면서 받을 함수를 정한다.
	_terrainVb->Lock(0, _totalVerNum * sizeof(TERRAINVERTEX), &pVertices, 0);

	TERRAINVERTEX* pv = (TERRAINVERTEX*)pVertices;

	for (int z = terrainZ - _nHtChangeRange; z <= terrainZ + _nHtChangeRange; z++)
	{
		for (int x = terrainX - _nHtChangeRange; x <= terrainX + _nHtChangeRange; x++)
		{
			if (x >= 0 && x < _verNumX && z >= 0 && z < _verNumZ)
			{
				int vidx = z * _verNumX + x;

				if (vidx >= 0 && vidx < _vecPos.size())
				{
					pv[vidx] = _terrainVertices[vidx];
				}
			}
		}
	}
	_terrainVb->Unlock();

	return S_OK;
}



//지형 스무싱
void terrain::smoothTerrain()
{
	int tempSmoothLevel = _smoothLevel;
	if (tempSmoothLevel <= 0) return;

	float* smooth = new float[_totalVerNum];

	while (tempSmoothLevel > 0)
	{
		tempSmoothLevel--;
		for (int z = 0; z < _verNumZ; z++)
		{
			for (int x = 0; x < _verNumX; x++)
			{
				int adjacentSections = 0;		//몇개의 정점과 평균값을 내니?
				float totalSections = 0.0f;		//주변의 정점 높이 총합은 얼마니?

												//왼쪽체크
				if ((x - 1) > 0)
				{
					totalSections += _terrainVertices[(z * _verNumX) + (x - 1)].pos.y;
					adjacentSections++;
					//왼쪽 상단
					if ((z - 1) > 0)
					{
						totalSections += _terrainVertices[((z - 1) * _verNumX) + (x - 1)].pos.y;
						adjacentSections++;
					}
					//왼쪽 하단
					if ((z + 1) < _verNumZ)
					{
						totalSections += _terrainVertices[((z + 1) * _verNumX) + (x - 1)].pos.y;
						adjacentSections++;
					}
				}
				//오른쪽 체크
				if ((x + 1) < _verNumX)
				{
					totalSections += _terrainVertices[(z * _verNumX) + (x + 1)].pos.y;
					adjacentSections++;

					//오른쪽 상단
					if ((z - 1) > 0)
					{
						totalSections += _terrainVertices[((z - 1) * _verNumX) + (x + 1)].pos.y;
						adjacentSections++;
					}
					//오른쪽 하단 
					if ((z + 1) < _verNumZ) {
						totalSections += _terrainVertices[((z + 1) * _verNumX) + (x + 1)].pos.y;
						adjacentSections++;
					}
				}
				//상단
				if ((z - 1) > 0)
				{
					totalSections += _terrainVertices[((z - 1) * _verNumX) + x].pos.y;
					adjacentSections++;
				}
				//하단
				if ((z + 1) < _verNumZ)
				{
					totalSections += _terrainVertices[((z + 1) * _verNumX) + x].pos.y;
					adjacentSections++;
				}
				smooth[(z * _verNumX) + x] = (
					_terrainVertices[(z * _verNumX) + x].pos.y +
					(totalSections / adjacentSections)) * 0.5f;
			}
		}

		//위에서 계산된 y 스무싱 적용
		for (int i = 0; i < _totalVerNum; i++)
		{
			_terrainVertices[i].pos.y = smooth[i];
		}
	}

	SAFE_DELETE_ARRAY(smooth);
}



void terrain::smoothChangeTerrainHt(int terrainX, int terrainZ)
{
	int tempSmoothLevel = _smoothLevel;
	if (tempSmoothLevel <= 0) return;

	float* smooth = new float[_totalVerNum];

	while (tempSmoothLevel > 0)
	{
		tempSmoothLevel--;
		for (int z = terrainZ - _nHtChangeRange; z <= terrainZ + _nHtChangeRange; z++)
		{
			for (int x = terrainX - _nHtChangeRange; x <= terrainX + _nHtChangeRange; x++)
			{
				int adjacentSections = 0;		//몇개의 정점과 평균값을 내니?
				float totalSections = 0.0f;		//주변의 정점 높이 총합은 얼마니?

				if (x >= 0 && x < _verNumX && z >= 0 && z < _verNumZ)
				{
					//왼쪽체크
					if ((x - 1) > 0)
					{
						totalSections += _terrainVertices[(z * _verNumX) + (x - 1)].pos.y;
						adjacentSections++;
						//왼쪽 상단
						if ((z - 1) > 0)
						{
							totalSections += _terrainVertices[((z - 1) * _verNumX) + (x - 1)].pos.y;
							adjacentSections++;
						}
						//왼쪽 하단
						if ((z + 1) < _verNumZ)
						{
							totalSections += _terrainVertices[((z + 1) * _verNumX) + (x - 1)].pos.y;
							adjacentSections++;
						}
					}
					//오른쪽 체크
					if ((x + 1) < _verNumX)
					{
						totalSections += _terrainVertices[(z * _verNumX) + (x + 1)].pos.y;
						adjacentSections++;

						//오른쪽 상단
						if ((z - 1) > 0)
						{
							totalSections += _terrainVertices[((z - 1) * _verNumX) + (x + 1)].pos.y;
							adjacentSections++;
						}
						//오른쪽 하단 
						if ((z + 1) < _verNumZ) {
							totalSections += _terrainVertices[((z + 1) * _verNumX) + (x + 1)].pos.y;
							adjacentSections++;
						}
					}
					//상단
					if ((z - 1) > 0)
					{
						totalSections += _terrainVertices[((z - 1) * _verNumX) + x].pos.y;
						adjacentSections++;
					}
					//하단
					if ((z + 1) < _verNumZ)
					{
						totalSections += _terrainVertices[((z + 1) * _verNumX) + x].pos.y;
						adjacentSections++;
					}
					smooth[(z * _verNumX) + x] = (
						_terrainVertices[(z * _verNumX) + x].pos.y +
						(totalSections / adjacentSections)) * 0.5f;
				}
			}
		}


		for (int z = terrainZ - _nHtChangeRange; z <= terrainZ + _nHtChangeRange; z++)
		{
			for (int x = terrainX - _nHtChangeRange; x <= terrainX + _nHtChangeRange; x++)
			{
				if (x >= 0 && x < _verNumX && z >= 0 && z < _verNumZ)
				{
					int vidx = z * _verNumX + x;

					if (vidx >= 0 && vidx < _vecPos.size())
					{
						_terrainVertices[vidx].pos.y = smooth[vidx];
					}
				}
			}
		}
	}

	SAFE_DELETE_ARRAY(smooth);
}



D3DXVECTOR3 terrain::selectSplatColor(string splatName, int x, int z)
{
	LPDIRECT3DTEXTURE9 tempSplat;
	tempSplat = TEXTURE_MANAGER->GetTexture(splatName);

	//텍스쳐의 pixel 정보를 얻기 위해 Texture 를 lock 한다.
	D3DLOCKED_RECT lockRect;
	tempSplat->LockRect(0, &lockRect, 0, 0);

	//해당 픽셀의 컬러 값을 얻는다.

	//(DWORD 형으로 형변환된 lock 된 이미지지의 시작 주소
	DWORD* pStart = (DWORD*)lockRect.pBits;
	DWORD dwColor = *(pStart + (z * (lockRect.Pitch / 4) + x));

	float r = (dwColor & 0x00ff0000) >> 16;
	float g = (dwColor & 0x0000ff00) >> 8;
	float b = (dwColor & 0x000000ff);

	//텍스쳐의 pixel 정보 Unlock
	tempSplat->UnlockRect(0);

	return D3DXVECTOR3(r, g, b);
}




void terrain::setHeightmap(string heightMapName)
{
	_heightMap = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath(heightMapName));
}

void terrain::setHeightmap(string heightMapName, bool isOver)
{
	_heightMap = RM_TEXTURE->getResource(heightMapName);
}

void terrain::setTile0(string tile_0)
{
	_texTile_0 = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath(tile_0));
}


void terrain::setTile1(string tile_1)
{
	_texTile_1= RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath(tile_1));
}

void terrain::setTile2(string tile_2)
{
	_texTile_2 = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath(tile_2));
}

void terrain::setTile3(string tile_3)
{
	_texTile_3 = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath(tile_3));
}

void terrain::setTile0(string tile_0, bool isOver)
{
	_texTile_0 = RM_TEXTURE->getResource(tile_0);
}

void terrain::setTile1(string tile_1, bool isOver)
{
	_texTile_1 = RM_TEXTURE->getResource(tile_1);
}

void terrain::setTile2(string tile_2, bool isOver)
{
	_texTile_2 = RM_TEXTURE->getResource(tile_2);
}

void terrain::setTile3(string tile_3, bool isOver)
{
	_texTile_3 = RM_TEXTURE->getResource(tile_3);
}

void terrain::setSplat(string tileSplat)
{
	_texSlat = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath(tileSplat));
}

void terrain::setSplat(string tileSplat, bool isOver)
{
	_texSlat = RM_TEXTURE->getResource(tileSplat);
}

void terrain::setSplat(LPDIRECT3DTEXTURE9 texSlat)
{
	_texSlat = texSlat;
}

void terrain::setCellsize(float cellSize)
{
	_cellScale = cellSize;
}

void terrain::setHeightscale(float heightScale)
{
	_heightScale = heightScale;
}

void terrain::setSmoothlevel(int smoothLevel)
{
	_smoothLevel = smoothLevel;
}

void terrain::setTileNum(int tileNum)
{
	_tileNum = tileNum;
}





//=========================================================================
//지형 높이값 실시간 변경 브러쉬 방법 -> 프레임 드랍과 더불어 온갖 버그...
//=========================================================================

HRESULT terrain::changeHeightTerrain()
{
	// 정점 위치 구한다.

	//타일링 갯수에 따른 간격 (정점당 uv 간격)
	float tileIntervalX = static_cast<float>(_tileNum) / _cellNumX;
	float tileIntervalY = static_cast<float>(_tileNum) / _cellNumZ;

	//지형 정점 가지고 있어야 한다.
	_terrainVertices = new TERRAINVERTEX[_totalVerNum];

	//텍스쳐의 pixel 정보를 얻기 위해 Texture 를 lock 한다.
	D3DLOCKED_RECT lockRect;
	_heightMap->LockRect(
		0,					//lock 을 할 밉맵 레벨 0
		&lockRect,			//lock 으로 얻어온 D3DLOCKED_RECT 정보 구조체
		0,					//lock 을 일부 영역만 하고 싶은 경우 사각형RECT 구조체의 포인터를 주는데 전체 할꺼면 NULL
		0					//lock 플레그 일단 0
	);

	//lockRect->Pitch	lock 을 한 영역 이미지의 가로 byte 크기 (얻어온 바이트크기는 다음을 성립한다 pitch % 4 == 0 ) < 3byte 컬러시 pitch byte 구하는 공식 ( 가로 픽셀수 * 3 + 3 ) & ~3 = pitch  >
	//lockRect->pBits	이미지데이터가 시작되는 포인터 주소

	//정정위치와 정점 UV 를 계산하기
	for (int z = 0; z < _verNumZ; z++)
	{
		for (int x = 0; x < _verNumX; x++)
		{
			D3DXVECTOR3 pos;

			//버텍스 배열인덱스 계산
			int idx = z * _verNumX + x;

			pos = _vecPos[idx];

			//정점 UV 계산

			//Terrain Tile Splating UV
			D3DXVECTOR2 baseUV;
			baseUV.x = x / static_cast<float>(_verNumX - 1);
			baseUV.y = z / static_cast<float>(_verNumZ - 1);

			//Terrain Tile UV
			D3DXVECTOR2 tileUV;
			tileUV.x = x * tileIntervalX;
			tileUV.y = z * tileIntervalY;


			_terrainVertices[idx].pos = pos;
			_terrainVertices[idx].normal = D3DXVECTOR3(0, 0, 0);	//아래에서 정점 노말 구할때 더해지니 일단 0 벡터로 초기화
			_terrainVertices[idx].baseUV = baseUV;
			_terrainVertices[idx].tileUV = tileUV;

			_vecPos.push_back(pos);
		}
	}

	//텍스쳐의 pixel 정보 Unlock
	_heightMap->UnlockRect(0);

	//지형 스무싱 
	this->smoothTerrain();


	// 정점 인덱스를 구한다
	LPTERRAINTRI pIndices = new tagTERRAINTRI[_totalTriangle];

	//인덱스 배열 인덱스
	int idx = 0;

	for (DWORD z = 0; z < _cellNumZ; z++)
	{
		for (DWORD x = 0; x < _cellNumX; x++)
		{
			// lt-----rt
			//  |    /|
			//  |   / |
			//  |  /  |
			//  | /   |
			//  |/    |
			// lb-----rb

			//해당 셀에 대한 정점 인덱스를 얻자
			DWORD lt = z * _verNumX + x;
			DWORD rt = z * _verNumX + x + 1;
			DWORD lb = ((z + 1)* _verNumX) + x;
			DWORD rb = ((z + 1)* _verNumX) + x + 1;

			//셀의 삼각형 하나
			pIndices[idx].dw0 = lt;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = lb;
			idx++;

			//셀의 삼각형 하나
			pIndices[idx].dw0 = lb;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = rb;
			idx++;
		}
	}

	// 노말이랑 Binormal 이랑 Tangent 계산하기
	D3DXVECTOR3* poses = new D3DXVECTOR3[_totalVerNum];		//정점위치
	D3DXVECTOR3* normals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* tangents = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* binormals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR2* uvs = new D3DXVECTOR2[_totalVerNum];
	DWORD* indices = (DWORD*)pIndices;

	//정점위치 및 UV 대입
	for (int i = 0; i < _totalVerNum; i++)
	{
		poses[i] = _terrainVertices[i].pos;
		uvs[i] = _terrainVertices[i].baseUV;
	}

	//노말계산
	ComputeNormal(normals, poses, _totalVerNum, indices, _totalTriangle * 3);

	//탄젠트 바이노말 계산
	ComputeTangentBinormal(
		tangents,
		binormals,
		poses,
		normals,
		uvs,
		indices,
		_totalTriangle,
		_totalVerNum);

	//계산된거 대입
	for (int i = 0; i < _totalVerNum; i++)
	{
		_terrainVertices[i].normal = normals[i];
		_terrainVertices[i].binormal = binormals[i];
		_terrainVertices[i].tangent = tangents[i];
	}

	// 버퍼 생성
	//정점버퍼 만들기
	_device->CreateVertexBuffer(
		sizeof(TERRAINVERTEX) * _totalVerNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&_terrainVb,
		0);

	//만들어진 정점 버퍼를 Lock 하여 지형 정점 값을 쓴다.
	void* p = NULL;
	_terrainVb->Lock(0, 0, &p, 0);
	memcpy(p, _terrainVertices, sizeof(TERRAINVERTEX) * _totalVerNum);
	_terrainVb->Unlock();

	//인덱스 버퍼 만들기
	_device->CreateIndexBuffer(
		sizeof(TERRAINTRI) * _totalTriangle,
		D3DUSAGE_WRITEONLY,	//D3DUSAGE_WRITEONLY 예는 락안하고 고정정으로 버퍼내용이 유지될때 최고성능을 발휘, D3DUSAGE_DYNAMIC 락 을 자주하여 버퍼 내용이 바뀌는 경우
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,	//D3DUSAGE_DYNAMIC 을 쓰려면 무조건 D3DPOOL_DEFAULT
		&_terrainIb,
		0);

	//인덱스 버퍼에 값을 쓴다.
	_terrainIb->Lock(0, 0, &p, 0);
	memcpy(p, pIndices, sizeof(TERRAINTRI) * _totalTriangle);
	_terrainIb->Unlock();

	// 정점 선언부를 만든다.
	//정점의 형태를 알려주는 배열
	D3DVERTEXELEMENT9 vertElement[7];	//배열을 정점정보 갯수 + 1

										//Position 
	vertElement[0].Stream = 0;							//Stream 은 0
	vertElement[0].Offset = 0;							//메모리의 시작 Byte 단위 0
	vertElement[0].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[0].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[0].Usage = D3DDECLUSAGE_POSITION;		//정보 타입
	vertElement[0].UsageIndex = 0;						//UsageIndex 일단 0

														//Normal
	vertElement[1].Stream = 0;							//Stream 은 0
	vertElement[1].Offset = 12;							//메모리의 시작 Byte 단위 0
	vertElement[1].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[1].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[1].Usage = D3DDECLUSAGE_NORMAL;			//정보 타입
	vertElement[1].UsageIndex = 0;						//UsageIndex 일단 0

														//BiNormal
	vertElement[2].Stream = 0;							//Stream 은 0
	vertElement[2].Offset = 24;							//메모리의 시작 Byte 단위 0
	vertElement[2].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[2].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[2].Usage = D3DDECLUSAGE_BINORMAL;		//정보 타입
	vertElement[2].UsageIndex = 0;						//UsageIndex 일단 0

														//Tangent
	vertElement[3].Stream = 0;							//Stream 은 0
	vertElement[3].Offset = 36;							//메모리의 시작 Byte 단위 0
	vertElement[3].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[3].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[3].Usage = D3DDECLUSAGE_TANGENT;		//정보 타입
	vertElement[3].UsageIndex = 0;						//UsageIndex 일단 0

														//BaseUV
	vertElement[4].Stream = 0;							//Stream 은 0
	vertElement[4].Offset = 48;							//메모리의 시작 Byte 단위 0
	vertElement[4].Type = D3DDECLTYPE_FLOAT2;			//자료의 타입
	vertElement[4].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[4].Usage = D3DDECLUSAGE_TEXCOORD;		//정보 타입
	vertElement[4].UsageIndex = 0;						//UsageIndex 일단 0


														//tileUV
	vertElement[5].Stream = 0;							//Stream 은 0
	vertElement[5].Offset = 56;							//메모리의 시작 Byte 단위 0
	vertElement[5].Type = D3DDECLTYPE_FLOAT2;			//자료의 타입
	vertElement[5].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[5].Usage = D3DDECLUSAGE_TEXCOORD;		//정보 타입
	vertElement[5].UsageIndex = 1;						//UsageIndex 두번째 UV 1 

														//더이상 없으니 종료
	D3DVERTEXELEMENT9 end = D3DDECL_END(); //{0xFF,0,D3DDECLTYPE_UNUSED,0,0,0}
	vertElement[6] = end;



	// LPDIRECT3DVERTEXDECLARATION9 생성
	_device->CreateVertexDeclaration(
		vertElement,			//앞에서 만든 D3DVERTEXELEMENT9 배열 포인터
		&_terrainDecl			//얻어올 LPDIRECT3DVERTEXDECLARATION9 포인터
	);

	SAFE_DELETE_ARRAY(poses);
	SAFE_DELETE_ARRAY(normals);
	SAFE_DELETE_ARRAY(tangents);
	SAFE_DELETE_ARRAY(binormals);
	SAFE_DELETE_ARRAY(uvs);
	SAFE_DELETE_ARRAY(indices);

	return S_OK;
}

HRESULT terrain::changeHeightTerrain(float cursorX, float cursorZ)
{
	//브러쉬맵의 가로세로 절반의 길이
	int brushIdxX = brush_verNumX / 2;
	int brushIdxZ = brush_verNumZ / 2;

	//브러쉬맵의 좌상단의 인덱스를 찾자
	int idxX = getIdx(cursorX, cursorZ).x - brushIdxX;
	int idxZ = getIdx(cursorX, cursorZ).y - brushIdxZ;

	//브러쉬맵의 우하단의 인덱스를 찾자
	int idxX2 = getIdx(cursorX, cursorZ).x + brushIdxX;
	int idxZ2 = getIdx(cursorX, cursorZ).y + brushIdxZ;

	//정정위치와 정점 UV 를 계산하기
	for (int z = 0; z < _verNumZ; z++)
	{
		for (int x = 0; x < _verNumX; x++)
		{
			int idx = z * _verNumX + x;

			if (x >= idxX && x <= idxX2 &&
				z >= idxZ && z <= idxZ2)
			{
				//브러쉬맵에 사용될 인덱스번호
				int idx2 = (z - idxZ) * brush_verNumX + (x - idxX);
				_vecPos[idx].y +=_vecBrush[idx2] * _brushScale * _nHeightSign;
			}
			_terrainVertices[idx].pos = _vecPos[idx];
		}
	}

	////지형 스무싱 
	this->smoothTerrain();


	// 정점 인덱스를 구한다
	LPTERRAINTRI pIndices = new tagTERRAINTRI[_totalTriangle];

	//인덱스 배열 인덱스
	int idx = 0;

	for (DWORD z = 0; z < _cellNumZ; z++)
	{
		for (DWORD x = 0; x < _cellNumX; x++)
		{
			// lt-----rt
			//  |    /|
			//  |   / |
			//  |  /  |
			//  | /   |
			//  |/    |
			// lb-----rb

			//해당 셀에 대한 정점 인덱스를 얻자
			DWORD lt = z * _verNumX + x;
			DWORD rt = z * _verNumX + x + 1;
			DWORD lb = ((z + 1)* _verNumX) + x;
			DWORD rb = ((z + 1)* _verNumX) + x + 1;

			//셀의 삼각형 하나
			pIndices[idx].dw0 = lt;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = lb;
			idx++;

			//셀의 삼각형 하나
			pIndices[idx].dw0 = lb;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = rb;
			idx++;
		}
	}

	// 노말이랑 Binormal 이랑 Tangent 계산하기
	D3DXVECTOR3* poses = new D3DXVECTOR3[_totalVerNum];		//정점위치
	D3DXVECTOR3* normals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* tangents = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* binormals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR2* uvs = new D3DXVECTOR2[_totalVerNum];
	DWORD* indices = (DWORD*)pIndices;

	//정점위치 및 UV 대입
	for (int i = 0; i < _totalVerNum; i++)
	{
		poses[i] = _terrainVertices[i].pos;
		uvs[i] = _terrainVertices[i].baseUV;
	}

	//노말계산
	ComputeNormal(normals, poses, _totalVerNum, indices, _totalTriangle * 3);

	//탄젠트 바이노말 계산
	ComputeTangentBinormal(
		tangents,
		binormals,
		poses,
		normals,
		uvs,
		indices,
		_totalTriangle,
		_totalVerNum);

	//계산된거 대입
	for (int i = 0; i < _totalVerNum; i++)
	{
		_terrainVertices[i].normal = normals[i];
		_terrainVertices[i].binormal = binormals[i];
		_terrainVertices[i].tangent = tangents[i];
	}

	// 버퍼 생성
	//정점버퍼 만들기
	_device->CreateVertexBuffer(
		sizeof(TERRAINVERTEX) * _totalVerNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&_terrainVb,
		0);

	//만들어진 정점 버퍼를 Lock 하여 지형 정점 값을 쓴다.
	void* p = NULL;
	_terrainVb->Lock(0, 0, &p, 0);
	memcpy(p, _terrainVertices, sizeof(TERRAINVERTEX) * _totalVerNum);
	_terrainVb->Unlock();

	//인덱스 버퍼 만들기
	_device->CreateIndexBuffer(
		sizeof(TERRAINTRI) * _totalTriangle,
		D3DUSAGE_DYNAMIC,	//D3DUSAGE_WRITEONLY 예는 락안하고 고정정으로 버퍼내용이 유지될때 최고성능을 발휘, D3DUSAGE_DYNAMIC 락 을 자주하여 버퍼 내용이 바뀌는 경우
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,	//D3DUSAGE_DYNAMIC 을 쓰려면 무조건 D3DPOOL_DEFAULT
		&_terrainIb,
		0);

	//인덱스 버퍼에 값을 쓴다.
	_terrainIb->Lock(0, 0, &p, 0);
	memcpy(p, pIndices, sizeof(TERRAINTRI) * _totalTriangle);
	_terrainIb->Unlock();

	// 정점 선언부를 만든다.
	//정점의 형태를 알려주는 배열
	D3DVERTEXELEMENT9 vertElement[7];	//배열을 정점정보 갯수 + 1

										//Position 
	vertElement[0].Stream = 0;							//Stream 은 0
	vertElement[0].Offset = 0;							//메모리의 시작 Byte 단위 0
	vertElement[0].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[0].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[0].Usage = D3DDECLUSAGE_POSITION;		//정보 타입
	vertElement[0].UsageIndex = 0;						//UsageIndex 일단 0

														//Normal
	vertElement[1].Stream = 0;							//Stream 은 0
	vertElement[1].Offset = 12;							//메모리의 시작 Byte 단위 0
	vertElement[1].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[1].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[1].Usage = D3DDECLUSAGE_NORMAL;			//정보 타입
	vertElement[1].UsageIndex = 0;						//UsageIndex 일단 0

														//BiNormal
	vertElement[2].Stream = 0;							//Stream 은 0
	vertElement[2].Offset = 24;							//메모리의 시작 Byte 단위 0
	vertElement[2].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[2].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[2].Usage = D3DDECLUSAGE_BINORMAL;		//정보 타입
	vertElement[2].UsageIndex = 0;						//UsageIndex 일단 0

														//Tangent
	vertElement[3].Stream = 0;							//Stream 은 0
	vertElement[3].Offset = 36;							//메모리의 시작 Byte 단위 0
	vertElement[3].Type = D3DDECLTYPE_FLOAT3;			//자료의 타입
	vertElement[3].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[3].Usage = D3DDECLUSAGE_TANGENT;		//정보 타입
	vertElement[3].UsageIndex = 0;						//UsageIndex 일단 0

														//BaseUV
	vertElement[4].Stream = 0;							//Stream 은 0
	vertElement[4].Offset = 48;							//메모리의 시작 Byte 단위 0
	vertElement[4].Type = D3DDECLTYPE_FLOAT2;			//자료의 타입
	vertElement[4].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[4].Usage = D3DDECLUSAGE_TEXCOORD;		//정보 타입
	vertElement[4].UsageIndex = 0;						//UsageIndex 일단 0


														//tileUV
	vertElement[5].Stream = 0;							//Stream 은 0
	vertElement[5].Offset = 56;							//메모리의 시작 Byte 단위 0
	vertElement[5].Type = D3DDECLTYPE_FLOAT2;			//자료의 타입
	vertElement[5].Method = D3DDECLMETHOD_DEFAULT;		//일단 무조건  D3DDECLMETHOD_DEFAULT
	vertElement[5].Usage = D3DDECLUSAGE_TEXCOORD;		//정보 타입
	vertElement[5].UsageIndex = 1;						//UsageIndex 두번째 UV 1 

														//더이상 없으니 종료
	D3DVERTEXELEMENT9 end = D3DDECL_END(); //{0xFF,0,D3DDECLTYPE_UNUSED,0,0,0}
	vertElement[6] = end;



	// LPDIRECT3DVERTEXDECLARATION9 생성
	_device->CreateVertexDeclaration(
		vertElement,			//앞에서 만든 D3DVERTEXELEMENT9 배열 포인터
		&_terrainDecl			//얻어올 LPDIRECT3DVERTEXDECLARATION9 포인터
	);

	SAFE_DELETE_ARRAY(poses);
	SAFE_DELETE_ARRAY(normals);
	SAFE_DELETE_ARRAY(tangents);
	SAFE_DELETE_ARRAY(binormals);
	SAFE_DELETE_ARRAY(uvs);
	SAFE_DELETE_ARRAY(indices);

	//쿼드트리를 만든다.
	_quadTree = new quadTree;
	_quadTree->init(_terrainVertices, _verNumX);

	return S_OK;
}

void terrain::setBrushmap(string brushMapName)
{
	_brushMap = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath(brushMapName));

	D3DSURFACE_DESC sd;
	_brushMap->GetLevelDesc(0, &sd);

	brush_verNumX = sd.Width + 1;	//가로 정점갯수는 높이 맵에 가로 해상도 + 1 과 같다. (이유는 쿼드트리쓰려면 정점갯수가 2의N승 + 1 이여야 하기 때문에)
	brush_verNumZ = sd.Height + 1;	//세로 정점잿수는 높이 맵에 세로 해상도 + 1 과 같다. (이유는 쿼드트리쓰려면 정점갯수가 2의N승 + 1 이여야 하기 때문에)
	brush_totalotalVerNum = brush_verNumX * brush_verNumZ;	//총 정점 갯수

															//가로세로 셀수
	brush_cellNumX = brush_verNumX - 1;
	brush_cellNumZ = brush_verNumZ - 1;
	brush_totalCellNum = brush_cellNumX * brush_cellNumZ;

	//터레인 크기
	brush_terrainSizeX = brush_cellNumX * _cellScale;
	brush_terrainSizeZ = brush_cellNumZ * _cellScale;

	D3DLOCKED_RECT lockRect;
	_brushMap->LockRect(0, &lockRect, 0, 0);

	for (int z = 0; z < brush_verNumZ; z++)
	{
		for (int x = 0; x < brush_verNumX; x++)
		{
			DWORD* pStart = (DWORD*)lockRect.pBits;	//(DWORD 형으로 형변환된 lock 된 이미지지의 시작 주소
			DWORD dwColor = *(pStart + (z * (lockRect.Pitch / 4) + x));

			float inv = 1.0f / 255.0f;
			float r = ((dwColor & 0x00ff0000) >> 16) * inv;
			float g = ((dwColor & 0x0000ff00) >> 8) * inv;
			float b = ((dwColor & 0x000000ff)) * inv;

			float factor = (r + g + b) / 3.0f;

			_vecBrush.push_back(factor * 0.1f);
		}
	}
}

void terrain::setBrushScale(float scale)
{
	_nHeightSign = scale;
}
