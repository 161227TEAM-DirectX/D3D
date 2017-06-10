#include "stdafx.h"
#include "shaderHW2.h"


HRESULT shaderHW2::init(void)
{
	//����ī�޶�
	_mainCamera.SetLocalPosition(0, 0, -10);

	//�������
	this->CreateQuad();

	//�ؽ��ķε�
	//����Ʈ�� �Ӹ�ü���� ���������
	//D3DXCreateTextureFromFile(����̽�, �����̸�, �ؽ���������)
	D3DXCreateTextureFromFile(_device, "Sample1.png", &_texture);
	D3DXCreateTextureFromFile(_device, "Sample1_Mask.png", &_textureMask);


	//�ؽ��� ���͸��
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//���̴� �ε��� ������ ������ ���� ������ ������ �޾ƿ� Error����
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;
	//fxFile �� ���� Effect ��ü �ε�
	D3DXCreateEffectFromFile(
		_device,			//����̽�
		"Texture_Mask.fx",	//�ҷ��� ���̴� �ڵ� �����̸�
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

void shaderHW2::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
	SAFE_RELEASE(_texture);
	SAFE_RELEASE(_textureMask);
	SAFE_RELEASE(_effect);
}

void shaderHW2::update(void)
{
	_quadTrans.DefaultMyControl(_timeDelta);
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();
}

void shaderHW2::render(void)
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

	//�÷� ���� ���� (���ǻ���!! ���õǴ� ���ʹ� ��� Vector4 �� �뵿�ܰ�ȴ�)
	D3DXVECTOR4 color(1, 0, 0, 1);
	_effect->SetVector("vColor", &color);

	//�ؽ��� ����
	_effect->SetTexture("MyTex", _texture);
	_effect->SetTexture("MaskTex", _textureMask);

	//Ÿ�ϼ� ����
	_effect->SetFloat("tilingX", 1);
	_effect->SetFloat("tilingY", 1);

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
		_device->SetFVF(MYVERTEX::FVF);
		_device->SetIndices(_ib);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

		_effect->EndPass();
	}

	_effect->End();
}

void shaderHW2::CreateQuad()
{
	//���� ���� ����
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 4,
		D3DUSAGE_WRITEONLY,
		MYVERTEX::FVF,
		D3DPOOL_DEFAULT,
		&_vb,
		NULL);

	// 1---2    UV��ǥ��� ������ ��ǥ��� �Ȱ��� 
	// |  /|	���ʻ���� 0,0 ������� 1,0 �����ϴ� 0,1 �����ϴ� 1,1
	// | / |								
	// 0---3								
	LPMYVERTEX pVertices = NULL;
	_vb->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].pos = D3DXVECTOR3(-3.5, -3.5, 0);
	pVertices[1].pos = D3DXVECTOR3(-3.5, 3.5, 0);
	pVertices[2].pos = D3DXVECTOR3(3.5, 3.5, 0);
	pVertices[3].pos = D3DXVECTOR3(3.5, -3.5, 0);

	pVertices[0].uv = D3DXVECTOR2(0, 1);
	pVertices[1].uv = D3DXVECTOR2(0, 0);
	pVertices[2].uv = D3DXVECTOR2(1, 0);
	pVertices[3].uv = D3DXVECTOR2(1, 1);

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
	DWORD idx[] = { 0, 1, 2, 0, 2, 3 };

	void* pIndices = NULL;
	_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, idx, sizeof(DWORD) * 6);
	_ib->Unlock();
}
