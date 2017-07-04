#pragma once
#include "transform.h"
#include "frustum.h"

class camera : public dx::transform
{
public:
	float				_fov;					//카메라 화각
	float				_camNear;				//카메라 Near (근거리)
	float				_camFar;				//카메라 Far	 (원거리)
	float				_aspect;				//카메라 종횡비
	bool				_isOrtho;				//직교냐? (직교투영)
	float				_orthoSize;				//직교시 사이즈
	frustum				_frustum;				//프러스텀
	float				_zoom;

protected:
	D3DXMATRIXA16		_matView;				//뷰행렬
	D3DXMATRIXA16		_matProjection;			//투영행렬
	D3DXMATRIXA16		_matViewProjection;		//뷰 * 투영행렬


private:
	LPDIRECT3DTEXTURE9	_renderTexture;			//렌더링될 Texture
	LPDIRECT3DSURFACE9	_renderSurface;			//렌더 Texture Deapth 버퍼와 Stencil 버퍼가 있는 Surface
	LPDIRECT3DSURFACE9	_deviceTargetSurface;
	LPDIRECT3DSURFACE9	_deviceDepthAndStencilSurface;

public:
	camera();
	~camera();

	//투영행렬과 뷰행렬 업데이트
	void updateMatrix();
	//뷰행렬과 투영행렬 세팅
	void updateCamToDevice();
	//프러스텀 업데이트
	void updateFrustum();
	//카메라 기본 업데이트
	void updateBase();
	void updateBase(bool isKMW);
	//프러스텀 기즈모 그리기.
	void renderFrustumGizmo();

	//카메라 관련 행렬 얻기
	D3DXMATRIXA16 getViewMatrix() { return _matView; }
	D3DXMATRIXA16 getProjectionMatrix() { return _matProjection; }
	D3DXMATRIXA16 getViewProjectionMatrix() { return _matViewProjection; }

	// 카메라 위치 벡터 얻기
	D3DXVECTOR3	getCameraPos();
	//화각 얻기
	float getFOV() { return _fov; }
	//화각 세팅
	void setFOV(float fov) { _fov = fov; }
	//직교 토글
	void orthoToggle() { _isOrtho = !_isOrtho; }

	//화면의 위치를 가지고 카메라의 투영레이를 얻는 함수
	void computeRay(LPRay pOutRay, D3DXVECTOR2* screenPos);
	void computeRay(LPRay pOutRay, D3DXVECTOR2* screenPos, int number);

	//월드 위치로  화면의 위치를 얻는다
	bool getWorldPosToScreenPos(D3DXVECTOR2* pScreenPos, const D3DXVECTOR3* pWorldPos);

	//렌더 Texture 를 준비 한다
	void readyRenderToTexture(int width, int height);

	//Shadow Map Texture를 준비한다.
	void readyShadowTexture(int size);

	//렌더 Texture 로 렌더링 시작
	void renderTextureBegin(DWORD backColor);

	//렌더 Texture 로 렌더링 종료
	void renderTextureEnd();

	//렌더 Texture 얻는다
	LPDIRECT3DTEXTURE9 getRenderTexture() { return _renderTexture; }



	void zoomIn();

	void zoomOut();

	void rotateSLerp();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


};

