#pragma once
#include "singletonBase.h"

class spriteManager : public singletonBase <spriteManager>
{
private:
	LPD3DXSPRITE	_sprite;	//스프라이트

public:
	HRESULT init(void);
	void release(void);

	//스프라이트 렌더 시작시 호출
	void beginSpriteRender();			
	//스프라이트 렌더 종료시 호출
	void endSpriteRender();	

	//일반렌더(텍스쳐, 그릴영역렉트, 위치좌표 x, y, 섞이는 색상, 이미지중심점)
	void renderTexture(
		LPDIRECT3DTEXTURE9 texture,
		LPRECT rcSour,
		float posX, float posY,
		DWORD color = 0xffffffff,
		D3DXVECTOR3* center = NULL);

	//스프라이트 크기 및 회전가능
	void renderTexture(
		LPDIRECT3DTEXTURE9 texture, 
		LPRECT rcSour,
		float posX, float posY,
		float scaleX, float scaleY,
		float rotate,
		DWORD color = 0xffffffff,
		D3DXVECTOR3* center = NULL);

	//렉트의 영역만큼 렌더
	void renderArea(
		LPDIRECT3DTEXTURE9 texture,
		LPRECT rcSour,
		LPRECT rcDest,
		DWORD color = 0xffffffff);

	//나인패치
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

