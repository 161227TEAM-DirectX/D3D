#pragma once
class iGameNode
{
public:
	iGameNode();
	virtual ~iGameNode();

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){}

	
};

