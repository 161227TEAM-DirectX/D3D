#pragma once
#include "gameNode.h"

class lightTestScene : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;			//��������
	LPDIRECT3DINDEXBUFFER9  _ib;			//�ε�������

	camera					_mainCamera;	//����ī�޶�
	transform				_cubeTrans;		//ť��Ʈ����
	D3DMATERIAL9			_cubeMaterial;	//ť������
	D3DLIGHT9				_light;			//����
	transform				_lightTrans;	//����Ʈ����

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

