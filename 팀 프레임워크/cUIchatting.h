#pragma once

#define ID_EDIT 100
#define CHATNUMBER 6 

enum FOCUS { FOCUSZERO = 0, FOCUSONE, FOCUSTWO };

class cDxImgUI;

struct CHATTINGUI
{
	LPDIRECT3DTEXTURE9 tex;
	RECT rc1, rc2;
	bool uiNumber;
};

class cUIchatting
{
private:
	HWND EDIT;
	CHATTINGUI  _chattingUi;
	string		_Schatting;

	vector<string> _vSChat;
	string _Schat;

	tagSaveName _LoadName;

	HIMC hImc;
	bool bHanMode;
	DWORD dwConv, dwSent;
	DWORD dwTemp;

private:
	char _Text[256];     // 텍스트를 저장하기위한 변수
	int _number;
	int _chatCount;
	int _chatHeight;
	int _chatIcount;

public:
	cUIchatting(int sx=0, int sy=600);
	~cUIchatting();

	void update();
	void render();
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

