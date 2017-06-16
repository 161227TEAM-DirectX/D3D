#include "stdafx.h"
#include "kimsTestScene.h"

HRESULT kimsTestScene::init(void)
{
	_terrain = new terrain;
	_terrain->init(
		"Resources/Textures/MyHeight512.bmp",
		"Resources/Textures/Sheep_terrain1.jpg",
		"Resources/Textures/Sheep_terrain2.jpg",
		"Resources/Textures/Sheep_terrain3.jpg",
		"Resources/Textures/Sheep_terrain4.jpg",
		"Resources/Textures/Sheep_Splat.bmp",
		1.0f,
		200.0f,
		3,
		100);

	_terrainShadow = new terrain;
	_terrainShadow->init(
		"Resources/Textures/MyHeight512.bmp",
		"Resources/Textures/Sheep_terrain1.jpg",
		"Resources/Textures/Sheep_terrain2.jpg",
		"Resources/Textures/Sheep_terrain3.jpg",
		"Resources/Textures/Sheep_terrain4.jpg",
		"Resources/Textures/Sheep_Splat.bmp",
		4.0f,
		200.0f,
		10,
		100);


	_trans = new dx::transform;
	_dirLight = new lightDirection;
	_hitPos = D3DXVECTOR3(0, 0, 0);

	//	tempDijkstra = new dijkstra;

	float tempY = _terrain->getHeight(0.0f, 0.0f);

	//임시 플레이어 코드
	D3DXMATRIX mat;
	//	D3DXMATRIX matScaling;
	D3DXMATRIX matRotate;
	//	D3DXMatrixScaling(&matScaling, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	mat = /*matScaling **/ matRotate;

	//enemy = new baseObject;
	//enemy->setMesh(RM_XMESH->getResource("Resources/Meshes/monster/thunderlizard_ok/x/thunderlizard.x", mat));
	//enemy->_transform->SetScale(0.1f, 0.1f, 0.1f);
	//enemy->setActive(true);
	//this->_renderObjects.push_back(enemy);

	_player = new xPlayer;
	_player->setlinkTerrain(*_terrain);
	_player->init();
	_player->getPlayerObject()->_transform->SetWorldPosition(D3DXVECTOR3(3, 0, 0));
	for (int i = 0; i < _player->getRenderObject().size(); i++)
	{
		_renderObjects.push_back(_player->getRenderObject()[i]);
	}



	////임시 몬스터 구현 코드
	//player = new monster;
	//player->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/thunderlizard_ok/x/thunderlizard.x", mat));
	//player->_transform->SetWorldPosition(0.0f, tempY, 0.0f);
	//player->setRegenPosition(0.0f, tempY, 0.0f);
	//player->LinkObject(testObject);
	//player->LinkTerrain(*_terrain);
	//player->LinkPlayer(_player->getPlayerObject());
	//player->setActive(true);
	//this->_renderObjects.push_back(player);
	//D3DXMatrixScaling(&matScaling, 0.5f, 0.5f, 0.5f);
	//mat = matScaling * matRotate;

	//boss = new bossMonster;
	//boss->setMesh(RM_SKINNED->getResource("Resources/Meshes/BossMonster/deathwing_ok/x/deathWing.x", mat));
	//boss->_transform->SetScale(0.5f, 0.5f, 0.5f);
	//boss->_transform->SetWorldPosition(0.0f, tempY, 0.0f);
	//boss->LinkObject(testObject);
	//boss->LinkTerrain(*_terrain);
	//boss->LinkPlayer(enemy);
	//boss->setActive(true);
	//this->_renderObjects.push_back(boss);

	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(70), 0, 0);
	this->setEnvironment("Resources/TextureCUBE/SuperKanjiCube.dds");

	//_mainCamera->SetWorldPosition(0.0f, 60.0f, 10.0f);
	//_mainCamera->LookPosition(boss->_transform->GetWorldPosition());

	////라이트 세팅
	//lightDirection* light1 = new lightDirection;
	//light1->_color = D3DXCOLOR(1, 1, 1, 1);
	//light1->_intensity = 1.0f;

	//lightPoint* light2 = new lightPoint;
	//light2->_color = D3DXCOLOR(1, 0, 0, 0);
	//light2->_minRange = 5.0f;
	//light2->_maxRange = 10.0f;
	//light2->_distancePow = 10.0f;

	//lightPoint* light3 = new lightPoint;
	//light3->_color = D3DXCOLOR(0, 1, 0, 0);
	//light3->_minRange = 5.0f;
	//light3->_maxRange = 10.0f;
	//light3->_distancePow = 10.0f;
	//light3->_transform->SetWorldPosition(3, 3, 0);
	//light3->_intensity = 0.5f;

	//_lights.push_back(light1);
	//_lights.push_back(light2);
	//_lights.push_back(light3);

	lButtonState = SELECTFUNC::SELECT_NONE;

	sour = -1;
	dest = -1;



	_player->setTargetMonster(*player);


	D3DXVECTOR3 pos = _player->getPlayerObject()->_transform->GetWorldPosition();
	pos.y = pos.y + 5;
	pos.z = pos.z - 5;
	gameNode::_mainCamera->SetWorldPosition(pos);
	gameNode::_mainCamera->LookPosition(_player->getPlayerObject()->_transform->GetWorldPosition());
	_mainCamera->AttachTo(_player->getPlayerObject()->_transform);


	_thrall = new xNpc;
	_thrall->setlinkTerrain(*_terrain);
	_thrall->init(0, 0, "상인쓰랄");

	_sylvanas = new xNpc;
	_sylvanas->setlinkTerrain(*_terrain);
	_sylvanas->init(0, 5, "시바나스");

	//_thrall->setCamera(_mainCamera);
	//_renderObjects.push_back(_sylvanas->getNpcObject());
	//_renderObjects.push_back(_thrall->getNpcObject());

	SOUNDMANAGER->play("마을1", 0.5f);

	return S_OK;
}

