#include "stdafx.h"
#include "terrainPickingTest.h"

HRESULT terrainPickingTest::init(void)
{
	FILEPATH_MANAGER->AddFilepath("���������Ҹ�", "Resource/Sound/deathWing/deathwing_shouting_good.mp3");
	FILEPATH_MANAGER->AddFilepath("���������Ҹ�2", "Resource/Sound/deathWing/event_deathwingattacks_roar_01.ogg");
	FILEPATH_MANAGER->AddFilepath("���������Ҹ�3", "Resource/Sound/deathWing/event_deathwingattacks_roar_03.ogg");
	FILEPATH_MANAGER->AddFilepath("���������Ҹ�4", "Resource/Sound/deathWing/event_deathwingattacks_roar_04.ogg");
	FILEPATH_MANAGER->AddFilepath("��������1", "Resource/Sound/deathWing/mon_deathwing_attack_02.ogg");
	FILEPATH_MANAGER->AddFilepath("��������2", "Resource/Sound/deathWing/mon_deathwing_attack_04.ogg");
	FILEPATH_MANAGER->AddFilepath("��������3", "Resource/Sound/deathWing/mon_deathwing_attack_10.ogg");
	FILEPATH_MANAGER->AddFilepath("��������4", "Resource/Sound/deathWing/mon_deathwing_wound_01.ogg");
	FILEPATH_MANAGER->AddFilepath("��������1", "Resource/Sound/deathWing/mon_deathwing_death_09.ogg");
	FILEPATH_MANAGER->AddFilepath("��������2", "Resource/Sound/deathWing/mon_deathwing_death_10.ogg");
	FILEPATH_MANAGER->AddFilepath("�������Ҹ�1", "Resource/Sound/deathWing/mon_deathwing_preaggro_03.ogg");
	FILEPATH_MANAGER->AddFilepath("�������Ҹ�2", "Resource/Sound/deathWing/mon_deathwing_preaggro_04.ogg");
	FILEPATH_MANAGER->AddFilepath("�����극��", "Resource/Sound/deathWing/European_Dragon_Roaring_and_breathe_fire-daniel-simon.mp3");
	FILEPATH_MANAGER->AddFilepath("�����극��2", "Resource/Sound/deathWing/flamebreath.ogg");
	FILEPATH_MANAGER->AddFilepath("��������", "Resource/Sound/deathWing/mdeathimpactcolossalgrassa.ogg");
	FILEPATH_MANAGER->AddFilepath("�ȱ�", "Resource/Sound/deathWing/mdeathimpactgiantdirta.ogg");

	SOUNDMANAGER->addSound("������", FILEPATH_MANAGER->GetFilepath("���������Ҹ�"));
	SOUNDMANAGER->addSound("������2", FILEPATH_MANAGER->GetFilepath("���������Ҹ�2"));
	SOUNDMANAGER->addSound("������3", FILEPATH_MANAGER->GetFilepath("���������Ҹ�3"));
	SOUNDMANAGER->addSound("������4", FILEPATH_MANAGER->GetFilepath("���������Ҹ�4"));
	SOUNDMANAGER->addSound("��������1", FILEPATH_MANAGER->GetFilepath("��������1"));
	SOUNDMANAGER->addSound("��������2", FILEPATH_MANAGER->GetFilepath("��������2"));
	SOUNDMANAGER->addSound("��������3", FILEPATH_MANAGER->GetFilepath("��������3"));
	SOUNDMANAGER->addSound("��������4", FILEPATH_MANAGER->GetFilepath("��������4"));
	SOUNDMANAGER->addSound("��������1", FILEPATH_MANAGER->GetFilepath("��������1"));
	SOUNDMANAGER->addSound("��������2", FILEPATH_MANAGER->GetFilepath("��������2"));
	SOUNDMANAGER->addSound("�������Ҹ�1", FILEPATH_MANAGER->GetFilepath("�������Ҹ�1"), false, true);
	SOUNDMANAGER->addSound("�������Ҹ�2", FILEPATH_MANAGER->GetFilepath("�������Ҹ�2"), false, true);
	SOUNDMANAGER->addSound("�극��1", FILEPATH_MANAGER->GetFilepath("�����극��"));
	SOUNDMANAGER->addSound("�극��2", FILEPATH_MANAGER->GetFilepath("�����극��2"));
	SOUNDMANAGER->addSound("��������", FILEPATH_MANAGER->GetFilepath("��������"));
	SOUNDMANAGER->addSound("�ȱ�", FILEPATH_MANAGER->GetFilepath("�ȱ�"), false, true);

	shadowInit();

	_terrain = new terrain;
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_3"));
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("����1").tile0);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("����1").tile1);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("����1").tile2);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("����1").tile3);
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_1"));
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("����1").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	_terrainShadow = new terrain;
	_terrainShadow->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_3"));
	_terrainShadow->setTile0(IOMAPMANAGER->loadMapInfo("����1").tile0);
	_terrainShadow->setTile1(IOMAPMANAGER->loadMapInfo("����1").tile1);
	_terrainShadow->setTile2(IOMAPMANAGER->loadMapInfo("����1").tile2);
	_terrainShadow->setTile3(IOMAPMANAGER->loadMapInfo("����1").tile3);
	_terrainShadow->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_1"));
	_terrainShadow->setMapPosition(IOMAPMANAGER->loadMapInfo("����1").vecPos);
	_terrainShadow->setting();
	_terrainShadow->changeHeightTerrain();

	//������Ʈ �ʱ�ȭ
	//_mapObject = new mapObject;
	//IOSAVEOBJECTMANAGER->loadFile("������Ʈ");
	//for (int i = 0; i < IOSAVEOBJECTMANAGER->getCount(); i++)
	//{
	//	object = IOSAVEOBJECTMANAGER->findTag("�ѹ�" + to_string(i + 1));
	//	baseObject* temp2 = new baseObject;
	//	D3DXMATRIX mapRotate;
	//	_mapObject->objectSet(object.objectNumber, temp2, mapRotate, object.objectX, object.objectY, object.objectZ, 0.3f, object.objectRotate);
	//	_renderObjects.push_back(temp2);
	//	//m_vecObject.push_back(temp2);
	//}

	_waterTerrain = new WaterTerrain;
	_waterTerrain->init(3.0f, 256);

