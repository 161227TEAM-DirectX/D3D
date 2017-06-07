#include "stdafx.h"
#include "shaderHW3.h"

HRESULT shaderHW3::init(void)
{
	//����ī�޶�
	_mainCamera.SetLocalPosition(0, 0, 0);

	//�������
	this->CreateQuad();
	//���� ������
	_quadTrans.SetScale(100, 100, 100);
	//���κ��� �����
	_quadTrans.RotateLocal(D3DXToRadian(90), 0, 0);

	//�ؽ��ķε�
	//����Ʈ�� �Ӹ�ü���� ���������
	//D3DXCreateTextureFromFile(����̽�, �����̸�, �ؽ���������)
	D3DXCreateTextureFromFile(_device, "terrainControl.png", &_texControl);
	D3DXCreateTextureFromFile(_device, "terrain1.png", &_texTile1);
	D3DXCreateTextureFromFile(_device, "terrain2.png", &_texTile2);
	D3DXCreateTextureFromFile(_device, "terrain3.png", &_texTile3);
	D3DXCreateTextureFromFile(_device, "terrain4.png", &_texTile4);


	//�ؽ��� ���͸��
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//���̴� �ε��� ������ ������ ���� ������ ������ �޾ƿ� Error����
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;
	//fxFile �� ���� Effect ��ü �ε�
	D3DXCreateEffectFromFile(
		_device,				//����̽�
		"Texture_Terrain.fx",	//�ҷ��� ���̴� �ڵ� �����̸�
		NULL, 					//���̴��� �������Ҷ� �߰��� ����� #define ���� ( �ϴ� NULL )
		NULL, 					//���̴��� �������Ҷ� #include ���ù��� ó���Ҷ� ����� �������̽� �÷��� ( �ϴ� NULL )
		shaderFlag,				//���̴� ������ �÷���
		NULL, 					//���̴� �Ű������� ������ �޸�Ǯ ( �ϴ� NULL )
		&_effect,				//�ε��� ���̴� Effect ������
		&error 					//���̴��� �ε��ϰ� �������Ҷ� ������ ����� �ش� ���ۿ� �����޽����� ���� ( ���������� �ε��Ǹ� NULL �� �����ȴ� )
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

void shaderHW3::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
	SAFE_RELEASE(_effect);
	SAFE_RELEASE(_texControl);
	SAFE_RELEASE(_texTile1);
	SAFE_RELEASE(_texTile2);
	SAFE_RELEASE(_texTile3);
	SAFE_RELEASE(_texTile4);
}

void shaderHW3::update(void)
{
	_quadTrans.DefaultMyControl(_timeDelta);
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();
}

void shaderHW3::render(void)
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

	//�ؽ��� ����
	_effect->SetTexture("TexControl", _texControl);
	_effect->SetTexture("TexTile0", _texTile1);
	_effect->SetTexture("TexTile1", _texTile2);
	_effect->SetTexture("TexTile2", _texTile3);
	_effect->SetTexture("TexTile3", _texTile4);

	//Ÿ�ϼ� ����
	_effect->SetFloat("tiling0", 30);
	_effect->SetFloat("tiling1", 30);
	_effect->SetFloat("tiling2", 30);
	_effect->SetFloat("tiling3", 30);

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

void shaderHW3::CreateQuad()
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