void kimsTestScene::release(void)
{
	//_player->release();
	

	//_thrall->release();
	

	//오브젝트 해제
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}
	SAFE_DELETE(_player);

	SAFE_DELETE(_thrall);

	SAFE_DELETE(_sylvanas);

	//지형과 지형그림자 해제
	SAFE_DELETE(this->_terrain);
	SAFE_DELETE(this->_terrainShadow);
	SAFE_DELETE(this->_trans);

	/*_terrain->release();
	SAFE_DELETE(_terrain);
	SAFE_DELETE(_trans);
	SAFE_DELETE(_dirLight);*/
	//	SAFE_DELETE(tempDijkstra);
}

void kimsTestScene::update(void)
{

	//사운드 재생
	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		SOUNDMANAGER->play("필드1");
	}
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		SOUNDMANAGER->play("마을1");
	}

	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	_thrall->setCamera(this->_mainCamera);
	_sylvanas->setCamera(this->_mainCamera);
	_thrall->update();
	_sylvanas->update();
	_player->update();
	
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		_renderObjects[i]->update();
	}
	//쉐도우맵 준비
	
	this->readyShadowMap(&this->_renderObjects, this->_terrainShadow);
	

	//player._skTransform->DefaultMyControl(_timeDelta);
	//enemy->update();
	//boss->update();
}

