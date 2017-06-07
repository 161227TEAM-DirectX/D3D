#include "stdafx.h"
#include "spriteTest.h"

HRESULT spriteTest::init(void)
{
	_tex = RM_TEXTURE->getResource("Resources/Textures/UI.png");

	_angle = 0.0f;

	return S_OK;
}

void spriteTest::release(void)
{
}

void spriteTest::update(void)
{
	_angle += D3DXToRadian(90) * _timeDelta;
}

void spriteTest::render(void)
{
	RECT rc = { 0, 0, 100, 100 };
	RECT rc2 = { 0, 0, GetMousePos().x, GetMousePos().y };

	//SPRITEMANAGER->renderTexture(_tex, &rc, 100, 100);
	//SPRITEMANAGER->renderTexture(_tex, &rc2, 100, 100);
	//SPRITEMANAGER->renderTexture(_tex, &rc2, 100, 100, 0xff00ff00);

	//이미지 회전
	//SPRITEMANAGER->renderTexture(_tex, &rc, GetMousePos().x, GetMousePos().y,
	//	1, 1,		//스케일
	//	_angle);	//회전
	
	//SPRITEMANAGER->renderTexture(_tex, &rc, GetMousePos().x, GetMousePos().y,
	//	1, 1,		//스케일
	//	_angle,		//회전
	//	0xffffffff, //원본이미지
	//	&D3DXVECTOR3(50, 50, 0)); //회전시킬 센터점

	//나인패치
	RECT rcCenter = { 10, 10, 50, 50 };
	SPRITEMANAGER->renderNinePatch(
		_tex,
		&rc, &rc2, &rcCenter, 0xffffffff, false);

}
