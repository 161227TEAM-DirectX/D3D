#include "stdafx.h"
#include "stageOne.h"
#include "xPlayer.h"
#include "Environment.h"
#include "WaterTerrain.h"
#include "mapObject.h"


stageOne::stageOne()
	:_shadowDistance(0.0f), angleZ(90), currTime(0.0f)
{
	_mainCamera = new camera;
	_directionLightCamera = new camera;
	sceneBaseDirectionLight = new lightDirection;
	player = new xPlayer;
	env = new Environment;
	water = new WaterTerrain;
	water->linkCamera(*_mainCamera);
	toRotate = new dx::transform;
}


stageOne::~stageOne()
{
	for (int i = 0; i < _renderObject.size(); i++)
	{
		SAFE_DELETE(_renderObject[i]);
	}
	SAFE_DELETE(_mainCamera);
	SAFE_DELETE(_directionLightCamera);
	SAFE_DELETE(sceneBaseDirectionLight);
	SAFE_DELETE(_terrain);
	SAFE_DELETE(_terrainShadow);
	water->release();
	SAFE_DELETE(water);
	SAFE_DELETE(toRotate);
}

HRESULT stageOne::init()
{
	this->shadowInit();

	_terrain = new terrain;
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_1"));
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("마을지형").tile0);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("마을지형").tile1);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("마을지형").tile2);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("마을지형").tile3);
	_terrain->setSlat(IOMAPMANAGER->loadMapInfo("마을지형").splat);
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("마을지형").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	_terrainShadow = new terrain;
	_terrainShadow->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_1"));
	_terrainShadow->setTile0(IOMAPMANAGER->loadMapInfo("마을지형").tile0);
	_terrainShadow->setTile1(IOMAPMANAGER->loadMapInfo("마을지형").tile1);
	_terrainShadow->setTile2(IOMAPMANAGER->loadMapInfo("마을지형").tile2);
	_terrainShadow->setTile3(IOMAPMANAGER->loadMapInfo("마을지형").tile3);
	_terrainShadow->setSlat(IOMAPMANAGER->loadMapInfo("마을지형").splat);
	_terrainShadow->setMapPosition(IOMAPMANAGER->loadMapInfo("마을지형").vecPos);
	_terrainShadow->setting();
	_terrainShadow->changeHeightTerrain();

	//환경맵 초기화
	env->init();
	env->linkCamera(*_mainCamera);

	water->init(3.0f, 256);

	//맵 오브젝트 초기화
	IOSAVEOBJECTMANAGER->loadFile("마을오브젝트");
	for (int i = 0; i < IOSAVEOBJECTMANAGER->getCount(); i++)
	{
		tagSaveObject object;
		memset(&object, 0, sizeof(tagSaveObject));

		object = IOSAVEOBJECTMANAGER->findTag("넘버" + to_string(i + 1));
		baseObject* temp = new baseObject;
		D3DXMATRIX matRotate;
		objectSet->objectSet(object.objectNumber, temp, matRotate, object.objectX, object.objectY, object.objectZ, 0.6f, object.objectRotate);

		_renderObject.push_back(temp);
	}


	//환경맵 / 물결맵 불러오기
	IOSAVEMANAGER->loadFile("마을세이브맵");

	envTemp = IOSAVEMANAGER->findTag("환경맵");
	waterTemp = IOSAVEMANAGER->findTag("물결맵");

	float tempY = _terrain->getHeight(0.0f, 0.0f);


	//플레이어 초기화
	player->out_setlinkTerrain(*_terrain);
	player->init();
	player->getPlayerObject()->_transform->SetWorldPosition(0.0f, tempY, 0.0f);
	player->getPlayerObject()->_transform->SetScale(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < player->getRenderObject().size(); i++)
	{
		_renderObject.push_back(player->getRenderObject()[i]);
	}

	ACMANAGER->Init(*_terrain, *player);
	
	SOUNDMANAGER->play("필드1", 0.1f);

	_mainCamera->out_SetLinkTrans(player->getPlayerObject()->_transform);
	_mainCamera->out_SetRelativeCamPos(D3DXVECTOR3(0, 5, 5));

	return S_OK;
}

void stageOne::release()
{
}

void stageOne::update()
{
	shadowUpdate();

	currTime += _timeDelta;
	if (currTime > 1)
	{
		//D3DXVECTOR3 matAxis(0.0f, 0.0f, 1.0f);
		D3DXMatrixIdentity(&matRotate);
		//D3DXMatrixRotationAxis(&matRotate, &matAxis, D3DXToRadian(angleZ));
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(angleZ));
		//_sceneBaseDirectionLight->_transform->RotateWorld(0.0f, 0.0f, D3DXToRadian(angleZ));
		//sceneBaseDirectionLight->_transform->SetRotateWorld(matRotate);
		toRotate->SetRotateWorld(matRotate);
		angleZ--;
		if (angleZ <= 0) angleZ = 360;
		else if (angleZ >= 360) angleZ = 0;
		currTime = 0;
	}

	sceneBaseDirectionLight->_transform->RotateSlerp(*sceneBaseDirectionLight->_transform, *toRotate, _timeDelta);

	player->update();

	player->out_setTargetByMouse(_mainCamera);

	//오브젝트 업데이트
	for (int i = 0; i < _renderObject.size(); i++) _renderObject[i]->update();

	water->update(waterTemp.number);
}

void stageOne::render()
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

	_terrain->render(_mainCamera, sceneBaseDirectionLight, _directionLightCamera);


	env->renderEnvironment(envTemp.number);
	water->render(waterTemp.number);

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
		if (_cullObject[i] == player->getPlayerObject())
		{
			player->out_ItemUpdate();
			player->out_updateBladeLight();
		}
	}
	player->render();
}

void stageOne::shadowInit(void)
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
	sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);
}

void stageOne::shadowUpdate(void)
{
	_mainCamera->updateBase();
	//sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

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
	this->readyShadowMap(&this->_renderObject, this->_terrainShadow);
}

void stageOne::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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
