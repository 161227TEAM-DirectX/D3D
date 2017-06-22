#include "stdafx.h"
#include "stageThree.h"
#include "bossMonster.h"
#include "xPlayer.h"


stageThree::stageThree()
	:_shadowDistance(0.0f)
{
	_mainCamera = new camera;
	_directionLightCamera = new camera;
	sceneBaseDirectionLight = new lightDirection;
}


stageThree::~stageThree()
{
	for (int i = 0; i < _renderObject.size(); i++)
	{
		SAFE_DELETE(_renderObject[i]);
	}
	SAFE_DELETE(_mainCamera);
	SAFE_DELETE(_directionLightCamera);
	SAFE_DELETE(sceneBaseDirectionLight);
}

HRESULT stageThree::init()
{
	this->shadowInit();

	bossMonster* boss = new bossMonster;
	boss->setMesh(XMESH_MANAGER->GetXmeshSkinned("데스윙"));
	boss->_transform->SetScale(5.0f, 5.0f, 5.0f);
	boss->_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
	boss->setActive(true);
	_renderObject.push_back(boss);


	return S_OK;
}

void stageThree::release()
{
}

void stageThree::update()
{
	// shadowUpdate();

	//오브젝트 업데이트
	for (int i = 0; i < _renderObject.size(); i++) _renderObject[i]->update();
}

void stageThree::render()
{
	_directionLightCamera->_frustum.renderGizmo();

	//카메라에 컬링된것만
	this->_cullObject.clear();
	for (int i = 0; i < this->_renderObject.size(); i++)
	{
		//프러스텀 확인
		if (_mainCamera->_frustum.isInFrustum(_renderObject[i]))
		{
			this->_cullObject.push_back(_renderObject[i]);
		}
	}

	//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	xMeshStatic::setCamera(_mainCamera);
	//xMeshStatic::setTechniqueName("ReciveShadow");
	xMeshStatic::setTechniqueName("Toon");
	xMeshStatic::_staticMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshStatic::setBaseLight(this->sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->sceneBaseDirectionLight);

	for (int i = 0; i < this->_cullObject.size(); i++)
	{
		this->_cullObject[i]->render();
	}
}

void stageThree::shadowInit(void)
{
	//배경씬 기본 빛 초기화
	sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight->_intensity = 1.0f;

	//그림자를 만들 카메라 박스 크기 조절용 변수 초기화
	_shadowDistance = 100.0f;

	//그림자 카메라의 투영 방식 변경 및 근접 / 원거리 크기 조절
	_directionLightCamera->_isOrtho = true;	//직교투영
	_directionLightCamera->_camNear = 0.1f;	//근거리
	_directionLightCamera->_camFar = _shadowDistance * 2.0f;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = _shadowDistance * 1.5f;	//투영크기

	//텍스처 준비
	_directionLightCamera->readyShadowTexture(4096);

	_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);

	sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);
}

void stageThree::shadowUpdate(void)
{
	_mainCamera->updateBase();
	sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	//광원 위치
	D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();	//메인카메라의 위치
	D3DXVECTOR3 camFront = _mainCamera->GetForward();		//메인카메리의 정면
	D3DXVECTOR3 lightDir = sceneBaseDirectionLight->_transform->GetForward();	//방향성 빛의 방향

	D3DXVECTOR3 lightPos = camPos +
		(camFront * (_shadowDistance * 0.5f)) +
		(-lightDir * _shadowDistance);

	_directionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	_directionLightCamera->LookDirection(lightDir);

	//쉐도우맵 준비
//	this->readyShadowMap(&this->_renderObject, /*지형정보*/)
}

void stageThree::shadowRender(void)
{

}

void stageThree::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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
		if (this->_mainCamera->_frustum.isInFrustum((*renderObjects)[i]))
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
		pTerrain->renderShadow(_mainCamera);
	}

	_directionLightCamera->renderTextureEnd();
}
