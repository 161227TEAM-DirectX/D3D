#include "stdafx.h"
#include "cUIchatting.h"


cUIchatting::cUIchatting(int sx,int sy)
{
	//텍스쳐초기화
	memset(_Text, 0, sizeof(_Text));
	_chattingUi.rc2 ={ sx,sy,0,0 };
	_chattingUi.uiNumber = false;
	_chatHeight = 1;
	bHanMode = true;

	//값 초기화
	_number = FOCUS::FOCUSZERO;
	FONTMANAGER->addFont("나눔고딕", "나눔고딕", 18);
	IOSAVENAMEMANAGER->loadFile("ResourceUI/chat/접속");
	_LoadName = IOSAVENAMEMANAGER->findTag("네트워크");
}


cUIchatting::~cUIchatting()
{
}

void cUIchatting::update()
{
	//아이뒤 로드 할라고 잠시 한것
	/*if (KEYMANAGER->isOnceKeyDown('M'))
	{
	vector<tagSaveName> _vSaveName;
	tagSaveName _SaveName;
	_SaveName.infoName = "네트워크";
	_SaveName.chatName = "xotmde";
	_SaveName.password = "xxxxxx";
	_vSaveName.push_back(_SaveName);
	IOSAVENAMEMANAGER->saveFile("접속", _vSaveName);
	}*/

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		g_isChat = !g_isChat;
		//number값 조절하기
		if (_number >= FOCUS::FOCUSTWO)
		{
			bHanMode = false;
			_number = FOCUS::FOCUSONE;
		}
		else _number++;
	}

	if (_number == FOCUS::FOCUSONE)
	{
		//엔터를 누르는순간 EDIT 박스에 포커스가 맞춰져서 칠수 있게 된다.
		//SetFocus(NULL) : NULL로 하면 포커스가 EDIT에 맞춰지지 않아서 칠수가 없게 된다.
		_chattingUi.uiNumber = true;
		SetFocus(EDIT);
	}

	if (_number == FOCUS::FOCUSTWO)
	{
		//채팅창5이상가면 삭제 시키기
		if (_vSChat.size() > CHATNUMBER)
		{
			_vSChat.erase(_vSChat.begin());
		}

		if (_Schatting.size() != 0)
		{
			_Schat = _Schatting;
			_vSChat.push_back(_Schat);
			bHanMode = false;
			if (_vSChat.size() <= CHATNUMBER)
			{
				_chatHeight++;
				_chatHeight = _chatHeight + 20;
			}

		}
		//ENTER가 한번더 선택되면 날려버리기 (EDIT)
		//입력되어있는 텍스쳐도 날려버리기
		_chattingUi.uiNumber = false;
		SetFocus(NULL);
		SetWindowText(EDIT, 0);
		memset(_Text, 0, sizeof(_Text));
		memset(&_Schatting, 0, sizeof(_Schatting));
	}
}

void cUIchatting::render()
{
	if (_chattingUi.uiNumber == true)
	{
		_chattingUi.tex = RM_TEXTURE->getResource("ResourceUI/chat/채팅창.png");
		SPRITEMANAGER->renderRectTexture(_chattingUi.tex, &_chattingUi.rc1, &_chattingUi.rc2, 0, 0, 1024, 1024, _chattingUi.rc2.left, _chattingUi.rc2.top);
		//폰트 사이즈를 조절하기위해서 
		FONTMANAGER->fontOutWithStyle("나눔고딕", "[" + _LoadName.chatName + "] : " + _Schatting, _chattingUi.rc2.left + 10, _chattingUi.rc2.top + 170, D3DCOLOR_XRGB(255, 255, 210));
	}

	if (_chattingUi.uiNumber == false)
	{
		_chattingUi.tex = RM_TEXTURE->getResource("ResourceUI/chat/채팅창2.png");
		SPRITEMANAGER->renderRectTexture(_chattingUi.tex, &_chattingUi.rc1, &_chattingUi.rc2, 0, 0, 1024, 1024, _chattingUi.rc2.left, _chattingUi.rc2.top);
	}

	//EDIT기능에 적힌 글자를 TEXT에 담앗으니 다시 temp에 담아서 출력시켜준다.
	_Schatting = _Text;

	for (int i = 0; i < _vSChat.size(); i++)
	{
		FONTMANAGER->fontOutWithStyle("나눔고딕", "[" + _LoadName.chatName + "] : " + _vSChat[i], _chattingUi.rc2.left + 10, ((_chattingUi.rc2.top + 160) + i * 20) - _chatHeight, D3DCOLOR_XRGB(255, 255, 210));
	}

	//FONTMANAGER->fontOut(to_string(bHanMode), 100, 100, D3DCOLOR_XRGB(255, 255, 255));
}



//EDIT박스를 만들어서 나타내게 한다.
LRESULT cUIchatting::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	hImc = ImmGetContext(hWnd);

	bHanMode = ImmGetOpenStatus(hImc);

	//(EDIT, hImc);

	ImmSetConversionStatus(hImc, bHanMode, 0);

	switch (message)
	{
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case VK_RETURN:

			switch (_number)
			{
			case FOCUS::FOCUSONE:
				//ImmReleaseContext(m_hWnd, h_imc);
				//애초에 Tric으로 화면 밖에 대화창을 두게 한다.               //화면의 위치//쓸쑤있는 글자 길이 
				EDIT = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10000, 10000, 432, 40, hWnd, (HMENU)ID_EDIT, NULL, NULL);
				break;
			}
			break;
		}
		break;

		//커맨드에서 GetWindowText() 이것을 안하니 다른데에서는 복사가 안되더라 이부분은 정확히는 모르겠고 헤갈린다.
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_EDIT:
			switch (HIWORD(wParam))
			{
				//EN_CHANGE : 문자열을 변경되었다라는 뜻
			case EN_CHANGE:
				//EDIT의 쳐지는 text정보를  (char)Text 로 담는다.
				GetWindowText(EDIT, _Text, 256);
			}
		}

		break;
	}
	return LRESULT();
}
