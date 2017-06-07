#pragma once
#include "gameNode.h"

class normalTest1 : public gameNode
{
private:
	typedef struct tagVertex
	{
		D3DXVECTOR3 pos;		//정점의 위치
		D3DXVECTOR2	uv;			//정점의 UV좌표 (0.0f ~ 1.0f)
		D3DXVECTOR3 normal;		//노멀벡터
	}MYVERTEX, *LPMYVERTEX;

	LPDIRECT3DVERTEXBUFFER9			_vb;			//정점버퍼
	LPDIRECT3DINDEXBUFFER9			_ib;			//인덱스버퍼
	LPDIRECT3DTEXTURE9				_texture;		//텍스쳐
	LPDIRECT3DVERTEXDECLARATION9	_vDeclation;	//정점정보선언

	camera							_mainCamera;	//메인카메라
	transform						_quadTrans;		//평면트렌스
	transform						_lightTrans;	//광원트렌스

	LPD3DXEFFECT					_effect;		//셰이더 이펙트

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateQuad();

	normalTest1() {}
	~normalTest1() {}
};

