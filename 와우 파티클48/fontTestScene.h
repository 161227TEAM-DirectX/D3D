#pragma once
#include "gameNode.h"

class fontTestScene : public gameNode
{
private:
	LPD3DXFONT _font;		//���̷�Ʈ ��Ʈ

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	fontTestScene() {}
	~fontTestScene() {}
};

