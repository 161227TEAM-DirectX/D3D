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

	//�̹��� ȸ��
	//SPRITEMANAGER->renderTexture(_tex, &rc, GetMousePos().x, GetMousePos().y,
	//	1, 1,		//������
	//	_angle);	//ȸ��
	
	//SPRITEMANAGER->renderTexture(_tex, &rc, GetMousePos().x, GetMousePos().y,
	//	1, 1,		//������
	//	_angle,		//ȸ��
	//	0xffffffff, //�����̹���
	//	&D3DXVECTOR3(50, 50, 0)); //ȸ����ų ������

	//������ġ
	RECT rcCenter = { 10, 10, 50, 50 };
	SPRITEMANAGER->renderNinePatch(
		_tex,
		&rc, &rc2, &rcCenter, 0xffffffff, false);

}
