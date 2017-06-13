#pragma once
#include "singletonBase.h"

class spriteManager : public singletonBase <spriteManager>
{
private:
	LPD3DXSPRITE	_sprite;	//��������Ʈ

public:
	HRESULT init(void);
	void release(void);

	//��������Ʈ ���� ���۽� ȣ��
	void beginSpriteRender();			
	//��������Ʈ ���� ����� ȣ��
	void endSpriteRender();	

	//�Ϲݷ���(�ؽ���, �׸�������Ʈ, ��ġ��ǥ x, y, ���̴� ����, �̹����߽���)
	void renderTexture(
		LPDIRECT3DTEXTURE9 texture,
		LPRECT rcSour,
		float posX, float posY,
		DWORD color = 0xffffffff,
		D3DXVECTOR3* center = NULL);

	//��������Ʈ ũ�� �� ȸ������
	void renderTexture(
		LPDIRECT3DTEXTURE9 texture, 
		LPRECT rcSour,
		float posX, float posY,
		float scaleX, float scaleY,
		float rotate,
		DWORD color = 0xffffffff,
		D3DXVECTOR3* center = NULL);

	//��Ʈ�� ������ŭ ����
	void renderArea(
		LPDIRECT3DTEXTURE9 texture,
		LPRECT rcSour,
		LPRECT rcDest,
		DWORD color = 0xffffffff);

	//������ġ
	void renderNinePatch(
		LPDIRECT3DTEXTURE9 texture,
		LPRECT rcSour,
		LPRECT rcDest,
		LPRECT rcCenter,
		DWORD color = 0xffffffff,
		bool isDrawCenter = true);

	spriteManager() {}
	~spriteManager() {}
};

