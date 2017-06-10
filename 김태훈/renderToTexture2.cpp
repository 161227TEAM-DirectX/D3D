#include "stdafx.h"
#include "renderToTexture2.h"

HRESULT renderToTexture2::init(void)
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

////////////////////////////////////////////////////
	//렌더투 텍스쳐 사용을 위한 내용들... 
	//카메라클래스안에 readyRenderToTexture 있음
	//추가카메라..
	_extraCam = new camera;
	_extraCam->_camFar = 100.0f;
	int width = 512;
	int height = 512;

	//엑스트라Cam 종횡비 
	_extraCam->_aspect = (float)width / (float)height;

	//엑스트라 카메라 RenderToTexture 준비
	_extraCam->readyRenderToTexture(width, height);
////////////////////////////////////////////////////

	return S_OK;
}

void renderToTexture2::release(void)
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

void renderToTexture2::update(void)
{
	//추가 카메라 컨트롤
	_extraCam->DefaultMyControl(_timeDelta);
	_extraCam->updateMatrix();

	for (int i = 0; i < _renderObjects.size(); i++) 
	{
		_renderObjects[i]->update();
	}
}

void renderToTexture2::render(void)
{
	//추가 확장 카메라 렌더링
	_extraCam->updateFrustum();
	_cullObjects.clear();
	for (int i = 0; i < _renderObjects.size(); i++)
	{
		if (_extraCam->_frustum.isInFrustum(_renderObjects[i]))
		{
			_cullObjects.push_back(_renderObjects[i]);
		}
	}
	//빈공간(재질 값이 없는 우주의 영역)에 들어갈 색 지정.
	//렌더 투 텍스쳐 시작
	_extraCam->renderTextureBegin(0xffff0000);

	xMeshStatic::setCamera(_extraCam);
	xMeshStatic::setLighting(&_lights);

	for (int i = 0; i < _cullObjects.size(); i++)
	{
		_cullObjects[i]->render();
	}

	//렌더 투 텍스쳐 끝
	_extraCam->renderTextureEnd();

	//메인카메라 프러스텀 컬링
	_mainCamera->updateFrustum();
	_cullObjects.clear();

	for (int i = 0; i < _renderObjects.size(); i++)
	{
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{
			_cullObjects.push_back(_renderObjects[i]);
		}
	}

	xMeshStatic::setCamera(_mainCamera);
	xMeshStatic::setLighting(&_lights);

	for (int i = 0; i < _cullObjects.size(); i++)
	{
		_cullObjects[i]->render();
	}

	//기즈모를 그려보자
	_extraCam->_frustum.renderGizmo();
}

void renderToTexture2::renderSprite(void)
{
	RECT rcSour = { 0, 0, 512, 512 };
	RECT rcDest = { 0, 0, 512, 512 };
	SPRITEMANAGER->renderArea(_extraCam->getRenderTexture(), &rcSour, &rcDest);
}
