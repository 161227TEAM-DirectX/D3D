#include "stdafx.h"
#include "camera.h"
camera::camera() : _isOrtho(FALSE), _renderTexture(NULL), _renderSurface(NULL), _deviceTargetSurface(NULL), _deviceDepthAndStencilSurface(NULL)
{
	//기본화각 60도
	_fov = D3DXToRadian(60);
	//기본 근거리
	_camNear = 0.1f;
	//기본 원거리
	_camFar = 1000.0f;
	//디폴트 종횡비
	_aspect = static_cast<float>(WINSIZEX) / static_cast<float>(WINSIZEY);
	//직교시 사이즈
	_orthoSize = 10.0f;

	_zoom = 1.0f;
}

camera::~camera()
{
	SAFE_RELEASE(_renderTexture);
	SAFE_RELEASE(_renderSurface);
}

void camera::updateMatrix()
{
	//원근투영
	if (_isOrtho == false)
	{
		//화각에 의한 투영행렬 업데이트
		D3DXMatrixPerspectiveFovLH(&_matProjection,	_fov, _aspect, _camNear, _camFar);			
	}
	//직교투영
	else
	{
		D3DXMatrixOrthoLH(&_matProjection, _aspect * _orthoSize, _orthoSize, _camNear, _camFar);
	}

	//뷰행렬 카메라 월드위치에 대한 역행렬
	D3DXMatrixInverse(&_matView, NULL, &matFinal);

	_matViewProjection = _matView * _matProjection;
}

void camera::updateCamToDevice()
{
	//행렬 업데이트
	this->updateMatrix();

	//뷰행렬 세팅
	_device->SetTransform(D3DTS_VIEW, &_matView);
	//투영행렬 세팅
	_device->SetTransform(D3DTS_PROJECTION, &_matProjection);
}

//프러스텀 업데이트
void camera::updateFrustum()
{
	_frustum.updateFrustum(&_matViewProjection);
}

void camera::updateBase()
{
	DefaultControl(_timeDelta);
	updateMatrix();
	updateCamToDevice();
	updateFrustum();
}

void camera::updateBase(bool isKMW)
{
	DefaultControl(_timeDelta, true);
	updateMatrix();
	updateCamToDevice();
	updateFrustum();
}

void camera::renderFrustumGizmo()
{
	_frustum.renderGizmo();
}

D3DXVECTOR3 camera::getCameraPos()
{
	return this->GetWorldPosition();
}

//화면의 위치를 가지고 카메라의 투영레이를 얻는 함수
//인자로서 LPRay를 쓰지말것. &Ray를 쓸것.
void camera::computeRay(LPRay pOutRay, D3DXVECTOR2* screenPos)
{
	//디바이스를 통해 뷰포트를 얻기
	D3DVIEWPORT9 viewPort;
	_device->GetViewport(&viewPort);

	//스크린의 위치 비율을 얻기
	float factorX = screenPos->x / viewPort.Width;
	float factorY = (1.0f - (screenPos->y / viewPort.Height));

	//0 ~ 1 => -1 ~ 1
	factorX = factorX * 2.0f - 1.0f;
	factorY = factorY * 2.0f - 1.0f;

	//투영행렬을 얻기
	D3DXMATRIXA16 matProj = this->getProjectionMatrix();

	//[1][][][]
	//[][1][][]
	//[][][1][]
	//[0][0][0][]
	//화각 스케일량을 나눈다
	D3DXVECTOR3 direction(factorX / matProj._11, factorY / matProj._22, 1.0f);

	//카메라 월드 행렬
	D3DXMATRIXA16 matCamWorld = this->GetFinalMatrix();

	//레이의 방향을 카메라 월드기준으로 계산한다
	//월드 방향이 나온다
	D3DXVec3TransformNormal(&direction, &direction, &matCamWorld);

	//방향벡터 정규화
	D3DXVec3Normalize(&direction, &direction);

	//Ray의 방향
	pOutRay->direction = direction;
	//Ray의 오리진은 카메라의 위치가 된다
	pOutRay->origin = this->GetWorldPosition();
}

