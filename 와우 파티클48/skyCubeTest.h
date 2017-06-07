#pragma once
#include "gameNode.h"

class skyCubeTest : public gameNode
{
//ť���ؽ��� �ٿ�޴°�
//http://www.humus.name/index.php?page=Textures
//
private:
	//camera					_mainCamera;			//���� ī�޶�

private:
	LPDIRECT3DCUBETEXTURE9	_environmentTexture;	//ȯ�� �ؽ���
	LPD3DXMESH				_environmentCubeMesh;	//ȯ�� ť��
	LPD3DXEFFECT			_environmentEffect;		//ȯ�� ����Ʈ

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//ȯ��� ����
	void setEnvironment(string cubeFileName);
	//ȯ��� ����
	void renderEnvironment(void);

	skyCubeTest() : _environmentTexture(NULL), _environmentCubeMesh(NULL) {}
	~skyCubeTest() {}
};

