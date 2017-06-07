#pragma once
#include "gameNode.h"

class xMeshLoading : public gameNode
{
private:
	LPD3DXMESH					_mesh;
	transform					_meshTrans;
	transform					_meshLocal;
	DWORD						_materialsNum;	//�ε��� �Ž��� ���� ����
	vector<LPDIRECT3DTEXTURE9>	_vecTextures;	//�ε��� �޽����� ����ϴ� Texture
	vector<D3DMATERIAL9>		_vecMaterials;	//�ε��� �޽����� ����ϴ� ���͸���...

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	xMeshLoading() {}
	~xMeshLoading() {}
};

