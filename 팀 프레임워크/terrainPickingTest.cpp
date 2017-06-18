#include "stdafx.h"
#include "terrainPickingTest.h"

HRESULT terrainPickingTest::init(void)
{

	_mainCamera = new camera;
	_directionLightCamera = new camera;
	_sceneBaseDirectionLight = new lightDirection;

	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;

	_shadowDistance = 1.0f;

	//카메라의 투영방식을 바꾼다.
	_directionLightCamera->_isOrtho = true;
	_directionLightCamera->_camNear = 0.01f;
	_directionLightCamera->_camFar = 1.0f;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = _shadowDistance * 2.5f;	//투영크기는 그림자크기로

	//방향성광원 카메라의 RenderToTexture준비
	_directionLightCamera->readyShadowTexture(1024);

	_terrain = new terrain;
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_3"));
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_1"));
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_2"));
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_3"));
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_4"));
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_1"));
	_terrain->setting();

	_terrainShadow = new terrain;
	_terrainShadow->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_3"));
	_terrainShadow->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_1"));
	_terrainShadow->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_2"));
	_terrainShadow->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_3"));
	_terrainShadow->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_4"));
	_terrainShadow->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_1"));
	_terrainShadow->setting();

//	_trans = new dx::transform;
//	_dirLight = new lightDirection;
	_hitPos = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIX mat;
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	mat = matRotate;

	boss = new bossMonster;
	_player = new xPlayer;
	_player->setlinkTerrain(*_terrain);
	_player->init();
	_player->getPlayerObject()->_transform->SetWorldPosition(1.0f, 0.0f, -3.0f);
//	_player->getPlayerObject()->_transform->SetWorldPosition(20.0f, 0.0f, -20.0f);
	_player->getPlayerObject()->_transform->SetScale(0.1f, 0.1f, 0.1f);
	for (int i = 0; i < _player->getRenderObject().size(); i++)
	{
		_renderObjects.push_back(_player->getRenderObject()[i]);
	}

	float tempY = _terrain->getHeight(0.0f, 0.0f);

	//InitMonster();
	

	ACMANAGER->Init(*_terrain, testObject, *_player);

//	for (int i = 0; i < mon.size(); i++)
//	{
//		//monster* temp = dynamic_cast<monster*>(mon[i]);
//		//temp->setActive(true);
//		mon[i]->setActive(true);
//		_renderObjects.push_back(mon[i]);
//	}


	boss->setMesh(RM_SKINNED->getResource("Resources/Meshes/BossMonster/deathwing_ok/x/deathWing.x", mat));
	boss->_transform->SetScale(0.2f, 0.2f, 0.2f);
	boss->_transform->SetWorldPosition(0.0f, tempY, 0.0f);
	boss->setActive(true);
	this->_renderObjects.push_back(boss);

	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);
//	this->setEnvironment("Resources/TextureCUBE/SuperKanjiCube.dds");
	_env = new Environment;
	_env->init();
	_env->linkCamera(*_mainCamera);

	_mainCamera->SetWorldPosition(0.0f, 10.0f, 10.0f);
	_mainCamera->LookPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	lButtonState = SELECTFUNC::SELECT_NONE;

	sour = -1;
	dest = -1;

	_player->setTargetMonster(*boss);

	return S_OK;
}

void terrainPickingTest::release(void)
{
	_player->release();
	SAFE_DELETE(_player);

	//오브젝트 해제
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}
	//지형과 지형그림자 해제
	SAFE_DELETE(this->_terrain);
	SAFE_DELETE(this->_terrainShadow);
//	SAFE_DELETE(this->_trans);
}

