#pragma once
#include "singletonBase.h"
//==================================================================
//		## fontManager ## (폰트 매니져)
//==================================================================

class fontManager : public singletonBase <fontManager>
{
private:
	typedef map<string, LPD3DXFONT> mapFont;
	typedef map<string, LPD3DXFONT>::iterator mapFontIter;

private:
	LPD3DXFONT _font;		//디폴트용 폰트
	mapFont _mapFont;		//맵안에 담아둘 폰트(폰트종류를 지정해줘야 한다)

public:
	HRESULT init(void);
	void release(void);

	//폰트종류 추가
	void addFont(string strKey, string fontName, int fontSize);

	//디폴트폰트로 출력
	void fontOut(string str, int x, int y, DWORD color);
	void fontOutShadow(string str, int x, int y, DWORD color, DWORD shadowColor = 0xff000000);
	void fontOutLine(string str, int x, int y, DWORD color, DWORD outLineColor = 0xff000000);

	//맵에 담긴 폰트로 출력
	void fontOutWithStyle(string strKey,string str, int x, int y, DWORD color);
	void fontOutShadowWithStyle(string strKey, string str, int x, int y, DWORD color, DWORD shadowColor = 0xff000000);
	void fontOutLineWithStyle(string strKey, string str, int x, int y, DWORD color, DWORD outLineColor = 0xff000000);

	fontManager() {}
	~fontManager() {}
};

