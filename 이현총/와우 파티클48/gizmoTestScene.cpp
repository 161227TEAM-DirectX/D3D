#include "stdafx.h"
#include "gizmoTestScene.h"

HRESULT gizmoTestScene::init(void)
{
//====================================================================
//			## �� �����̽� ##
//====================================================================
	//����� �� �交�� �غ�
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0��ġ�� �ٶ󺻴�
	D3DXVECTOR3 eyePos(3, 10, -20);			//ī�޶� ���� ��ġ
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

void gizmoTestScene::release(void)
{
}

void gizmoTestScene::update(void)
{
}

void gizmoTestScene::render(void)
{
	//�����Ŵ��� ���巻��
	GIZMOMANAGER->WorldGrid(1, 10);
	GIZMOMANAGER->Circle(D3DXVECTOR3(0, 2, 0), 3.0f, D3DXVECTOR3(0, 0, 1), 0xff00fffff);

	//GIZMOMANAGER->WireSphere(D3DXVECTOR3(-3, 0, 1), 2, 0xffffff00);

	//GIZMOMANAGER->AABB(D3DXVECTOR3(0, 1, -5), D3DXVECTOR3(10, 8, 10), 0xffffff00);
}
