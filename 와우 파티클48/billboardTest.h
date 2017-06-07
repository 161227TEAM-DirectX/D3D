#pragma once
#include "gameNode.h"

class billboardTest : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9		_vb;			//��������
	LPDIRECT3DINDEXBUFFER9		_ib;			//�ε�������
	LPDIRECT3DTEXTURE9			_texture;		//�ؽ���
		
	camera						_mainCamera;	//����ī�޶�
	transform					_quadTrans;		//���Ʈ����

	LPD3DXEFFECT				_effect;		//���̴� ����Ʈ

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateQuad();

	billboardTest() {}
	~billboardTest() {}
};

