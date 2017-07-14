#include "stdafx.h"
#include "stageThree.h"
#include "bossMonster.h"
#include "xPlayer.h"
#include "terrain.h"
#include "mapObject.h"
#include "Environment.h"
#include "WaterTerrain.h"
#include "cUIPlayer.h"

stageThree* ex_pStage3 = new stageThree;

stageThree::stageThree()
	: boss(nullptr)
	, player(nullptr)
	, _mainCamera(nullptr)
	, _directionLightCamera(nullptr)
	, sceneBaseDirectionLight(nullptr)
	, _terrain(nullptr)
	, _terrainShadow(nullptr)
	, env(nullptr)
	, water(nullptr)
	, _shadowDistance(0.0f)
	, cinematicBool(false)
	, m_pUIPlayer(nullptr)
{
	_mon.clear();
	_renderObject.clear();
	_cullObject.clear();

	memset(&envTemp, 0, sizeof(tagSaveMap));
	memset(&waterTemp, 0, sizeof(tagSaveMap));
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
	SAFE_DELETE(_terrain);
	SAFE_DELETE(_terrainShadow);
	SAFE_DELETE(env);
	SAFE_DELETE(water);
	SAFE_DELETE(m_pUIPlayer);
}



HRESULT stageThree::init()
{
	return S_OK;
}

void stageThree::release()
{
	SAFE_DELETE(m_pUIPlayer);
}

void stageThree::update()
{
	CINEMATICMANAGER->cinematicBossLoad(&boss->_transform->GetWorldPosition(), _mainCamera, boss->_transform);

	if (CINEMATICMANAGER->GetGScineMticBossBool() == true)
	{
		if (cinematicBool == false)
		{
			_mainCamera->out_SetLinkTrans(player->getPlayerObject()->_transform);
			_mainCamera->out_SetRelativeCamPos(D3DXVECTOR3(0, 10, 15));
			cinematicBool = true;
		}
		else
		{
			if (!g_isChat)
			{
				_mainCamera->updateBase();
			}
		}
	}

	shadowUpdate();

	player->update();

	player->out_setTargetByMouse(_mainCamera);

	//오브젝트 업데이트
	for (int i = 0; i < _renderObject.size(); i++) _renderObject[i]->update();

	water->update(waterTemp.number);

	//UI 업데이트
	m_pUIPlayer->update();
	m_pUIPlayer->linkMinimapPlayerAngle(player->getPlayerObject()->_transform->GetAngleY());
	m_pUIPlayer->linkMinimapPlayerMove(player->getPlayerObject()->_transform->GetWorldPosition().x + _terrain->GetTerrainSizeX() / 2,
									   player->getPlayerObject()->_transform->GetWorldPosition().z + _terrain->GetTerrainSizeZ() / 2,
									   _terrain->GetTerrainSizeX());
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

	_terrain->render(_mainCamera, sceneBaseDirectionLight, _directionLightCamera);

	env->renderEnvironment(envTemp.number);
	//	water->render(waterTemp.number);

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

	CINEMATICMANAGER->cinematicBossRender();

	if (CINEMATICMANAGER->GetGScineMticBossBool() == true)
	{
		m_pUIPlayer->render();
	}

}

void stageThree::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pUIPlayer->WndProc(hWnd, message, wParam, lParam);
}

void stageThree::shadowInit(void)
{
	////배경씬 기본 빛 초기화
	//sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	//sceneBaseDirectionLight->_intensity = 1.0f;
	////그림자를 만들 카메라 박스 크기 조절용 변수 초기화
	//_shadowDistance = 100.0f;
	////그림자 카메라의 투영 방식 변경 및 근접 / 원거리 크기 조절
	//_directionLightCamera->_isOrtho = true;	//직교투영
	//_directionLightCamera->_camNear = 0.1f;	//근거리
	//_directionLightCamera->_camFar = _shadowDistance * 2.0f;
	//_directionLightCamera->_aspect = 1;
	//_directionLightCamera->_orthoSize = _shadowDistance * 1.5f;	//투영크기
	////텍스처 준비
	//_directionLightCamera->readyShadowTexture(4096);
	//_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);
	//sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	//sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);

	//배경씬 기본 빛 초기화
	sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight->_intensity = 1.0f;

	//그림자를 만들 카메라 박스 크기 조절용 변수 초기화
	_shadowDistance = 10.0f;

	//그림자 카메라의 투영 방식 변경 및 근접 / 원거리 크기 조절
	_directionLightCamera->_isOrtho = true;
	_directionLightCamera->_camNear = 0.01f;
	_directionLightCamera->_camFar = 30;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = 60;	//투영크기는 그림자크기로
	_directionLightCamera->readyShadowTexture(4096);

	_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);

	sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);
}