//	_trans = new dx::transform;
//	_dirLight = new lightDirection;
	_hitPos = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIX mat;
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	mat = matRotate;

//	boss = new bossMonster;
	_player = new xPlayer;
	_player->out_setlinkTerrain(*_terrain);
	_player->init();
	_player->getPlayerObject()->_transform->SetWorldPosition(1.0f, 0.0f, -3.0f);
//	_player->getPlayerObject()->_transform->SetWorldPosition(20.0f, 0.0f, -20.0f);
	_player->getPlayerObject()->_transform->SetScale(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < _player->getRenderObject().size(); i++)
	{
		_renderObjects.push_back(_player->getRenderObject()[i]);
	}

	float tempY = _terrain->getHeight(0.0f, 0.0f);

	InitMonster();
	

	ACMANAGER->Init(*_terrain, testObject, *_player);

	for (int i = 0; i < mon.size(); i++)
	{
		//monster* temp = dynamic_cast<monster*>(mon[i]);
		//temp->setActive(true);
		mon[i]->setActive(true);
		mon[i]->setI(i);
		_renderObjects.push_back(mon[i]);
	}


	//boss->setMesh(RM_SKINNED->getResource("Resource/Meshes/BossMonster/deathwing_ok/x/deathWing.x", mat));
	//boss->_transform->SetScale(1.0f, 1.0f, 1.0f);
	//boss->_transform->SetWorldPosition(0.0f, tempY, 0.0f);
	//boss->setActive(true);
	//this->_renderObjects.push_back(boss);

//	this->setEnvironment("Resource/TextureCUBE/SuperKanjiCube.dds");



	_env = new Environment;
	_env->init();
	_env->linkCamera(*_mainCamera);

	_mainCamera->SetWorldPosition(0.0f, 10.0f, 10.0f);
	_mainCamera->LookPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	lButtonState = SELECTFUNC::SELECT_NONE;

	sour = -1;
	dest = -1;

	_player->setTargetMonster(*boss);
	_player->out_setMonsterRegion(&mon);

	return S_OK;
}

void terrainPickingTest::release(void)
{
	_player->release();
	SAFE_DELETE(_player);

	//������Ʈ ����
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}
	//������ �����׸��� ����
	SAFE_DELETE(this->_terrain);
	SAFE_DELETE(this->_terrainShadow);
