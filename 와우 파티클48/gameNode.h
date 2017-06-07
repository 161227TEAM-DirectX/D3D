#pragma once

class gameNode
{
protected:
	camera* _mainCamera;
	LPDIRECT3DCUBETEXTURE9	_environmentTexture;		//환경 텍스쳐
	LPD3DXMESH				_environmemtSphereMesh;		//환경 구
	LPD3DXEFFECT			_environmentEffect;			//환경 이펙트

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void renderSprite(void) {};
	void renderEnvironment(void);
	void setEnvironment(string cubeFilePath);

	//카메라 업데이트
	void updateCamera(void);

	//메인 프로시져
	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();
};