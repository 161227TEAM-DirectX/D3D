#include "stdafx.h"
#include "terrain.h"
#include "quadTree.h"

terrain::terrain()
	: _quadTree(NULL)			//���� Ʈ��
	, _isQuad(false)			//���� ���� ����
	, _cellScale(1.0f)			//�� ����
	, _heightScale(200)			//���� ������(�ȼ��÷��� 255�϶� ����)
	, _smoothLevel(3)			//������ ó�� Ƚ��
	, _tileNum(100)				//Ÿ�ϸ� ����
	, _verNumX(0)				//���� ������(���� �׸� ������ ���� 1�� �� ����.���ذ� �ȵǸ� �׸��� �׷��� ��.)
	, _verNumZ(0)				//���� ������(���� �׸� ������ ���� 1�� �� ����.���ذ� �ȵǸ� �׸��� �׷��� ��.)
	, _totalVerNum(0)			//��ü ������(���� ������ * ���� ������)
	, _cellNumX(0)				//���� ����(���� �׸� ������)
	, _cellNumZ(0)				//���� ����(���� �׸� ������)
	, _totalCellNum(0)			//��ü ����
	, _totalTriangle(0)			//��ü �ﰢ����		
	, _terrainSizeX(0.f)		//���� ���� ������(128,256,����)
	, _terrainSizeZ(0.f)		//���� ���� ������(128,256,����)
	, _terrainStartX(0.f)		//���� ���� ��ġX
	, _terrainStartZ(0.f)		//���� ���� ��ġZ
	, _terrainEndX(0.f)			//���� ���� ��ġX
	, _terrainEndZ(0.f)			//���� ���� ��ġZ
	, _isVertexDraw(false)		//���ؽ� ������ �׸�����
	, _nHtChangeRange(3)		//���̰��� �ٲ� ����(����)
	, _fHtChangeValue(0.1f)		//���̰��� �ٲ� ��(�󸶸�ŭ �ø��� ��������)
	, _nHtChangeSign(1)			//���̰��� ������ų�� ���ҽ�ų�� ��ȣ
	, _isSmoothing(true)		//�������� �Ұ���
{
	//���� ���̴�����Ʈ �ε�
	_terrainEffect = RM_SHADERFX->getResource(FILEPATH_MANAGER->GetFilepath("FX_�����⺻"));
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
	//�����ϰ� ����
	_heightScale = heightScale;
	_cellScale = cellSize;

	//���̸� �ҷ��´�
	_heightMap = RM_TEXTURE->getResource(heightMapName);
	//�ҷ����µ� �����ϸ� �ٷ� ����
	if (_heightMap == NULL) return E_FAIL;

	//���� �ʿ� ���� �̹��� ������ �ҷ��´�. (�ε��� Texture ������ ��´�)
	D3DSURFACE_DESC sd;
	//GetLevelDesc(�Ӹ�ü�� ����, D3DSURFACE_DESC ����ü ������)
	_heightMap->GetLevelDesc(0, &sd);

	//���μ��� ���� ���� ���Ѵ�.
	_verNumX = sd.Width + 1;	//���� ���������� ���� �ʿ� ���� �ػ� + 1 �� ����. (������ ����Ʈ�������� ���������� 2��N�� + 1 �̿��� �ϱ� ������)
	_verNumZ = sd.Height + 1;	//���� ��������� ���� �ʿ� ���� �ػ� + 1 �� ����. (������ ����Ʈ�������� ���������� 2��N�� + 1 �̿��� �ϱ� ������)
	_totalVerNum = _verNumX * _verNumZ;	//�� ���� ����

										//���μ��� ����
	_cellNumX = _verNumX - 1;
	_cellNumZ = _verNumZ - 1;
	_totalCellNum = _cellNumX * _cellNumZ;

	//�� �ﰢ������
	_totalTriangle = _totalCellNum * 2;

	//�ͷ����� �����.
	//������ ���� (�̰��� Ŭ���� ������ �ε巯������)
	//Ÿ�� Texture �� ��� ������������ ����
	if (FAILED(createTerrain(tileNum)))
	{
		return E_FAIL;
	}

	//�ͷ��� ũ��
	_terrainSizeX = _cellNumX * _cellScale;
	_terrainSizeZ = _cellNumZ * _cellScale;

	//�ͷ��� ����
	_terrainStartX = _terrainVertices[0].pos.x;
	_terrainStartZ = _terrainVertices[0].pos.z;
	_terrainEndX = _terrainVertices[_totalVerNum - 1].pos.x;
	_terrainEndZ = _terrainVertices[_totalVerNum - 1].pos.z;

	//����Ʈ���� �����.
	_quadTree = new quadTree;
	_quadTree->init(_terrainVertices, _verNumX);

	//���� �ؽ��� �ε�
	_texTile_0 = RM_TEXTURE->getResource(tile_0);
	_texTile_1 = RM_TEXTURE->getResource(tile_1);
	_texTile_2 = RM_TEXTURE->getResource(tile_2);
	_texTile_3 = RM_TEXTURE->getResource(tile_3);
	_texSlat = RM_TEXTURE->getResource(tileSplat);

	//���� ���̴�����Ʈ �ε�
	_terrainEffect = RM_SHADERFX->getResource("Resource/Maptool/Shaders/TerrainBase.fx");

	dijk = new dijkstra;
}



