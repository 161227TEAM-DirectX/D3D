#pragma once
#include "gameNode.h"

class textureTestScene : public gameNode
{
private:
	typedef struct tagVertex
	{
		D3DXVECTOR3 pos;			//정점의 위치
		D3DXVECTOR2	uv;				//정점의 UV좌표 (0.0f ~ 1.0f)
		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
		//현재 정점의 정보를 나타내는 플래그 상수값
	}MYVERTEX, *LPMYVERTEX;

	LPDIRECT3DVERTEXBUFFER9 _vb;	//정점 버퍼
	LPDIRECT3DINDEXBUFFER9 _ib;		//인덱스 버퍼
	//로딩될 텍스쳐(png, jpg, bmp, tga, dds) => 텍스쳐포맷(dds : 다이렉트 전용 텍스쳐 포맷)
	LPDIRECT3DTEXTURE9 _texture;	//로딩될 텍스쳐

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	textureTestScene() {}
	~textureTestScene() {}
};