//	SAFE_DELETE(this->_trans);

	_waterTerrain->release();
}

void terrainPickingTest::update(void)
{
	shadowUpdate();

	lButtonStateChange();
	selectLButton();

	_player->update();

	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		_renderObjects[i]->update();
	}
}

void terrainPickingTest::render(void)
{
	shadowRender();
	_directionLightCamera->_frustum.renderGizmo();

	//ī�޶� �ø��ȰŸ�....
	this->_cullObjects.clear();
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		//�������� �ȿ� �ִ�?
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{
			this->_cullObjects.push_back(_renderObjects[i]);
		}
	}
	_terrain->render(_mainCamera, _sceneBaseDirectionLight, _directionLightCamera);

//	_mapObject->objectRenderTool(m_vecObject, _mainCamera, _sceneBaseDirectionLight);

	//_waterTerrain->render(1);

	_env->renderEnvironment(2);

	//������� ���� �׸����� ReciveShadow �� Technique ����
	xMeshStatic::setCamera(_mainCamera);
	//xMeshStatic::setTechniqueName("ReciveShadow");
	xMeshStatic::setTechniqueName("Toon");
	xMeshStatic::_staticMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshStatic::setBaseLight(this->_sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);
	
	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
		if (_cullObjects[i] == _player->getPlayerObject())
		{
			_player->out_ItemUpdate();
		}
	}

	_player->render();
	
	RM_SKINNED->getResource("Resource/Player/FHUMAN_PLATE/FHUMAN.X")->ShowAnimationName(0, 0);

	const vector<Node*>& temp = _terrain->getDijkstra().getVecNode();
	for (size_t i = 0; i < temp.size(); i++)
	{
		temp[i]->Render();
	}

	_terrain->getDijkstra().render();

	//_mainCamera->renderTextureEnd();

	//testRender();
	//char tempchar[128];
	//sprintf_s(tempchar, "vecNodeSize : %d, adjSize: %d", temp.size(), _terrain->getDijkstra().getadjNode().size());
	//FONTMANAGER->fontOut(tempchar, 0, 100, 0xffffffff);

	//if (KEYMANAGER->isToggleKey(VK_F6))
	//{
	//	sprintf_s(tempchar, "���(����ε���) : ");
	//	FONTMANAGER->fontOut(tempchar, 0, 85, 0xffffffff);
	//	int position = 0;
	//	for (int i = _terrain->getDijkstra().getPath().size() -1; i >= 0 ; --i)
	//	{
	//		sprintf_s(tempchar, "%d->", _terrain->getDijkstra().getPath()[i]);
	//		FONTMANAGER->fontOut(tempchar, 195 + position * 55, 85, 0xffffffff);
	//		position++;
	//	}
	//}
}

void terrainPickingTest::lButtonStateChange(void)
{
	if (KEYMANAGER->isOnceKeyDown('1')) lButtonState = SELECTFUNC::SELECT_NODE;
	else if (KEYMANAGER->isOnceKeyDown('2')) lButtonState = SELECTFUNC::SELECT_LINE;
	else if (KEYMANAGER->isOnceKeyDown('3')) lButtonState = SELECTFUNC::SELECT_MOVING;
	else if (KEYMANAGER->isOnceKeyDown('4')) lButtonState = SELECTFUNC::SELECT_OBJECT;
	else if (KEYMANAGER->isOnceKeyDown('5')) lButtonState = SELECTFUNC::SELECT_NONE;
}

void terrainPickingTest::selectLButton(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		_mainCamera->computeRay(&ray, &screenPos);

		const vector<Node*>& temp = _terrain->getDijkstra().getVecNode();

		switch (lButtonState)
		{
		case terrainPickingTest::SELECT_NODE:
			//Terrain �̶� Rayüũ
			if (_terrain->isIntersectRay(&_hitPos, &ray))
			{
				_terrain->getDijkstra().addNode(_hitPos);
				//tempDijkstra->addNode(_hitPos);
			}
			break;
		case terrainPickingTest::SELECT_LINE:
			
			for (int i = 0; i < temp.size(); i++)
			{
				if (PHYSICSMANAGER->isRayHitSphere(&ray, &temp[i]->getPosition(), temp[i]->getRadius(), nullptr, nullptr))
				{
					if (sour == -1) sour = i;
					else if (dest == -1)
					{
						dest = i;
						_terrain->getDijkstra().connectNode(sour, dest);
					}
				}
			}
			break;
		case terrainPickingTest::SELECT_MOVING:
		{
			if (_terrain->isIntersectRay(&_hitPos, &ray))
			{
				//player.getAction().setRand(_terrain);
			//	tempDijkstra->FindPath(_hitPos, player->_skTransform->GetWorldPosition()/*, testObject*/);
			//	player->setNextAction(tempDijkstra->OptimizedAction(*player, _terrain, testObject, player->_skTransform->GetWorldPosition(), _hitPos));
			}
		}
			break;
		case terrainPickingTest::SELECT_OBJECT:
			if (_terrain->isIntersectRay(&_hitPos, &ray)) addObject();
			break;
		case terrainPickingTest::SELECT_NONE:
			break;
		}
	}
}