void terrain::setting()
{
	//���� �ʿ� ���� �̹��� ������ �ҷ��´�. (�ε��� Texture ������ ��´�)
	D3DSURFACE_DESC sd;
	//GetLevelDesc(�Ӹ�ü�� ����, D3DSURFACE_DESC ����ü ������)
	_heightMap->GetLevelDesc(0, &sd);

	//���μ��� ���� ���� ���Ѵ�.
	_verNumX = sd.Width + 1;	//���� ���������� ���� �ʿ� ���� �ػ� + 1 �� ����. (������ ����Ʈ�������� ���������� 2��N�� + 1 �̿��� �ϱ� ������)
	_verNumZ = sd.Height + 1;	//���� ��������� ���� �ʿ� ���� �ػ� + 1 �� ����. (������ ����Ʈ�������� ���������� 2��N�� + 1 �̿��� �ϱ� ������)
	_totalVerNum = _verNumX * _verNumZ;	//�� ���� ����

										//���μ��� ����
	_cellNumX = _verNumX - 1;
	_cellNumZ = _verNumZ - 1;
	_totalCellNum = _cellNumX * _cellNumZ;

	//�� �ﰢ������
	_totalTriangle = _totalCellNum * 2;

	//�ͷ����� �����.
	//������ ����
	createTerrain(_tileNum);


	//�ͷ��� ũ��
	_terrainSizeX = _cellNumX * _cellScale;
	_terrainSizeZ = _cellNumZ * _cellScale;

	//�ͷ��� ����
	_terrainStartX = _terrainVertices[0].pos.x;
	_terrainStartZ = _terrainVertices[0].pos.z;
	_terrainEndX = _terrainVertices[_totalVerNum - 1].pos.x;
	_terrainEndZ = _terrainVertices[_totalVerNum - 1].pos.z;

	//����Ʈ���� �����.
	_quadTree = new quadTree;
	_quadTree->init(_terrainVertices, _verNumX);

	dijk = new dijkstra;
}



void terrain::changeHeight(int terrainX, int terrainZ)
{
	changeTerrainHt(terrainX, terrainZ);

	//����Ʈ���� �����ؾ��� ��츸 �����ϵ��� ó��.
	if (_isQuad)
	{
		//��ƮƮ���� ���� �ƴ� ��� 
		if (_quadTree != NULL) SAFE_DELETE(_quadTree);
		_quadTree = new quadTree;
		_quadTree->init(_terrainVertices, _verNumX);
	}
}



void terrain::render(camera * cam, lightDirection * directionLight)
{
	//���� ��ļ���
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	//���̴�����Ʈ ������� ����
	_terrainEffect->SetMatrix("matWorld", &matWorld);

	//���̴�����Ʈ ����� ����
	_terrainEffect->SetMatrix("matViewProjection", &cam->getViewProjectionMatrix());

	//���̴�����Ʈ �ؽ��� ����
	_terrainEffect->SetTexture("Terrain0_Tex", _texTile_0);
	_terrainEffect->SetTexture("Terrain1_Tex", _texTile_1);
	_terrainEffect->SetTexture("Terrain2_Tex", _texTile_2);
	_terrainEffect->SetTexture("Terrain3_Tex", _texTile_3);
	_terrainEffect->SetTexture("TerrainControl_Tex", _texSlat);

	//���̴�����Ʈ ���� ����
	D3DXVECTOR3 dirLight = -directionLight->_transform->GetUp();
	_terrainEffect->SetVector("worldLightDir", &D3DXVECTOR4(dirLight, 1));

	//���̴� ����
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


	////��������
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
	//ShadowMap ����
	_terrainEffect->SetTexture("Shadow_Tex", directionLightCamera->getRenderTexture());

	//ShadowViewProjection ���� 
	_terrainEffect->SetMatrix("matLightViewProjection", &directionLightCamera->getViewProjectionMatrix());

	//���� ��ļ���
	D3DXMATRIXA16 matInd;
	D3DXMatrixIdentity(&matInd);
	_terrainEffect->SetMatrix("matWorld", &matInd);

	//�� ��ļ���
	_terrainEffect->SetMatrix("matViewProjection", &cam->getViewProjectionMatrix());

	//Texture ����
	_terrainEffect->SetTexture("Terrain0_Tex", _texTile_0);
	_terrainEffect->SetTexture("Terrain1_Tex", _texTile_1);
	_terrainEffect->SetTexture("Terrain2_Tex", _texTile_2);
	_terrainEffect->SetTexture("Terrain3_Tex", _texTile_3);
	_terrainEffect->SetTexture("TerrainControl_Tex", _texSlat);

	//���� ����
	D3DXVECTOR3 dirLight = directionLight->_transform->GetForward();
	_terrainEffect->SetVector("worldLightDir", &D3DXVECTOR4(dirLight, 1));

	//���� ����
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
	//���� ��ļ���
	D3DXMATRIXA16 matInd;
	D3DXMatrixIdentity(&matInd);
	_terrainEffect->SetMatrix("matWorld", &matInd);

	//�� ��ļ���
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



//Ray ��Ʈ ��ġ�� ��´�.
bool terrain::isIntersectRay(D3DXVECTOR3 * pOut, LPRay ray)
{
	vector<D3DXVECTOR3> hits;

	//�ֻ�� ���� Ʈ������ Ray Check ����.
	_quadTree->getRayHits(&hits, ray);

	//��Ʈ�Ȱ� ����
	if (hits.size() == 0) return false;

	//���� ó�� ��ġ�� ó�� ��ġ������ �Ÿ� ����
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

	//��������´ٸ� ���� �Ÿ��� ����� Hit ��ġ�� ���´�
	*pOut = hitPos;

	return true;
}



//�ش� X, Z ��ġ�� ������ ���̸� ��´�.
float terrain::getHeight(float x, float z)
{
	//�ͷ��� ������ �Ѿ�� 0.0 ���� �����Ѵ�
	if (x < _terrainStartX || x > _terrainEndX ||
		z > _terrainStartZ || z < _terrainEndZ)
	{
		return 0.0f;
	}


	//Terrain �� �»�� 0 �� �������� ���� Terrain �� ������ ��ġ�� ã��
	float pX = x - _terrainStartX;
	float pZ = -(z + _terrainEndZ);

	//�ش� ��ġ�� ��� ���� ���ԵǴ��� �ľ�
	float invCell = 1.0f / _cellScale;
	pX *= invCell;
	pZ *= invCell;

	//�ش� ��ġ�� �� �ε���
	int idxX = static_cast<int>(pX);
	int idxZ = static_cast<int>(pZ);

	//���� �ױ��� ������ ��´�.
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

	//�ش� �������� delta ���� ���Ѵ�.
	float dX = pX - static_cast<float>(idxX);
	float dZ = pZ - static_cast<float>(idxZ);

	float height = 0.0f;

	//�ش� ���� �»�ܿ� �ִ�?
	if (dX < 1.0f - dZ)
	{
		float deltaU = rt.y - lt.y;		//lt �������� rt ���������� y ��ġ�� ������
		float deltaV = lb.y - lt.y;		//lt �������� lb ���������� y ��ġ�� ������

		height = lt.y + (deltaU * dX) + (deltaV * dZ);
	}

	//�ش� ���� ���ϴ��� �ִ�?
	else
	{
		float deltaU = lb.y - rb.y;
		float deltaV = rt.y - rb.y;


		//�쿡�� �·� �Ͽ��� ������ ���������� �ٲ���� ������
		//delta ���� ������ ���Ѵ�.
		dX = 1.0f - dX;
		dZ = 1.0f - dZ;

		height = rb.y + (deltaU * dX) + (deltaV * dZ);
	}

	return height;
}



D3DXVECTOR2 terrain::getIdx(float x, float z)
{
	//�ͷ��� ������ �Ѿ�� 0.0 ���� �����Ѵ�
	if (x < _terrainStartX || x > _terrainEndX ||
		z > _terrainStartZ || z < _terrainEndZ)
	{
		return  D3DXVECTOR2(0.0f, 0.0f);
	}

	//Terrain �� �»�� 0 �� �������� ���� Terrain �� ������ ��ġ�� ã��
	float pX = x - _terrainStartX;
	float pZ = -(z + _terrainEndZ);

	//�ش� ��ġ�� ��� ���� ���ԵǴ��� �ľ�
	float invCell = 1.0f / _cellScale;
	pX *= invCell;
	pZ *= invCell;

	//�ش� ��ġ�� �� �ε���
	int idxX = static_cast<int>(pX);
	int idxZ = static_cast<int>(pZ);

	return D3DXVECTOR2(idxX, idxZ);
}



//�ش� X, Z ��ġ�� ��� ���͸� ��´�.
bool terrain::getSlant(D3DXVECTOR3 * pOut, float gravityPower, float x, float z)
{
	//�ͷ��� ������ �Ѿ�� 0.0 ���� �����Ѵ�
	if (x < _terrainStartX || x > _terrainEndX ||
		z > _terrainStartZ || z < _terrainEndZ)
	{
		return false;
	}


	//Terrain �� �»�� 0 �� �������� ���� Terrain �� ������ ��ġ�� ã��
	float pX = x - _terrainStartX;
	float pZ = -(z + _terrainEndZ);

	//�ش� ��ġ�� ��� ���� ���ԵǴ��� �ľ�
	float invCell = 1.0f / _cellScale;
	pX *= invCell;
	pZ *= invCell;


	//�ش� ��ġ�� �� �ε���
	int idxX = static_cast<int>(pX);
	int idxZ = static_cast<int>(pZ);

	//���� �ױ��� ������ ��´�.
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

	//�ش� �п����� delta ���� ���Ѵ�.
	float dX = pX - static_cast<float>(idxX);
	float dZ = pZ - static_cast<float>(idxZ);


	float fHeight = 0.0f;

	//�������� �븻 ����
	D3DXVECTOR3 normal;

	//�ش� ���� �»�ܿ� �ִ�?
	if (dX < 1.0f - dZ)
	{
		//�ش��������� ���� ���͸� ���Ѵ�.
		D3DXVECTOR3 edge1 = rt - lt;
		D3DXVECTOR3 edge2 = lb - lt;
		D3DXVec3Cross(&normal, &edge1, &edge2);
	}

	//�ش� ���� ���ϴ��� �ִ�?
	else
	{
		//�ش��������� ���� ���͸� ���Ѵ�.
		D3DXVECTOR3 edge1 = rt - lb;
		D3DXVECTOR3 edge2 = rb - lb;
		D3DXVec3Cross(&normal, &edge1, &edge2);
	}

	//�븻�� ����ȭ
	D3DXVec3Normalize(&normal, &normal);


	//�߷� ����
	D3DXVECTOR3 gravity(0, -gravityPower, 0);

	//������ ����
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &normal, &gravity);

	//�������Ϳ��� �������͸� ������ ����� ������ ��� ������ �ȴ�.
	D3DXVec3Cross(pOut, &right, &normal);

	return true;
}



