#include "stdafx.h"
#include "stageTwo.h"
#include "xPlayer.h"
#include "mapObject.h"
#include "Environment.h"
#include "WaterTerrain.h"
#include "monster.h"
#include "cUIPlayer.h"

stageTwo* ex_pStage2 = new stageTwo;

stageTwo::stageTwo()
	: _mainCamera(nullptr)
	, _directionLightCamera(nullptr)
	, sceneBaseDirectionLight(nullptr)
	, player(nullptr)
	, objectSet(nullptr)
	, _terrain(nullptr)
	, _terrainShadow(nullptr)
	, env(nullptr)
	, water(nullptr)
	, toRotate(nullptr)
	, _gate1(nullptr)
	, _gate2(nullptr)
	, _shadowDistance(0.0f)
	, currTime(0.0f)
	, angleZ(89)
{
	_renderObject.clear();
	_cullObject.clear();
	_monsterRegion.clear();

	D3DXMatrixIdentity(&matRotate);

	memset(&envTemp, 0, sizeof(tagSaveMap));
	memset(&waterTemp, 0, sizeof(tagSaveMap));
}

stageTwo::~stageTwo()
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
	SAFE_DELETE(toRotate);
	SAFE_DELETE(m_pUIPlayer);
	SAFE_DELETE(player);
	SAFE_DELETE(objectSet);
	SAFE_DELETE(_gate2);
	SAFE_DELETE(_gate1);
}



HRESULT stageTwo::init()
{
	SOUNDMANAGER->play("�ʵ�1", 0.1f);

	player->getPlayerObject()->_transform->SetWorldPosition(PLAYERMANAGER->GetPos());

	return S_OK;
}

void stageTwo::release()
{
	SAFE_DELETE(m_pUIPlayer);
	for (int i = 0; i < _renderObject.size(); i++)
	{
		SAFE_DELETE(_renderObject[i]);
	}
	_renderObject.clear();
	SAFE_DELETE(_mainCamera);
	SAFE_DELETE(_directionLightCamera);
	SAFE_DELETE(sceneBaseDirectionLight);
	SAFE_DELETE(_terrain);
	SAFE_DELETE(_terrainShadow);
	SAFE_DELETE(env);
	water->release();
	SAFE_DELETE(water);
	SAFE_DELETE(toRotate);
	SAFE_DELETE(m_pUIPlayer);
	SAFE_DELETE(player);
	SAFE_DELETE(objectSet);
}

void stageTwo::update()
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

	//������Ʈ ������Ʈ
	for (int i = 0; i < _renderObject.size(); i++) _renderObject[i]->update();

	water->update(waterTemp.number);

	//UI ������Ʈ
	m_pUIPlayer->update();
	m_pUIPlayer->linkMinimapPlayerAngle(player->getPlayerObject()->_transform->GetAngleY());
	m_pUIPlayer->linkMinimapPlayerMove(player->getPlayerObject()->_transform->GetWorldPosition().x + _terrain->GetTerrainSizeX() / 2,
									   player->getPlayerObject()->_transform->GetWorldPosition().z + _terrain->GetTerrainSizeZ() / 2,
									   _terrain->GetTerrainSizeX());

	sceneChange();
}

void stageTwo::render()
{
	//_directionLightCamera->_frustum.renderGizmo();

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
	objectSet->portalRender(_mainCamera);

	_terrain->render(_mainCamera, sceneBaseDirectionLight, _directionLightCamera);


	env->renderEnvironment(envTemp.number);
	water->render(waterTemp.number);

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

	const vector<Node*>& temp = _terrain->getDijkstra().getVecNode();
	for (size_t i = 0; i < temp.size(); i++)
	{
		temp[i]->Render();
	}

	_terrain->getDijkstra().render();

	m_pUIPlayer->render();
}