void kimsTestScene::render(void)
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
	xMeshStatic::setTechniqueName("Toon");
	xMeshStatic::setBaseLight(this->_sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resources/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);
	
	_terrain->render(_mainCamera, _sceneBaseDirectionLight, _directionLightCamera);

	_player->render();
	_thrall->render();

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
		if (_cullObjects[i] == _player->getPlayerObject())
		{
			_player->itemUpdate();
		}
	}
	


	//_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//포그세팅 0xff806A12
	//_device->SetRenderState(D3DRS_FOGENABLE, TRUE);					//포그 사용여부
	//_device->SetRenderState(D3DRS_FOGCOLOR, 0xff806A12);			//포그 색상
	//_device->SetRenderState(D3DRS_FOGSTART, FloatToDWORD(10.0f));	//포그 시작 거리
	//_device->SetRenderState(D3DRS_FOGEND, FloatToDWORD(100.0f));	//포그 종료 거리
	//_device->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);		//포그선형 모드
	//_terrain->render(_mainCamera, _dirLight);
	//_device->SetRenderState(D3DRS_FOGENABLE, false);

	//렌더시킬 조명행렬 초기화 (각각의 라이트 클래스안에 만들어져있음)
	//D3DXMATRIXA16 matLights[10];
	//for (int i = 0; i < _lights.size(); i++)
	//{
	//	matLights[i] = _lights[i]->getLightMatrix();
	//}

	//셰이더에 라이트 세팅
	//xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	//xMeshStatic::_staticMeshEffect->SetInt("LightNum", _lights.size());
	//세이더에 카메라 세팅
	//xMeshStatic::setCamera(_mainCamera);

	//xMeshSkinned::_sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	//xMeshSkinned::_sSkinnedMeshEffect->SetInt("LightNum", _lights.size());
	//xMeshSkinned::setCamera(_mainCamera);

	//enemy->render();

	//if (enemy->_mesh != nullptr)
	//{
	//	셰이더에 라이트 세팅
	//	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	//	xMeshStatic::_staticMeshEffect->SetInt("LightNum", _lights.size());
	//	세이더에 카메라 세팅
	//	xMeshStatic::setCamera(_mainCamera);
	//}
	//
	//if (enemy->_mesh != nullptr)
	//{
	//	xMeshSkinned::_sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	//	xMeshSkinned::_sSkinnedMeshEffect->SetInt("LightNum", _lights.size());
	//	xMeshSkinned::setCamera(_mainCamera);
	//}


	//	boss->render();

	//if (!testObject.empty())
	//{
	//	for (size_t i = 0; i < testObject.size(); i++)
	//	{
	//		testObject[i]->render();
	//	}
	//}

	//	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

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
		for (int i = _terrain->getDijkstra().getPath().size() - 1; i >= 0; --i)
		{
			sprintf_s(tempchar, "%d->", _terrain->getDijkstra().getPath()[i]);
			FONTMANAGER->fontOut(tempchar, 195 + position * 55, 85, 0xffffffff);
			position++;
		}
	}


	////Hit 위치에 구만들기
	//GIZMOMANAGER->WireSphere(_hitPos, 0.5f, 0xffff0000);
	//
	////Trans 위치에 구
	//GIZMOMANAGER->WireSphere(_trans->GetWorldPosition(), 1.0f, 0xffff00ff);
	//_trans->RenderGimozo();
}

void kimsTestScene::lButtonStateChange(void)
{
	if (KEYMANAGER->isOnceKeyDown('1')) lButtonState = SELECTFUNC::SELECT_NODE;
	else if (KEYMANAGER->isOnceKeyDown('2')) lButtonState = SELECTFUNC::SELECT_LINE;
	else if (KEYMANAGER->isOnceKeyDown('3')) lButtonState = SELECTFUNC::SELECT_MOVING;
	else if (KEYMANAGER->isOnceKeyDown('4')) lButtonState = SELECTFUNC::SELECT_OBJECT;
	else if (KEYMANAGER->isOnceKeyDown('5')) lButtonState = SELECTFUNC::SELECT_NONE;
}

void kimsTestScene::selectLButton(void)
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
		case kimsTestScene::SELECT_NODE:
			//Terrain 이랑 Ray체크
			if (_terrain->isIntersectRay(&_hitPos, &ray))
			{
				_terrain->getDijkstra().addNode(_hitPos);
				//tempDijkstra->addNode(_hitPos);
			}
			break;
		case kimsTestScene::SELECT_LINE:

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
		case kimsTestScene::SELECT_MOVING:
		{
			if (_terrain->isIntersectRay(&_hitPos, &ray))
			{
				//player.getAction().setRand(_terrain);
				//	tempDijkstra->FindPath(_hitPos, player->_skTransform->GetWorldPosition()/*, testObject*/);
				//	player->setNextAction(tempDijkstra->OptimizedAction(*player, _terrain, testObject, player->_skTransform->GetWorldPosition(), _hitPos));
			}
		}
		break;
		case kimsTestScene::SELECT_OBJECT:
			if (_terrain->isIntersectRay(&_hitPos, &ray)) addObject();
			break;
		case kimsTestScene::SELECT_NONE:
			break;
		}
	}
}

void kimsTestScene::addObject(void)
{
	enemy->_transform->SetWorldPosition(_hitPos);
}