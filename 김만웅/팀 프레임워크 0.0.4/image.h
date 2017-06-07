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
	COLORREF	_transColor;		//���÷�Ű( -1 ) �̸� ���� ����

public:
	HRESULT init(int width, int height);
	void release(void);
	void render(HDC hdc);
	
	//�޸� DC ���
	inline HDC getMemDC(void) { return _hMemDC; }

	image() {}
	~image() {}
};