void camera::computeRay(LPRay pOutRay, D3DXVECTOR2 * screenPos, int number)
{
	//스크린의 위치 비율을 얻기
	if(number == 1)
	{
		float factorX = screenPos->x / leftViewPort.Width;
		float factorY = (1.0f - (screenPos->y / leftViewPort.Height));


		//0 ~ 1 => -1 ~ 1
		factorX = factorX * 2.0f - 1.0f;
		factorY = factorY * 2.0f - 1.0f;

		//투영행렬을 얻기
		D3DXMATRIXA16 matProj = this->getProjectionMatrix();

		//[1][][][]
		//[][1][][]
		//[][][1][]
		//[0][0][0][]
		//화각 스케일량을 나눈다
		D3DXVECTOR3 direction(
			factorX / matProj._11,
			factorY / matProj._22,
			1.0f);

		//카메라 월드 행렬
		D3DXMATRIXA16 matCamWorld = this->GetFinalMatrix();

		//레이의 방향을 카메라 월드기준으로 계산한다
		D3DXVec3TransformNormal(&direction, &direction, &matCamWorld);

		//방향벡터 정규화
		D3DXVec3Normalize(&direction, &direction);

		//Ray의 방향
		pOutRay->direction = direction;
		//Ray의 오리진은 카메라의 위치로
		pOutRay->origin = this->GetWorldPosition();

		////디바이스를 통해 뷰포트를 얻기

		_device->GetViewport(&leftViewPort);
	}

	if(number == 2)
	{
		D3DVIEWPORT9 viewPort;
		////디바이스를 통해 뷰포트를 얻기
		_device->GetViewport(&viewPort);

		float factorX = screenPos->x / WINSIZEX;
		float factorY = (1.0f - (screenPos->y / WINSIZEY));


		//0 ~ 1 => -1 ~ 1
		factorX = factorX * 2.0f - 1.0f;
		factorY = factorY * 2.0f - 1.0f;

		//투영행렬을 얻기
		D3DXMATRIXA16 matProj = this->getProjectionMatrix();

		//[1][][][]
		//[][1][][]
		//[][][1][]
		//[0][0][0][]
		//화각 스케일량을 나눈다
		D3DXVECTOR3 direction(
			factorX / matProj._11,
			factorY / matProj._22,
			1.0f);

		//카메라 월드 행렬
		D3DXMATRIXA16 matCamWorld = this->GetFinalMatrix();

		//레이의 방향을 카메라 월드기준으로 계산한다
		D3DXVec3TransformNormal(&direction, &direction, &matCamWorld);

		//방향벡터 정규화
		D3DXVec3Normalize(&direction, &direction);

		//Ray의 방향
		pOutRay->direction = direction;
		//Ray의 오리진은 카메라의 위치로
		pOutRay->origin = this->GetWorldPosition();
	}
}

bool camera::getWorldPosToScreenPos(D3DXVECTOR2 * pScreenPos, const D3DXVECTOR3 * pWorldPos)
{
	//카메라의 ViewProjection 행렬을 얻는다.
	D3DXMATRIXA16 matViewProj = this->getViewProjectionMatrix();

	//월드 위치를 동차로...
	D3DXVECTOR3 pos;
	D3DXVec3TransformCoord(&pos, pWorldPos, &matViewProj);

	//동차공간
	//				*-------*<-( 1, 1, 1 )
	//			   /|      /|
	//			  *-------* |
	//            | *-----|-*
	//		      |/      |/
	//(-1,-1, 0)->*-------* 

	//0 ~ 1 사이 값에 없으면 이면 카메라 뒤에 있다는예기
	if (pos.z < 0.0f || pos.z > 1.0f) return false;

	//화면 중앙에 있다면 pos xy 값은 다음과 같다.
	//pos.x == 0  
	//pos.y == 0

	//화면 절반 사이즈
	float halfScreenW = WINSIZEX * 0.5f;
	float halfScreenH = WINSIZEY * 0.5f;

	//최종 화면 위치
	pScreenPos->x = halfScreenW + (halfScreenW * pos.x);
	pScreenPos->y = halfScreenH - (halfScreenH * pos.y);	//Y 값은 반전

	return true;
}

