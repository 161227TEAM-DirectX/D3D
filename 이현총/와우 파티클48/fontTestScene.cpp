#include "stdafx.h"
#include "fontTestScene.h"

HRESULT fontTestScene::init(void)
{
	//��Ʈ ��ü �����
	D3DXCreateFont(
		_device,			//����̽�
		50,					//��Ʈ�� ����(������ ��Ʈũ��)
		0,					//��Ʈ�� �� (�̰��� �׳� 0�� �ָ� ��Ʈ�� ���̿� ����ؼ� ��Ⱦ�� ���缭 ó���ȴ�)
		FW_BOLD,			//��Ʈ �β� ���� (���彺Ÿ�� ũ��)					
		1,					//�Ӹ��� �׳� 1
		FALSE,				//���ڸ� ����
		DEFAULT_CHARSET,	//ĳ���ͼ� (�׳� ����Ʈ)
		OUT_DEFAULT_PRECIS,	//�ܰ�ó�����
		DEFAULT_QUALITY,	//����Ƽ
		DEFAULT_PITCH | FF_DONTCARE,	//�۽�ü �йи��� ���� �̰͵� �׳� �̰;����
		"�ü�ü",				//���� ��Ʈ�̸� �׳� �ѱ۷� ��Ʈ�̸� ���� ��
		&_font				//������ ��Ʈ��ü
	);

	return S_OK;
}

void fontTestScene::release(void)
{
	//��Ʈ��ü ����
	SAFE_RELEASE(_font);
}

void fontTestScene::update(void)
{
}

void fontTestScene::render(void)
{
	/*
	//��¿���(������ ��ǥ��)
	RECT rc = { 100, 100, 0, 0 };
	_font->DrawText(
		NULL,
		"������ Ż�� ����???",
		-1,
		&rc,
		DT_LEFT | DT_NOCLIP,
		0xfffffffff
	);
	
	//��¿���(������ ��ǥ��)
	RECT rc1 = { 0, 0, 0, 0 };
	_font->DrawText(
		NULL,
		"������ Ż�� ������",
		-1,
		&rc1,
		DT_LEFT | DT_NOCLIP,
		0xfffffffff
	);

	//��¿���(������ ��ǥ��)
	RECT rc2 = { 0, 0, WINSIZEX, WINSIZEY };
	_font->DrawText(
		NULL,
		"������ Ż�� �Ϸ���?",
		-1,
		&rc2,
		DT_CENTER | DT_VCENTER,
		0xfffffffff
	);
	*/

	/*��Ʈ�Ŵ��� ����*/
	FONTMANAGER->fontOut("����1.2��~~~", 100, 100, D3DCOLOR_XRGB(255, 255, 0));
	FONTMANAGER->fontOutShadow("����1.2��~~~", 100, 150, D3DCOLOR_XRGB(255, 255, 0));
	FONTMANAGER->fontOutShadow("����1.2��~~~", 100, 200, D3DCOLOR_XRGB(255, 255, 0), D3DCOLOR_XRGB(128, 128, 128));

	FONTMANAGER->addFont("��Ʈ1", "�ü�ü", 50);
	FONTMANAGER->addFont("��Ʈ2", "�޸տ�ü", 30);
	FONTMANAGER->fontOutWithStyle("��Ʈ1", "��ο���", WINSIZEX / 2, WINSIZEY / 2, 0xffff1234);
	FONTMANAGER->fontOutWithStyle("��Ʈ2", "��ο���", WINSIZEX / 2, WINSIZEY / 2 + 100, 0xffff1234);
}
