#pragma once
#include "gameNode.h"

class skyCubeTest : public gameNode
{
//큐브텍스쳐 다운받는곳
//http://www.humus.name/index.php?page=Textures
//
private:
	//camera					_mainCamera;			//메인 카메라

private:
	LPDIRECT3DCUBETEXTURE9	_environmentTexture;	//환경 텍스쳐
	LPD3DXMESH				_environmentCubeMesh;	//환경 큐브
	LPD3DXEFFECT			_environmentEffect;		//환경 이펙트

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//환경맵 세팅
	void setEnvironment(string cubeFileName);
	//환경맵 렌더
	void renderEnvironment(void);

	skyCubeTest() : _environmentTexture(NULL), _environmentCubeMesh(NULL) {}
	~skyCubeTest() {}
};

