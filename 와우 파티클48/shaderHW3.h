#pragma once
#include "gameNode.h"

class shaderHW3 : public gameNode
{
private:
	typedef struct tagVertex
	{
		D3DXVECTOR3 pos;		//정점의 위치
		D3DXVECTOR2	uv;			//정점의 UV좌표 (0.0f ~ 1.0f)
		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
		//D3DFVF_XYZ 정점의 위치정보 | D3DFVF_TEX1 정점의 TEXTURE UV 좌표는 1 개다
	}MYVERTEX, *LPMYVERTEX;

private:
	LPDIRECT3DVERTEXBUFFER9		_vb;			//정점 버퍼
	LPDIRECT3DINDEXBUFFER9		_ib;			//인덱스 버퍼
	LPD3DXEFFECT				_effect;		//로딩될 셰이더
	LPDIRECT3DTEXTURE9			_texControl;	//컨트롤 텍스쳐
	LPDIRECT3DTEXTURE9			_texTile1;		//타일1 텍스쳐
	LPDIRECT3DTEXTURE9			_texTile2;		//타일2 텍스쳐
	LPDIRECT3DTEXTURE9			_texTile3;		//타일3 텍스쳐
	LPDIRECT3DTEXTURE9			_texTile4;		//타일4 텍스쳐

	camera						_mainCamera;	//메인카메라
	transform					_quadTrans;		//쿼드트렌스

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateQuad();

	shaderHW3() {}
	~shaderHW3() {}
};

