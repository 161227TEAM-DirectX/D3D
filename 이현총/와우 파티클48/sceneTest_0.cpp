#include "stdafx.h"
#include "sceneTest_0.h"

HRESULT sceneTest_0::init(void)
{
	//���� ������ ä�� �ֱ�
	_vertices[0].pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_vertices[0].color = 0xffff0000;
	_vertices[1].pos = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_vertices[1].color = 0xff00ff00;
	_vertices[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vertices[2].color = 0xff0000ff;

	//������ �÷� ������ ����ϱ� ���ؼ��� ����̽��� �⺻ ����Ʈ ����� �����ؾ� �Ѵ�
	//��а� ����Ʈ ����� ����� ���� ������ ������
	_device->SetRenderState(
		D3DRS_LIGHTING,			//�������Ҳ���?
		FALSE					//���ð��� ��� �ǳ�?
	);

	return S_OK;
}

void sceneTest_0::release(void)
{
}

void sceneTest_0::update(void)
{
}

void sceneTest_0::render(void)
{
	//������������ ������ �ﰢ�� �׸���
	
	//���� �׸��� ������ ���� ���� FVF �÷��� ���� �־�����
	//_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	//_device->SetFVF(FVF);
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,		//�׸��� ���� �ﰢ���̴�
		1,						//�׷����� ��ü���� ���?
		_vertices,				//���� ����ü
		sizeof(MYVERTEX)		//���� ����ü �Ѱ��� ũ��
	);
}
