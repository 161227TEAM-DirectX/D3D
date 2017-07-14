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

	//������Ʈ ������Ʈ
	for (int i = 0; i < _renderObject.size(); i++) _renderObject[i]->update();

	water->update(waterTemp.number);

	//UI ������Ʈ
	m_pUIPlayer->update();
	m_pUIPlayer->linkMinimapPlayerAngle(player->getPlayerObject()->_transform->GetAngleY());
	m_pUIPlayer->linkMinimapPlayerMove(player->getPlayerObject()->_transform->GetWorldPosition().x + _terrain->GetTerrainSizeX() / 2,
									   player->getPlayerObject()->_transform->GetWorldPosition().z + _terrain->GetTerrainSizeZ() / 2,
									   _terrain->GetTerrainSizeX());
}

void stageThree::render()
{
	_directionLightCamera->_frustum.renderGizmo();

	//ī�޶� �ø��Ȱ͸�
	this->_cullObject.clear();
	for (int i = 0; i < this->_renderObject.size(); i++)
	{
		//�������� Ȯ��
		if (_mainCamera->_frustum.isInFrustum(_renderObject[i]))
		{
			this->_cullObject.push_back(_renderObject[i]);
		}
	}

	_terrain->render(_mainCamera, sceneBaseDirectionLight, _directionLightCamera);

	env->renderEnvironment(envTemp.number);
	//	water->render(waterTemp.number);

	//������� ���� �׸����� ReciveShadow �� Technique ����
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
	////���� �⺻ �� �ʱ�ȭ
	//sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	//sceneBaseDirectionLight->_intensity = 1.0f;
	////�׸��ڸ� ���� ī�޶� �ڽ� ũ�� ������ ���� �ʱ�ȭ
	//_shadowDistance = 100.0f;
	////�׸��� ī�޶��� ���� ��� ���� �� ���� / ���Ÿ� ũ�� ����
	//_directionLightCamera->_isOrtho = true;	//��������
	//_directionLightCamera->_camNear = 0.1f;	//�ٰŸ�
	//_directionLightCamera->_camFar = _shadowDistance * 2.0f;
	//_directionLightCamera->_aspect = 1;
	//_directionLightCamera->_orthoSize = _shadowDistance * 1.5f;	//����ũ��
	////�ؽ�ó �غ�
	//_directionLightCamera->readyShadowTexture(4096);
	//_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);
	//sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	//sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);

	//���� �⺻ �� �ʱ�ȭ
	sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight->_intensity = 1.0f;

	//�׸��ڸ� ���� ī�޶� �ڽ� ũ�� ������ ���� �ʱ�ȭ
	_shadowDistance = 10.0f;

	//�׸��� ī�޶��� ���� ��� ���� �� ���� / ���Ÿ� ũ�� ����
	_directionLightCamera->_isOrtho = true;
	_directionLightCamera->_camNear = 0.01f;
	_directionLightCamera->_camFar = 30;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = 60;	//����ũ��� �׸���ũ���
	_directionLightCamera->readyShadowTexture(4096);

	_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);

	sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);
}

void stageThree::shadowUpdate(void)
{
	//sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);
	////���� ��ġ
	//D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();	//����ī�޶��� ��ġ
	//D3DXVECTOR3 camFront = _mainCamera->GetForward();		//����ī�޸��� ����
	//D3DXVECTOR3 lightDir = sceneBaseDirectionLight->_transform->GetForward();	//���⼺ ���� ����
	//D3DXVECTOR3 lightPos = camPos +
	//	(camFront * (_shadowDistance * 0.5f)) +
	//	(-lightDir * _shadowDistance);
	//_directionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	//_directionLightCamera->LookDirection(lightDir);
	////������� �غ�
	//this->readyShadowMap(&this->_renderObject, this->_terrainShadow);
	//_mainCamera->updateBase();

	D3DXVECTOR3 camPos = player->getPlayerObject()->_transform->GetWorldPosition();	//����ī�޶��� ��ġ

	D3DXVECTOR3 lightDir = sceneBaseDirectionLight->_transform->GetForward();			//���⼺ ������ ����

	_directionLightCamera->SetWorldPosition(camPos.x, camPos.y + 20, camPos.z);
	_directionLightCamera->LookDirection(lightDir);

	//������� �غ�
	this->readyShadowMap(&this->_renderObject, this->_terrainShadow);
}

