#pragma once
#include "gameNode.h"

class defMeshMaterialScene : public gameNode
{
private:
	camera			_mainCamera;		//����ī�޶�
	D3DLIGHT9		_light;				//����
	transform		_lightTrans;		//����Ʈ����

	LPD3DXMESH		_meshCube;			//ť��޽�
	transform		_transCube;			//ť��Ʈ����
	D3DMATERIAL9	_cubeMeterial;		//ť������

	LPD3DXMESH		_meshSphere;		//���޽�
	transform		_transSphere;		//��Ʈ����
	D3DMATERIAL9	_sphereMeterial;	//������

	LPD3DXMESH		_meshTeapot;		//�����ڸ޽�
	transform		_transTeapot;		//������Ʈ����
	D3DMATERIAL9	_teapotMeterial;	//����������

	LPD3DXMESH		_meshTorus;			//���Ӹ޽�
	transform		_transTorus;		//����Ʈ����
	D3DMATERIAL9	_torusMeterial;		//��������

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	defMeshMaterialScene() {}
	~defMeshMaterialScene() {}
};

