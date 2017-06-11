#include "stdafx.h"
#include "image.h"

HRESULT image::init(int width, int height)
{
	//DC ���
	HDC hdc = GetDC(_hWnd);

	//��Ʈ�� ���μ��� ũ�����
	_width = width;
	_height = height;

	//BitmapDC ����
	_hMemDC = CreateCompatibleDC(hdc);
	//dwWidth, dwHeight ũ���� ���ũ���� �����.
	_newBit = CreateCompatibleBitmap(hdc, width, height);
	//BitmapDC �� ǥ���� �ҷ��� Bitmap ���� �ϰ� ���� ǥ�� ������ m_OldBit ��....
	_oldBit = (HBITMAP)SelectObject(_hMemDC, _newBit);

	//���÷�Ű( -1 ) �̸� ���� ����
	_transColor = -1;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release(void)
{
	//Bitmap ����
	DeleteObject(SelectObject(_hMemDC, _oldBit));
	//Bitmap DC ����
	DeleteDC(_hMemDC);
}

void image::render(HDC hdc)
{
	//���÷�Ű�� ���ٸ�
	if (_transColor == -1) 
	{
		BitBlt(hdc, 0, 0, _width, _height, _hMemDC, 0, 0, SRCCOPY);
	}
	//���÷��� �ִٸ�..
	else 
	{
		GdiTransparentBlt(hdc, 0, 0, _width, _height, _hMemDC, 0, 0, _width, _height, _transColor);
	}
}