void stageThree::shadowRender(void)
{

}

void stageThree::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
{
	//���⼺������ ���� ī�޶��� Frustum ������Ʈ
	_directionLightCamera->updateMatrix();
	_directionLightCamera->updateFrustum();

	//���̷��Ƕ����� ī�޶� ������ �ֵ鸸 �׸���...
	static vector<baseObject*>	shadowCullObject;
	shadowCullObject.clear();

	for (int i = 0; i < renderObjects->size(); i++)
	{
		//�������� �ȿ� �ִ�?
		if (this->_mainCamera->_frustum.isInFrustum((*renderObjects)[i]))
		{
			shadowCullObject.push_back((*renderObjects)[i]);
		}
	}

	//������ �� �׸���.
	_directionLightCamera->renderTextureBegin(0xffffffff);

	//�����޽� ����
	xMeshStatic::setCamera(this->_directionLightCamera);
	xMeshStatic::setTechniqueName("CreateShadow");

	//��Ų��޽� ����
	xMeshSkinned::setCamera(this->_directionLightCamera);
	xMeshSkinned::setTechniqueName("CreateShadow");

	for (int i = 0; i < shadowCullObject.size(); i++)
	{
		if (shadowCullObject[i]->_ignoreCreateShadow == false)
		{
			shadowCullObject[i]->render();
		}
	}

	//���� Terrain �� ������ ���� �׷����Ѵٸ�...
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


	//���� �ʱ�ȭ
	_terrain = new terrain;
	_terrain->setHeightmap("���̸�_3");
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("��������").tile0, true);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("��������").tile1, true);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("��������").tile2, true);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("��������").tile3, true);
	_terrain->setSplat(IOMAPMANAGER->loadMapInfo("��������").splat, true);
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("��������").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	//�׸��� ���� �ʱ�ȭ
	_terrainShadow = new terrain;
	_terrainShadow->setHeightmap("���̸�_3");
	_terrainShadow->setTile0(IOMAPMANAGER->loadMapInfo("��������").tile0, true);
	_terrainShadow->setTile1(IOMAPMANAGER->loadMapInfo("��������").tile1, true);
	_terrainShadow->setTile2(IOMAPMANAGER->loadMapInfo("��������").tile2, true);
	_terrainShadow->setTile3(IOMAPMANAGER->loadMapInfo("��������").tile3, true);
	_terrainShadow->setSplat(IOMAPMANAGER->loadMapInfo("��������").splat, true);
	_terrainShadow->setMapPosition(IOMAPMANAGER->loadMapInfo("��������").vecPos);
	_terrainShadow->setting();
	_terrainShadow->changeHeightTerrain();

	env->init();
	env->linkCamera(*_mainCamera);
	water->init(3.0f, 256);

	//ȯ��� / ����� �ҷ�����
	IOSAVEMANAGER->loadFile("�������̺��");
	envTemp = IOSAVEMANAGER->findTag("ȯ���");
	waterTemp = IOSAVEMANAGER->findTag("�����");

	float tempY = _terrain->getHeight(5.0f, 5.0f);

	//�÷��̾� �ʱ�ȭ
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

	//�׼� �Ŵ��� �ʱ�ȭ
	ACMANAGER->Init(*_terrain, *player);

	tempY = _terrain->getHeight(0.0f, 0.0f);
	IOSAVEMONSTERBOX->loadFile("test");
	//�������� �ʱ�ȭ
	boss->setMesh(XMESH_MANAGER->GetXmeshSkinned("������"));
	boss->_transform->SetScale(2.0f, 2.0f, 2.0f);
	boss->_transform->SetWorldPosition(0.0f, tempY, 0.0f);
	boss->setActive(true);
	_renderObject.push_back(boss);

	SOUNDMANAGER->play("����1", 0.1f);

	//�ʱ�ȭ
	CINEMATICMANAGER->init();
	//�ε�Ȱ� ���� �ֱ� 
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
