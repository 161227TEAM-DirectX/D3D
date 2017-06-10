#include "stdafx.h"
#include "xMeshLoading.h"

HRESULT xMeshLoading::init(void)
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

	_meshTrans.SetScale(0.05f, 0.05f, 0.05f);
	_meshLocal.AttachTo(&_meshTrans);
	_meshLocal.RotateLocal(0, D3DXToRadian(180), 0);

	//������ ����
	_device->SetRenderState(D3DRS_LIGHTING, false);

	//�ε��� ����� ���۴� ����
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
		//Texture ����
		_device->SetTexture(0, _vecTextures[i]);

		_mesh->DrawSubset(i);
	}

	//�ٱ׸��� ���� Texture �� �������ִ� ����
	_device->SetTexture(0, NULL);
}
