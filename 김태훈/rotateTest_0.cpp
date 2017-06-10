#include "stdafx.h"
#include "rotateTest_0.h"

HRESULT rotateTest_0::init(void)
{
	//ť�� ����
	this->CreateCube();

	//ȸ���� �ʱ�ȭ
	_xAngle = 0.0f;
	_yAngle = 0.0f;
	_zAngle = 0.0f;

	//ť�� ���� ��� �ʱ�ȭ
	D3DXMatrixIdentity(&_matWorld);
	
//====================================================================
//			## �� �����̽� ##
//====================================================================
	//����� �� �交�� �غ�
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0��ġ�� �ٶ󺻴�
	D3DXVECTOR3 eyePos(1, 3, -5);			//ī�޶� ���� ��ġ
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
	


	return S_OK;
}

void rotateTest_0::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
}

void rotateTest_0::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_yAngle -= 10.0f;
	}
	else if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_yAngle += 10.0f;
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_xAngle -= 10.0f;
	}
	else if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_xAngle += 10.0f;
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_zAngle -= 10.0f;
	}
	else if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_zAngle += 10.0f;
	}

	/*
	//������ ������ �߻�
	D3DXMATRIXA16  matRotX, matRotY, matRotZ;
	//X�࿡���� ȸ�����
	D3DXMatrixRotationX(&matRotX, _xAngle * D3DXToRadian(1));
	//Y�࿡���� ȸ�����
	D3DXMatrixRotationY(&matRotY, _yAngle * D3DXToRadian(1));
	//Z�࿡���� ȸ�����
	D3DXMatrixRotationZ(&matRotZ, _zAngle * D3DXToRadian(1));

	//�������
	//ȸ������� ���ع����� ���Ϸ� ȸ�� ���
	_matWorld = matRotX * matRotY * matRotZ;
	*/

	/*���ʹϿ����� ������������ �ּ�ȭ�ϱ�*/
	//3�࿡ ���� ȸ�� ������ ���ʹϿ����� ���
	D3DXQUATERNION quat;

	//�� ȸ�� ���� ���� ȸ�� ������ ���ʹϿ¸� ��´�
	D3DXQuaternionRotationYawPitchRoll(&quat, _yAngle * D3DXToRadian(1), _xAngle * D3DXToRadian(1), _zAngle * D3DXToRadian(1));

	//ȸ�� ���ʹϿ����� ȸ������� ��´�
	D3DXMATRIXA16 matRotation;
	D3DXMatrixRotationQuaternion(&matRotation, &quat);

	//�������
	_matWorld = matRotation;

	//���ʹϿ��� ����
	//1. ���� 4�������� 3�࿡ ���� ȸ�������� ���� �� �ִ�
	//2. ���� 4���� �����Ǿ� �ֱ⶧���� ȸ������ �ٸ� ������� ���Ҷ� ��귮�� ����
	//3. ������ ������ �ذ��� �� �ִ� (�� �����ϰ� �ذ����� ���� ����)
	//D3D���� ���ʹϿ��� ���� ȸ������ �Լ��� �����Ѵ�
}

void rotateTest_0::render(void)
{
	_device->SetTransform(D3DTS_WORLD, &_matWorld);

	//SetStreamSource => ���� �̾߱� �ϸ� ���ؽ� ���� ����
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));

	//�ε������� ����
	_device->SetIndices(_ib);

	//���� �׸��� ������ ���� ���� ���� �÷��� ����
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,	 //���α׸���			
		0,				//���� ���ؽ��迭 �ε���				
		0,
		24,				//���� ����			
		0,				//���� �ε����迭 �ε���		
		12				//�׸��� ��ü�� ������ 12��
	);

	//ȸ���� ���
	char str[128];
	sprintf(str, "XAngle: %.2f", _xAngle);
	FONTMANAGER->fontOut(str, 0, 100, 0xffff0000);
	sprintf(str, "YAngle: %.2f", _yAngle);
	FONTMANAGER->fontOut(str, 0, 130, 0xffff0000);
	sprintf(str, "ZAngle: %.2f", _zAngle);
	FONTMANAGER->fontOut(str, 0, 160, 0xffff0000);

	GIZMOMANAGER->Circle(D3DXVECTOR3(0, 0, 0), 3.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0xffff0000);
	GIZMOMANAGER->Circle(D3DXVECTOR3(0, 0, 0), 3.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xff00ff00);
	GIZMOMANAGER->Circle(D3DXVECTOR3(0, 0, 0), 3.0f, D3DXVECTOR3(
		sin(_yAngle * D3DXToRadian(1)),
		0.0f,
		cos(_yAngle * D3DXToRadian(1))),
		0xff0000ff);
}

void rotateTest_0::CreateCube(void)
{
	//���� ���� �����
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 24,		//������� ���������� ũ��(�ﰢ���� ���� 3�� �ʿ�)
		D3DUSAGE_WRITEONLY,			//��������� ���������� �Ӽ�(�ϴ� writeonly�� ������ ������, �Ŀ� �������ۿ� ������ ���� �Ͼ�ٸ� ���̳������� ��������)
		MYVERTEX::FVF,				//FVF����
		D3DPOOL_DEFAULT,			//�޸�Ǯ �������
		&_vb,						//������ ���ع���
		NULL);						//�׳� ������ �������� ���� NULL

	//���� �÷� ����
	MYVERTEX quad[4];
	quad[0].pos = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	quad[1].pos = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	quad[2].pos = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	quad[3].pos = D3DXVECTOR3(0.5f, -0.5f, -0.5f);

	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(-90));

	//���� �迭 �غ�
	MYVERTEX vertices[24];

	//�ո�
	memcpy(vertices, quad, sizeof(MYVERTEX) * 4);
	vertices[0].color = 0xffff0000;
	vertices[1].color = 0xffff0000;
	vertices[2].color = 0xffff0000;
	vertices[3].color = 0xffff0000;

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//������ ����
	memcpy(vertices + 4, quad, sizeof(MYVERTEX) * 4);
	vertices[4].color = 0xff00ff00;
	vertices[5].color = 0xff00ff00;
	vertices[6].color = 0xff00ff00;
	vertices[7].color = 0xff00ff00;
	
	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//�޸� ����
	memcpy(vertices + 8, quad, sizeof(MYVERTEX) * 4);
	vertices[8].color = 0xffff0000;
	vertices[9].color = 0xffff0000;
	vertices[10].color = 0xffff0000;
	vertices[11].color = 0xffff0000;

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//������ ����
	memcpy(vertices + 12, quad, sizeof(MYVERTEX) * 4);
	vertices[12].color = 0xff00ff00;
	vertices[13].color = 0xff00ff00;
	vertices[14].color = 0xff00ff00;
	vertices[15].color = 0xff00ff00;

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-90));

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}
	
	//���� ����
	memcpy(vertices + 16, quad, sizeof(MYVERTEX) * 4);
	vertices[16].color = 0xff0000ff;
	vertices[17].color = 0xff0000ff;
	vertices[18].color = 0xff0000ff;
	vertices[19].color = 0xff0000ff;

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-180));

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//�Ʒ��� ����
	memcpy(vertices + 20, quad, sizeof(MYVERTEX) * 4);
	vertices[20].color = 0xff0000ff;
	vertices[21].color = 0xff0000ff;
	vertices[22].color = 0xff0000ff;
	vertices[23].color = 0xff0000ff;

	//���� ��
	void* pVertices = NULL;
	_vb->Lock(0, 0, &pVertices, 0);
	//�޸� ����
	memcpy(pVertices, vertices, sizeof(MYVERTEX) * 24);
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