void stageThree::shadowUpdate(void)
{
	//sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);
	////광원 위치
	//D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();	//메인카메라의 위치
	//D3DXVECTOR3 camFront = _mainCamera->GetForward();		//메인카메리의 정면
	//D3DXVECTOR3 lightDir = sceneBaseDirectionLight->_transform->GetForward();	//방향성 빛의 방향
	//D3DXVECTOR3 lightPos = camPos +
	//	(camFront * (_shadowDistance * 0.5f)) +
	//	(-lightDir * _shadowDistance);
	//_directionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	//_directionLightCamera->LookDirection(lightDir);
	////쉐도우맵 준비
	//this->readyShadowMap(&this->_renderObject, this->_terrainShadow);
	//_mainCamera->updateBase();

	D3DXVECTOR3 camPos = player->getPlayerObject()->_transform->GetWorldPosition();	//메인카메라의 위치

	D3DXVECTOR3 lightDir = sceneBaseDirectionLight->_transform->GetForward();			//방향성 광원의 방향

	_directionLightCamera->SetWorldPosition(camPos.x, camPos.y + 20, camPos.z);
	_directionLightCamera->LookDirection(lightDir);

	//쉐도우맵 준비
	this->readyShadowMap(&this->_renderObject, this->_terrainShadow);
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
		//pTerrain->renderShadow(_mainCamera);
	}

	_directionLightCamera->renderTextureEnd();
}

void stageThree::loadingStage()
{
	boss = new bossMonster;
	player = new xPlayer;
	_mainCamera = new camera;
	_directionLightCamera = new camera;
	sceneBaseDirectionLight = new lightDirection;
	env = new Environment;
	water = new WaterTerrain;
	water->linkCamera(*_mainCamera);

	this->shadowInit();


	//지형 초기화
	_terrain = new terrain;
	_terrain->setHeightmap("높이맵_3");
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("보스지형").tile0, true);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("보스지형").tile1, true);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("보스지형").tile2, true);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("보스지형").tile3, true);
	_terrain->setSplat(IOMAPMANAGER->loadMapInfo("보스지형").splat, true);
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("보스지형").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	//그림자 지형 초기화
	_terrainShadow = new terrain;
	_terrainShadow->setHeightmap("높이맵_3");
	_terrainShadow->setTile0(IOMAPMANAGER->loadMapInfo("보스지형").tile0, true);
	_terrainShadow->setTile1(IOMAPMANAGER->loadMapInfo("보스지형").tile1, true);
	_terrainShadow->setTile2(IOMAPMANAGER->loadMapInfo("보스지형").tile2, true);
	_terrainShadow->setTile3(IOMAPMANAGER->loadMapInfo("보스지형").tile3, true);
	_terrainShadow->setSplat(IOMAPMANAGER->loadMapInfo("보스지형").splat, true);
	_terrainShadow->setMapPosition(IOMAPMANAGER->loadMapInfo("보스지형").vecPos);
	_terrainShadow->setting();
	_terrainShadow->changeHeightTerrain();

	env->init();
	env->linkCamera(*_mainCamera);
	water->init(3.0f, 256);

	//환경맵 / 물결맵 불러오기
	IOSAVEMANAGER->loadFile("보스세이브맵");
	envTemp = IOSAVEMANAGER->findTag("환경맵");
	waterTemp = IOSAVEMANAGER->findTag("물결맵");

	float tempY = _terrain->getHeight(5.0f, 5.0f);

	//플레이어 초기화
	player->out_setlinkTerrain(*_terrain);
	player->init();
	//player->getPlayerObject()->_transform->SetWorldPosition(5.0f, tempY, 5.0f);
	player->getPlayerObject()->_transform->LookDirection(D3DXVECTOR3(0, 0, -1));
	player->getPlayerObject()->_transform->SetAngleY(180);
	player->getPlayerObject()->_transform->SetScale(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < player->getRenderObject().size(); i++)
	{
		_renderObject.push_back(player->getRenderObject()[i]);
	}

	//액션 매니저 초기화
	ACMANAGER->Init(*_terrain, *player);

	tempY = _terrain->getHeight(0.0f, 0.0f);
	IOSAVEMONSTERBOX->loadFile("test");
	//보스몬스터 초기화
	boss->setMesh(XMESH_MANAGER->GetXmeshSkinned("데스윙"));
	boss->_transform->SetScale(2.0f, 2.0f, 2.0f);
	boss->_transform->SetWorldPosition(0.0f, tempY, 0.0f);
	boss->setActive(true);
	_renderObject.push_back(boss);

	SOUNDMANAGER->play("보스1", 0.1f);

	//초기화
	CINEMATICMANAGER->init();
	//로드된값 집어 넣기 
	CINEMATICMANAGER->cinematicBossInit();
	_mon.push_back(boss);
	player->out_setMonsterRegion(&_mon);

	m_pUIPlayer = new cUIPlayer;
	m_pUIPlayer->linkMinimapPlayerAngle(player->getPlayerObject()->_transform->GetAngleY());
	m_pUIPlayer->linkMinimapPlayerMove(player->getPlayerObject()->_transform->GetWorldPosition().x + _terrain->GetTerrainSizeX() / 2,
									   player->getPlayerObject()->_transform->GetWorldPosition().z + _terrain->GetTerrainSizeZ() / 2,
									   _terrain->GetTerrainSizeX());

	m_pUIPlayer->SetMinimap("worldmap3View");
	m_pUIPlayer->SetMapNum(2);
	m_pUIPlayer->init();

}
