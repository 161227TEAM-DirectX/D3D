#pragma once
#include "gameNode.h"
#include "grid.h"

class sceneTest_4 : public gameNode
{
private:
	grid* _grid;

	LPDIRECT3DVERTEXBUFFER9 _vb;	//������ ������ ��������
	LPDIRECT3DINDEXBUFFER9 _ib;		//���� �ε����� ������ �ε�������
	D3DXMATRIXA16 _matWorld;		//���� ��Ʈ����
	float _angle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest_4() {}
	~sceneTest_4() {}
};

