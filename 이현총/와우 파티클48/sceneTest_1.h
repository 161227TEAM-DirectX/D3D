#pragma once
#include "gameNode.h"

class sceneTest_1 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;	//���� �����͸� ������ ���ع���

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest_1() {}
	~sceneTest_1() {}
};

