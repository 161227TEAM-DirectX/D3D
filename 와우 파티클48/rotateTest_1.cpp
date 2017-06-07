#include "stdafx.h"
#include "rotateTest_1.h"

HRESULT rotateTest_1::init(void)
{
	//ť�����
	this->CreateCube();

	D3DXMatrixIsIdentity(&_matWorld);

	//ȸ������ ���� �ʱ�ȭ�� ��Ű��
	_forward = D3DXVECTOR3(0, 0, 1);
	_up = D3DXVECTOR3(0, 1, 0);
	_right = D3DXVECTOR3(1, 0, 0);
	_pos = D3DXVECTOR3(0, 0, 0);
	//�ٶ� ��ġ
	_targetPos = D3DXVECTOR3(0, 0, 10);

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

void rotateTest_1::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
}

void rotateTest_1::update(void)
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_pos += _right * -5.0f * _timeDelta;
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		_pos += _right * 5.0f * _timeDelta;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_pos += _forward * 5.0f * _timeDelta;
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_pos += _forward * -5.0f * _timeDelta;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_targetPos.x += -5.0f * _timeDelta;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_targetPos.x += 5.0f * _timeDelta;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_targetPos.y += 5.0f * _timeDelta;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_targetPos.y += -5.0f * _timeDelta;
	}
	if (KEYMANAGER->isStayKeyDown(VK_HOME))
	{
		_targetPos.z += 5.0f * _timeDelta;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_END))
	{
		_targetPos.z += -5.0f * _timeDelta;
	}

	//ť�갡 Ÿ���� �ٶ󺸰� �����
	
	//Ÿ�� ����
	D3DXVECTOR3 dirToTarget = _targetPos - _pos;
	//����ȭ
	D3DXVec3Normalize(&dirToTarget, &dirToTarget);

	//forward�� ����
	_forward = dirToTarget;

	//Up X Forward = Right
	D3DXVec3Cross(&_right, &_up, &_forward);
	D3DXVec3Normalize(&_right, &_right);
	//Forwart X Right = Up
	D3DXVec3Cross(&_up, &_forward, &_right);
	D3DXVec3Normalize(&_up, &_up);

	//ť�� ũ�⺯ȯ(����*��Į��)
	D3DXVECTOR3 r = _right * 2;
	D3DXVECTOR3 u = _up * 0.5f;
	D3DXVECTOR3 f = _forward;

	//������� (�̵� + ���� ��ȯ���)
	//[r.x]		[u.x]	[f.x]	[0]
	//[r.y]		[u.y]	[f.y]	[0]
	//[r.z]		[u.z]	[f.z]	[0]
	//[�̵�]		[�̵�]	[�̵�]	[1]
	_matWorld._11 = r.x; _matWorld._12 = r.y; _matWorld._13 = r.z; _matWorld._14 = 0;
	_matWorld._21 = u.x; _matWorld._22 = u.y; _matWorld._23 = u.z; _matWorld._24 = 0;
	_matWorld._31 = f.x; _matWorld._32 = f.y; _matWorld._33 = f.z; _matWorld._34 = 0;
	_matWorld._41 = _pos.x; _matWorld._42 = _pos.y; _matWorld._43 = _pos.z; _matWorld._44 = 1;
}

void rotateTest_1::render(void)
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

	//�����Ŵ����� Ÿ����ġ ����
	GIZMOMANAGER->WireSphere(_targetPos, 1.0f, 0xffff00ff);
}

void rotateTest_1::CreateCube(void)
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