void terrainPickingTest::shadowInit(void)
{
	_mainCamera = new camera;

	_directionLightCamera = new camera;

	_sceneBaseDirectionLight = new lightDirection;

	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;

	//�׸��� �Ÿ�?
	_shadowDistance = 100.0f;

	//ī�޶��� ��������� �ٲ۴�.
	_directionLightCamera->_isOrtho = true;
	_directionLightCamera->_camNear = 0.1f;
	_directionLightCamera->_camFar = _shadowDistance * 2.0f;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = _shadowDistance * 1.5f;	//����ũ��� �׸���ũ���

	//���⼺���� ī�޶��� RenderToTexture�غ�
	_directionLightCamera->readyShadowTexture(4096);

	_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);

//	_scenePlaneVertex[0].pos = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
//	_scenePlaneVertex[1].pos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
//	_scenePlaneVertex[2].pos = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
//	_scenePlaneVertex[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
//	_scenePlaneVertex[0].uv = D3DXVECTOR2(0.0f, 0.0f);
//	_scenePlaneVertex[1].uv = D3DXVECTOR2(1.0f, 0.0f);
//	_scenePlaneVertex[2].uv = D3DXVECTOR2(1.0f, 1.0f);
//	_scenePlaneVertex[3].uv = D3DXVECTOR2(0.0f, 1.0f);
//	_scenePlaneIndex[0] = 0;
//	_scenePlaneIndex[1] = 1;
//	_scenePlaneIndex[2] = 3;
//	_scenePlaneIndex[3] = 3;
//	_scenePlaneIndex[4] = 1;
//	_scenePlaneIndex[5] = 2;

	//����Ʈ ����Ʈ �ε�
//	_postEffect = RM_SHADERFX->getResource("Resource/Shaders/PostEffect.fx");
	
	this->_sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);
}

void terrainPickingTest::shadowUpdate(void)
{
	_mainCamera->updateBase();
	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	//D3DXVECTOR3 pPos = _player->getPlayerObject()->_transform->GetWorldPosition();

	//D3DXVECTOR3 lightPos = pPos;

	//lightPos.y += _mainCamera->GetWorldPosition().y;

	//D3DXVECTOR3 dPos = pPos - lightPos;


	//_shadowDistance = 2 * D3DXVec3Length(&dPos);
	//_directionLightCamera->_camFar = _shadowDistance * 1.0f;
	//_directionLightCamera->_orthoSize = _shadowDistance * 1.0f;	//����ũ��� �׸���ũ���

	//_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	//���� ��ġ
	D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();		//����ī�޶��� ��ġ
	D3DXVECTOR3 camFront = _mainCamera->GetForward();			//����ī�޶��� ����
	D3DXVECTOR3 lightDir = _sceneBaseDirectionLight->_transform->GetForward();	//���⼺ ������ ����


	_waterTerrain->update(1);

	D3DXVECTOR3 lightPos = camPos +
		(camFront * (_shadowDistance * 0.5f)) +
		(-lightDir * _shadowDistance);

	_directionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	_directionLightCamera->LookDirection(lightDir);

	//������� �غ�
	this->readyShadowMap(&this->_renderObjects, this->_terrainShadow);
}

void terrainPickingTest::shadowRender(void)
{
	//����ī�޶� RTT�غ�
	//_mainCamera->renderTextureBegin(0x00101010);
}

