#include "stdafx.h"
#include "fontTestScene.h"

HRESULT fontTestScene::init(void)
{
	//폰트 객체 만들기
	D3DXCreateFont(
		_device,			//디바이스
		50,					//폰트의 높이(간단히 폰트크기)
		0,					//폰트의 폭 (이값은 그냥 0을 주면 폰트의 높이에 비례해서 종횡비 맞춰서 처리된다)
		FW_BOLD,			//폰트 두께 설정 (볼드스타일 크기)					
		1,					//밉맵은 그냥 1
		FALSE,				//이텔릭 여부
		DEFAULT_CHARSET,	//캐릭터셋 (그냥 디폴트)
		OUT_DEFAULT_PRECIS,	//외각처리방식
		DEFAULT_QUALITY,	//퀄러티
		DEFAULT_PITCH | FF_DONTCARE,	//글시체 패밀리셋 설정 이것도 그냥 이것쓰면됨
		"궁서체",				//사용될 폰트이름 그냥 한글로 폰트이름 쓰면 됨
		&_font				//생성된 폰트객체
	);

	return S_OK;
}

void fontTestScene::release(void)
{
	//폰트객체 해제
	SAFE_RELEASE(_font);
}

void fontTestScene::update(void)
{
}

void fontTestScene::render(void)
{
	/*
	//출력영역(윈도우 좌표계)
	RECT rc = { 100, 100, 0, 0 };
	_font->DrawText(
		NULL,
		"ㅌㅅㅇ 탈주 닌자???",
		-1,
		&rc,
		DT_LEFT | DT_NOCLIP,
		0xfffffffff
	);
	
	//출력영역(윈도우 좌표계)
	RECT rc1 = { 0, 0, 0, 0 };
	_font->DrawText(
		NULL,
		"ㅌㅅㅇ 탈주 하지마",
		-1,
		&rc1,
		DT_LEFT | DT_NOCLIP,
		0xfffffffff
	);

	//출력영역(윈도우 좌표계)
	RECT rc2 = { 0, 0, WINSIZEX, WINSIZEY };
	_font->DrawText(
		NULL,
		"ㅌㅅㅇ 탈주 하려고?",
		-1,
		&rc2,
		DT_CENTER | DT_VCENTER,
		0xfffffffff
	);
	*/

	/*폰트매니져 사용시*/
	FONTMANAGER->fontOut("개발1.2팀~~~", 100, 100, D3DCOLOR_XRGB(255, 255, 0));
	FONTMANAGER->fontOutShadow("개발1.2팀~~~", 100, 150, D3DCOLOR_XRGB(255, 255, 0));
	FONTMANAGER->fontOutShadow("개발1.2팀~~~", 100, 200, D3DCOLOR_XRGB(255, 255, 0), D3DCOLOR_XRGB(128, 128, 128));

	FONTMANAGER->addFont("폰트1", "궁서체", 50);
	FONTMANAGER->addFont("폰트2", "휴먼옛체", 30);
	FONTMANAGER->fontOutWithStyle("폰트1", "헬로월드", WINSIZEX / 2, WINSIZEY / 2, 0xffff1234);
	FONTMANAGER->fontOutWithStyle("폰트2", "헬로월드", WINSIZEX / 2, WINSIZEY / 2 + 100, 0xffff1234);
}
