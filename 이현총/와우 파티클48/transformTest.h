#pragma once
#include "gameNode.h"

class transformTest : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9		_vb;			//��������
	LPDIRECT3DINDEXBUFFER9		_ib;			//�ε�������
	transform					_cubeTrans;		//ť���� Ʈ������
	camera						_mainCamera;	//����ī�޶�

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube(void);

	transformTest() {}
	~transformTest() {}
};

