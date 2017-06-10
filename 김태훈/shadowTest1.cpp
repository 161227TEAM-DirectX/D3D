#include "stdafx.h"
#include "shadowTest1.h"

HRESULT shadowTest1::init(void)
{
	//원래 있던 매쉬에서 다음과 같은 행렬로 보정시켜 
	//모든 정보를 틀어버린다.
	D3DXMATRIXA16 matScale, matRotate;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//원본 메쉬 로딩
	xMeshStatic* mesh = RM_XMESH->getResource("Resources/Meshes/GunShip/gunShip.X", &matCorrection);
	xMeshStatic* box = RM_XMESH->getResource("Resources/Meshes/Disc/Disc.x");

	//오브젝트 생성
	baseObject* newObject1 = new baseObject();
	newObject1->setMesh(mesh);
	newObject1->setActive(true);

	baseObject* newObject2 = new baseObject();
	newObject2->setMesh(mesh);
	newObject2->setActive(true);
	newObject2->_transform->SetWorldPosition(0, -5.0f, 0.0f);

	baseObject* newObject3 = new baseObject();
	newObject3->setMesh(box);
	newObject3->setActive(true);
	newObject3->_transform->SetWorldPosition(0, -10.0f, 0.0f);
	newObject3->_ignoreCreateShadow = true;	//그림자 안그린다.

	//렌더 오브젝트 푸쉬
	_renderObjects.push_back(newObject1);
	_renderObjects.push_back(newObject2);
	_renderObjects.push_back(newObject3);

	//라이트 위치
	this->_sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	this->_sceneBaseDirectionLight->_transform->SetRotateWorld(D3DXToRadian(90), 0, 0);

	return S_OK;
}

void shadowTest1::release(void)
{
	//오브젝트 해제
	for (int i = 0; i < _renderObjects.size(); i++)
	{
		SAFE_DELETE(_renderObjects[i]);
	}
}

void shadowTest1::update(void)
{
	this->_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	_mainCamera->updateFrustum();
	_cullObjects.clear();

	for (int i = 0; i < _renderObjects.size(); i++)
	{
		_renderObjects[i]->update();

		//프러스텀 안에 있니?
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{
			_cullObjects.push_back(_renderObjects[i]);
		}
	}

	//쉐도우맵 준비
	//랜더링될 오브젝트 전달한다 (반드시 Render에서 하지말고 업데이트에서 해라)
	this->readyShadowMap(&_renderObjects);
}

void shadowTest1::render(void)
{
	xMeshStatic::setCamera(_mainCamera);
	//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	xMeshStatic::setTechniqueName("ReciveShadow");		
	//베이스 라이팅 셋팅
	xMeshStatic::setBaseLight(_sceneBaseDirectionLight);
	
	for (int i = 0; i < _cullObjects.size(); i++)
	{
		_cullObjects[i]->render();
	}

	//프러텀을 그려보장
	_directionLightCamera->_frustum.renderGizmo();
	_sceneBaseDirectionLight->_transform->RenderGimozo();
}

void shadowTest1::renderSprite(void)
{
	//쉐도우 맵을 그려보자....
	RECT rcSour = { 0, 0, 4096, 4096 };
	RECT rcDest = { 0, 0, 300, 300 };

	SPRITEMANAGER->renderArea(_directionLightCamera->getRenderTexture(), &rcSour, &rcDest);
}
