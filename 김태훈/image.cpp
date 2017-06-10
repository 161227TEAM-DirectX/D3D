#include "stdafx.h"
#include "image.h"

HRESULT image::init(int width, int height)
{
	//DC 얻기
	HDC hdc = GetDC(_hWnd);

	//비트맵 가로세로 크기대입
	_width = width;
	_height = height;

	//BitmapDC 생성
	_hMemDC = CreateCompatibleDC(hdc);
	//dwWidth, dwHeight 크기의 빈비크맵을 만든다.
	_newBit = CreateCompatibleBitmap(hdc, width, height);
	//BitmapDC 의 표면을 불러온 Bitmap 으로 하고 이전 표면 정보를 m_OldBit 가....
	_oldBit = (HBITMAP)SelectObject(_hMemDC, _newBit);

	//뺄컬러키( -1 ) 이면 없는 것임
	_transColor = -1;

	//얻어온 DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release(void)
{
	//Bitmap 해제
	DeleteObject(SelectObject(_hMemDC, _oldBit));
	//Bitmap DC 해제
	DeleteDC(_hMemDC);
}

void image::render(HDC hdc)
{
	//뺄컬러키가 없다면
	if (_transColor == -1) 
	{
		BitBlt(hdc, 0, 0, _width, _height, _hMemDC, 0, 0, SRCCOPY);
	}
	//뺄컬러가 있다면..
	else 
	{
		GdiTransparentBlt(hdc, 0, 0, _width, _height, _hMemDC, 0, 0, _width, _height, _transColor);
	}
}
