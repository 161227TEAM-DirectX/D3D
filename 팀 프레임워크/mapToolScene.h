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
	//ȭ�� ������ ��Ƶ� ����
	D3DSURFACE_DESC d3dsd;
	//ȭ�� ������ ���� ��Ƶ� ����
	DWORD g_dwBackBufferWidth = 0;
	//ȭ�� ������ ���� ��Ƶ� ����
	DWORD g_dwBackBufferHeight = 0;

public:
	mapToolScene();
	virtual ~mapToolScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

