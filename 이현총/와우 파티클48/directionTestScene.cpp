#include "stdafx.h"
#include "directionTestScene.h"

HRESULT directionTestScene::init(void)
{
	//����� �������� ����
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 3,
		D3DUSAGE_WRITEONLY,
		MYVERTEX::FVF,
		D3DPOOL_DEFAULT,
		&_planeVB,
		NULL);

	LPMYVERTEX pVertices;
	_planeVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].pos = D3DXVECTOR3(0, 0, 1);
	pVertices[0].color = 0xffff0000;
	pVertices[1].pos = D3DXVECTOR3(1, 0, -1);
	pVertices[1].color = 0xff00ff00;
	pVertices[2].pos = D3DXVECTOR3(-1, 0, -1);
	pVertices[2].color = 0xff0000ff;

	_planeVB->Unlock();

	//����� ������� �ʱ�ȭ
	D3DXMatrixIdentity(&_matPlane);	//�������(�׵����)
	//��ġ(0, 0, 0)
	//������(1, 1, 1)
	//ȸ�� ����

	//ȸ�� �ʱ�ȭ
	_yawAngle = 0.0f;
	_yawSpeed = D3DXToRadian(90);

	//��ġ �ʱ�ȭ
	_pos.x = 0.0f;
	_pos.y = 0.0f;
	_pos.z = 0.0f;

	//��ġ1 �ʱ�ȭ
	_pos2.x = 3.0f;
	_pos2.y = 0.0f;
	_pos2.z = 0.0f;
	D3DXMatrixIdentity(&_matPlane2);

	//�̵� �ӵ�
	_moveSpeed = 3.0f;


	//��, ������� �غ�
//====================================================================
//			## �� �����̽� ##
//====================================================================
	//����� �� �交�� �غ�
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0��ġ�� �ٶ󺻴�
	D3DXVECTOR3 eyePos(0, 20, 0);			//ī�޶� ���� ��ġ
	D3DXVECTOR3 up(0, 0, 1);				//��溤�� �׳� 0,1,0

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

void directionTestScene::release(void)
{
	SAFE_RELEASE(_planeVB);
}

void directionTestScene::update(void)
{
	//ȸ�� ��Ʈ��
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_yawAngle -= _yawSpeed * _timeDelta;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_yawAngle += _yawSpeed * _timeDelta;
	}
	//���� ����ŭ ȸ�����
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, _yawAngle);

	//��Ʈ�� ȸ�� ������ ������Ű��
	//�ʴ� �̵���
	float moveDelta = _moveSpeed * _timeDelta; 

	//ȸ���� ���̱��� �繰�� �������
	D3DXVECTOR3 moveDir(0, 0, 1);
	//������⿡ ȸ������� �ֱ�
	D3DXVec3TransformNormal(&moveDir, &moveDir, &matRot);

	//�̵����� �̵��� * �������
	D3DXVECTOR3 moveVector = moveDir * moveDelta;

	//��ġ���� �̵����� ���Ѵ�
	_pos += moveVector;

	//��ġ���
	D3DXMATRIXA16 matPostion;
	D3DXMatrixTranslation(&matPostion,
		_pos.x,
		_pos.y,
		_pos.z);
	_matPlane = matRot * matPostion;

	//�ι�° ����⿡ ���� ���
	D3DXMATRIXA16 matPostion2;
	D3DXMatrixTranslation(&matPostion2,
		_pos2.x,
		_pos2.y,
		_pos2.z);
	_matPlane = matRot * matPostion;

	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		//_matPlane2 = matPostion2 *  _matPlane;
		_matPlane2 = _matPlane *  matPostion2;
		//mat = _matPlane2;
	}
	else
	{
		_matPlane2 = matPostion2;
		mat = _matPlane2;
	}


	/*
	//ȸ�����
	D3DXMATRIXA16 matRot2;

	//�ٶ���� �� ���� ����
	D3DXVECTOR3 dirToTarget = _pos - _pos2;

	//����ȭ �����ֱ�
	D3DXVec3Normalize(&dirToTarget, &dirToTarget);

	//�����2�� �ٶ󺸴� ��, ȸ���� ���� �ʴ´�
	D3DXVECTOR3 dir2(0, 0, 1);
	
	//������
	float yawAngle = acosf(D3DXVec3Dot(&dir2, &dirToTarget));

	//����� Ÿ�� ���� ����
	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &dir2, &dirToTarget);

	//���� ����� ����ȭ ���� �ʾҴ�
	//����ȭ �����ֱ�
	D3DXVec3Normalize(&cross, &cross);

	//�׿� ������ ����� ������ �� ȸ�����
	D3DXMatrixRotationAxis(&matRot2, &cross, yawAngle);

	_matPlane2 = matRot2 * matPostion2;
	*/
}

void directionTestScene::render(void)
{
	//����� ������� ����
	_device->SetTransform(D3DTS_WORLD, &_matPlane);

	//����� �׸���
	_device->SetStreamSource(0, _planeVB, 0, sizeof(MYVERTEX));
	_device->SetFVF(MYVERTEX::FVF);
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	//�����2 ������� ����
	_device->SetTransform(D3DTS_WORLD, &_matPlane2);

	//�����2 �׸���
	_device->SetStreamSource(0, _planeVB, 0, sizeof(MYVERTEX));
	_device->SetFVF(MYVERTEX::FVF);
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	/*
	//������ ���� ��� ������ ��� ��Ұ��� ���ٰ���
	mat._11, mat._12, mat._13, mat._14
	mat._21, mat._22, mat._23, mat._24
	mat._31, mat._32, mat._33, mat._34
	mat._41, mat._42, mat._43, mat._44
	
	mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3]
	mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3]
	mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3]
	mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]
	*/

	//D3DXMatrixIdentity(&mat);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			char str[128];
			sprintf(str, "[%2.2f]", mat.m[i][j]);
			FONTMANAGER->fontOut(str, 300 + j * 80, i * 30, 0xffffffff);
		}
	}


}
