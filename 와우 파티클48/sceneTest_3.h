#pragma once
#include "gameNode.h"

class sceneTest_3 : public gameNode
{
private:
	MYVERTEX _vertex[4];
	DWORD _index[6];
	float _angle;
	D3DXMATRIXA16 _matWorld;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest_3() {}
	~sceneTest_3() {}
};

