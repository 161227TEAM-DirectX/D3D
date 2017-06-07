#pragma once
#include "gameNode.h"

class hierarchyScene0 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;		//정점버퍼
	LPDIRECT3DINDEXBUFFER9 _ib;			//인덱스버퍼

	transform _cubeTrans;				//큐브
	transform _childCubeTrans;			//큐브의 자식
	transform _grandChildCubeTrans;		//큐브의 자식

	camera _mainCamera;					//메인카메라

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube();
	void RenderCube();

	hierarchyScene0() {}
	~hierarchyScene0() {}
};

