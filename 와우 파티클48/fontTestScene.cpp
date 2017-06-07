#include "stdafx.h"
#include "fontTestScene.h"

HRESULT fontTestScene::init(void)
{
	//肉闘 梓端 幻級奄
	D3DXCreateFont(
		_device,			//巨郊戚什
		50,					//肉闘税 株戚(娃舘備 肉闘滴奄)
		0,					//肉闘税 賑 (戚葵精 益撹 0聖 爽檎 肉闘税 株戚拭 搾景背辞 曽半搾 限仲辞 坦軒吉陥)
		FW_BOLD,			//肉闘 砧臆 竺舛 (瑳球什展析 滴奄)					
		1,					//荒己精 益撹 1
		FALSE,				//戚土遣 食採
		DEFAULT_CHARSET,	//蝶遣斗実 (益撹 巨虹闘)
		OUT_DEFAULT_PRECIS,	//須唖坦軒号縦
		DEFAULT_QUALITY,	//禎君銅
		DEFAULT_PITCH | FF_DONTCARE,	//越獣端 鳶腔軒実 竺舛 戚依亀 益撹 戚依床檎喫
		"叡辞端",				//紫遂吃 肉闘戚硯 益撹 廃越稽 肉闘戚硯 床檎 喫
		&_font				//持失吉 肉闘梓端
	);

	return S_OK;
}

void fontTestScene::release(void)
{
	//肉闘梓端 背薦
	SAFE_RELEASE(_font);
}

void fontTestScene::update(void)
{
}

void fontTestScene::render(void)
{
	/*
	//窒径慎蝕(制亀酔 疎妊域)
	RECT rc = { 100, 100, 0, 0 };
	_font->DrawText(
		NULL,
		"ぜさし 纏爽 観切???",
		-1,
		&rc,
		DT_LEFT | DT_NOCLIP,
		0xfffffffff
	);
	
	//窒径慎蝕(制亀酔 疎妊域)
	RECT rc1 = { 0, 0, 0, 0 };
	_font->DrawText(
		NULL,
		"ぜさし 纏爽 馬走原",
		-1,
		&rc1,
		DT_LEFT | DT_NOCLIP,
		0xfffffffff
	);

	//窒径慎蝕(制亀酔 疎妊域)
	RECT rc2 = { 0, 0, WINSIZEX, WINSIZEY };
	_font->DrawText(
		NULL,
		"ぜさし 纏爽 馬形壱?",
		-1,
		&rc2,
		DT_CENTER | DT_VCENTER,
		0xfffffffff
	);
	*/

	/*肉闘古艦閃 紫遂獣*/
	FONTMANAGER->fontOut("鯵降1.2得~~~", 100, 100, D3DCOLOR_XRGB(255, 255, 0));
	FONTMANAGER->fontOutShadow("鯵降1.2得~~~", 100, 150, D3DCOLOR_XRGB(255, 255, 0));
	FONTMANAGER->fontOutShadow("鯵降1.2得~~~", 100, 200, D3DCOLOR_XRGB(255, 255, 0), D3DCOLOR_XRGB(128, 128, 128));

	FONTMANAGER->addFont("肉闘1", "叡辞端", 50);
	FONTMANAGER->addFont("肉闘2", "妃胡疹端", 30);
	FONTMANAGER->fontOutWithStyle("肉闘1", "拍稽杉球", WINSIZEX / 2, WINSIZEY / 2, 0xffff1234);
	FONTMANAGER->fontOutWithStyle("肉闘2", "拍稽杉球", WINSIZEX / 2, WINSIZEY / 2 + 100, 0xffff1234);
}
