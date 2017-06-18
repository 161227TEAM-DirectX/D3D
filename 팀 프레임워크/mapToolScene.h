#pragma once
#include "iGameNode.h"

class rightView;
class leftViewHead;

class mapToolScene : public iGameNode
{
private:
	rightView*	   _rightView;
	leftViewHead*  _leftViewHead;
		
private:
	LPDIRECT3DSURFACE9 pBackBuffer = NULL;
	//화면 사이즈 담아둘 변수
	D3DSURFACE_DESC d3dsd;
	//화면 사이즈 넓이 담아둘 변수
	DWORD g_dwBackBufferWidth = 0;
	//화면 사이즈 높이 담아둘 변수
	DWORD g_dwBackBufferHeight = 0;

public:
	mapToolScene();
	virtual ~mapToolScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