//���� ���� �����
HRESULT terrain::createTerrain(int tileNum)
{
	// ���� ��ġ ���Ѵ�.

	//Ÿ�ϸ� ������ ���� ���� (������ uv ����)
	float tileIntervalX = static_cast<float>(tileNum) / _cellNumX;
	float tileIntervalY = static_cast<float>(tileNum) / _cellNumZ;

	//���� ���� ������ �־�� �Ѵ�.
	_terrainVertices = new TERRAINVERTEX[_totalVerNum];

	//�ؽ����� pixel ������ ��� ���� Texture �� lock �Ѵ�.
	D3DLOCKED_RECT lockRect;
	_heightMap->LockRect(
		0,					//lock �� �� �Ӹ� ���� 0
		&lockRect,			//lock ���� ���� D3DLOCKED_RECT ���� ����ü
		0,					//lock �� �Ϻ� ������ �ϰ� ���� ��� �簢��RECT ����ü�� �����͸� �ִµ� ��ü �Ҳ��� NULL
		0					//lock �÷��� �ϴ� 0
	);

	//lockRect->Pitch	lock �� �� ���� �̹����� ���� byte ũ�� 
	//(���� ����Ʈũ��� ������ �����Ѵ� pitch % 4 == 0 ) < 3byte �÷��� pitch byte ���ϴ� ���� ( ���� �ȼ��� * 3 + 3 ) & ~3 = pitch  >
	//lockRect->pBits	�̹��������Ͱ� ���۵Ǵ� ������ �ּ�

	//������ġ�� ���� UV �� ����ϱ�
	for (int z = 0; z < _verNumZ; z++)
	{
		for (int x = 0; x < _verNumX; x++)
		{
			D3DXVECTOR3 pos;

			//������ x, z ��ġ ���
			pos.x = (x - (_cellNumX * 0.5)) * _cellScale;
			pos.z = (-z + (_cellNumZ * 0.5)) * _cellScale;

			//���θ����� �����̶�� (���� ������ ���� Y ��ġ�� �����)
			if (x == _verNumX - 1)
			{
				int idx = z * _verNumX + x - 1;
				pos.y = _terrainVertices[idx].pos.y;
			}

			//���� ������ �����̶�� (���� ������ ���� Y ��ġ�� �����)
			else if (z == _verNumZ - 1)
			{
				int idx = (z - 1) * _verNumX + x;
				pos.y = _terrainVertices[idx].pos.y;
			}
			else
			{
				//�ش� �ȼ��� �÷� ���� ��´�.
				DWORD* pStart = (DWORD*)lockRect.pBits;	//(DWORD ������ ����ȯ�� lock �� �̹������� ���� �ּ�
				DWORD dwColor = *(pStart + (z * (lockRect.Pitch / 4) + x));

				//�� �÷� ���� 0 ~ 1 ������ �Ǽ��� ������.
				float inv = 1.0f / 255.0f;
				float r = ((dwColor & 0x00ff0000) >> 16) * inv;
				float g = ((dwColor & 0x0000ff00) >> 8) * inv;
				float b = ((dwColor & 0x000000ff)) * inv;

				//���� �� ��
				float factor = (r + g + b) / 3.0f;

				//���� ��
				pos.y = factor * _heightScale;
			}

			//���� UV ���

			//Terrain Tile Splating UV
			D3DXVECTOR2 baseUV;
			baseUV.x = x / static_cast<float>(_verNumX - 1);
			baseUV.y = z / static_cast<float>(_verNumZ - 1);

			//Terrain Tile UV
			D3DXVECTOR2 tileUV;
			tileUV.x = x * tileIntervalX;
			tileUV.y = z * tileIntervalY;

			//���ؽ� �迭�ε��� ���
			int idx = z * _verNumX + x;

			_terrainVertices[idx].pos = pos;
			_terrainVertices[idx].normal = D3DXVECTOR3(0, 0, 0);	//�Ʒ����� ���� �븻 ���Ҷ� �������� �ϴ� 0 ���ͷ� �ʱ�ȭ
			_terrainVertices[idx].baseUV = baseUV;
			_terrainVertices[idx].tileUV = tileUV;

			_vecPos.push_back(pos);
		}
	}

	//�ؽ����� pixel ���� Unlock
	_heightMap->UnlockRect(0);

	//���� ������ 
	if (_isSmoothing)
	{
		this->smoothTerrain();
	}

	// ���� �ε����� ���Ѵ�
	LPTERRAINTRI pIndices = new tagTERRAINTRI[_totalTriangle];

	//�ε��� �迭 �ε���
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

			//�ش� ���� ���� ���� �ε����� ����
			DWORD lt = z * _verNumX + x;
			DWORD rt = z * _verNumX + x + 1;
			DWORD lb = ((z + 1)* _verNumX) + x;
			DWORD rb = ((z + 1)* _verNumX) + x + 1;

			//���� �ﰢ�� �ϳ�
			pIndices[idx].dw0 = lt;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = lb;
			idx++;

			//���� �ﰢ�� �ϳ�
			pIndices[idx].dw0 = lb;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = rb;
			idx++;
		}
	}

	// �븻�̶� Binormal �̶� Tangent ����ϱ�
	D3DXVECTOR3* poses = new D3DXVECTOR3[_totalVerNum];		//������ġ
	D3DXVECTOR3* normals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* tangents = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* binormals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR2* uvs = new D3DXVECTOR2[_totalVerNum];
	DWORD* indices = (DWORD*)pIndices;

	//������ġ �� UV ����
	for (int i = 0; i < _totalVerNum; i++)
	{
		poses[i] = _terrainVertices[i].pos;
		uvs[i] = _terrainVertices[i].baseUV;
	}

	//�븻���
	ComputeNormal(normals, poses, _totalVerNum, indices, _totalTriangle * 3);

	//ź��Ʈ ���̳븻 ���
	ComputeTangentBinormal(
		tangents,
		binormals,
		poses,
		normals,
		uvs,
		indices,
		_totalTriangle,
		_totalVerNum);

	//���Ȱ� ����
	for (int i = 0; i < _totalVerNum; i++)
	{
		_terrainVertices[i].normal = normals[i];
		_terrainVertices[i].binormal = binormals[i];
		_terrainVertices[i].tangent = tangents[i];
	}

	// ���� ����
	//�������� �����
	_device->CreateVertexBuffer(
		sizeof(TERRAINVERTEX) * _totalVerNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&_terrainVb,
		0);

	//������� ���� ���۸� Lock �Ͽ� ���� ���� ���� ����.
	void* p = NULL;
	_terrainVb->Lock(0, 0, &p, 0);
	memcpy(p, _terrainVertices, sizeof(TERRAINVERTEX) * _totalVerNum);
	_terrainVb->Unlock();

	//�ε��� ���� �����
	_device->CreateIndexBuffer(
		sizeof(TERRAINTRI) * _totalTriangle,
		D3DUSAGE_WRITEONLY,	//D3DUSAGE_WRITEONLY ���� �����ϰ� ���������� ���۳����� �����ɶ� �ְ����� ����, D3DUSAGE_DYNAMIC �� �� �����Ͽ� ���� ������ �ٲ�� ���
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,	//D3DUSAGE_DYNAMIC �� ������ ������ D3DPOOL_DEFAULT
		&_terrainIb,
		0);

	//�ε��� ���ۿ� ���� ����.
	_terrainIb->Lock(0, 0, &p, 0);
	memcpy(p, pIndices, sizeof(TERRAINTRI) * _totalTriangle);
	_terrainIb->Unlock();

	// ���� ����θ� �����.
	//������ ���¸� �˷��ִ� �迭
	D3DVERTEXELEMENT9 vertElement[7];	//�迭�� �������� ���� + 1

										//Position 
	vertElement[0].Stream = 0;							//Stream �� 0
	vertElement[0].Offset = 0;							//�޸��� ���� Byte ���� 0
	vertElement[0].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[0].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[0].Usage = D3DDECLUSAGE_POSITION;		//���� Ÿ��
	vertElement[0].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//Normal
	vertElement[1].Stream = 0;							//Stream �� 0
	vertElement[1].Offset = 12;							//�޸��� ���� Byte ���� 0
	vertElement[1].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[1].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[1].Usage = D3DDECLUSAGE_NORMAL;			//���� Ÿ��
	vertElement[1].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//BiNormal
	vertElement[2].Stream = 0;							//Stream �� 0
	vertElement[2].Offset = 24;							//�޸��� ���� Byte ���� 0
	vertElement[2].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[2].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[2].Usage = D3DDECLUSAGE_BINORMAL;		//���� Ÿ��
	vertElement[2].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//Tangent
	vertElement[3].Stream = 0;							//Stream �� 0
	vertElement[3].Offset = 36;							//�޸��� ���� Byte ���� 0
	vertElement[3].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[3].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[3].Usage = D3DDECLUSAGE_TANGENT;		//���� Ÿ��
	vertElement[3].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//BaseUV
	vertElement[4].Stream = 0;							//Stream �� 0
	vertElement[4].Offset = 48;							//�޸��� ���� Byte ���� 0
	vertElement[4].Type = D3DDECLTYPE_FLOAT2;			//�ڷ��� Ÿ��
	vertElement[4].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[4].Usage = D3DDECLUSAGE_TEXCOORD;		//���� Ÿ��
	vertElement[4].UsageIndex = 0;						//UsageIndex �ϴ� 0


														//tileUV
	vertElement[5].Stream = 0;							//Stream �� 0
	vertElement[5].Offset = 56;							//�޸��� ���� Byte ���� 0
	vertElement[5].Type = D3DDECLTYPE_FLOAT2;			//�ڷ��� Ÿ��
	vertElement[5].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[5].Usage = D3DDECLUSAGE_TEXCOORD;		//���� Ÿ��
	vertElement[5].UsageIndex = 1;						//UsageIndex �ι�° UV 1 

														//���̻� ������ ����
	D3DVERTEXELEMENT9 end = D3DDECL_END(); //{0xFF,0,D3DDECLTYPE_UNUSED,0,0,0}
	vertElement[6] = end;



	// LPDIRECT3DVERTEXDECLARATION9 ����
	_device->CreateVertexDeclaration(
		vertElement,			//�տ��� ���� D3DVERTEXELEMENT9 �迭 ������
		&_terrainDecl			//���� LPDIRECT3DVERTEXDECLARATION9 ������
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

	//���� ������
	if (_isSmoothing)
	{
		smoothChangeTerrainHt(terrainX, terrainZ);
	}

	//���ۿ� �� void�� �Լ� ����.
	void* pVertices = NULL;

	//���ؽ� ���۸� ���� �ϸ鼭 ���� �Լ��� ���Ѵ�.
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



//���� ������
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
				int adjacentSections = 0;		//��� ������ ��հ��� ����?
				float totalSections = 0.0f;		//�ֺ��� ���� ���� ������ �󸶴�?

												//����üũ
				if ((x - 1) > 0)
				{
					totalSections += _terrainVertices[(z * _verNumX) + (x - 1)].pos.y;
					adjacentSections++;
					//���� ���
					if ((z - 1) > 0)
					{
						totalSections += _terrainVertices[((z - 1) * _verNumX) + (x - 1)].pos.y;
						adjacentSections++;
					}
					//���� �ϴ�
					if ((z + 1) < _verNumZ)
					{
						totalSections += _terrainVertices[((z + 1) * _verNumX) + (x - 1)].pos.y;
						adjacentSections++;
					}
				}
				//������ üũ
				if ((x + 1) < _verNumX)
				{
					totalSections += _terrainVertices[(z * _verNumX) + (x + 1)].pos.y;
					adjacentSections++;

					//������ ���
					if ((z - 1) > 0)
					{
						totalSections += _terrainVertices[((z - 1) * _verNumX) + (x + 1)].pos.y;
						adjacentSections++;
					}
					//������ �ϴ� 
					if ((z + 1) < _verNumZ) {
						totalSections += _terrainVertices[((z + 1) * _verNumX) + (x + 1)].pos.y;
						adjacentSections++;
					}
				}
				//���
				if ((z - 1) > 0)
				{
					totalSections += _terrainVertices[((z - 1) * _verNumX) + x].pos.y;
					adjacentSections++;
				}
				//�ϴ�
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

		//������ ���� y ������ ����
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
				int adjacentSections = 0;		//��� ������ ��հ��� ����?
				float totalSections = 0.0f;		//�ֺ��� ���� ���� ������ �󸶴�?

				if (x >= 0 && x < _verNumX && z >= 0 && z < _verNumZ)
				{
					//����üũ
					if ((x - 1) > 0)
					{
						totalSections += _terrainVertices[(z * _verNumX) + (x - 1)].pos.y;
						adjacentSections++;
						//���� ���
						if ((z - 1) > 0)
						{
							totalSections += _terrainVertices[((z - 1) * _verNumX) + (x - 1)].pos.y;
							adjacentSections++;
						}
						//���� �ϴ�
						if ((z + 1) < _verNumZ)
						{
							totalSections += _terrainVertices[((z + 1) * _verNumX) + (x - 1)].pos.y;
							adjacentSections++;
						}
					}
					//������ üũ
					if ((x + 1) < _verNumX)
					{
						totalSections += _terrainVertices[(z * _verNumX) + (x + 1)].pos.y;
						adjacentSections++;

						//������ ���
						if ((z - 1) > 0)
						{
							totalSections += _terrainVertices[((z - 1) * _verNumX) + (x + 1)].pos.y;
							adjacentSections++;
						}
						//������ �ϴ� 
						if ((z + 1) < _verNumZ) {
							totalSections += _terrainVertices[((z + 1) * _verNumX) + (x + 1)].pos.y;
							adjacentSections++;
						}
					}
					//���
					if ((z - 1) > 0)
					{
						totalSections += _terrainVertices[((z - 1) * _verNumX) + x].pos.y;
						adjacentSections++;
					}
					//�ϴ�
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

	//�ؽ����� pixel ������ ��� ���� Texture �� lock �Ѵ�.
	D3DLOCKED_RECT lockRect;
	tempSplat->LockRect(0, &lockRect, 0, 0);

	//�ش� �ȼ��� �÷� ���� ��´�.

	//(DWORD ������ ����ȯ�� lock �� �̹������� ���� �ּ�
	DWORD* pStart = (DWORD*)lockRect.pBits;
	DWORD dwColor = *(pStart + (z * (lockRect.Pitch / 4) + x));

	float r = (dwColor & 0x00ff0000) >> 16;
	float g = (dwColor & 0x0000ff00) >> 8;
	float b = (dwColor & 0x000000ff);

	//�ؽ����� pixel ���� Unlock
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
//���� ���̰� �ǽð� ���� �귯�� ��� -> ������ ����� ���Ҿ� �°� ����...
//=========================================================================

HRESULT terrain::changeHeightTerrain()
{
	// ���� ��ġ ���Ѵ�.

	//Ÿ�ϸ� ������ ���� ���� (������ uv ����)
	float tileIntervalX = static_cast<float>(_tileNum) / _cellNumX;
	float tileIntervalY = static_cast<float>(_tileNum) / _cellNumZ;

	//���� ���� ������ �־�� �Ѵ�.
	_terrainVertices = new TERRAINVERTEX[_totalVerNum];

	//�ؽ����� pixel ������ ��� ���� Texture �� lock �Ѵ�.
	D3DLOCKED_RECT lockRect;
	_heightMap->LockRect(
		0,					//lock �� �� �Ӹ� ���� 0
		&lockRect,			//lock ���� ���� D3DLOCKED_RECT ���� ����ü
		0,					//lock �� �Ϻ� ������ �ϰ� ���� ��� �簢��RECT ����ü�� �����͸� �ִµ� ��ü �Ҳ��� NULL
		0					//lock �÷��� �ϴ� 0
	);

	//lockRect->Pitch	lock �� �� ���� �̹����� ���� byte ũ�� (���� ����Ʈũ��� ������ �����Ѵ� pitch % 4 == 0 ) < 3byte �÷��� pitch byte ���ϴ� ���� ( ���� �ȼ��� * 3 + 3 ) & ~3 = pitch  >
	//lockRect->pBits	�̹��������Ͱ� ���۵Ǵ� ������ �ּ�

	//������ġ�� ���� UV �� ����ϱ�
	for (int z = 0; z < _verNumZ; z++)
	{
		for (int x = 0; x < _verNumX; x++)
		{
			D3DXVECTOR3 pos;

			//���ؽ� �迭�ε��� ���
			int idx = z * _verNumX + x;

			pos = _vecPos[idx];

			//���� UV ���

			//Terrain Tile Splating UV
			D3DXVECTOR2 baseUV;
			baseUV.x = x / static_cast<float>(_verNumX - 1);
			baseUV.y = z / static_cast<float>(_verNumZ - 1);

			//Terrain Tile UV
			D3DXVECTOR2 tileUV;
			tileUV.x = x * tileIntervalX;
			tileUV.y = z * tileIntervalY;


			_terrainVertices[idx].pos = pos;
			_terrainVertices[idx].normal = D3DXVECTOR3(0, 0, 0);	//�Ʒ����� ���� �븻 ���Ҷ� �������� �ϴ� 0 ���ͷ� �ʱ�ȭ
			_terrainVertices[idx].baseUV = baseUV;
			_terrainVertices[idx].tileUV = tileUV;

			_vecPos.push_back(pos);
		}
	}

	//�ؽ����� pixel ���� Unlock
	_heightMap->UnlockRect(0);

	//���� ������ 
	this->smoothTerrain();


	// ���� �ε����� ���Ѵ�
	LPTERRAINTRI pIndices = new tagTERRAINTRI[_totalTriangle];

	//�ε��� �迭 �ε���
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

			//�ش� ���� ���� ���� �ε����� ����
			DWORD lt = z * _verNumX + x;
			DWORD rt = z * _verNumX + x + 1;
			DWORD lb = ((z + 1)* _verNumX) + x;
			DWORD rb = ((z + 1)* _verNumX) + x + 1;

			//���� �ﰢ�� �ϳ�
			pIndices[idx].dw0 = lt;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = lb;
			idx++;

			//���� �ﰢ�� �ϳ�
			pIndices[idx].dw0 = lb;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = rb;
			idx++;
		}
	}

	// �븻�̶� Binormal �̶� Tangent ����ϱ�
	D3DXVECTOR3* poses = new D3DXVECTOR3[_totalVerNum];		//������ġ
	D3DXVECTOR3* normals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* tangents = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* binormals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR2* uvs = new D3DXVECTOR2[_totalVerNum];
	DWORD* indices = (DWORD*)pIndices;

	//������ġ �� UV ����
	for (int i = 0; i < _totalVerNum; i++)
	{
		poses[i] = _terrainVertices[i].pos;
		uvs[i] = _terrainVertices[i].baseUV;
	}

	//�븻���
	ComputeNormal(normals, poses, _totalVerNum, indices, _totalTriangle * 3);

	//ź��Ʈ ���̳븻 ���
	ComputeTangentBinormal(
		tangents,
		binormals,
		poses,
		normals,
		uvs,
		indices,
		_totalTriangle,
		_totalVerNum);

	//���Ȱ� ����
	for (int i = 0; i < _totalVerNum; i++)
	{
		_terrainVertices[i].normal = normals[i];
		_terrainVertices[i].binormal = binormals[i];
		_terrainVertices[i].tangent = tangents[i];
	}

	// ���� ����
	//�������� �����
	_device->CreateVertexBuffer(
		sizeof(TERRAINVERTEX) * _totalVerNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&_terrainVb,
		0);

	//������� ���� ���۸� Lock �Ͽ� ���� ���� ���� ����.
	void* p = NULL;
	_terrainVb->Lock(0, 0, &p, 0);
	memcpy(p, _terrainVertices, sizeof(TERRAINVERTEX) * _totalVerNum);
	_terrainVb->Unlock();

	//�ε��� ���� �����
	_device->CreateIndexBuffer(
		sizeof(TERRAINTRI) * _totalTriangle,
		D3DUSAGE_WRITEONLY,	//D3DUSAGE_WRITEONLY ���� �����ϰ� ���������� ���۳����� �����ɶ� �ְ����� ����, D3DUSAGE_DYNAMIC �� �� �����Ͽ� ���� ������ �ٲ�� ���
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,	//D3DUSAGE_DYNAMIC �� ������ ������ D3DPOOL_DEFAULT
		&_terrainIb,
		0);

	//�ε��� ���ۿ� ���� ����.
	_terrainIb->Lock(0, 0, &p, 0);
	memcpy(p, pIndices, sizeof(TERRAINTRI) * _totalTriangle);
	_terrainIb->Unlock();

	// ���� ����θ� �����.
	//������ ���¸� �˷��ִ� �迭
	D3DVERTEXELEMENT9 vertElement[7];	//�迭�� �������� ���� + 1

										//Position 
	vertElement[0].Stream = 0;							//Stream �� 0
	vertElement[0].Offset = 0;							//�޸��� ���� Byte ���� 0
	vertElement[0].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[0].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[0].Usage = D3DDECLUSAGE_POSITION;		//���� Ÿ��
	vertElement[0].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//Normal
	vertElement[1].Stream = 0;							//Stream �� 0
	vertElement[1].Offset = 12;							//�޸��� ���� Byte ���� 0
	vertElement[1].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[1].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[1].Usage = D3DDECLUSAGE_NORMAL;			//���� Ÿ��
	vertElement[1].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//BiNormal
	vertElement[2].Stream = 0;							//Stream �� 0
	vertElement[2].Offset = 24;							//�޸��� ���� Byte ���� 0
	vertElement[2].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[2].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[2].Usage = D3DDECLUSAGE_BINORMAL;		//���� Ÿ��
	vertElement[2].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//Tangent
	vertElement[3].Stream = 0;							//Stream �� 0
	vertElement[3].Offset = 36;							//�޸��� ���� Byte ���� 0
	vertElement[3].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[3].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[3].Usage = D3DDECLUSAGE_TANGENT;		//���� Ÿ��
	vertElement[3].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//BaseUV
	vertElement[4].Stream = 0;							//Stream �� 0
	vertElement[4].Offset = 48;							//�޸��� ���� Byte ���� 0
	vertElement[4].Type = D3DDECLTYPE_FLOAT2;			//�ڷ��� Ÿ��
	vertElement[4].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[4].Usage = D3DDECLUSAGE_TEXCOORD;		//���� Ÿ��
	vertElement[4].UsageIndex = 0;						//UsageIndex �ϴ� 0


														//tileUV
	vertElement[5].Stream = 0;							//Stream �� 0
	vertElement[5].Offset = 56;							//�޸��� ���� Byte ���� 0
	vertElement[5].Type = D3DDECLTYPE_FLOAT2;			//�ڷ��� Ÿ��
	vertElement[5].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[5].Usage = D3DDECLUSAGE_TEXCOORD;		//���� Ÿ��
	vertElement[5].UsageIndex = 1;						//UsageIndex �ι�° UV 1 

														//���̻� ������ ����
	D3DVERTEXELEMENT9 end = D3DDECL_END(); //{0xFF,0,D3DDECLTYPE_UNUSED,0,0,0}
	vertElement[6] = end;



	// LPDIRECT3DVERTEXDECLARATION9 ����
	_device->CreateVertexDeclaration(
		vertElement,			//�տ��� ���� D3DVERTEXELEMENT9 �迭 ������
		&_terrainDecl			//���� LPDIRECT3DVERTEXDECLARATION9 ������
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
	//�귯������ ���μ��� ������ ����
	int brushIdxX = brush_verNumX / 2;
	int brushIdxZ = brush_verNumZ / 2;

	//�귯������ �»���� �ε����� ã��
	int idxX = getIdx(cursorX, cursorZ).x - brushIdxX;
	int idxZ = getIdx(cursorX, cursorZ).y - brushIdxZ;

	//�귯������ ���ϴ��� �ε����� ã��
	int idxX2 = getIdx(cursorX, cursorZ).x + brushIdxX;
	int idxZ2 = getIdx(cursorX, cursorZ).y + brushIdxZ;

	//������ġ�� ���� UV �� ����ϱ�
	for (int z = 0; z < _verNumZ; z++)
	{
		for (int x = 0; x < _verNumX; x++)
		{
			int idx = z * _verNumX + x;

			if (x >= idxX && x <= idxX2 &&
				z >= idxZ && z <= idxZ2)
			{
				//�귯���ʿ� ���� �ε�����ȣ
				int idx2 = (z - idxZ) * brush_verNumX + (x - idxX);
				_vecPos[idx].y +=_vecBrush[idx2] * _brushScale * _nHeightSign;
			}
			_terrainVertices[idx].pos = _vecPos[idx];
		}
	}

	////���� ������ 
	this->smoothTerrain();


	// ���� �ε����� ���Ѵ�
	LPTERRAINTRI pIndices = new tagTERRAINTRI[_totalTriangle];

	//�ε��� �迭 �ε���
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

			//�ش� ���� ���� ���� �ε����� ����
			DWORD lt = z * _verNumX + x;
			DWORD rt = z * _verNumX + x + 1;
			DWORD lb = ((z + 1)* _verNumX) + x;
			DWORD rb = ((z + 1)* _verNumX) + x + 1;

			//���� �ﰢ�� �ϳ�
			pIndices[idx].dw0 = lt;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = lb;
			idx++;

			//���� �ﰢ�� �ϳ�
			pIndices[idx].dw0 = lb;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = rb;
			idx++;
		}
	}

	// �븻�̶� Binormal �̶� Tangent ����ϱ�
	D3DXVECTOR3* poses = new D3DXVECTOR3[_totalVerNum];		//������ġ
	D3DXVECTOR3* normals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* tangents = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR3* binormals = new D3DXVECTOR3[_totalVerNum];
	D3DXVECTOR2* uvs = new D3DXVECTOR2[_totalVerNum];
	DWORD* indices = (DWORD*)pIndices;

	//������ġ �� UV ����
	for (int i = 0; i < _totalVerNum; i++)
	{
		poses[i] = _terrainVertices[i].pos;
		uvs[i] = _terrainVertices[i].baseUV;
	}

	//�븻���
	ComputeNormal(normals, poses, _totalVerNum, indices, _totalTriangle * 3);

	//ź��Ʈ ���̳븻 ���
	ComputeTangentBinormal(
		tangents,
		binormals,
		poses,
		normals,
		uvs,
		indices,
		_totalTriangle,
		_totalVerNum);

	//���Ȱ� ����
	for (int i = 0; i < _totalVerNum; i++)
	{
		_terrainVertices[i].normal = normals[i];
		_terrainVertices[i].binormal = binormals[i];
		_terrainVertices[i].tangent = tangents[i];
	}

	// ���� ����
	//�������� �����
	_device->CreateVertexBuffer(
		sizeof(TERRAINVERTEX) * _totalVerNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&_terrainVb,
		0);

	//������� ���� ���۸� Lock �Ͽ� ���� ���� ���� ����.
	void* p = NULL;
	_terrainVb->Lock(0, 0, &p, 0);
	memcpy(p, _terrainVertices, sizeof(TERRAINVERTEX) * _totalVerNum);
	_terrainVb->Unlock();

	//�ε��� ���� �����
	_device->CreateIndexBuffer(
		sizeof(TERRAINTRI) * _totalTriangle,
		D3DUSAGE_DYNAMIC,	//D3DUSAGE_WRITEONLY ���� �����ϰ� ���������� ���۳����� �����ɶ� �ְ����� ����, D3DUSAGE_DYNAMIC �� �� �����Ͽ� ���� ������ �ٲ�� ���
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,	//D3DUSAGE_DYNAMIC �� ������ ������ D3DPOOL_DEFAULT
		&_terrainIb,
		0);

	//�ε��� ���ۿ� ���� ����.
	_terrainIb->Lock(0, 0, &p, 0);
	memcpy(p, pIndices, sizeof(TERRAINTRI) * _totalTriangle);
	_terrainIb->Unlock();

	// ���� ����θ� �����.
	//������ ���¸� �˷��ִ� �迭
	D3DVERTEXELEMENT9 vertElement[7];	//�迭�� �������� ���� + 1

										//Position 
	vertElement[0].Stream = 0;							//Stream �� 0
	vertElement[0].Offset = 0;							//�޸��� ���� Byte ���� 0
	vertElement[0].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[0].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[0].Usage = D3DDECLUSAGE_POSITION;		//���� Ÿ��
	vertElement[0].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//Normal
	vertElement[1].Stream = 0;							//Stream �� 0
	vertElement[1].Offset = 12;							//�޸��� ���� Byte ���� 0
	vertElement[1].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[1].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[1].Usage = D3DDECLUSAGE_NORMAL;			//���� Ÿ��
	vertElement[1].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//BiNormal
	vertElement[2].Stream = 0;							//Stream �� 0
	vertElement[2].Offset = 24;							//�޸��� ���� Byte ���� 0
	vertElement[2].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[2].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[2].Usage = D3DDECLUSAGE_BINORMAL;		//���� Ÿ��
	vertElement[2].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//Tangent
	vertElement[3].Stream = 0;							//Stream �� 0
	vertElement[3].Offset = 36;							//�޸��� ���� Byte ���� 0
	vertElement[3].Type = D3DDECLTYPE_FLOAT3;			//�ڷ��� Ÿ��
	vertElement[3].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[3].Usage = D3DDECLUSAGE_TANGENT;		//���� Ÿ��
	vertElement[3].UsageIndex = 0;						//UsageIndex �ϴ� 0

														//BaseUV
	vertElement[4].Stream = 0;							//Stream �� 0
	vertElement[4].Offset = 48;							//�޸��� ���� Byte ���� 0
	vertElement[4].Type = D3DDECLTYPE_FLOAT2;			//�ڷ��� Ÿ��
	vertElement[4].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[4].Usage = D3DDECLUSAGE_TEXCOORD;		//���� Ÿ��
	vertElement[4].UsageIndex = 0;						//UsageIndex �ϴ� 0


														//tileUV
	vertElement[5].Stream = 0;							//Stream �� 0
	vertElement[5].Offset = 56;							//�޸��� ���� Byte ���� 0
	vertElement[5].Type = D3DDECLTYPE_FLOAT2;			//�ڷ��� Ÿ��
	vertElement[5].Method = D3DDECLMETHOD_DEFAULT;		//�ϴ� ������  D3DDECLMETHOD_DEFAULT
	vertElement[5].Usage = D3DDECLUSAGE_TEXCOORD;		//���� Ÿ��
	vertElement[5].UsageIndex = 1;						//UsageIndex �ι�° UV 1 

														//���̻� ������ ����
	D3DVERTEXELEMENT9 end = D3DDECL_END(); //{0xFF,0,D3DDECLTYPE_UNUSED,0,0,0}
	vertElement[6] = end;



	// LPDIRECT3DVERTEXDECLARATION9 ����
	_device->CreateVertexDeclaration(
		vertElement,			//�տ��� ���� D3DVERTEXELEMENT9 �迭 ������
		&_terrainDecl			//���� LPDIRECT3DVERTEXDECLARATION9 ������
	);

	SAFE_DELETE_ARRAY(poses);
	SAFE_DELETE_ARRAY(normals);
	SAFE_DELETE_ARRAY(tangents);
	SAFE_DELETE_ARRAY(binormals);
	SAFE_DELETE_ARRAY(uvs);
	SAFE_DELETE_ARRAY(indices);

	//����Ʈ���� �����.
	_quadTree = new quadTree;
	_quadTree->init(_terrainVertices, _verNumX);

	return S_OK;
}

