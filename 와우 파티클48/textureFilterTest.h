#pragma once
#include "gameNode.h"
class textureFilterTest : public gameNode
{
private:
	typedef struct tagVertex
	{
		D3DXVECTOR3 pos;		//������ ��ġ
		D3DXVECTOR2	uv;			//������ UV��ǥ (0.0f ~ 1.0f)
		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
		//D3DFVF_XYZ ������ ��ġ���� | D3DFVF_TEX1 ������ TEXTURE UV ��ǥ�� 1 ����
	}MYVERTEX, *LPMYVERTEX;

	LPDIRECT3DVERTEXBUFFER9		_vb;			//���� ����
	LPDIRECT3DINDEXBUFFER9		_ib;			//�ε��� ����
	LPDIRECT3DTEXTURE9			_texture;		//�ε��� �ؽ��� (png, jpg, bmp, tga, dds) => �ؽ�������(dds : ���̷�Ʈ ���� �ؽ��� ����)
	camera						_mainCamera;	//����ī�޶�
	transform					_quadTrans;		//����Ʈ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateQuad();

	textureFilterTest() {}
	~textureFilterTest() {}
};

