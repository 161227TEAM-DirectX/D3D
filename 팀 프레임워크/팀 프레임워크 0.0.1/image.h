#pragma once
//====================================================================
//			## image ##
//====================================================================
class image
{
private:
	HDC			_hMemDC;
	HBITMAP		_newBit;
	HBITMAP		_oldBit;
	DWORD		_width;
	DWORD		_height;
	COLORREF	_transColor;		//뺄컬러키( -1 ) 이면 없는 것임

public:
	HRESULT init(int width, int height);
	void release(void);
	void render(HDC hdc);
	
	//메모리 DC 얻기
	inline HDC getMemDC(void) { return _hMemDC; }

	image() {}
	~image() {}
};