void terrain::setBrushmap(string brushMapName)
{
	_brushMap = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath(brushMapName));

	D3DSURFACE_DESC sd;
	_brushMap->GetLevelDesc(0, &sd);

	brush_verNumX = sd.Width + 1;	//���� ���������� ���� �ʿ� ���� �ػ� + 1 �� ����. (������ ����Ʈ�������� ���������� 2��N�� + 1 �̿��� �ϱ� ������)
	brush_verNumZ = sd.Height + 1;	//���� ��������� ���� �ʿ� ���� �ػ� + 1 �� ����. (������ ����Ʈ�������� ���������� 2��N�� + 1 �̿��� �ϱ� ������)
	brush_totalotalVerNum = brush_verNumX * brush_verNumZ;	//�� ���� ����

															//���μ��� ����
	brush_cellNumX = brush_verNumX - 1;
	brush_cellNumZ = brush_verNumZ - 1;
	brush_totalCellNum = brush_cellNumX * brush_cellNumZ;

	//�ͷ��� ũ��
	brush_terrainSizeX = brush_cellNumX * _cellScale;
	brush_terrainSizeZ = brush_cellNumZ * _cellScale;

	D3DLOCKED_RECT lockRect;
	_brushMap->LockRect(0, &lockRect, 0, 0);

	for (int z = 0; z < brush_verNumZ; z++)
	{
		for (int x = 0; x < brush_verNumX; x++)
		{
			DWORD* pStart = (DWORD*)lockRect.pBits;	//(DWORD ������ ����ȯ�� lock �� �̹������� ���� �ּ�
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
