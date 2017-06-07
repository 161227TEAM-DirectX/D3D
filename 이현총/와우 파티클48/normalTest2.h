#pragma once
#include "gameNode.h"

class normalTest2 : public gameNode
{
private:
	typedef struct tagVertex
	{
		D3DXVECTOR3 pos;		//������ ��ġ
		D3DXVECTOR2	uv;			//������ UV��ǥ (0.0f ~ 1.0f)
		
		//����Space 3�ѻ�
		D3DXVECTOR3 normal;		//�븻
		D3DXVECTOR3 binormal;	//���̳븻
		D3DXVECTOR3 tangent;	//ź��Ʈ
	}MYVERTEX, *LPMYVERTEX;

	LPDIRECT3DVERTEXBUFFER9			_vb;			//��������
	LPDIRECT3DINDEXBUFFER9			_ib;			//�ε�������
	LPDIRECT3DTEXTURE9				_diffuseTex;	//�ؽ���
	LPDIRECT3DTEXTURE9				_normalTex;		//�ؽ���

	LPDIRECT3DVERTEXDECLARATION9	_vDeclation;	//������������

	camera							_mainCamera;	//����ī�޶�
	transform						_quadTrans;		//���Ʈ����
	transform						_lightTrans;	//����Ʈ����

	LPD3DXEFFECT					_effect;		//���̴� ����Ʈ

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateQuad();

	normalTest2() {}
	~normalTest2() {}
};

