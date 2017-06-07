#pragma once
#include "gameNode.h"

class hierarchyScene3 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;		//��������
	LPDIRECT3DINDEXBUFFER9 _ib;			//�ε�������

	transform	_cubeTrans;				//ť��
	vector<transform*> _followTrans;		//����ٴϴ� Ʈ��������
		
	transform _camTrans;				//ī�޶� Ʈ������
	camera _mainCamera;					//����ī�޶�

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube();
	void RenderCube();

	hierarchyScene3() {}
	~hierarchyScene3() {}
};

