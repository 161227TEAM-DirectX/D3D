#include "stdafx.h"
#include "xMeshStatic.h"

LPD3DXEFFECT		xMeshStatic::_staticMeshEffect = NULL;
LPDIRECT3DTEXTURE9	xMeshStatic::_defDiffuseTex = NULL;
LPDIRECT3DTEXTURE9	xMeshStatic::_defNormalTex = NULL;
LPDIRECT3DTEXTURE9	xMeshStatic::_defSpecularTex = NULL;
LPDIRECT3DTEXTURE9	xMeshStatic::_defEmissionTex = NULL;

xMeshStatic::xMeshStatic()
{
	//���̴��� ����Ʈ�ؽ��� �ʱ�ȭ
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
	LPD3DXBUFFER pAdjacency = NULL;	//���� ����
	LPD3DXBUFFER pMaterial = NULL;	//���� ����

	//XFile �� ���� �޽��� �ҷ����� �Լ�
	if (FAILED(D3DXLoadMeshFromX(
		filePath.c_str(),			//X ���� �ε� ���...
		D3DXMESH_MANAGED,			//�޽� �ɼ� �ϴ� D3DXMESH_MANAGED ��....
		_device,					//����̽�
		&pAdjacency,				//���� �������� ����
		&pMaterial,					//���� �������� ����
		NULL,						//Effect 
		&_materialsNum,				//�޽����� ���Ǵ� ���� ����
		&_mesh						//�޽�
	))) 
	{
		SAFE_RELEASE(pAdjacency);
		SAFE_RELEASE(pMaterial);
		return E_FAIL;
	}

	//�ε� ��ο��� ���ϸ� �����ϰ� ��θ� �޴´�.
	string path;
	int lastPathIndex = 0;		//������ \ �� ��ġ

	//filePath.find_first_of( 'A' ); filePath ���ڿ��� 'A' �� ����ִ� ��ġ ���� (�տ��� ���� �˻�)
	lastPathIndex = filePath.find_last_of('/'); //�ڿ��� ���� �˻�
	if (lastPathIndex == -1) 
	{	//��ã���� -1 �� ����
		lastPathIndex = filePath.find_last_of('\\'); //��� ������ �ϴ� / �� ��ã���� \ �� ã�´�.
	}
	//��� ������ �ִٸ�...
	if (lastPathIndex != -1) 
	{
		//filePath.substr( /*������ġ*/, /*����*/ );
		path = filePath.substr(0, lastPathIndex + 1);
	}

	//Texture �ε��� �ʿ��� ���ڿ���..
	string texFilePath;		//���� ���...
	string texExp;			//���� Ȯ���� ��
	string texFile;			//���� ��	

	//���� ������ ��´�
	LPD3DXMATERIAL	pMaterials = (LPD3DXMATERIAL)pMaterial->GetBufferPointer();

	//����������ŭ for ������ �����糤��.
	for (DWORD i = 0; i < _materialsNum; i++) 
	{
		//�ε�� ���͸���
		D3DMATERIAL9 mtrl = pMaterials[i].MatD3D;

		//�޽��� ���͸��󿡴� Ambient ������ ������
		//Diffuse ������ �����ϰ� ����..
		mtrl.Ambient = mtrl.Diffuse;

		//���͸��� ���� Ǫ��
		_vecMaterials.push_back(mtrl);

		//���͸����� Texture ������ �ִٸ�..
		if (pMaterials[i].pTextureFilename != NULL) 
		{
			//tex ���ϰ�δ� Mesh ���ϰ�� + texture �����̸�
			texFilePath = path + pMaterials[i].pTextureFilename;

			//Texture �ε��ϰ� Ǫ��
			_vecDiffuseTex.push_back(RM_TEXTURE->getResource(texFilePath));

			//���� �̸��� Ȯ���� ��ġ
			int dotIndex = texFilePath.find_last_of(".");

			//���� ��� Ȯ���ڸ� ������.
			texFile = texFilePath.substr(0, dotIndex);
			texExp = texFilePath.substr(dotIndex + 1, filePath.length());

			//
			// �븻�� ���� _N �� �ٴ´�.
			//
			texFilePath = texFile + "_N." + texExp;
			LPDIRECT3DTEXTURE9 pNorTex = RM_TEXTURE->getResource(texFilePath);
			//���ٸ�...
			if (pNorTex == NULL) _vecNormalTex.push_back(_defNormalTex);
			else _vecNormalTex.push_back(pNorTex);

			//
			// ����ŧ�� ���� _S �� �ٴ´�.
			//
			texFilePath = texFile + "_S." + texExp;
			LPDIRECT3DTEXTURE9 pSpecTex = RM_TEXTURE->getResource(texFilePath);
			//���ٸ�...
			if (pSpecTex == NULL) _vecSpecularTex.push_back(_defSpecularTex);
			else _vecSpecularTex.push_back(pSpecTex);

			//
			// �̹̼� ���� _E �� �ٴ´�.
			//
			texFilePath = texFile + "_E." + texExp;
			LPDIRECT3DTEXTURE9 pEmiTex = RM_TEXTURE->getResource(texFilePath);
			//���ٸ�...
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

	//���� ���� ������ �� ����Ͽ� ������ Texture �� �ε� �߱⶧���� 
	//���̻� pMaterial ���� ���۴� �ʿ� ���� �� �޸� ������ ���־�� �Ѵ�.
	SAFE_RELEASE(pMaterial);

	//�޽� ����ȭ (���� ���۸� �̿��Ͽ� �޽��� ����ȭ �Ѵ�)
	_mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |		//�޽� ����¼������ ���� (DrawSubset ȿ���� ���δ� 
		D3DXMESHOPT_COMPACT |		//�޽����� ������ �ʴ� ������ �ε��� ����
		D3DXMESHOPT_VERTEXCACHE,	//���� Cache ��Ʈ�� ������.
		(DWORD*)pAdjacency->GetBufferPointer(),	//�������� �Ѱܾ� �Ѵ�.
		NULL,			//����ȭ�� ������ ����� ��� �������� (���̻� �ʿ������ NULL)
		NULL,			//����ȭ�� �ε��� ����
		NULL			//����ȭ�� ���� ���� ���� 
	);

	//����ȭ�� �������� ����
	SAFE_RELEASE(pAdjacency);

	//
	// �޽� ���� ó��
	//
	//��������� �޾Ҵٸ�..
	if (matCorrection) 
	{
		scale = fabsf(matCorrection->_11);
		meshCorrection(matCorrection);
	}
	else 
	{
		//��������� ������ ����ó�����ؾ� Bound ������ ������ �ִ�.
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
	//������� ����
	D3DXMATRIXA16 matWorld = trans->GetFinalMatrix();
	_staticMeshEffect->SetMatrix("matWorld", &matWorld);

	//���� ���� �ϴ�...
	D3DXVECTOR4 lightDir(1, -1, 1, 1);
	_staticMeshEffect->SetVector("vLightDir", &lightDir);

	//����Ʈ �÷� �ϴ� ���
	D3DXVECTOR4 lightColor(1, 1, 1, 1);
	_staticMeshEffect->SetVector("vLightColor", &lightColor);

	//Effect �� �׸��� ����
	_staticMeshEffect->SetTechnique("Mesh");

	UINT passNum;
	_staticMeshEffect->Begin(&passNum, 0);

	for (UINT i = 0; i < passNum; i++)
	{
		_staticMeshEffect->BeginPass(i);
		//����¼���ŭ ���� �糤��...
		for (int m = 0; m < _materialsNum; m++) 
		{
			//�ؽ��� ����
			_staticMeshEffect->SetTexture("Diffuse_Tex", _vecDiffuseTex[m]);
			_staticMeshEffect->SetTexture("Normal_Tex", _vecNormalTex[m]);
			_staticMeshEffect->SetTexture("Specular_Tex",_vecSpecularTex[m]);
			_staticMeshEffect->SetTexture("Emission_Tex",_vecEmissionTex[m]);
			//�����Ŀ�
			_staticMeshEffect->SetFloat("fSpecPower", _vecMaterials[m].Power);
			//Begin �� ������ ���� ���� �ٲ�� ������ ���� ����
			_staticMeshEffect->CommitChanges();
			//�޽��׸���
			_mesh->DrawSubset(m);
		}
		_staticMeshEffect->EndPass();
	}

	_staticMeshEffect->End();
}

void xMeshStatic::meshCorrection(D3DXMATRIXA16 * matCorrection)
{
	//���� Element �� ��� ���� ������ ����
	D3DVERTEXELEMENT9 pVerElement[MAX_FVF_DECL_SIZE];

	//pVerElement �迭���� ������ ��� ������ ���� �ȴ�.
	_mesh->GetDeclaration(pVerElement);

	//���� Position Offset;
	int positionOffset = -1;

	//���� Normal Offset;
	int normalOffet = -1;

	//���� Tangent Offset;
	int tangentOffet = -1;

	//���� Binormal Offset;
	int binormalOffet = -1;

	//�ϴ� �����糤��..
	for (DWORD i = 0; i < MAX_FVF_DECL_SIZE; i++) {

		//�������� �����ٸ�....
		if (pVerElement[i].Type == D3DDECLTYPE_UNUSED)
		{
			//Ż��
			break;
		}

		//������ġ ������ �����ٸ�....
		if (pVerElement[i].Usage == D3DDECLUSAGE_POSITION)
		{
			positionOffset = pVerElement[i].Offset;
		}

		//�����븻 ������ �����ٸ�...
		else if (pVerElement[i].Usage == D3DDECLUSAGE_NORMAL)
		{
			normalOffet = pVerElement[i].Offset;
		}

		//����ź��Ʈ ������ �����ٸ�...
		else if (pVerElement[i].Usage == D3DDECLUSAGE_TANGENT)
		{
			tangentOffet = pVerElement[i].Offset;
		}

		//�������̳븻 ������ �����ٸ�...
		else if (pVerElement[i].Usage == D3DDECLUSAGE_BINORMAL)
		{
			binormalOffet = pVerElement[i].Offset;
		}
	}

	//���ؽ� ����
	DWORD verNum = _mesh->GetNumVertices();

	//�޽��� ���� FVF ����Ȥ�� Decl ������ �̿��Ͽ� �����ϳ��� ũ�⸦ �˾Ƴ���.
	//DWORD verSize = D3DXGetFVFVertexSize( pMesh->GetFVF() );
	DWORD verSize = D3DXGetDeclVertexSize(pVerElement, 0);

	//�޽��� ���ؽ� ���۸� Lock �Ѵ�
	void* p = NULL;
	_mesh->LockVertexBuffer(0, &p);

	//�ٿ�� MinMax ����� ���� �ʱ�ȭ
	_boundMin = D3DXVECTOR3(0, 0, 0);
	_boundMax = D3DXVECTOR3(0, 0, 0);

	//���ؽ� ����Ŭ ���� �糤��
	for (DWORD i = 0; i < verNum; i++) {

		//���ؽ� ���� �ּ�
		char* pVertex = ((char*)p + (i * verSize));

		//���� ��ġ�� �ִٸ�
		if (positionOffset != -1) 
		{
			D3DXVECTOR3* pos = (D3DXVECTOR3*)(pVertex + positionOffset);

			D3DXVec3TransformCoord(pos, pos, matCorrection);

			//���� �ּ� ������
			if (_boundMin.x > pos->x)		_boundMin.x = pos->x;
			if (_boundMin.y > pos->y)		_boundMin.y = pos->y;
			if (_boundMin.z > pos->z)		_boundMin.z = pos->z;

			//���� �ִ� ������
			if (_boundMax.x < pos->x)		_boundMax.x = pos->x;
			if (_boundMax.y < pos->y)		_boundMax.y = pos->y;
			if (_boundMax.z < pos->z)		_boundMax.z = pos->z;

			//���� ��ġ Ǫ��
			_vertices.push_back(*pos);
		}

		//�븻������ �ִٸ�..
		if (normalOffet != -1) 
		{
			D3DXVECTOR3* nor = (D3DXVECTOR3*)(pVertex + normalOffet);
			D3DXVec3TransformNormal(nor, nor, matCorrection);
			D3DXVec3Normalize(nor, nor);
			//���� �븻 Ǫ��
			_normals.push_back(*nor);
		}

		//tangent ������ �ִٸ�.
		if (tangentOffet != -1) 
		{
			D3DXVECTOR3* tangent = (D3DXVECTOR3*)(pVertex + tangentOffet);
			D3DXVec3TransformNormal(tangent, tangent, matCorrection);
			D3DXVec3Normalize(tangent, tangent);
		}

		//binormal ������ �ִٸ�
		if (binormalOffet != -1) 
		{
			D3DXVECTOR3* binor = (D3DXVECTOR3*)(pVertex + binormalOffet);
			D3DXVec3TransformNormal(binor, binor, matCorrection);
			D3DXVec3Normalize(binor, binor);
		}
	}
	_mesh->UnlockVertexBuffer();

	//Bound �߰� ���
	_boundCenter = (_boundMin + _boundMax) * 0.5f;
	_boundSize = D3DXVECTOR3( 
		_boundMax.x - _boundMin.x,
		_boundMax.y - _boundMin.y,
		_boundMax.z - _boundMin.z);
	_boundHalfSize = _boundSize * 0.5f;
	_boundRadius = D3DXVec3Length(&(_boundCenter - _boundMin));

	//
	// �ε��� ���۸� ��´�
	//
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	_mesh->GetIndexBuffer(&pIndexBuffer);

	//���� ����
	_triNum = _mesh->GetNumFaces();

	//�ε��� ���ۿ� ���� ������ ��´�.
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

	//���� �ε��� ���۴� ����
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

//������ ����
void xMeshStatic::setLighting(light ** pLights, int lightNum)
{
	//����Ʈ ��� ����
	D3DXMATRIXA16 matLight[10];
	for (int i = 0; i < lightNum; i++)
	{
		matLight[i] = pLights[i]->getLightMatrix();
	}
	//Effect�� ������ ����
	_staticMeshEffect->SetMatrixArray("matLights", matLight, 10);
	_staticMeshEffect->SetInt("LightNum", lightNum);
}

void xMeshStatic::setLighting(std::vector<light*>* pLights)
{
	//����Ʈ ��� ����
	D3DXMATRIXA16 matLight[10];
	for (int i = 0; i < pLights->size(); i++)
	{
		matLight[i] = (*(pLights))[i]->getLightMatrix();
	}
	//Effect�� ������ ����
	_staticMeshEffect->SetMatrixArray("matLights", matLight, 10);
	_staticMeshEffect->SetInt("LightNum", pLights->size());
}

//technique ����
void xMeshStatic::setTechniqueName(std::string name)
{
	_staticMeshEffect->SetTechnique(name.c_str());
}
