#pragma once
#include "gameNode.h"

class spriteTest : public gameNode
{
private:
	LPDIRECT3DTEXTURE9 _tex;	//�ؽ���
	float _angle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	spriteTest() {}
	~spriteTest() {}
};

