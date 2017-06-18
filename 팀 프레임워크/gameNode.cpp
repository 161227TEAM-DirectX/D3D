#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode() : _environmentTexture(NULL), _environmemtSphereMesh(NULL)
{
	//환경구 이펙트 초기화
	_environmentEffect = RM_SHADERFX->getResource("Resources/Shaders/EnvironmentCube.fx");
	
	//메인카메라 초기화
	_mainCamera = new camera;
	
	//기본 광원 생성
	_sceneBaseDirectionLight = new lightDirection;

	//방향성 광원에 카메라 를 생성한다.
	_directionLightCamera = new camera;

	//방향성광원 자식에 붙인다.
	//_directionLightCamera->AttachTo(_sceneBaseDirectionLight->_transform );

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
}

gameNode::~gameNode()
{
	//환경텍스쳐, 메시 해제
	SAFE_RELEASE(_environmentTexture);
	SAFE_RELEASE(_environmemtSphereMesh);
	//메인카메라 해제
	SAFE_DELETE(_mainCamera);
	//방향성 광원과 카메라 해제
	SAFE_DELETE(this->_sceneBaseDirectionLight);
	SAFE_DELETE(this->_directionLightCamera);
}

HRESULT gameNode::initGameNode(void)
{
	/*가상함수 초기화*/
	//초기화가 제대로 안되었다면 그냥 종료시켜라
	if (FAILED(this->init())) return E_FAIL;

	//메인카메라 RenderToTexture 준비
	_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);
	//0----1
	//|  / |
	//| /  |
	//3----2
	_scenePlaneVertex[0].pos = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	_scenePlaneVertex[1].pos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	_scenePlaneVertex[2].pos = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	_scenePlaneVertex[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	_scenePlaneVertex[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	_scenePlaneVertex[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	_scenePlaneVertex[2].uv = D3DXVECTOR2(1.0f, 1.0f);
	_scenePlaneVertex[3].uv = D3DXVECTOR2(0.0f, 1.0f);
	_scenePlaneIndex[0] = 0;
	_scenePlaneIndex[1] = 1;
	_scenePlaneIndex[2] = 3;
	_scenePlaneIndex[3] = 3;
	_scenePlaneIndex[4] = 1;
	_scenePlaneIndex[5] = 2;

	//포스트 이펙트 로딩
	_postEffect = RM_SHADERFX->getResource("Resources/Shaders/PostEffect.fx");

	return S_OK;
}

void gameNode::releaseGameNode(void)
{
	/*가상함수 해제*/
	this->release();
}

void gameNode::updateGameNode(void)
{

	if (KEYMANAGER->isToggleKey(VK_CAPITAL))
	{
		_mainCamera->DefaultControl(_timeDelta);
	}
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

	/*가상함수 업데이트*/
	this->update();
}

void gameNode::renderGameNode(void)
{
	_directionLightCamera->SetWorldPosition(1, 1, 1);
	_directionLightCamera->RenderGimozo();
	//메인카메라 RTT준비
	_mainCamera->renderTextureBegin(0x00101010);
	
	//환경 렌더
	this->renderEnvironment();
	
	/*가상함수 렌더*/
	this->render();

	//메인카메라 RTT종료
	_mainCamera->renderTextureEnd();

	//포스트 이펙트 세팅
	_postEffect->SetTechnique("Base");
	_postEffect->SetTexture("screenTex", _mainCamera->getRenderTexture());
	float pixelU = 1.0f / WINSIZEX;
	float pixelV = 1.0f / WINSIZEY;
	_postEffect->SetFloat("pixelSizeU", pixelU);
	_postEffect->SetFloat("pixelSizeV", pixelV);
	_postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	_postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);

	//포스트 이펙트 렌더
	UINT iPass;
	_postEffect->Begin(&iPass, 0);
	for (UINT i = 0; i < iPass; i++) 
	{
		_postEffect->BeginPass(i);
		_device->SetFVF(SCENE_VERTEX::FVF);
		_device->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			4,
			2,
			_scenePlaneIndex,
			D3DFMT_INDEX16,
			_scenePlaneVertex,
			sizeof(SCENE_VERTEX));
		_postEffect->EndPass();
	}
	_postEffect->End();
	
	//스프라이트 렌더
	SPRITEMANAGER->beginSpriteRender();
	this->renderSprite(); //렌더스프라이트 (가상함수)
	SPRITEMANAGER->endSpriteRender();
}

//환경맵 세팅
void gameNode::setEnvironment(string cubeFilePath)
{
	//기존의 환경맵이 세팅되어있을지 모르니 먼저 릴리즈해주고 시작하자
	SAFE_RELEASE(_environmentTexture);

	//환경맵 로딩
	D3DXCreateCubeTextureFromFile(_device, cubeFilePath.c_str(), &_environmentTexture);

	//환경구 로딩되어있지 않다면....
	if (_environmemtSphereMesh == NULL)
	{
		D3DXCreateSphere(_device, 3.0f, 20, 20, &_environmemtSphereMesh, NULL);
	}
}

//환경맵 렌더
void gameNode::renderEnvironment(void)
{
	//환경 맵 로딩된게 없다면 리턴해라
	if (_environmentTexture == NULL) return;

	//환경 이펙트 세팅
	_environmentEffect->SetTexture("MyCube_Tex", _environmentTexture);

	//WVP 매트릭스
	D3DXMATRIXA16 matWorld = _mainCamera->GetFinalMatrix();
	D3DXMATRIXA16 matViewProj = _mainCamera->getViewProjectionMatrix();
	D3DXMATRIXA16 matWVP = matWorld * matViewProj;

	//이펙트 세팅
	_environmentEffect->SetMatrix("matWVP", &matWVP);
	_environmentEffect->SetMatrix("matWorld", &matWorld);

	//셰이더 그려라
	UINT numPass;
	_environmentEffect->Begin(&numPass, 0);		//셰이더로 그린다는 것을 알리고 pass 수를 얻는다.
	for (UINT i = 0; i < numPass; i++)			//공정 수대로 돈다.
	{
		_environmentEffect->BeginPass(i);		//i번째 공정시작
		_environmemtSphereMesh->DrawSubset(0);	//구 그려라
		_environmentEffect->EndPass();			//i번째 공정끝
	}
	_environmentEffect->End();					//셰이더로 그리기 끝
}

//셰도우맵 준비
void gameNode::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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

//카메라 업데이트
void gameNode::updateCamera(void)
{
	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();
}