void terrainPickingTest::testRender(void)
{
//	//����Ʈ ����Ʈ ����
//	_postEffect->SetTechnique("Base");
//	_postEffect->SetTexture("screenTex", _mainCamera->getRenderTexture());
//	float pixelU = 1.0f / WINSIZEX;
//	float pixelV = 1.0f / WINSIZEY;
//	_postEffect->SetFloat("pixelSizeU", pixelU);
//	_postEffect->SetFloat("pixelSizeV", pixelV);
//	_postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
//	_postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);
//
//	//����Ʈ ����Ʈ ����
//	UINT iPass;
//	_postEffect->Begin(&iPass, 0);
//	for (UINT i = 0; i < iPass; i++)
//	{
//		_postEffect->BeginPass(i);
//		_device->SetFVF(SCENE_VERTEX::FVF);
//		_device->DrawIndexedPrimitiveUP(
//			D3DPT_TRIANGLELIST,
//			0,
//			4,
//			2,
//			_scenePlaneIndex,
//			D3DFMT_INDEX16,
//			_scenePlaneVertex,
//			sizeof(SCENE_VERTEX));
//		_postEffect->EndPass();
//	}
//	_postEffect->End();
}

void terrainPickingTest::addObject(void)
{
	enemy->_transform->SetWorldPosition(_hitPos);
}

void terrainPickingTest::InitMonster(void)
{
	//�ӽ� �÷��̾� �ڵ�
	D3DXMATRIXA16 mat;
	//	D3DXMATRIX matScaling;
	D3DXMATRIX matRotate;
	//	D3DXMatrixScaling(&matScaling, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	mat = /*matScaling **/ matRotate;
	monster* tempObject;

	tempObject = new monster;

	tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	float tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	float tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	float tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	//xMeshSkinned* temp = new xMeshSkinned;
	//temp->init("Resource/Meshes/monster/arcanegolem_ok/x/golem2.x", &mat);
	//tempObject->setMesh(temp);
	tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/arcanegolem_ok/x/golem2.x", mat));
	//xMeshSkinned* newMesh = RM_SKINNED->getResource("Resource/Meshes/monster/arcanegolem_ok/x/golem2.x", mat);


	mon.push_back(tempObject);
	tempObject = nullptr;

	monster* tempObject2 = new monster;
	tempObject2->_transform->SetScale(1.0f, 1.0f, 1.0f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject2->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject2->setRegenPosition(tempX, tempY, tempZ);
	//xMeshSkinned* temp2 = new xMeshSkinned;
	//temp2->init("Resource/Meshes/monster/arcanegolem_ok/x/golem2.x", &mat);
	//tempObject->setMesh(temp2);
	tempObject2->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/arcanegolem_ok/x/golem2.x", mat));
	mon.push_back(tempObject2);
	tempObject2 = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/boar_ok/x/boar.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/bogbeast_ok/x/bogbeast.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/Brutallus_ok/x/brutallus.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/chimerabeast_ok/x/chimerabeast.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/cockatriceelite_ok/x/cockatriceelite.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/crocodile_ok/x/crocodile.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/direfurbolg_ok/x/direfurbolg.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/doomguard_ok/x/doomguard.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/harpy_ok/x/harpy.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/raptor_ok/x/raptor.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/scorpion_ok/x/scorpion.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;

	//tempObject = new monster;
	//tempObject->_transform->SetScale(1.0f, 1.0f, 1.0f);

	//tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	//tempY = _terrain->getHeight(tempX, tempZ);

	//tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	//tempObject->setRegenPosition(tempX, tempY, tempZ);
	//tempObject->setMesh(RM_SKINNED->getResource("Resource/Meshes/monster/thunderlizard_ok/x/thunderlizard.x", mat));
	////mon.push_back(tempObject);
	//tempObject = nullptr;
}

void terrainPickingTest::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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
		pTerrain->renderShadow(_mainCamera);
	}

	_directionLightCamera->renderTextureEnd();


	//���� Terrain �� ������ ���� �����Ѵٸ�
	//if (pTerrain != NULL)
	//{
	//	//pTerrain->_terrainEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
	//	//pTerrain->_terrainEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
	//}

	//������ �ؽ���
	//xMeshStatic::_staticMeshEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
	//������ ���
	//xMeshStatic::_staticMeshEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
	//������ �ؽ���
	//xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
	//������ ���
	//xMeshSkinned::_sSkinnedMeshEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
}