void stageTwo::shadowInit(void)
{
	//���� �⺻ �� �ʱ�ȭ
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

void stageTwo::shadowUpdate(void)
{
	/*
	_mainCamera->updateBase();
	//sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	//���� ��ġ
	D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();	//����ī�޶��� ��ġ
	D3DXVECTOR3 camFront = _mainCamera->GetForward();		//����ī�޸��� ����
	D3DXVECTOR3 lightDir = sceneBaseDirectionLight->_transform->GetForward();	//���⼺ ���� ����

	D3DXVECTOR3 lightPos = camPos +
	(camFront * (_shadowDistance * 0.5f)) +
	(-lightDir * _shadowDistance);

	_directionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	_directionLightCamera->LookDirection(lightDir);

	//������� �غ�
	this->readyShadowMap(&this->_renderObject, this->_terrainShadow);*/
	//===========================================================================


	if (KEYMANAGER->isToggleKey('P'))
	{
		_mainCamera->updateBase(true);
	}
	else
	{
		if (!g_isChat)
		{
			_mainCamera->updateBase();
		}
	}

	D3DXVECTOR3 camPos = player->getPlayerObject()->_transform->GetWorldPosition();	//����ī�޶��� ��ġ

	D3DXVECTOR3 lightDir = sceneBaseDirectionLight->_transform->GetForward();			//���⼺ ������ ����

	_directionLightCamera->SetWorldPosition(camPos.x, camPos.y + 5, camPos.z);
	_directionLightCamera->LookDirection(lightDir);

	//������� �غ�
	this->readyShadowMap(&this->_renderObject, this->_terrainShadow);
}

void stageTwo::shadowRender(void)
{
}

void stageTwo::loadMonster(void)
{
	IOSAVEMONSTERBOX->loadFile("test");
	IOSAVEMONSTERMANAGER->loadFile("����");
	vector<tagSaveMonster> temp;
	tagSaveMonster tagMTemp;

	for (int i = 0; i < IOSAVEMONSTERMANAGER->getCount(); i++)
	{
		tagMTemp = IOSAVEMONSTERMANAGER->findTag("���ͳѹ�" + to_string(i + 1));

		temp.push_back(tagMTemp);
	}

	for (int i = 0; i < temp.size(); i++)
	{
		D3DXMATRIX matRotate;
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

		monster* tempMonster = new monster(findMonsterName(temp[i].monsterNumber));
		tempMonster->_transform->SetScale(temp[i].scale, temp[i].scale, temp[i].scale);
		tempMonster->_transform->SetWorldPosition(temp[i].monsterX, temp[i].monsterY, temp[i].monsterZ);
		tempMonster->setRegenPosition(temp[i].monsterX, temp[i].monsterY, temp[i].monsterZ);
		tempMonster->setMesh(findMonster(temp[i].monsterNumber));
		tempMonster->setActive(true);
		tempMonster->SetObjectNumber(temp[i].monsterNumber);
		_renderObject.push_back(tempMonster);
		_monsterRegion.push_back(tempMonster);

	}
	int a = 0;
}

void stageTwo::loadNode(void)
{
	IOSAVENODEMANAGER->loadFile("���");
	vector<tagSaveNode> temp;
	tagSaveNode tempNode;

	for (int i = 0; i < IOSAVENODEMANAGER->getCount(); i++)
	{
		tempNode = IOSAVENODEMANAGER->findTag("���" + to_string(i + 1));

		temp.push_back(tempNode);
	}

	for (int i = 0; i < temp.size(); i++)
	{
		_terrain->getDijkstra().addNode(D3DXVECTOR3(temp[i].nodeX, temp[i].nodeY, temp[i].nodeZ));
	}

	for (int i = 0; i < temp.size(); i++)
	{
		for (int j = 0; j < temp[i].nodeFSSize; j++)
		{
			int tempSour = i;
			int tempDest = temp[i].nodeFS[j].first;
			_terrain->getDijkstra().connectNode(tempSour, tempDest);
		}
	}
	int a = 0;
}

xMesh * stageTwo::findMonster(int & index)
{
	D3DXMATRIX mat;
	D3DXMatrixRotationY(&mat, D3DXToRadian(180));
	switch (index)
	{
	case 1:
		return XMESH_MANAGER->GetXmeshSkinned("��");
	case 2:
		return XMESH_MANAGER->GetXmeshSkinned("��");
	case 3:
		return XMESH_MANAGER->GetXmeshSkinned("�����");
	case 4:
		return XMESH_MANAGER->GetXmeshSkinned("��������");
	case 5:
		return XMESH_MANAGER->GetXmeshSkinned("���Ż�罺");
	case 6:
		return XMESH_MANAGER->GetXmeshSkinned("�����");
	case 7:
		return XMESH_MANAGER->GetXmeshSkinned("��");
	case 8:
		return XMESH_MANAGER->GetXmeshSkinned("�Ǿ�");
	case 9:
		return XMESH_MANAGER->GetXmeshSkinned("��");
	case 10:
		return XMESH_MANAGER->GetXmeshSkinned("�Ұ���");
	case 11:
		return XMESH_MANAGER->GetXmeshSkinned("����");
	case 12:
		return XMESH_MANAGER->GetXmeshSkinned("����");
	case 13:
		return XMESH_MANAGER->GetXmeshSkinned("����");
	case 14:
		return XMESH_MANAGER->GetXmeshSkinned("������");
	}
}

string stageTwo::findMonsterName(int & index)
{
	string temp = "";
	switch (index)
	{
	case 1:
		temp = "��ũ����";
		return temp;
	case 2:
		temp = "�Ǹ���";
		return temp;
	case 3:
		temp = "�����";
		return temp;
	case 4:
		temp = "��������";
		return temp;
	case 5:
		temp = "���Ż�罺";
		return temp;
	case 6:
		temp = "�����";
		return temp;
	case 7:
		temp = "���ڻ�";
		return temp;
	case 8:
		temp = "ũ��Ŀ����";
		return temp;
	case 9:
		temp = "Ǯ����";
		return temp;
	case 10:
		temp = "�Ұ���";
		return temp;
	case 11:
		temp = "����";
		return temp;
	case 12:
		temp = "����";
		return temp;
	case 13:
		temp = "����";
		return temp;
	case 14:
		temp = "���⵵����";
		return temp;
	}
}

void stageTwo::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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

void stageTwo::sceneChange()
{

	if (PHYSICSMANAGER->isOverlap(player->getPlayerObject(), _gate1))
	{
		PLAYERMANAGER->SetPos(D3DXVECTOR3(5.5f, 0, 100.0f));
		//PLAYERMANAGER->SetPos(D3DXVECTOR3(0, 0, -110));
		SCENEMANAGER->changeScene("gameSceneOne");
	}

	if (player != nullptr)
	{
		if (PHYSICSMANAGER->isOverlap(player->getPlayerObject(), _gate2))
		{

			PLAYERMANAGER->SetPos(D3DXVECTOR3(0, 0, 33));
			SCENEMANAGER->changeScene("gameSceneThree", false);
		}
	}
}



void stageTwo::loadingScene()
{
	player = new xPlayer;
	_mainCamera = new camera;
	_directionLightCamera = new camera;
	sceneBaseDirectionLight = new lightDirection;
	objectSet = new mapObject;
	env = new Environment;
	water = new WaterTerrain;
	water->linkCamera(*_mainCamera);
	toRotate = new dx::transform;


	this->shadowInit();


	//���� �ʱ�ȭ
	_terrain = new terrain;
	_terrain->setHeightmap("���̸�_1");
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("���������").tile0, true);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("���������").tile1, true);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("���������").tile2, true);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("���������").tile3, true);
	_terrain->setSplat(IOMAPMANAGER->loadMapInfo("���������").splat, true);
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("���������").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	//�׸��� ���� �ʱ�ȭ
	_terrainShadow = new terrain;
	_terrainShadow->setHeightmap("���̸�_1");
	_terrainShadow->setTile0(IOMAPMANAGER->loadMapInfo("���������").tile0, true);
	_terrainShadow->setTile1(IOMAPMANAGER->loadMapInfo("���������").tile1, true);
	_terrainShadow->setTile2(IOMAPMANAGER->loadMapInfo("���������").tile2, true);
	_terrainShadow->setTile3(IOMAPMANAGER->loadMapInfo("���������").tile3, true);
	_terrainShadow->setSplat(IOMAPMANAGER->loadMapInfo("���������").splat, true);
	_terrainShadow->setMapPosition(IOMAPMANAGER->loadMapInfo("���������").vecPos);
	_terrainShadow->setting();
	_terrainShadow->changeHeightTerrain();

	//ȯ��� �ʱ�ȭ
	env->init();
	env->linkCamera(*_mainCamera);

	water->init(3.0f, 256);

	//�� ������Ʈ �ʱ�ȭ
	IOSAVEOBJECTMANAGER->loadFile("����Ϳ�����Ʈ");
	for (int i = 0; i < IOSAVEOBJECTMANAGER->getCount(); i++)
	{
		int x = IOSAVEOBJECTMANAGER->getCount();
		tagSaveObject object;
		memset(&object, 0, sizeof(tagSaveObject));

		object = IOSAVEOBJECTMANAGER->findTag("�ѹ�" + to_string(i + 1));
		baseObject* temp = new baseObject;
		D3DXMATRIX matRotate;
		objectSet->objectSet(object.objectNumber, temp, matRotate, object.objectX, object.objectY, object.objectZ, object.objectScale, object.objectRotate);


		int a = object.objectNumber;


		_renderObject.push_back(temp);
	}


	//ȯ��� / ����� �ҷ�����
	IOSAVEMANAGER->loadFile("����ͼ��̺��");

	envTemp = IOSAVEMANAGER->findTag("ȯ���");
	waterTemp = IOSAVEMANAGER->findTag("�����");

	float tempY = _terrain->getHeight(0.0f, 0.0f);


	//�÷��̾� �ʱ�ȭ
	player->out_setlinkTerrain(*_terrain);
	player->init();
	//player->getPlayerObject()->_transform->SetWorldPosition(0.0f, tempY, 0.0f);
	
	player->getPlayerObject()->_transform->SetScale(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < player->getRenderObject().size(); i++)
	{
		_renderObject.push_back(player->getRenderObject()[i]);
	}

	ACMANAGER->Init(*_terrain, *player);

	loadMonster();

	loadNode();

	player->out_setMonsterRegion(&_monsterRegion);



	_mainCamera->out_SetLinkTrans(player->getPlayerObject()->_transform);
	_mainCamera->out_SetRelativeCamPos(D3DXVECTOR3(0, 5, -5));

	for (int i = 0; i < _renderObject.size(); i++)
	{
		if (192 == _renderObject[i]->getObjectNumber() || 190 == _renderObject[i]->getObjectNumber())
		{
			//�̰� �չ�
			if (_renderObject[i]->getportalNumber() == 0)
			{
				_gate1 = _renderObject[i];
			}

			if (_renderObject[i]->getportalNumber() == 1)
			{
				_gate2 = _renderObject[i];
			}
		}
	}


	m_pUIPlayer = new cUIPlayer;
	m_pUIPlayer->SetMinimap("worldmap2View");
	m_pUIPlayer->SetMapNum(1);
	m_pUIPlayer->SetPlayerPosX(player->getPlayerObject()->_transform->GetWorldPosition().x);
	m_pUIPlayer->SetPlayerPosY(player->getPlayerObject()->_transform->GetWorldPosition().z);

	m_pUIPlayer->linkMinimapPlayerAngle(player->getPlayerObject()->_transform->GetAngleY());
	m_pUIPlayer->linkMinimapPlayerMove(player->getPlayerObject()->_transform->GetWorldPosition().x + _terrain->GetTerrainSizeX() / 2,
									   player->getPlayerObject()->_transform->GetWorldPosition().z + _terrain->GetTerrainSizeZ() / 2,
									   _terrain->GetTerrainSizeX());
	m_pUIPlayer->init();
}

void stageTwo::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pUIPlayer->WndProc(hWnd, message, wParam, lParam);
}
