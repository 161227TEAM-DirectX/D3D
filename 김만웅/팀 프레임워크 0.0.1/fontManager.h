#pragma once
#include "singletonBase.h"
//==================================================================
//		## fontManager ## (��Ʈ �Ŵ���)
//==================================================================

class fontManager : public singletonBase <fontManager>
{
private:
	typedef map<string, LPD3DXFONT> mapFont;
	typedef map<string, LPD3DXFONT>::iterator mapFontIter;

private:
	LPD3DXFONT _font;		//����Ʈ�� ��Ʈ
	mapFont _mapFont;		//�ʾȿ� ��Ƶ� ��Ʈ(��Ʈ������ ��������� �Ѵ�)

public:
	HRESULT init(void);
	void release(void);

	//��Ʈ���� �߰�
	void addFont(string strKey, string fontName, int fontSize);

	//����Ʈ��Ʈ�� ���
	void fontOut(string str, int x, int y, DWORD color);
	void fontOutShadow(string str, int x, int y, DWORD color, DWORD shadowColor = 0xff000000);
	void fontOutLine(string str, int x, int y, DWORD color, DWORD outLineColor = 0xff000000);

	//�ʿ� ��� ��Ʈ�� ���
	void fontOutWithStyle(string strKey,string str, int x, int y, DWORD color);
	void fontOutShadowWithStyle(string strKey, string str, int x, int y, DWORD color, DWORD shadowColor = 0xff000000);
	void fontOutLineWithStyle(string strKey, string str, int x, int y, DWORD color, DWORD outLineColor = 0xff000000);

	fontManager() {}
	~fontManager() {}
};

