#pragma once
#include "gameNode.h"

class fontTestScene : public gameNode
{
private:
	LPD3DXFONT _font;		//다이렉트 폰트

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	fontTestScene() {}
	~fontTestScene() {}
};

