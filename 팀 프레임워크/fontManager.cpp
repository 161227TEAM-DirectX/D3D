#include "stdafx.h"
#include "fontManager.h"

HRESULT fontManager::init(void)
{
	//����Ʈ�� ����� ��Ʈ ��ü �����
	D3DXCreateFont(
		_device,			//����̽�
		20,					//��Ʈ�� ����(������ ��Ʈũ��)
		0,					//��Ʈ�� �� (�̰��� �׳� 0�� �ָ� ��Ʈ�� ���̿� ����ؼ� ��Ⱦ�� ���缭 ó���ȴ�)
		FW_BOLD,			//��Ʈ �β� ���� (���彺Ÿ�� ũ��)					
		1,					//�Ӹ��� �׳� 1
		FALSE,				//���ڸ� ����
		DEFAULT_CHARSET,	//ĳ���ͼ� (�׳� ����Ʈ)
		OUT_DEFAULT_PRECIS,	//�ܰ�ó�����
		DEFAULT_QUALITY,	//����Ƽ
		DEFAULT_PITCH | FF_DONTCARE,//�۽�ü �йи��� ���� �̰͵� �׳� �̰;����
		"����ü",				//���� ��Ʈ�̸� �׳� �ѱ۷� ��Ʈ�̸� ���� ��
		&_font				//������ ��Ʈ��ü
	);

	return S_OK;
}

void fontManager::release(void)
{
	//����Ʈ�� ��Ʈ ����
	SAFE_RELEASE(_font);

	//�ʿ� ����ִ� ��Ʈ���� ���� ����
	mapFontIter iter;
	for (iter = _mapFont.begin(); iter != _mapFont.end(); ++iter)
	{
		SAFE_RELEASE(iter->second);
	}
}

//��Ʈ���� �߰�
void fontManager::addFont(string strKey, string fontName, int fontSize)
{
	//�̹� ��Ʈ������ ������ �߰����� �ʵ��� �Ѵ�
	mapFontIter find = _mapFont.find(strKey);
	if (find != _mapFont.end()) return;

	//���ο� ��Ʈ �߰�
	LPD3DXFONT newFont;
	D3DXCreateFont(
		_device,			//����̽�
		fontSize,			//��Ʈ�� ����(������ ��Ʈũ��)
		0,					//��Ʈ�� �� (�̰��� �׳� 0�� �ָ� ��Ʈ�� ���̿� ����ؼ� ��Ⱦ�� ���缭 ó���ȴ�)
		FW_BOLD,			//��Ʈ �β� ���� (���彺Ÿ�� ũ��)					
		1,					//�Ӹ��� �׳� 1
		FALSE,				//���ڸ� ����
		DEFAULT_CHARSET,	//ĳ���ͼ� (�׳� ����Ʈ)
		OUT_DEFAULT_PRECIS,	//�ܰ�ó�����
		DEFAULT_QUALITY,	//����Ƽ
		DEFAULT_PITCH | FF_DONTCARE,//�۽�ü �йи��� ���� �̰͵� �׳� �̰;����
		fontName.c_str(),	//���� ��Ʈ�̸� �׳� �ѱ۷� ��Ʈ�̸� ���� ��
		&newFont			//������ ��Ʈ��ü
	);
	
	//���� ���� ��Ʈ�� �ʿ� ��´�
	_mapFont.insert(make_pair(strKey, newFont));
}

void fontManager::fontOut(LPD3DXSPRITE sprite, string str)
{
	_font->DrawText(sprite, str.c_str(), -1, nullptr, 0, D3DCOLOR_XRGB(255, 255, 255));
}

//����Ʈ��Ʈ�� ���
void fontManager::fontOut(string str, int x, int y, DWORD color)
{
	//��¿��� (������ ��ǥ��)
	RECT rcTextArea = { x, y, 0, 0 };

	_font->DrawText(
		NULL,
		str.c_str(),
		-1,
		&rcTextArea,
		DT_LEFT | DT_NOCLIP,
		color);
}

void fontManager::fontOutShadow(string str, int x, int y, DWORD color, DWORD shadowColor)
{
	//������ ���� �׸���
	fontOut(str, x + 1, y + 1, shadowColor);

	//���� �ؽ�Ʈ�� �׸���
	fontOut(str, x, y, color);
}

void fontManager::fontOutLine(string str, int x, int y, DWORD color, DWORD outLineColor)
{
	//�ܰ��� ���� �׸���
	fontOut(str, x + 1, y, outLineColor);
	fontOut(str, x, y + 1, outLineColor);
	fontOut(str, x - 1, y, outLineColor);
	fontOut(str, x, y - 1, outLineColor);

	//���� �ؽ�Ʈ�� �׸���
	fontOut(str, x, y, color);
}

//�ʿ� ��� ��Ʈ�� ���
void fontManager::fontOutWithStyle(string strKey, string str, int x, int y, DWORD color)
{
	LPD3DXFONT font = NULL;
	//��Ʈ������ Ű���� ��ã�Ҵٸ� ����Ʈ�� ��Ʈ����� �ϰ� ã�Ҵٸ� ã�� ��Ʈ�� �����ϸ� �ȴ�
	mapFontIter find = _mapFont.find(strKey);
	if (find == _mapFont.end()) font = _font;
	else font = find->second;

	//��¿��� (������ ��ǥ��)
	RECT rcTextArea = { x, y, 0, 0 };

	font->DrawText(
		NULL,
		str.c_str(),
		-1,
		&rcTextArea,
		DT_LEFT | DT_NOCLIP,
		color);
}

void fontManager::fontOutShadowWithStyle(string strKey, string str, int x, int y, DWORD color, DWORD shadowColor)
{
	//������ ���� �׸���
	fontOutWithStyle(strKey, str, x + 1, y + 1, shadowColor);

	//���� �ؽ�Ʈ�� �׸���
	fontOutWithStyle(strKey, str, x, y, color);
}

void fontManager::fontOutLineWithStyle(string strKey, string str, int x, int y, DWORD color, DWORD outLineColor)
{
	//������ ���� �׸���
	fontOutWithStyle(strKey, str, x + 1, y, outLineColor);
	fontOutWithStyle(strKey, str, x, y + 1, outLineColor);
	fontOutWithStyle(strKey, str, x - 1, y, outLineColor);
	fontOutWithStyle(strKey, str, x, y - 1, outLineColor);

	//���� �ؽ�Ʈ�� �׸���
	fontOutWithStyle(strKey, str, x, y, color);
}
