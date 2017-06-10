#include "stdafx.h"
#include "normalTest1.h"

HRESULT normalTest1::init(void)
{
	//�������
	this->CreateQuad();

	//������ ���¸� �˷��ִ� �迭
	D3DVERTEXELEMENT9	vertElement[4];				//�迭�� �������� ���� + 1
	//Pos	
	vertElement[0].Stream = 0;						//	
	vertElement[0].Offset = 0;						//�޸� ���� ����Ʈ ����
	vertElement[0].Type = D3DDECLTYPE_FLOAT3;		//�ڷ�Ÿ��
	vertElement[0].Method = D3DDECLMETHOD_DEFAULT;	//�׳� ����Ʈ
	vertElement[0].Usage = D3DDECLUSAGE_POSITION;	//����Ÿ���� ��ġ
	vertElement[0].UsageIndex = 0;					//�ϴ� 0
	
	//UV
	vertElement[1].Stream = 0;						//	
	vertElement[1].Offset = 12;						//�޸� ���� ����Ʈ ����
	vertElement[1].Type = D3DDECLTYPE_FLOAT2;		//�ڷ�Ÿ��
	vertElement[1].Method = D3DDECLMETHOD_DEFAULT;	//�׳� ����Ʈ
	vertElement[1].Usage = D3DDECLUSAGE_TEXCOORD;	//����Ÿ���� �ؽ���
	vertElement[1].UsageIndex = 0;					//�ϴ� 0

	//normal
	vertElement[2].Stream = 0;						//	
	vertElement[2].Offset = 20;						//�޸� ���� ����Ʈ ����
	vertElement[2].Type = D3DDECLTYPE_FLOAT3;		//�ڷ�Ÿ��
	vertElement[2].Method = D3DDECLMETHOD_DEFAULT;	//�׳� ����Ʈ
	vertElement[2].Usage = D3DDECLUSAGE_NORMAL;		//����Ÿ���� �븻
	vertElement[2].UsageIndex = 0;					//�ϴ� 0

	//���̻� ������ ��������
	D3DVERTEXELEMENT9 end = D3DDECL_END(); //{0xFF,0,D3DDECLTYPE_UNUSED,0,0,0}
	vertElement[3] = end;

	_device->CreateVertexDeclaration(
		vertElement,
		&_vDeclation);

	//�ؽ��� �ε�
	D3DXCreateTextureFromFile(_device, "��ȿ��.png", &_texture);

	//���̴� �ε�
	//���̴� �ε��� ������ ������ ���� ������ ������ �޾ƿ� Error����
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;
	//fxFile �� ���� Effect ��ü �ε�
	D3DXCreateEffectFromFile(
		_device,			//����̽�
		"TextureBlinn.fx",	//�ҷ��� ���̴� �ڵ� �����̸�
		NULL, 				//���̴��� �������Ҷ� �߰��� ����� #define ���� ( �ϴ� NULL )
		NULL, 				//���̴��� �������Ҷ� #include ���ù��� ó���Ҷ� ����� �������̽� �÷��� ( �ϴ� NULL )
		shaderFlag,			//���̴� ������ �÷���
		NULL, 				//���̴� �Ű������� ������ �޸�Ǯ ( �ϴ� NULL )
		&_effect,			//�ε��� ���̴� Effect ������
		&error 				//���̴��� �ε��ϰ� �������Ҷ� ������ ����� �ش� ���ۿ� �����޽����� ���� ( ���������� �ε��Ǹ� NULL �� �����ȴ� )
	);

	//�ε��� ������ �ִٸ�....
	if (error != NULL)
	{
		//Error ���� Release
		SAFE_RELEASE(error);
		return E_FAIL;
	}

	return S_OK;
}

void normalTest1::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
	SAFE_RELEASE(_texture);
	SAFE_RELEASE(_effect);
	SAFE_RELEASE(_vDeclation);
}

void normalTest1::update(void)
{
	_lightTrans.DefaultMyControl(_timeDelta);
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();
}

void normalTest1::render(void)
{
	//����Ʈ�� ���� �������� �����Ѵ�.
	D3DXMATRIXA16 matWorld = _quadTrans.GetFinalMatrix();

	//����̽��κ��� ���õ� View ��İ� Projection ����� ��´�.
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProjection;
	_device->GetTransform(D3DTS_VIEW, &matView);
	_device->GetTransform(D3DTS_PROJECTION, &matProjection);

	//�Ѻ�ȯ ���
	D3DXMATRIXA16 matWVP = matWorld * matView * matProjection;
	_effect->SetMatrix("matWVP", &matWVP);

	//�������
	_effect->SetMatrix("matWorld", &matWorld);

	//��������
	D3DXVECTOR3 lightDir = _lightTrans.GetForward();
	_effect->SetVector("vLightDir", &D3DXVECTOR4(lightDir, 1));

	//�ü���ġ
	D3DXVECTOR3	eyePos = _mainCamera.GetWorldPosition();
	_effect->SetVector("vEyePos", &D3DXVECTOR4(eyePos, 1));

	//�Ŀ�
	_effect->SetFloat("specPower", 10);

	//�ؽ��� ����
	_effect->SetTexture("DiffuseTex", _texture);

	//��ũ�м���
	_effect->SetTechnique("MyShader");

	//���̴��� ���� ����
	UINT iPassNum = 0;

	//����Ʈ�� ����������
	_effect->Begin(&iPassNum, 0);

	//�н� ����� for������ ������
	for (UINT i = 0; i < iPassNum; i++)
	{
		_effect->BeginPass(i);

		//����
		//���� �׸���
		_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));
		_device->SetVertexDeclaration(_vDeclation);
		_device->SetIndices(_ib);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

		_effect->EndPass();
	}

	_effect->End();

	_lightTrans.RenderGimozo();
}

void normalTest1::CreateQuad()
{
	//������ġ
	D3DXVECTOR3 vertexPos[] =
	{
		D3DXVECTOR3(-3.5, -3.5, 0),
		D3DXVECTOR3(-3.5, 3.5, 0),
		D3DXVECTOR3(3.5, 3.5, 0),
		D3DXVECTOR3(3.5, -3.5, 0)
	};

	//����UV
	D3DXVECTOR2 vertexUV[] =
	{
		D3DXVECTOR2(0, 1),
		D3DXVECTOR2(0, 0),
		D3DXVECTOR2(1, 0),
		D3DXVECTOR2(1, 1)
	};

	//���� �ε���
	DWORD vertexIndices[] = { 0, 1, 2, 0, 2, 3 };

	//���� �븻
	D3DXVECTOR3	vertexNormal[4];
	ComputeNormal(vertexNormal, vertexPos, 4, vertexIndices, 6);

	//���� ���� ����
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 4,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_DEFAULT,
		&_vb,
		NULL);

	// 1---2    UV��ǥ��� ������ ��ǥ��� �Ȱ��� 
	// |  /|	���ʻ���� 0,0 ������� 1,0 �����ϴ� 0,1 �����ϴ� 1,1
	// | / |								
	// 0---3								
	LPMYVERTEX pVertices = NULL;
	_vb->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4; i++)
	{
		pVertices[i].pos = vertexPos[i];
		pVertices[i].uv = vertexUV[i];
		pVertices[i].normal = vertexNormal[i];
	}

	_vb->Unlock();

	//�ε��� ���� ����
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
