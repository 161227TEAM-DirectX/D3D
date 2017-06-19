#pragma once
#include "iGameNode.h"

class Environment : public iGameNode
{
private:
	LPDIRECT3DCUBETEXTURE9         _temp;
	vector<LPDIRECT3DCUBETEXTURE9> _environmentTexture; //ȯ�� �ؽ���
	LPD3DXMESH                     _environmentCubeMesh;//ȯ�� ť��
	LPD3DXEFFECT                   _environmentEffect;  //ȯ�� ����Ʈ
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

