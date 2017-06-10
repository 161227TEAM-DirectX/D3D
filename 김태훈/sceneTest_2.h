#pragma once
#include "gameNode.h"

class sceneTest_2 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;		//���ع���
	D3DXMATRIXA16 _matWorld;			//�������
	float _angle;						//����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest_2() {}
	~sceneTest_2() {}
};

