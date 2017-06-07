#pragma once
#include "gameNode.h"

class sceneTest_1 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;	//정점 데이터를 보관할 버텍버퍼

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest_1() {}
	~sceneTest_1() {}
};

