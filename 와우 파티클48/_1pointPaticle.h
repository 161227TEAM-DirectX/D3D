#pragma once
#include "gameNode.h"

class _1pointPaticle : public gameNode
{
private:
	//��ƼŬ ���� ����ü
	struct PARTICLE_VERTEX 
	{
		D3DXVECTOR3	pos;	//���� ��ġ
		float		size;	//��ƼŬ ���� ���� ������
		DWORD		color;	//���� �÷�
		enum { FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
	};

	PARTICLE_VERTEX			_particleVertex[3];
	LPDIRECT3DTEXTURE9		_texture;		//��ƼŬ�� �ؽ���

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	_1pointPaticle() {}
	~_1pointPaticle() {}
};