void camera::readyRenderToTexture(int width, int height)
{
	SAFE_RELEASE(_renderTexture);
	SAFE_RELEASE(_renderSurface);

	//RenderTarget 빈 Texture 만들기
	_device->CreateTexture(
		width,						//Texture 가로 해상도 
		height,						//Texture 세로 해상도
		1,							//밉맵체인 레벨
		D3DUSAGE_RENDERTARGET,		//RenderTarget 용 Texture이다
		D3DFMT_A8R8G8B8,			//TEXTURE 포맷 RenderTexture 용은D3DFMT_A8R8G8B8 로하자
		D3DPOOL_DEFAULT,			//RenderTarget 용 Texture 는 Pool 을 Default
		&_renderTexture,			//생성된 Texture 받아올 포인터
		NULL
	);

	//Render 할 Surface 
	_device->CreateDepthStencilSurface(
		width,						//Texture 가로 해상도 
		height,						//Texture 세로 해상도
		D3DFMT_D24S8,				//Deapth 는 24 비트 Stencil 은 8 비트	
		D3DMULTISAMPLE_NONE,		//멀티 샘플링 안티알리아싱은 존재하지 않는다, 
		0,							//멀티 샘플링 퀄리티는 0
		TRUE,						//버퍼 교체시 이전 퍼버내용을 유지하지 않니? ( TRUE 로 쓰면 버퍼교체 될때 이전에 써진 버퍼내용을 기억하지 않는다 )
		&_renderSurface,			//얻어올 포인터...
		NULL);
}

void camera::readyShadowTexture(int size)
{
	SAFE_RELEASE(_renderTexture);
	SAFE_RELEASE(_renderSurface);

	//RenderTarget 빈 Texture 만들기
	_device->CreateTexture(
		size,						//Texture 가로 해상도 
		size,						//Texture 세로 해상도
		1,							//밉맵체인 레벨
		D3DUSAGE_RENDERTARGET,		//RenderTarget 용 Texture이다
		D3DFMT_R32F,				//모든 컬러 버퍼를 Red 로 다사용 ( 4byte float 실수로 사용 )
		D3DPOOL_DEFAULT,			//RenderTarget 용 Texture 는 Pool 을 Default
		&_renderTexture,			//생성된 Texture 받아올 포인터
		NULL
	);

	//Render 할 Surface 
	_device->CreateDepthStencilSurface(
		size,						//Texture 가로 해상도 
		size,						//Texture 세로 해상도
		D3DFMT_D24S8,				//Deapth 는 24 비트 Stencil 은 8 비트	
		D3DMULTISAMPLE_NONE,		//멀티 샘플링 안티알리아싱은 존재하지 않는다, 
		0,							//멀티 샘플링 퀄리티는 0
		TRUE,						//버퍼 교체시 이전 퍼버내용을 유지하지 않니? ( TRUE 로 쓰면 버퍼교체 될때 이전에 써진 버퍼내용을 기억하지 않는다 )
		&_renderSurface,			//얻어올 포인터...
		NULL);
}

//렌더 Texture 로 렌더링 시작
void camera::renderTextureBegin(DWORD backColor)
{
	//현 디바이스의 Target 버퍼의표면과 DepthStencil 버퍼의 표면정보를 기억
	_device->GetRenderTarget(0, &_deviceTargetSurface);
	_device->GetDepthStencilSurface(&_deviceDepthAndStencilSurface);

	//RenderTexture 의 Surface 를 얻는다.
	LPDIRECT3DSURFACE9 texSurface = NULL;
	if (SUCCEEDED(this->_renderTexture->GetSurfaceLevel(0, &texSurface)))
	{
		//Texture 표면을 Device 의 Target 버퍼로 세팅한다.
		_device->SetRenderTarget(0, texSurface);

		//세팅된 Surface 정보는 바로 날려주는 센스
		SAFE_RELEASE(texSurface);
	}

	//Depth 버퍼와 Stencil 버퍼의 Surface 로 _renderSurface 세팅
	_device->SetDepthStencilSurface(_renderSurface);

	//디바이스 버퍼 클리어 (위에서 세팅된 텍스쳐랑 서피스가 클리어 된다)
	_device->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		backColor,
		1.0f,
		0);
}

//렌더 Texture 로 렌더링 종료
void camera::renderTextureEnd()
{
	//Render Texture에 그릴 작업이 끝났으면 다시 원상복귀하는 센스
	_device->SetRenderTarget(0, _deviceTargetSurface);
	_device->SetDepthStencilSurface(_deviceDepthAndStencilSurface);

	//세팅된 Surface 정보는 바로 날려주는 센스
	SAFE_RELEASE(_deviceTargetSurface);
	SAFE_RELEASE(_deviceDepthAndStencilSurface);
}


void camera::zoomIn()
{
	this->MovePositionWorld( this->GetForward() * 0.2f);
}

void camera::zoomOut()
{
	this->MovePositionWorld( this->GetForward() * -0.2f);
}

void camera::rotateSLerp()
{
}

void camera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WORD Wheel = HIWORD(lParam);
	switch (message)
	{
	case WM_MOUSEWHEEL:
		((short)HIWORD(wParam)<0) ? zoomOut() : zoomIn();

		break;
	default:
		break;
	}
}
