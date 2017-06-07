#include "stdafx.h"
#include "sceneTest_2.h"

HRESULT sceneTest_2::init(void)
{
	//���� ���� �����
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 3,		//������� ���������� ũ��(�ﰢ���� ���� 3�� �ʿ�)
		D3DUSAGE_WRITEONLY,			//��������� ���������� �Ӽ�(�ϴ� writeonly�� ������ ������, �Ŀ� �������ۿ� ������ ���� �Ͼ�ٸ� ���̳������� ��������)
		MYVERTEX::FVF,				//FVF����
		D3DPOOL_DEFAULT,			//�޸�Ǯ �������
		&_vb,						//������ ���ع���
		NULL);						//�׳� ������ �������� ���� NULL

									//���� ���� ä���ֱ�
	LPMYVERTEX vertices = NULL;
	//Lock�ɰ� ������ ä������ �ּҸ� vertices�� �޾ƿ���
	//
	_vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertices[0].color = 0xffff0000;
	vertices[1].pos = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertices[1].color = 0xff00ff00;
	vertices[2].pos = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	vertices[2].color = 0xff0000ff;

	//�� ��������� ������
	_vb->Unlock();

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

	//�����ʱ�ȭ
	_angle = 0;
	
	return S_OK;
}

void sceneTest_2::release(void)
{
	//�������ع�������
	SAFE_RELEASE(_vb);
}

void sceneTest_2::update(void)
{
	//�ʴ� 90�� ȸ��
	_angle += D3DXToRadian(90) * _timeDelta;

	//���� �࿡���� ȸ�����
	D3DXMATRIXA16 matRotation;
	//D3DXMatrixRotationX(&matRotation, _angle);		//x�� �������� ȸ�����
	D3DXMatrixRotationY(&matRotation, _angle);		//y�� �������� ȸ�����
	//D3DXMatrixRotationZ(&matRotation, _angle);		//z�� �������� ȸ�����
	//������ �࿡ ���� ȸ�����
	//D3DXMatrixRotationAxis(&matRotation, &D3DXVECTOR3(0, 1, 0), _angle);

	//�������
	_matWorld = matRotation;


}

void sceneTest_2::render(void)
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
	D3DXVECTOR3 eyePos(0, 1, -10);			//ī�޶� ���� ��ġ
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

	//SetStreamSource => ���� �̾߱� �ϸ� ���ؽ� ���� ����
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));

	//���� �׸��� ������ ���� ���� ���� �÷��� ����
	_device->SetFVF(MYVERTEX::FVF);

	//�׸��°��� �ﰢ��, 0��° ��������, �ﰢ���� 1��
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
