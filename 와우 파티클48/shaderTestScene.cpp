#include "stdafx.h"
#include "shaderTestScene.h"

HRESULT shaderTestScene::init(void)
{
	//ī�޶� ����
	_mainCamera.SetLocalPosition(-1, 2, -10);

	//ť�����
	this->CreateCube();

	//���̴� �ε��� ������ ������ ���� ������ ������ �޾ƿ� Error����
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;

	//fx���Ϸ� ���� ����Ʈ ��ü�� �ε��Ѵ�
	D3DXCreateEffectFromFile(
		_device,				//����̽�
		"HLSL_LambertLighting.fx",	//�����̸�
		NULL,					//���̴��� �������Ҷ� �߰��� ����� #define����
		NULL,					//���̴��� �������Ҷ� #include���ù� ó���Ҷ� ����� �������̽� �÷���
		shaderFlag,				//���̴� ������ �÷���
		NULL,					//���̴� �Ű������� ������ �޸� Ǯ
		&_effect,				//�ε��� ���̴� ����Ʈ ������
		&error);				//���̴� �ε��ϰ� ������ �Ҷ� �����Ͽ� ������ ����� ������ۿ� �����޼����� ����

	//������ �ִٸ�
	if (error != NULL)
	{
		//�������� ������
		SAFE_RELEASE(error);
		return E_FAIL;
	}

	//���̴� �ε��� �� �Ǿ����� �ڵ��� �޾ƿ´�
	_hTechnique = _effect->GetTechniqueByName("MyShader");

	//�������� �ڵ�
	_hMatWorld = _effect->GetParameterByName(NULL, "matWorld");
	_hMatView = _effect->GetParameterByName(NULL, "matView");
	_hMatProjection = _effect->GetParameterByName(NULL, "matProjection");
	_hColor = _effect->GetParameterByName(NULL, "vColor");

	return S_OK;
}

void shaderTestScene::release(void)
{
	SAFE_RELEASE(this->_vb);
	SAFE_RELEASE(this->_ib);

	//����Ʈ ����
	SAFE_RELEASE(_effect);
}

void shaderTestScene::update(void)
{
	//ť��Ʈ���� ������Ʈ
	//_cubeTrans.DefaultMyControl(_timeDelta);
	_lightTrans.DefaultMyControl(_timeDelta);

	//ī�޶� ����Ʈ��Ʈ��
	_mainCamera.DefaultControl(_timeDelta);
	//ī�޶� ������Ʈ
	_mainCamera.updateCamToDevice();
}

void shaderTestScene::render(void)
{
	//����Ʈ�� �������� ���� �����ϱ�
	D3DXMATRIXA16 matWorld = _cubeTrans.GetFinalMatrix();
	//������ļ���
	_effect->SetMatrix(_hMatWorld, &matWorld);
	//����̽��κ��� ���õ� ����İ� ��������� ���
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProjection;
	_device->GetTransform(D3DTS_VIEW, &matView);
	_device->GetTransform(D3DTS_PROJECTION, &matProjection);

	//����� ����
	_effect->SetMatrix(_hMatView, &matView);
	//������� ����
	_effect->SetMatrix(_hMatProjection, &matProjection);
	//�÷����� ����(���ǻ��� ���õǴ� ���ʹ� ��� ����4�� �뵿�ܰ�)
	D3DXVECTOR4 color(1, 0, 1, 1); //RGBA
	_effect->SetVector(_hColor, &color);


	//������ ����
	D3DXVECTOR4 lightDir(_lightTrans.GetForward(), 1);
	_effect->SetVector("vLightDir", &lightDir);
	//���� ���������
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);
	_effect->SetMatrix("matInvWorld", &matInvWorld);



	//��ũ�м���
	_effect->SetTechnique(_hTechnique);

	//���̴��� ť�귻��
	UINT iPassNum = 0;

	//����Ʈ�� ����������
	_effect->Begin(&iPassNum, 0);

	//�н� ����� for������ ������
	for (UINT i = 0; i < iPassNum; i++)
	{
		_effect->BeginPass(i);

		//����
		this->RenderCube();

		_effect->EndPass();
	}

	_effect->End();

	_lightTrans.RenderGimozo();

}

