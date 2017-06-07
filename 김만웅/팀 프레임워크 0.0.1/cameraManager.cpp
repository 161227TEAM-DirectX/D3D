#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init(void)
{
	_eyePos = D3DXVECTOR3(3, 5, -10);		//카메라 눈의 위치
	_lookAtPos = D3DXVECTOR3(0, 0, 0);		//카메라가 바라보는 위치(0, 0, 0)
	_up = D3DXVECTOR3(0, 1, 0);				//상방벡터 (0, 1, 0)

	_camRotX = _camRotY = 0.0f;
	_camDist = 20.0f;
	_ptPrevMouse = { 0, 0 };
	_isLButtonDown = false;
	_target = NULL;


	return S_OK;
}

void cameraManager::release(void)
{
}

void cameraManager::update(void)
{
	D3DXMATRIXA16 matR, matRX, matRY, matView;
	D3DXMatrixRotationX(&matRX, _camRotX);
	D3DXMatrixRotationY(&matRY, _camRotY);
	matR = matRX * matRY;

	_eyePos = D3DXVECTOR3(0, 0, -_camDist);
	D3DXVec3TransformCoord(&_eyePos, &_eyePos, &matR);
	if (_target)
	{
		_lookAtPos = *_target;
		_eyePos = _eyePos + *_target;
	}

	D3DXMatrixLookAtLH(&matView, &_eyePos, &_lookAtPos, &_up);
	_device->SetTransform(D3DTS_VIEW, &matView);
}

void cameraManager::setTarget(D3DXVECTOR3 * target)
{
	//타겟세팅
	_target = target;

//====================================================================
//			## 뷰 스페이스 ##
//====================================================================
	//뷰행렬 및 뷰벡터 준비
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0위치를 바라본다
	D3DXVECTOR3 eyePos(3, 5, -10);			//카메라 눈의 위치
	D3DXVECTOR3 up(0, 1, 0);				//상방벡터 그냥 0,1,0
	//D3DXMatrixLookAtLH(뷰행렬, 눈위치, 바라볼위치, 업벡터)
	D3DXMatrixLookAtLH(&matView, &eyePos, &lookAtPos, &up);
	//뷰행렬 세팅
	_device->SetTransform(D3DTS_VIEW, &matView);
//====================================================================
//			## 투영 ##
//====================================================================
	//투영행렬 준비
	D3DXMATRIXA16 matProjection;
	D3DXMatrixPerspectiveFovLH(
		&matProjection,		//투영행렬
		D3DXToRadian(60),	//화각 60도
		(float)(WINSIZEX) / static_cast<float>(WINSIZEY), //화면 종횡비
		0.01f,				//근거리 평면 거리(0일때 뎁스가 꼬인다)
		100.0f);			//원거리 평면 거리
	//투영행렬 세팅
	_device->SetTransform(D3DTS_PROJECTION, &matProjection);
//============================================================================
	//라이트기능은 잠시 꺼두자
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void cameraManager::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		_isLButtonDown = TRUE;
		_ptPrevMouse.x = LOWORD(lParam);
		_ptPrevMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		_isLButtonDown = FALSE;
		break;
	case WM_MOUSEMOVE:
		if (_isLButtonDown)
		{
			POINT ptCurrMouse;
			ptCurrMouse.x = LOWORD(lParam);
			ptCurrMouse.y = HIWORD(lParam);

			float deltaX = ptCurrMouse.x - _ptPrevMouse.x;
			float deltaY = ptCurrMouse.y - _ptPrevMouse.y;

			_camRotY += (deltaX / 100.0f);
			_camRotX += (deltaY / 100.0f);

			if (_camRotX < -D3DX_PI / 2.0f + 0.0001f)
			{
				_camRotX = -D3DX_PI / 2.0f + 0.0001f;
			}
			if (_camRotX > D3DX_PI / 2.0f - 0.0001f)
			{
				_camRotX = D3DX_PI / 2.0f - 0.0001f;
			}
			_ptPrevMouse = ptCurrMouse;
		}
		break;
	case WM_MOUSEWHEEL:
		_camDist -= GET_WHEEL_DELTA_WPARAM(wParam) / 100.0f;
		if (_camDist < 1) _camDist = 1;
		break;
		
	}
}
