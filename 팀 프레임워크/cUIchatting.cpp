#include "stdafx.h"
#include "cUIchatting.h"


cUIchatting::cUIchatting(int sx,int sy)
{
	//�ؽ����ʱ�ȭ
	memset(_Text, 0, sizeof(_Text));
	_chattingUi.rc2 ={ sx,sy,0,0 };
	_chattingUi.uiNumber = false;
	_chatHeight = 1;
	bHanMode = true;

	//�� �ʱ�ȭ
	_number = FOCUS::FOCUSZERO;
	FONTMANAGER->addFont("�������", "�������", 18);
	IOSAVENAMEMANAGER->loadFile("ResourceUI/chat/����");
	_LoadName = IOSAVENAMEMANAGER->findTag("��Ʈ��ũ");
}


cUIchatting::~cUIchatting()
{
}

void cUIchatting::update()
{
	//���̵� �ε� �Ҷ�� ��� �Ѱ�
	/*if (KEYMANAGER->isOnceKeyDown('M'))
	{
	vector<tagSaveName> _vSaveName;
	tagSaveName _SaveName;
	_SaveName.infoName = "��Ʈ��ũ";
	_SaveName.chatName = "xotmde";
	_SaveName.password = "xxxxxx";
	_vSaveName.push_back(_SaveName);
	IOSAVENAMEMANAGER->saveFile("����", _vSaveName);
	}*/

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		g_isChat = !g_isChat;
		//number�� �����ϱ�
		if (_number >= FOCUS::FOCUSTWO)
		{
			bHanMode = false;
			_number = FOCUS::FOCUSONE;
		}
		else _number++;
	}

	if (_number == FOCUS::FOCUSONE)
	{
		//���͸� �����¼��� EDIT �ڽ��� ��Ŀ���� �������� ĥ�� �ְ� �ȴ�.
		//SetFocus(NULL) : NULL�� �ϸ� ��Ŀ���� EDIT�� �������� �ʾƼ� ĥ���� ���� �ȴ�.
		_chattingUi.uiNumber = true;
		SetFocus(EDIT);
	}

	if (_number == FOCUS::FOCUSTWO)
	{
		//ä��â5�̻󰡸� ���� ��Ű��
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
		//ENTER�� �ѹ��� ���õǸ� ���������� (EDIT)
		//�ԷµǾ��ִ� �ؽ��ĵ� ����������
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
		_chattingUi.tex = RM_TEXTURE->getResource("ResourceUI/chat/ä��â.png");
		SPRITEMANAGER->renderRectTexture(_chattingUi.tex, &_chattingUi.rc1, &_chattingUi.rc2, 0, 0, 1024, 1024, _chattingUi.rc2.left, _chattingUi.rc2.top);
		//��Ʈ ����� �����ϱ����ؼ� 
		FONTMANAGER->fontOutWithStyle("�������", "[" + _LoadName.chatName + "] : " + _Schatting, _chattingUi.rc2.left + 10, _chattingUi.rc2.top + 170, D3DCOLOR_XRGB(255, 255, 210));
	}

	if (_chattingUi.uiNumber == false)
	{
		_chattingUi.tex = RM_TEXTURE->getResource("ResourceUI/chat/ä��â2.png");
		SPRITEMANAGER->renderRectTexture(_chattingUi.tex, &_chattingUi.rc1, &_chattingUi.rc2, 0, 0, 1024, 1024, _chattingUi.rc2.left, _chattingUi.rc2.top);
	}

	//EDIT��ɿ� ���� ���ڸ� TEXT�� ������� �ٽ� temp�� ��Ƽ� ��½����ش�.
	_Schatting = _Text;

	for (int i = 0; i < _vSChat.size(); i++)
	{
		FONTMANAGER->fontOutWithStyle("�������", "[" + _LoadName.chatName + "] : " + _vSChat[i], _chattingUi.rc2.left + 10, ((_chattingUi.rc2.top + 160) + i * 20) - _chatHeight, D3DCOLOR_XRGB(255, 255, 210));
	}

	//FONTMANAGER->fontOut(to_string(bHanMode), 100, 100, D3DCOLOR_XRGB(255, 255, 255));
}



//EDIT�ڽ��� ���� ��Ÿ���� �Ѵ�.
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
				//���ʿ� Tric���� ȭ�� �ۿ� ��ȭâ�� �ΰ� �Ѵ�.               //ȭ���� ��ġ//�����ִ� ���� ���� 
				EDIT = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10000, 10000, 432, 40, hWnd, (HMENU)ID_EDIT, NULL, NULL);
				break;
			}
			break;
		}
		break;

		//Ŀ�ǵ忡�� GetWindowText() �̰��� ���ϴ� �ٸ��������� ���簡 �ȵǴ��� �̺κ��� ��Ȯ���� �𸣰ڰ� �찥����.
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_EDIT:
			switch (HIWORD(wParam))
			{
				//EN_CHANGE : ���ڿ��� ����Ǿ��ٶ�� ��
			case EN_CHANGE:
				//EDIT�� ������ text������  (char)Text �� ��´�.
				GetWindowText(EDIT, _Text, 256);
			}
		}

		break;
	}
	return LRESULT();
}
