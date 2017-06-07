#include "stdafx.h"
#include "sceneTest_1.h"

HRESULT sceneTest_1::init(void)
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
	vertices[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertices[2].color = 0xff0000ff;

	//�� ��������� ������
	_vb->Unlock();

	//������ �÷� ������ ����ϱ� ���ؼ��� ����̽��� �⺻ ����Ʈ ����� �����ؾ� �Ѵ�
	//��а� ����Ʈ ����� ����� ���� ������ ������
	_device->SetRenderState(
		D3DRS_LIGHTING,			//�������Ҳ���?
		FALSE					//���ð��� ��� �ǳ�?
	);

	return S_OK;
}

void sceneTest_1::release(void)
{
	//������������
	SAFE_RELEASE(_vb);
}

void sceneTest_1::update(void)
{
}

void sceneTest_1::render(void)
{
	//SetStreamSource => ���� �̾߱� �ϸ� ���ؽ� ���� ����
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));

	//���� �׸��� ������ ���� ���� ���� �÷��� ����
	_device->SetFVF(MYVERTEX::FVF);

	//�׸��°��� �ﰢ��, 0��° ��������, �ﰢ���� 1��
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
