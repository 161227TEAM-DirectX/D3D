#pragma once

class gameNode
{
protected:
	camera* _mainCamera;
	LPDIRECT3DCUBETEXTURE9	_environmentTexture;		//ȯ�� �ؽ���
	LPD3DXMESH				_environmemtSphereMesh;		//ȯ�� ��
	LPD3DXEFFECT			_environmentEffect;			//ȯ�� ����Ʈ

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void renderSprite(void) {};
	void renderEnvironment(void);
	void setEnvironment(string cubeFilePath);

	//ī�޶� ������Ʈ
	void updateCamera(void);

	//���� ���ν���
	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();
};