#pragma once
#include "gameNode.h"

class xMeshLoadinigWithCorrectMatrix : public gameNode
{
private:
	LPD3DXMESH					_mesh;
	transform					_meshTrans;
	DWORD						_materialsNum;	//로딩된 매쉬의 재질 갯수
	vector<LPDIRECT3DTEXTURE9>	_vecTextures;	//로딩된 메쉬에서 사용하는 Texture
	vector<D3DMATERIAL9>		_vecMaterials;	//로딩된 메쉬에서 사용하는 매터리얼...

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	xMeshLoadinigWithCorrectMatrix() {}
	~xMeshLoadinigWithCorrectMatrix() {}
};