void shaderTestScene::CreateCube()
{
	//���� ���� �����
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX_PN) * 24,	//������� ���������� ũ��(�ﰢ���� ���� 3�� �ʿ�)
		D3DUSAGE_WRITEONLY,			//��������� ���������� �Ӽ�(�ϴ� writeonly�� ������ ������, �Ŀ� �������ۿ� ������ ���� �Ͼ�ٸ� ���̳������� ��������)
		MYVERTEX_PN::FVF,			//FVF����
		D3DPOOL_DEFAULT,			//�޸�Ǯ �������
		&_vb,						//������ ���ع���
		NULL);						//�׳� ������ �������� ���� NULL

									//���� �÷� ����
	MYVERTEX_PN quad[4];
	quad[0].pos = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	quad[1].pos = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	quad[2].pos = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	quad[3].pos = D3DXVECTOR3(0.5f, -0.5f, -0.5f);

	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(-90));

	//���� �迭 �غ�
	MYVERTEX_PN vertices[24];

	//�ո�
	memcpy(vertices, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[0].normal = D3DXVECTOR3(0, 0, -1);
	vertices[1].normal = D3DXVECTOR3(0, 0, -1);
	vertices[2].normal = D3DXVECTOR3(0, 0, -1);
	vertices[3].normal = D3DXVECTOR3(0, 0, -1);

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//������ ����
	memcpy(vertices + 4, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[4].normal = D3DXVECTOR3(1, 0, 0);
	vertices[5].normal = D3DXVECTOR3(1, 0, 0);
	vertices[6].normal = D3DXVECTOR3(1, 0, 0);
	vertices[7].normal = D3DXVECTOR3(1, 0, 0);

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//�޸� ����
	memcpy(vertices + 8, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[8].normal = D3DXVECTOR3(0, 0, 1);
	vertices[9].normal = D3DXVECTOR3(0, 0, 1);
	vertices[10].normal = D3DXVECTOR3(0, 0, 1);
	vertices[11].normal = D3DXVECTOR3(0, 0, 1);

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//������ ����
	memcpy(vertices + 12, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[12].normal = D3DXVECTOR3(-1, 0, 0);
	vertices[13].normal = D3DXVECTOR3(-1, 0, 0);
	vertices[14].normal = D3DXVECTOR3(-1, 0, 0);
	vertices[15].normal = D3DXVECTOR3(-1, 0, 0);

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-90));

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//���� ����
	memcpy(vertices + 16, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[16].normal = D3DXVECTOR3(0, 1, 0);
	vertices[17].normal = D3DXVECTOR3(0, 1, 0);
	vertices[18].normal = D3DXVECTOR3(0, 1, 0);
	vertices[19].normal = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-180));

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//�Ʒ��� ����
	memcpy(vertices + 20, quad, sizeof(MYVERTEX_PN) * 4);
	vertices[20].normal = D3DXVECTOR3(0, -1, 0);
	vertices[21].normal = D3DXVECTOR3(0, -1, 0);
	vertices[22].normal = D3DXVECTOR3(0, -1, 0);
	vertices[23].normal = D3DXVECTOR3(0, -1, 0);

	//���� ��
	void* pVertices = NULL;
	_vb->Lock(0, 0, &pVertices, 0);
	//�޸� ����
	memcpy(pVertices, vertices, sizeof(MYVERTEX_PN) * 24);
	_vb->Unlock();

	//�ε��� ���� ����
	_device->CreateIndexBuffer(
		sizeof(WORD) * 36,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&_ib,
		NULL);

	//		5--------6
	//     /|       /|
	//    4--------7 |
	//    | |      | | 
	//    | 1------| 2
	//    |/       |/
	//    0--------3

	WORD indices[36];
	for (int i = 0; i < 6; i++)
	{
		//���� ��ŸƮ �ε���
		WORD vertexIndex = i * 4;
		//�ε��� �迭 ��ŸƮ �ε���
		WORD indicesIndex = i * 6;

		indices[indicesIndex + 0] = vertexIndex + 0;
		indices[indicesIndex + 1] = vertexIndex + 1;
		indices[indicesIndex + 2] = vertexIndex + 2;
		indices[indicesIndex + 3] = vertexIndex + 0;
		indices[indicesIndex + 4] = vertexIndex + 2;
		indices[indicesIndex + 5] = vertexIndex + 3;
	}

	//�ε��� ��
	void* pIndices = NULL;
	_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, indices, sizeof(WORD) * 36);
	_ib->Unlock();
}

void shaderTestScene::RenderCube()
{
	//SetStreamSource => ���� �̾߱� �ϸ� ���ؽ� ���� ����
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX_PN));

	//�ε������� ����
	_device->SetIndices(_ib);

	//���� �׸��� ������ ���� ���� ���� �÷��� ����
	_device->SetFVF(MYVERTEX_PN::FVF);

	_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,	 //���α׸���			
		0,				//���� ���ؽ��迭 �ε���				
		0,
		24,				//���� ����			
		0,				//���� �ε����迭 �ε���		
		12				//�׸��� ��ü�� ������ 12��
	);
}
