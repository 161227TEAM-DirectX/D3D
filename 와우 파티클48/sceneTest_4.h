#pragma once
#include "gameNode.h"
#include "grid.h"

class sceneTest_4 : public gameNode
{
private:
	grid* _grid;

	LPDIRECT3DVERTEXBUFFER9 _vb;	//정점을 보관할 정점버퍼
	LPDIRECT3DINDEXBUFFER9 _ib;		//정점 인덱스를 보관할 인덱스버퍼
	D3DXMATRIXA16 _matWorld;		//월드 메트릭스
	float _angle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest_4() {}
	~sceneTest_4() {}
};

