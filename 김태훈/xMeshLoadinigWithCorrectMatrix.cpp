#include "stdafx.h"
#include "xMeshLoadinigWithCorrectMatrix.h"

HRESULT xMeshLoadinigWithCorrectMatrix::init(void)
{
	//�ε� ���....
	string filePath = "Resources/Meshes/GunShip/gunship.x";			//X ���� ��θ�
	//Texture �� �ҷ��´ٸ�
	//Resources/Meshes/GunShip/ �̰�ο��� �ҷ��;� �Ѵ�...

	LPD3DXBUFFER	pAdjacency;		//���� ����
	LPD3DXBUFFER	pMaterial;		//���� ����
	DWORD			dwNumMtrl;		//���� �� 

									//XFile �� ���� �޽��� �ҷ����� �Լ�
	D3DXLoadMeshFromX(
		filePath.c_str(),			//X ���� �ε� ���...
		D3DXMESH_MANAGED,			//�޽� �ɼ� �ϴ� D3DXMESH_MANAGED ��....
		_device,					//����̽�
		&pAdjacency,				//���� �������� ����
		&pMaterial,					//���� �������� ����
		NULL,						//Effect 
		&_materialsNum,				//�޽����� ���Ǵ� ���� ����
		&_mesh						//�޽�
	);

	//�ε� ��ο��� ���ϸ� �����ϰ� ��θ� �޴´�.
	string path;
	int lastPathIndex = 0;			//������ \ �� ��ġ

									//filePath.find_first_of( 'A' ); filePath ���ڿ��� 'A' �� ����ִ� ��ġ ���� ( �տ��� ���� �˻� )
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

	//���� ������ ��´�
	LPD3DXMATERIAL	pMaterials = (LPD3DXMATERIAL)pMaterial->GetBufferPointer();

	//����������ŭ for ������ �����糤��.
	for (DWORD i = 0; i < _materialsNum; i++) {

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
			//���ϰ�� 
			string texFilePath = path + pMaterials[i].pTextureFilename;
			//Texture �ε��ϰ� Ǫ��
			_vecTextures.push_back(RM_TEXTURE->loadResource(texFilePath));
		}
		else
		{
			//������ �ݵ�� null ����( �߿� )
			_vecTextures.push_back(NULL);
		}
	}

	//���� ���� ������ �� ����Ͽ� ������ Texture �� �ε� �߱⶧���� 
	//���̻� pMaterial ���� ���۴� �ʿ� ���� �� �޸� ���縦 ���־�� �Ѵ�.
	SAFE_RELEASE(pMaterial);

	//�޽� ����ȭ ( ���� ���۸� �̿��Ͽ� �޽��� ����ȭ �Ѵ� )
	_mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |		//�޽� ����¼������ ���� ( DrawSubset ȿ���� ���δ� )
		D3DXMESHOPT_COMPACT |		//�޽����� ������ �ʴ� ������ �ε��� ����
		D3DXMESHOPT_VERTEXCACHE,	//���� Cache ��Ʈ�� ������.
		(DWORD*)pAdjacency->GetBufferPointer(),		//�������� �Ѱܾ� �Ѵ�.
		NULL,			//����ȭ�� ������ ����� ��� �������� ( ���̻� �ʿ������ NULL )
		NULL,			//����ȭ�� �ε��� ����
		NULL			//����ȭ�� ���� ���� ���� 
	);


	//����ȭ�� �������� ����
	SAFE_RELEASE(pAdjacency);

	//
	// �޽� ���� ó��
	//
	//���� �ִ� �Ž����� ������ ���� ��ķ� �������� 
	//��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);

	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

	D3DXMATRIXA16 matCorrection = matScale * matRotate;
	//D3DXMATRIXA16 matCorrection;
	//D3DXMatrixIdentity(&matCorrection);

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
	for (DWORD i = 0; i < MAX_FVF_DECL_SIZE; i++) 
	{
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
	//DWORD verSize = D3DXGetFVFVertexSize( _mesh->GetFVF() );
	DWORD verSize = D3DXGetDeclVertexSize(pVerElement, 0);

	//�޽��� ���ؽ� ���۸� Lock �Ѵ�
	void* p = NULL;
	_mesh->LockVertexBuffer(0, &p);

	//���ؽ� ����Ŭ ���� �糤��....
	for (DWORD i = 0; i < verNum; i++) 
	{
		//���ؽ� ���� �ּ�
		char* pVertex = ((char*)p + (i * verSize));

		//���� ��ġ�� �ִٸ�...
		if (positionOffset != -1) 
		{
			D3DXVECTOR3* pos = (D3DXVECTOR3*)(pVertex + positionOffset);
			D3DXVec3TransformCoord(pos, pos, &matCorrection);
		}

		//�븻������ �ִٸ�..
		if (normalOffet != -1) 
		{
			D3DXVECTOR3* nor = (D3DXVECTOR3*)(pVertex + normalOffet);
			D3DXVec3TransformNormal(nor, nor, &matCorrection);
			D3DXVec3Normalize(nor, nor);
		}

		//tangent ������ �ִٸ�.
		if (tangentOffet != -1) 
		{
			D3DXVECTOR3* tangent = (D3DXVECTOR3*)(pVertex + tangentOffet);
			D3DXVec3TransformNormal(tangent, tangent, &matCorrection);
			D3DXVec3Normalize(tangent, tangent);
		}

		//binormal ������ �ִٸ�
		if (binormalOffet != -1) 
		{
			D3DXVECTOR3* binor = (D3DXVECTOR3*)(pVertex + binormalOffet);
			D3DXVec3TransformNormal(binor, binor, &matCorrection);
			D3DXVec3Normalize(binor, binor);
		}
	}

	_mesh->UnlockVertexBuffer();

	//������ ����
	_device->SetRenderState(D3DRS_LIGHTING, false);

	//�ε��� ����� ���۴� ����
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
		//Texture ����
		_device->SetTexture(0, _vecTextures[i]);

		_mesh->DrawSubset(i);
	}

	//�ٱ׸��� ���� Texture �� �������ִ� ����
	_device->SetTexture(0, NULL);
}
