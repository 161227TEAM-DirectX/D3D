#pragma once
#include "gameNode.h"

class billboardTest : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9		_vb;			//정점버퍼
	LPDIRECT3DINDEXBUFFER9		_ib;			//인덱스버퍼
	LPDIRECT3DTEXTURE9			_texture;		//텍스쳐
		
	camera						_mainCamera;	//메인카메라
	transform					_quadTrans;		//평면트렌스

	LPD3DXEFFECT				_effect;		//셰이더 이펙트

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateQuad();

	billboardTest() {}
	~billboardTest() {}
};

