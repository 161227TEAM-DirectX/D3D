#pragma once
#include "gameNode.h"

class sceneTest_2 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;		//버텍버퍼
	D3DXMATRIXA16 _matWorld;			//월드행렬
	float _angle;						//각도

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest_2() {}
	~sceneTest_2() {}
};

