#pragma once
#include "gameNode.h"

class defMeshMaterialScene : public gameNode
{
private:
	camera			_mainCamera;		//메인카메라
	D3DLIGHT9		_light;				//광원
	transform		_lightTrans;		//광원트렌스

	LPD3DXMESH		_meshCube;			//큐브메쉬
	transform		_transCube;			//큐브트렌스
	D3DMATERIAL9	_cubeMeterial;		//큐브재질

	LPD3DXMESH		_meshSphere;		//구메쉬
	transform		_transSphere;		//구트렌스
	D3DMATERIAL9	_sphereMeterial;	//구재질

	LPD3DXMESH		_meshTeapot;		//주전자메쉬
	transform		_transTeapot;		//주전자트렌스
	D3DMATERIAL9	_teapotMeterial;	//주전자재질

	LPD3DXMESH		_meshTorus;			//도넛메쉬
	transform		_transTorus;		//도넛트렌스
	D3DMATERIAL9	_torusMeterial;		//도넛재질

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	defMeshMaterialScene() {}
	~defMeshMaterialScene() {}
};

