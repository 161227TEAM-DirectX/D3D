#pragma once
#include "gameNode.h"

class _1pointPaticle : public gameNode
{
private:
	//파티클 정점 구조체
	struct PARTICLE_VERTEX 
	{
		D3DXVECTOR3	pos;	//정점 위치
		float		size;	//파티클 사용시 정점 사이즈
		DWORD		color;	//정점 컬러
		enum { FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
	};

	PARTICLE_VERTEX			_particleVertex[3];
	LPDIRECT3DTEXTURE9		_texture;		//파티클용 텍스쳐

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	_1pointPaticle() {}
	~_1pointPaticle() {}
};

