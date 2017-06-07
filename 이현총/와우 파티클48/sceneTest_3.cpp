#include "stdafx.h"
#include "sceneTest_3.h"

HRESULT sceneTest_3::init(void)
{
	//����������
	_vertex[0].pos = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	_vertex[1].pos = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	_vertex[2].pos = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	_vertex[3].pos = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	_vertex[0].color = D3DCOLOR_XRGB(255, 255, 0);
	_vertex[1].color = D3DCOLOR_XRGB(255, 255, 0);
	_vertex[2].color = D3DCOLOR_XRGB(255, 0, 0);
	_vertex[3].color = D3DCOLOR_XRGB(255, 0, 0);

	//�ε���������
	_index[0] = 0;
	_index[1] = 1;
	_index[2] = 2;
	_index[3] = 0;
	_index[4] = 2;
	_index[5] = 3;

	//������ �÷� ������ ����ϱ� ���ؼ��� ����̽��� �⺻ ����Ʈ ����� �����ؾ� �Ѵ�
	//��а� ����Ʈ ����� ����� ���� ������ ������
	_device->SetRenderState(
		D3DRS_LIGHTING,			//�������Ҳ���?
		FALSE					//���ð��� ��� �ǳ�?
	);

	//�����̽� �ø�(��������)
	//_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);	//�ð���� �ȱ׸��ڴ�(�ݽð���� �׷�����)
	//_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�ݽð���� �ȱ׸��ڴ� (�ð���� �׷�����) => ����Ʈ
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�ø����� (����� ��� �׷�����)
	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //���̾�������
	//�����ʱ�ȭ
	_angle = 0.0f;
	
	return S_OK;
}

void sceneTest_3::release(void)
{
}

void sceneTest_3::update(void)
{
	//�ʴ� 90�� ȸ��
	_angle += D3DXToRadian(90) * _timeDelta;

	//���� �࿡���� ȸ�����
	D3DXMATRIXA16 matRotation;
	//D3DXMatrixRotationX(&matRotation, _angle);	//x�� �������� ȸ�����
	D3DXMatrixRotationY(&matRotation, _angle);		//y�� �������� ȸ�����
	//D3DXMatrixRotationZ(&matRotation, _angle);	//z�� �������� ȸ�����
	//������ �࿡ ���� ȸ�����
	//D3DXMatrixRotationAxis(&matRotation, &D3DXVECTOR3(0, 1, 0), _angle);

	//�������
	_matWorld = matRotation;
}

void sceneTest_3::render(void)
{
//====================================================================
//			## ���� �����̽� ##
//====================================================================
	//Ư����ü�� �׸������� ��ü�� �ش�Ǵ� ��������� �����ϰ� �׸���!!!
	_device->SetTransform(D3DTS_WORLD, &_matWorld);

//====================================================================
//			## �� �����̽� ##
//====================================================================
	//����� �� �交�� �غ�
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0��ġ�� �ٶ󺻴�
	D3DXVECTOR3 eyePos(0, 1, -5);			//ī�޶� ���� ��ġ
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
		0.001f,				//�ٰŸ� ��� �Ÿ�(0�϶� ������ ���δ�)
		100.0f);			//���Ÿ� ��� �Ÿ�

							//������� ����
	_device->SetTransform(D3DTS_PROJECTION, &matProjection);

//============================================================================

	//���� �׸��� ������ ���� ���� ���� �÷��� ����
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,				//�׸��°� �ﰢ��
		0,								//�ּ� �ε��� ������
		4,								//���� ����
		2,								//�ﰢ�� ����
		_index,							//�ε��� �迭
		D3DFMT_INDEX32,					//����32��Ʈ
		_vertex,						//���� �迭
		sizeof(MYVERTEX));				//��������ü ũ��

}
