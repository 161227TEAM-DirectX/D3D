#include "stdafx.h"
#include "textureTestScene.h"

HRESULT textureTestScene::init(void)
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

	pVertices[0].pos = D3DXVECTOR3(-5, -5, 0);
	pVertices[1].pos = D3DXVECTOR3(-5, 5, 0);
	pVertices[2].pos = D3DXVECTOR3(5, 5, 0);
	pVertices[3].pos = D3DXVECTOR3(5, -5, 0);

	pVertices[0].uv = D3DXVECTOR2(0, 3);
	pVertices[1].uv = D3DXVECTOR2(0, 0);
	pVertices[2].uv = D3DXVECTOR2(3, 0);
	pVertices[3].uv = D3DXVECTOR2(3, 3);

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

	//�ؽ��� �ε�
	D3DXCreateTextureFromFile(
		_device,
		"��ȿ��.jpg",
		&_texture);

//��, ������� �غ�
//====================================================================
//			## �� �����̽� ##
//====================================================================
	//����� �� �交�� �غ�
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0��ġ�� �ٶ󺻴�
	D3DXVECTOR3 eyePos(0, 0, -10);			//ī�޶� ���� ��ġ
	D3DXVECTOR3 up(0, 1, 0);				//��溤�� �׳� 0,1,0

	//D3DXMatrixLookAtLH(�����, ����ġ, �ٶ���ġ, ������)
	D3DXMatrixLookAtLH(&matView, &eyePos, &lookAtPos, &up);

	//����� ����
	_device->SetTransform(D3DTS_VIEW, &matView);

//====================================================================
//			## ���� ##
//====================================================================
	//������� �غ�
	D3DXMATRIXA16 matProjection;

	D3DXMatrixPerspectiveFovLH(
		&matProjection,		//�������
		D3DXToRadian(60),	//ȭ�� 60��
		(float)(WINSIZEX) / static_cast<float>(WINSIZEY), //ȭ�� ��Ⱦ��
		0.01f,				//�ٰŸ� ��� �Ÿ�(0�϶� ������ ���δ�)
		100.0f);			//���Ÿ� ��� �Ÿ�

	//������� ����
	_device->SetTransform(D3DTS_PROJECTION, &matProjection);
//============================================================================

	//����Ʈ����� ��� ������
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

//====================================================================
//			## �ؽ��� Wrap ��� ##
//====================================================================
	//�ݺ������� ���´� 1 �Ѿ�� UV ��ǥ�� 1�� ���� �ٽ� 0���� ����
	_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	////�ݺ������� ���� ���´� 1�Ѿ�� UV ��ǥ�� 1���� 0���� ������ 0���Ϸ� ������ �ٽ� 1�� ���Ͽ� ����
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	//
	////�Ӹ������ ����� 1 �Ѿ�� UV ��ǥ�� �α׸� 1�� �����Ѵ�
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	//
	////�Ӹ������ ����� 1�Ѿ�� UV��ǥ ���õ� ���� �÷��� ĥ�Ѵ�
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
	//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
	////UV ��ǥ�� 1 �Ѿ���� �׸� ������
	//_device->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0xffff00ff); 



	return S_OK;
}

void textureTestScene::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
	SAFE_RELEASE(_texture);
}

void textureTestScene::update(void)
{
}

void textureTestScene::render(void)
{
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
