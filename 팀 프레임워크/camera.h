#pragma once
#include "transform.h"
#include "frustum.h"

class camera : public dx::transform
{
public:
	float				_fov;					//ī�޶� ȭ��
	float				_camNear;				//ī�޶� Near (�ٰŸ�)
	float				_camFar;				//ī�޶� Far	 (���Ÿ�)
	float				_aspect;				//ī�޶� ��Ⱦ��
	bool				_isOrtho;				//������? (��������)
	float				_orthoSize;				//������ ������
	frustum				_frustum;				//��������
	float				_zoom;

protected:
	D3DXMATRIXA16		_matView;				//�����
	D3DXMATRIXA16		_matProjection;			//�������
	D3DXMATRIXA16		_matViewProjection;		//�� * �������


private:
	LPDIRECT3DTEXTURE9	_renderTexture;			//�������� Texture
	LPDIRECT3DSURFACE9	_renderSurface;			//���� Texture Deapth ���ۿ� Stencil ���۰� �ִ� Surface
	LPDIRECT3DSURFACE9	_deviceTargetSurface;
	LPDIRECT3DSURFACE9	_deviceDepthAndStencilSurface;

public:
	camera();
	~camera();

	//������İ� ����� ������Ʈ
	void updateMatrix();
	//����İ� ������� ����
	void updateCamToDevice();
	//�������� ������Ʈ
	void updateFrustum();
	//ī�޶� �⺻ ������Ʈ
	void updateBase();
	void updateBase(bool isKMW);
	//�������� ����� �׸���.
	void renderFrustumGizmo();

	//ī�޶� ���� ��� ���
	D3DXMATRIXA16 getViewMatrix() { return _matView; }
	D3DXMATRIXA16 getProjectionMatrix() { return _matProjection; }
	D3DXMATRIXA16 getViewProjectionMatrix() { return _matViewProjection; }

	// ī�޶� ��ġ ���� ���
	D3DXVECTOR3	getCameraPos();
	//ȭ�� ���
	float getFOV() { return _fov; }
	//ȭ�� ����
	void setFOV(float fov) { _fov = fov; }
	//���� ���
	void orthoToggle() { _isOrtho = !_isOrtho; }

	//ȭ���� ��ġ�� ������ ī�޶��� �������̸� ��� �Լ�
	void computeRay(LPRay pOutRay, D3DXVECTOR2* screenPos);
	void computeRay(LPRay pOutRay, D3DXVECTOR2* screenPos, int number);

	//���� ��ġ��  ȭ���� ��ġ�� ��´�
	bool getWorldPosToScreenPos(D3DXVECTOR2* pScreenPos, const D3DXVECTOR3* pWorldPos);

	//���� Texture �� �غ� �Ѵ�
	void readyRenderToTexture(int width, int height);

	//Shadow Map Texture�� �غ��Ѵ�.
	void readyShadowTexture(int size);

	//���� Texture �� ������ ����
	void renderTextureBegin(DWORD backColor);

	//���� Texture �� ������ ����
	void renderTextureEnd();

	//���� Texture ��´�
	LPDIRECT3DTEXTURE9 getRenderTexture() { return _renderTexture; }



	void zoomIn();

	void zoomOut();

	void rotateSLerp();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


};

