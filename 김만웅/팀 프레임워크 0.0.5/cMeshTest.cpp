#include "stdafx.h"
#include "cMeshTest.h"


cMeshTest::cMeshTest()
{
}


cMeshTest::~cMeshTest()
{
}

HRESULT cMeshTest::init()
{
	//메인카메라 초기화
	_mainCamera = new camera;

	//기본 광원 생성
	_sceneBaseDirectionLight = new lightDirection;

	//방향성 광원에 카메라 를 생성한다.
	_directionLightCamera = new camera;

	//기본 값
	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;

	//그림자 거리
	_shadowDistance = 100.0f;

	//카메라의 투영방식을 바꾼다...
	_directionLightCamera->_isOrtho = true;
	_directionLightCamera->_camNear = 0.1f;
	_directionLightCamera->_camFar = _shadowDistance * 2.0f;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = _shadowDistance * 1.5f;	//투영크기는 그림자크기로

	//방향성광원 카메라의 RenderToTexture 준비
	_directionLightCamera->readyShadowTexture(4096);


	//원래 있던 매쉬에서 다음과 같은 행렬로 보정시켜 
	//모든 정보를 틀어버린다.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.007f, 0.007f, 0.007f);
	D3DXMATRIXA16 matCorrection = matScale;

	//기본라이트 방향
	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);

	D3DXMATRIXA16 matCorrection2;
	D3DXMatrixScaling(&matCorrection2, 1.0f, 1.0f, 1.0f);
	xMeshSkinned* pSkinned =
		RM_SKINNED->getResource("Resources/Meshes/Witch/WitchApprentice.X",
								&(matCorrection2*0.1f));

	_pSkinned1 = new skinnedAnimation;
	_pSkinned1->init(pSkinned);
	_pSkinnedTrans1 = new dx::transform;
	_aniObjects.push_back(_pSkinned1);

	baseObject* pChar;
	pChar = new baseObject();
	pChar->setMesh(pSkinned);
	pChar->setActive(true);

	_renderObjects.push_back(pChar);


	return S_OK;
}

void cMeshTest::release()
{
	SAFE_DELETE(_pSkinnedTrans1);
	SAFE_DELETE(_pSkinned1);

	//오브젝트 해제
	for (int i = 0; i < _renderObjects.size(); i++)
	{
		SAFE_DELETE(_renderObjects[i]);
	}

	SAFE_DELETE(_sceneBaseDirectionLight);
	SAFE_DELETE(_directionLightCamera);
	SAFE_DELETE(_mainCamera);
}

void cMeshTest::update()
{
	_pSkinned1->update();

	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();
	_mainCamera->updateFrustum();

	//광원 위치
	D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();		//메인카메라의 위치
	D3DXVECTOR3 camFront = _mainCamera->GetForward();			//메인카메라의 정면
	D3DXVECTOR3 lightDir = _sceneBaseDirectionLight->_transform->GetForward();	//방향성 광원의 방향

	D3DXVECTOR3 lightPos = camPos +
		(camFront * (_shadowDistance * 0.5f)) +
		(-lightDir * _shadowDistance);

	_directionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	_directionLightCamera->LookDirection(lightDir);

	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		_renderObjects[i]->update();
	}

	for (int i=0; i < _aniObjects.size(); i++)
	{
		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			_aniObjects[i]->Play("Idle", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			_aniObjects[i]->Play("Walk", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_aniObjects[i]->Play("run", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('4'))
		{
			_aniObjects[i]->PlayOneShot("Atk01", 0.3, 0.3);
		}
		if (KEYMANAGER->isOnceKeyDown('5'))
		{
			_aniObjects[i]->PlayOneShotAfterHold("Death", 0.3);
		}

		static float speed = 1.0f;
		_pSkinned1->SetPlaySpeed(speed);
	}
}

void cMeshTest::render()
{
	//카메라에 컬링된거만....
	this->_cullObjects.clear();
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		//프러스텀 안에 있니?
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{
			this->_cullObjects.push_back(_renderObjects[i]);
		}
	}

	xMeshStatic::setCamera(_mainCamera);
	if (KEYMANAGER->isStayKeyDown('1'))
	{
		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
		xMeshStatic::setTechniqueName("CreateShadow");
	}
	else
	{
		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
		xMeshStatic::setTechniqueName("ReciveShadow");
	}

	xMeshStatic::setBaseLight(this->_sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resources/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		//this->_cullObjects[i]->render();
	}

	for (int i=0; i < _aniObjects.size(); i++)
	{
		_aniObjects[i]->render(_pSkinnedTrans1);
	}
	//_pSkinned1->render(_pSkinnedTrans1);
}

void cMeshTest::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
{
	//방향성광원에 붙은 카메라의 Frustum 업데이트
	_directionLightCamera->updateMatrix();
	_directionLightCamera->updateFrustum();

	//다이렉션라이팅 카메라에 들어오는 애들만 그린다...
	static vector<baseObject*>	shadowCullObject;
	shadowCullObject.clear();

	for (int i = 0; i < renderObjects->size(); i++)
	{
		//프러스텀 안에 있니?
		if (this->_directionLightCamera->_frustum.isInFrustum((*renderObjects)[i]))
		{
			shadowCullObject.push_back((*renderObjects)[i]);
		}
	}

	//쉐도우 맵 그린다.
	_directionLightCamera->renderTextureBegin(0xffffffff);

	//고정메쉬 세팅
	xMeshStatic::setCamera(this->_directionLightCamera);
	xMeshStatic::setTechniqueName("CreateShadow");
	//스킨드메쉬 세팅
	xMeshSkinned::setCamera(this->_directionLightCamera);
	xMeshSkinned::setTechniqueName("CreateShadow");

	for (int i = 0; i < shadowCullObject.size(); i++)
	{
		if (shadowCullObject[i]->_ignoreCreateShadow == false)
		{
			shadowCullObject[i]->render();
		}
	}

	//만약 Terrain 도 쉐도우 맵을 그려야한다면...
	if (pTerrain != NULL)
	{
		pTerrain->renderShadow(_directionLightCamera);
	}

	_directionLightCamera->renderTextureEnd();


	//만약 Terrain 도 쉐도우 맵을 셋팅한다면
	if (pTerrain != NULL)
	{
		pTerrain->_terrainEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
		pTerrain->_terrainEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
	}

	//쉐도우 텍스쳐
	xMeshStatic::_staticMeshEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
	//쉐도우 행렬
	xMeshStatic::_staticMeshEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
	//쉐도우 텍스쳐
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
	//쉐도우 행렬
	xMeshSkinned::_sSkinnedMeshEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());

}
