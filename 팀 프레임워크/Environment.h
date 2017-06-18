#pragma once
#include "iGameNode.h"

class Environment : public iGameNode
{
private:
	LPDIRECT3DCUBETEXTURE9         _temp;
	vector<LPDIRECT3DCUBETEXTURE9> _environmentTexture; //환경 텍스쳐
	LPD3DXMESH                     _environmentCubeMesh;//환경 큐브
	LPD3DXEFFECT                   _environmentEffect;  //환경 이펙트
	camera*						   _mainCamera;

public:
	Environment() : _environmentCubeMesh(nullptr), _environmentEffect(nullptr){}
	~Environment(){}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void linkCamera(camera& temp) { this->_mainCamera = &temp; }

	void renderEnvironment(int number);
};

