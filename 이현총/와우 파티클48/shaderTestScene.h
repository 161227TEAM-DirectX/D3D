#pragma once
#include "gameNode.h"

class shaderTestScene : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9	_vb;	//��������
	LPDIRECT3DINDEXBUFFER9	_ib;	//�ε��� ����
	camera		_mainCamera;		//����ī�޶�
	transform	_cubeTrans;			//ť��Ʈ����
	transform	_lightTrans;		//����ƮƮ����


	//����Ʈ���� �Լ�(���̴�)
	LPD3DXEFFECT _effect;			//�ε��� ���̴�
	D3DXHANDLE	 _hTechnique;		//��ũ���ڵ�
	D3DXHANDLE	 _hMatWorld;		//��������ڵ�
	D3DXHANDLE	 _hMatView;			//������ڵ�
	D3DXHANDLE	 _hMatProjection;	//��������ڵ�
	D3DXHANDLE	 _hColor;			//�÷������ڵ�

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void CreateCube();
	void RenderCube();

	shaderTestScene() {}
	~shaderTestScene() {}
};

