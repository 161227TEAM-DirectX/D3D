#include "stdafx.h"
#include "textureFilterTest.h"

HRESULT textureFilterTest::init(void)
{
	//�������
	this->CreateQuad();

	//���� ������
	_quadTrans.SetScale(100, 100, 100);
	//���κ��� �����
	_quadTrans.RotateLocal(D3DXToRadian(90), 0, 0);

	/*
	//�ؽ��ķε�
	//����Ʈ�� �Ӹ�ü���� ���������
	//D3DXCreateTextureFromFile(����̽�, �����̸�, �ؽ���������)
	D3DXCreateTextureFromFile(_device, "Sample1.png", &_texture);
	*/
	
	//�Ӹ�ü�ξ��� �ε�
	D3DXCreateTextureFromFileEx(
	_device,
	"Sample1.png",
	256,
	256,
	0,
	0,
	D3DFMT_UNKNOWN,
	D3DPOOL_MANAGED,
	D3DX_FILTER_NONE,
	D3DX_FILTER_NONE,
	0,
	0,
	0,
	&_texture);
	

	//����Ʈ ����
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

void textureFilterTest::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
	SAFE_RELEASE(_texture);
}

void textureFilterTest::update(void)
{
	_quadTrans.DefaultMyControl(_timeDelta);
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();

	//���͸�� ����
	//_device->SetSamplerState(����������ȣ, ��� ���� �����Ҳ���, ���Ϳɼ�);
	//D3DSAMP_MINFILTER ���� Sample �Ȱź��� �۰� �����°�쿡 ���� ���͸� ���
	//D3DSAMP_MAGFILTER ���� Sample �Ȱź��� ũ�� �����°�쿡 ���� ���͸� ���
	//D3DSAMP_MIPFILTER �Ӹ�ü���� ��迡�� ��� ���͸��Ұ���

	//���Ϳɼ�
	//D3DTEXF_LINEAR �ֺ��ʼ��� ��������
	//D3DTEXF_ANISOTROPIC �̹漺���͸��� ���� ����
	//D3DTEXF_POINT ���ȼ��� ����

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		//�ؽ����� ���͸��
		_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		//�ؽ����� ���͸��
		_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

		//�̹漺 ���͸��� ������ �����Ҽ� �ִ�.
		//D3DTEXF_ANISOTROPIC �ܰ踦 ����
		//Device->SetSamplerState( 0, D3DSAMP_MAXANISOTROPY, 16 );  //16 �ܰ� ������ �ȼ�����

		//�׷���ī�帶�� �ִ� �����ɼ� �ִ� D3DTEXF_ANISOTROPIC �ܰ� �� �ٸ���.
		//�׷��� D3DCAP9 �� ���� Ȯ���Ҽ� �ִ�
		_device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, maxAnisotropic);
	}
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		//�ؽ����� ���͸��
		_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	}
}

void textureFilterTest::render(void)
{
	//����̽��� ���� Ʈ�������� ���忡 ����
	_quadTrans.SetDeviceWorld();

	//�׸��� ���� �ε��� �ؽ��ĸ� �����ϱ�
	_device->SetTexture(0, _texture);

	//���� �׸���
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));
	_device->SetFVF(MYVERTEX::FVF);
	_device->SetIndices(_ib);
	_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//�ؽ��� ��������
	_device->SetTexture(0, NULL);
}

void textureFilterTest::CreateQuad()
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

	pVertices[0].uv = D3DXVECTOR2(0, 100);
	pVertices[1].uv = D3DXVECTOR2(0, 0);
	pVertices[2].uv = D3DXVECTOR2(100, 0);
	pVertices[3].uv = D3DXVECTOR2(100, 100);

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
