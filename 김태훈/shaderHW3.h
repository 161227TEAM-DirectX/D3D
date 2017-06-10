#pragma once
#include "gameNode.h"

class shaderHW3 : public gameNode
{
private:
	typedef struct tagVertex
	{
		D3DXVECTOR3 pos;		//������ ��ġ
		D3DXVECTOR2	uv;			//������ UV��ǥ (0.0f ~ 1.0f)
		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
		//D3DFVF_XYZ ������ ��ġ���� | D3DFVF_TEX1 ������ TEXTURE UV ��ǥ�� 1 ����
	}MYVERTEX, *LPMYVERTEX;

private:
	LPDIRECT3DVERTEXBUFFER9		_vb;			//���� ����
	LPDIRECT3DINDEXBUFFER9		_ib;			//�ε��� ����
	LPD3DXEFFECT				_effect;		//�ε��� ���̴�
	LPDIRECT3DTEXTURE9			_texControl;	//��Ʈ�� �ؽ���
	LPDIRECT3DTEXTURE9			_texTile1;		//Ÿ��1 �ؽ���
	LPDIRECT3DTEXTURE9			_texTile2;		//Ÿ��2 �ؽ���
	LPDIRECT3DTEXTURE9			_texTile3;		//Ÿ��3 �ؽ���
	LPDIRECT3DTEXTURE9			_texTile4;		//Ÿ��4 �ؽ���

	camera						_mainCamera;	//����ī�޶�
	transform					_quadTrans;		//����Ʈ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateQuad();

	shaderHW3() {}
	~shaderHW3() {}
};

