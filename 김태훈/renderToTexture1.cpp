#include "stdafx.h"
#include "renderToTexture1.h"


HRESULT renderToTexture1::init(void)
{
	//원래 있던 메쉬에서 다음과 같은 행렬로 보정시켜  모든 정보를 틀어버리자.
	D3DXMATRIXA16 matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//원본 메쉬로딩
	xMeshStatic* mesh = RM_XMESH->getResource("Resources/Meshes/Fighter/Fighter.x", &matCorrection);

	//라이트 입력
	lightDirection* pLight1 = new lightDirection;
	pLight1->_color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->_intensity = 1.0f;
	//라이트 벡터에 담기
	_lights.push_back(pLight1);


	//오브젝트 생성
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		for (int j = 0; j < OBJECT_NUM; j++)
		{
			baseObject* pNewObject = new baseObject();
			pNewObject->setMesh(mesh);
			pNewObject->setActive(true);
			//위치 셋팅
			pNewObject->_transform->SetWorldPosition(i * 10, 0, j * 20);
			//렌더 오브젝트 입력
			this->_renderObjects.push_back(pNewObject);
		}
	}

	//추가 카메라
	_extraCam = new camera();
	_extraCam->_camFar = 100.0f;

	int width = 512;
	int height = 512;

	//엑스트라 Cam 종횡비
	_extraCam->_aspect = (float)width / (float)height;

	//RenderTarget 빈  texture 만들기
	_device->CreateTexture(
		width,						//텍스쳐 가로 해상도
		height,						//텍스쳐 세로 해상도
		1,							//밉맵체인 레벨
		D3DUSAGE_RENDERTARGET,		//RenderTarget용 Texture
		D3DFMT_A8R8G8B8,			//텍스쳐 포맷. RenderTexture 는 D3DFMT_A8R8G8B8 로 쓰자
		D3DPOOL_DEFAULT,			//RecderTexture 용 Texture 는 Pool 을 Default
		&_renderTexture,			//생성된 텍스쳐 받아올 포인터
		NULL
	);

	//Render할  Surface
	_device->CreateDepthStencilSurface(
		width,						// texture 가로해상도
		height,						// texture 세로해상도
		D3DFMT_D24S8,				//Depth 는 24비트, Stencil 은 8비트
		D3DMULTISAMPLE_NONE,		//멀티 샘플링. 안티알리아싱은 존재하지 않는다.(넣으면 부하 걸림)
		0,							//멀티 샘플링 퀄리티는 0
		TRUE,						//버퍼 교체시 이전 버퍼내용을 유지하니? 안하니?(TRUE 로 쓰면 버퍼교체 될때 이전에 써진 버퍼내용을 기억하지 않는다.)
		&_renderSurface,			//얻어올 포인터
		NULL						//그냥 널
	);
	//※ 주의 : 가로, 세로 크기와 포멧형식은 사용할 텍스쳐나 표면의 크기,
	//포맷형식과 반드시 일치해야 한다.그렇지 않으면 사용할 수 없다.

	return S_OK;
}

void renderToTexture1::release(void)
{
	//라이트 해재
	for (int i = 0; i < this->_lights.size(); i++)
	{
		SAFE_DELETE(this->_lights[i]);
	}
	//오브젝트 해재
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}
	//추가카메라 해제
	SAFE_DELETE(this->_extraCam);
}

void renderToTexture1::update(void)
{
	//추가 카메라 컨트롤
	this->_extraCam->DefaultMyControl(_timeDelta);
	this->_extraCam->updateMatrix();
	this->_extraCam->updateFrustum();


	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_mainCamera->updateFrustum();
	}

	this->_cullObjects.clear();
	for (int i = 0; i < this->_renderObjects.size(); i++) 
	{
		this->_renderObjects[i]->update();

		//프러스텀 안에 있니?
		if (_mainCamera->_frustum.isInFrustum(this->_renderObjects[i]))
		{
			this->_cullObjects.push_back(this->_renderObjects[i]);
		}
	}
}

void renderToTexture1::render(void)
{
	//화면에 랜더링 되는 대신 Texture에 랜더링한다.

	//현 디바이스의 Target 버퍼의표면과 DepthStencil 버퍼의 표면정보를 기억
	LPDIRECT3DSURFACE9		pDeviceTargetSurface;
	LPDIRECT3DSURFACE9		pDeviceDepthAndStencilSurface;
	_device->GetRenderTarget(0, &pDeviceTargetSurface);
	_device->GetDepthStencilSurface(&pDeviceDepthAndStencilSurface);

	//RenderTexture 의 Surface 를 얻는다.
	LPDIRECT3DSURFACE9 texSurface = NULL;
	if (SUCCEEDED(this->_renderTexture->GetSurfaceLevel(0, &texSurface)))
	{
		//Texture 표면을 Device 의 Target 버퍼로 셋팅한다.
		_device->SetRenderTarget(0, texSurface);

		//셋팅된 Surface 정보는 바로 날려주는 예의를 갖추자...
		SAFE_RELEASE(texSurface);
	}

	//Depth 버퍼와 Stencil 버퍼의 Surface로 _renderSurface 셋팅
	_device->SetDepthStencilSurface(_renderSurface);

	//디바이스 버퍼 클리어 (사실 위에서 Setting된 Textuer랑 Surface가 클리어 된다)
	_device->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		0xffffff00,							//재질 정보가 안들어간 부분의 색상
		1.0f,								//그릴 Z 버퍼 깊이(1로 고정하자)
		0);


	xMeshStatic::setCamera(this->_extraCam);
	xMeshStatic::setLighting(&this->_lights);

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
	}

	//Render Texture 에 그릴 작업이 끝났으면 다시 원상복귀하는 센스....
	_device->SetRenderTarget(0, pDeviceTargetSurface);
	_device->SetDepthStencilSurface(pDeviceDepthAndStencilSurface);

	//셋팅된 Surface 정보는 바로 날려주는 예의를 갖추자...
	SAFE_RELEASE(pDeviceTargetSurface);
	SAFE_RELEASE(pDeviceDepthAndStencilSurface);

	xMeshStatic::setCamera(this->_mainCamera);
	xMeshStatic::setLighting(&this->_lights);

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
	}
	//프러텀을 그려보장
	this->_mainCamera->_frustum.renderGizmo();
	//Extra 카메라 프러스텀
	this->_extraCam->_frustum.renderGizmo();
}

void renderToTexture1::renderSprite(void)
{
	RECT rcSour = { 0, 0, 256, 256 };
	RECT rcDest = { 0, 0, 256, 256 };
	SPRITEMANAGER->renderArea(_renderTexture, &rcSour, &rcDest);
}
