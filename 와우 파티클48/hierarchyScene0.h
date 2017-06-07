#pragma once
#include "gameNode.h"

class hierarchyScene0 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;		//��������
	LPDIRECT3DINDEXBUFFER9 _ib;			//�ε�������

	transform _cubeTrans;				//ť��
	transform _childCubeTrans;			//ť���� �ڽ�
	transform _grandChildCubeTrans;		//ť���� �ڽ�

	camera _mainCamera;					//����ī�޶�

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube();
	void RenderCube();

	hierarchyScene0() {}
	~hierarchyScene0() {}
};

