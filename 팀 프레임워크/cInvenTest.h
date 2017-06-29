#pragma once
#include "iGameNode.h"
//
class shopHead;
class forceView;

class cInvenTest : public iGameNode
{
private:
	shopHead*	_shopHead;
	forceView*	_forceView;

	D3DVIEWPORT9 smallView;
	D3DVIEWPORT9 foceView;
	LPDIRECT3DSURFACE9 pBackBuffer = NULL;
	D3DSURFACE_DESC d3dsd;
	DWORD g_dwBackBufferWidth = 0;
	DWORD g_dwBackBufferHeight = 0;

public:
	cInvenTest();
	virtual ~cInvenTest();
	
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