void terrainPickingTest::update(void)
{
	_mainCamera->updateBase();
	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	//광원 위치
	D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();		//메인카메라의 위치
	//D3DXVECTOR3 camFront = _mainCamera->GetForward();			//메인카메라의 정면
	D3DXVECTOR3 lightDir = _sceneBaseDirectionLight->_transform->GetForward();	//방향성 광원의 방향

	//D3DXVECTOR3 lightPos = camPos +
	//	(camFront * (_shadowDistance * 0.5f)) +
	//	(-lightDir * _shadowDistance);

	_directionLightCamera->SetWorldPosition(camPos.x, camPos.y, camPos.z);
	_directionLightCamera->LookDirection(lightDir);

	lButtonStateChange();
	selectLButton();

	_player->update();

	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		_renderObjects[i]->update();
	}

	//쉐도우맵 준비
	this->readyShadowMap(&this->_renderObjects, this->_terrainShadow);
}

void terrainPickingTest::render(void)
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

	_env->renderEnvironment(1);

	xMeshStatic::setCamera(_mainCamera);
	//if (KEYMANAGER->isStayKeyDown('0'))
	//{
	//	//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	//	xMeshStatic::setTechniqueName("CreateShadow");
	//}
	//else
	//{
	//	//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	//	
	//}
	xMeshStatic::setTechniqueName("CreateShadow");
	xMeshStatic::setBaseLight(this->_sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resources/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);
	
	_player->render();

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
	}
	_terrain->render(_mainCamera, _sceneBaseDirectionLight, _directionLightCamera);
	
	RM_SKINNED->getResource("Resources/Player/FHUMAN_PLATE/FHUMAN.X")->ShowAnimationName(0, 0);

	const vector<Node*>& temp = _terrain->getDijkstra().getVecNode();
	for (size_t i = 0; i < temp.size(); i++)
	{
		temp[i]->Render();
	}

	_terrain->getDijkstra().render();

	char tempchar[128];
	sprintf_s(tempchar, "vecNodeSize : %d, adjSize: %d", temp.size(), _terrain->getDijkstra().getadjNode().size());
	FONTMANAGER->fontOut(tempchar, 0, 100, 0xffffffff);

	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		sprintf_s(tempchar, "경로(노드인덱스) : ");
		FONTMANAGER->fontOut(tempchar, 0, 85, 0xffffffff);
		int position = 0;
		for (int i = _terrain->getDijkstra().getPath().size() -1; i >= 0 ; --i)
		{
			sprintf_s(tempchar, "%d->", _terrain->getDijkstra().getPath()[i]);
			FONTMANAGER->fontOut(tempchar, 195 + position * 55, 85, 0xffffffff);
			position++;
		}
	}
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
			//Terrain 이랑 Ray체크
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

void terrainPickingTest::addObject(void)
{
	enemy->_transform->SetWorldPosition(_hitPos);
}

void terrainPickingTest::InitMonster(void)
{
	//임시 플레이어 코드
	D3DXMATRIX mat;
	//	D3DXMATRIX matScaling;
	D3DXMATRIX matRotate;
	//	D3DXMatrixScaling(&matScaling, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	mat = /*matScaling **/ matRotate;
	monster* tempObject;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	float tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	float tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	float tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/arcanegolem_ok/x/golem2.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/Beargod_ok/x/beargod.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/boar_ok/x/boar.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/bogbeast_ok/x/bogbeast.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/Brutallus_ok/x/brutallus.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/chimerabeast_ok/x/chimerabeast.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/cockatriceelite_ok/x/cockatriceelite.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/crocodile_ok/x/crocodile.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/direfurbolg_ok/x/direfurbolg.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/doomguard_ok/x/doomguard.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/harpy_ok/x/harpy.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/raptor_ok/x/raptor.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/scorpion_ok/x/scorpion.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;

	tempObject = new monster;
	tempObject->_transform->SetScale(0.1f, 0.1f, 0.1f);

	tempX = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempZ = myUtil::RandomFloatRange(1.0f, 20.0f);
	tempY = _terrain->getHeight(tempX, tempZ);

	tempObject->_transform->SetWorldPosition(tempX, tempY, tempZ);
	tempObject->setRegenPosition(tempX, tempY, tempZ);
	tempObject->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/thunderlizard_ok/x/thunderlizard.x", mat));
	mon.push_back(tempObject);
	tempObject = nullptr;
}

void terrainPickingTest::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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
