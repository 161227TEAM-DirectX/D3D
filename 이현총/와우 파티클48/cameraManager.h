#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase <cameraManager>
{
private:
	D3DXVECTOR3 _eyePos;
	D3DXVECTOR3 _lookAtPos;
	D3DXVECTOR3 _up;
	
	float _camRotX;
	float _camRotY;
	float _camDist;
	bool _isLButtonDown;
	POINT _ptPrevMouse;
	D3DXVECTOR3* _target;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void setTarget(D3DXVECTOR3* target = NULL);
	void MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	cameraManager() {}
	~cameraManager() {}
};

