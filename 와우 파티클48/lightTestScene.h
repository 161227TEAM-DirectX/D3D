#pragma once
#include "gameNode.h"

class lightTestScene : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;			//정점버퍼
	LPDIRECT3DINDEXBUFFER9  _ib;			//인덱스버퍼

	camera					_mainCamera;	//메인카메라
	transform				_cubeTrans;		//큐브트렌스
	D3DMATERIAL9			_cubeMaterial;	//큐브재질
	D3DLIGHT9				_light;			//조명
	transform				_lightTrans;	//조명트렌스

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube();
	void RenderCube();

	lightTestScene() {}
	~lightTestScene() {}
};

