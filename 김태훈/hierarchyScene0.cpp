#include "stdafx.h"
#include "hierarchyScene0.h"

HRESULT hierarchyScene0::init(void)
{
	//ť�����
	this->CreateCube();

	//ť����ġ
	_cubeTrans.SetWorldPosition(-1, 2, 1);
	//�ڽ�ť����ġ
	_childCubeTrans.SetWorldPosition(1, 0, 0);
	//�׷������ϵ� ť����ġ
	_grandChildCubeTrans.SetWorldPosition(0, -1, 0);

	//����Ʈ off
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

void hierarchyScene0::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
}

void hierarchyScene0::update(void)
{
	float deltaMove = 3.0f * _timeDelta;
	float deltaAngle = D3DXToRadian(90) * _timeDelta;

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) == FALSE)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_cubeTrans.MovePositionSelf(-deltaMove, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_cubeTrans.MovePositionSelf(deltaMove, 0.0f, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_cubeTrans.MovePositionSelf(0.0f, 0.0f, deltaMove);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_cubeTrans.MovePositionSelf(0.0f, 0.0f, -deltaMove);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_cubeTrans.RotateSelf(0.0f, -deltaAngle, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_cubeTrans.RotateSelf(0.0f, deltaAngle, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_cubeTrans.RotateSelf(-deltaAngle, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_cubeTrans.RotateSelf(deltaAngle, 0.0f, 0.0f);
		}
	}

	//ī�޶� ����Ʈ��Ʈ��
	_mainCamera.DefaultControl(_timeDelta);
	//ī�޶� ������Ʈ
	_mainCamera.updateCamToDevice();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_childCubeTrans.SetWorldPosition(0, 0, 10.0f);
	}
}

void hierarchyScene0::render(void)
{
	//ť���� ������� ����
	_cubeTrans.SetDeviceWorld();
	//ť�귻��
	this->RenderCube();

	if (KEYMANAGER->isStayKeyDown('1'))
	{
		_childCubeTrans.AttachTo(&_cubeTrans);
	}
	else
	{
		_childCubeTrans.ReleaseParent();
	}

	_childCubeTrans.SetDeviceWorld();
	this->RenderCube();

	if (KEYMANAGER->isStayKeyDown('2'))
	{
		_grandChildCubeTrans.AttachTo(&_cubeTrans);
	}
	else
	{
		_grandChildCubeTrans.ReleaseParent();
	}

	_grandChildCubeTrans.SetDeviceWorld();
	this->RenderCube();
}

void hierarchyScene0::CreateCube()
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

void hierarchyScene0::RenderCube()
{
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
}
