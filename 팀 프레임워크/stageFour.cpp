#include "stdafx.h"
#include "stageFour.h"
#include "Environment.h"
#include "WaterTerrain.h"
#include "mapObject.h"
#include "xPlayer.h"

HRESULT stageFour::clear(void)
{
	_shadowDistance = 0.0f;
	angleZ = 89;
	currTime = 0.0f;
	_mainCamera = nullptr;
	_directionLightCamera = nullptr;
	sceneBaseDirectionLight = nullptr;
	player = nullptr;
	env = nullptr;
	water = nullptr;
	toRotate = nullptr;
	objectSet = nullptr;
	cinematicBool = false;

	return S_OK;
}

void stageFour::destroy(void)
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
	SAFE_DELETE(objectSet);
}

HRESULT stageFour::init()
{
	_mainCamera = new camera;
	_directionLightCamera = new camera;
	sceneBaseDirectionLight = new lightDirection;
	player = new xPlayer;
	env = new Environment;
	water = new WaterTerrain;
	water->linkCamera(*_mainCamera);
	toRotate = new dx::transform;
	objectSet = new mapObject;

	this->shadowInit();

	_terrain = new terrain;
	_terrain->setHeightmap("���̸�_1");
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("��������").tile0, true);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("��������").tile1, true);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("��������").tile2, true);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("��������").tile3, true);
	_terrain->setSplat(IOMAPMANAGER->loadMapInfo("��������").splat, true);
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("��������").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	_terrainShadow = new terrain;
	_terrainShadow->setHeightmap("���̸�_1");
	_terrainShadow->setTile0(IOMAPMANAGER->loadMapInfo("��������").tile0, true);
	_terrainShadow->setTile1(IOMAPMANAGER->loadMapInfo("��������").tile1, true);
	_terrainShadow->setTile2(IOMAPMANAGER->loadMapInfo("��������").tile2, true);
	_terrainShadow->setTile3(IOMAPMANAGER->loadMapInfo("��������").tile3, true);
	_terrainShadow->setSplat(IOMAPMANAGER->loadMapInfo("��������").splat, true);
	_terrainShadow->setMapPosition(IOMAPMANAGER->loadMapInfo("��������").vecPos);
	_terrainShadow->setting();
	_terrainShadow->changeHeightTerrain();

	//ȯ��� �ʱ�ȭ
	env->init();
	env->linkCamera(*_mainCamera);

	water->init(3.0f, 256);

	//�� ������Ʈ �ʱ�ȭ
	IOSAVEOBJECTMANAGER->loadFile("���ۿ�����Ʈ");
	for (int i = 0; i < IOSAVEOBJECTMANAGER->getCount(); i++)
	{
		tagSaveObject object;
		memset(&object, 0, sizeof(tagSaveObject));

		object = IOSAVEOBJECTMANAGER->findTag("�ѹ�" + to_string(i + 1));
		baseObject* temp = new baseObject;
		D3DXMATRIX matRotate;
		objectSet->objectSet(object.objectNumber, temp, matRotate, object.objectX, object.objectY, object.objectZ, object.objectScale, object.objectRotate);

		_renderObject.push_back(temp);
	}


	//ȯ��� / ����� �ҷ�����
	IOSAVEMANAGER->loadFile("���ۼ��̺��");

	envTemp = IOSAVEMANAGER->findTag("ȯ���");
	waterTemp = IOSAVEMANAGER->findTag("�����");

	float tempY = _terrain->getHeight(0.0f, 0.0f);


	//�÷��̾� �ʱ�ȭ
	player->out_setlinkTerrain(*_terrain);
	player->init();
	player->getPlayerObject()->_transform->SetWorldPosition(0.0f, tempY, 0.0f);
	player->getPlayerObject()->_transform->SetScale(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < player->getRenderObject().size(); i++)
	{
		_renderObject.push_back(player->getRenderObject()[i]);
	}

	ACMANAGER->Init(*_terrain, *player);

	SOUNDMANAGER->play("�ʵ�1", 0.1f);
	

	//�ʱ�ȭ
	CINEMATICMANAGER->init();
	//�ε�Ȱ� ���� �ֱ� 
	CINEMATICMANAGER->cinematicE4Init();

	return S_OK;
}

void stageFour::release()
{
}

void stageFour::update()
{
	//�ó׸�ƽ �̺�Ʈ�� �ε� 
	CINEMATICMANAGER->cinematicE4Load(_mainCamera, CINEMATICMANAGER->GetGScineMticE4Bool());

	if (CINEMATICMANAGER->GetGScineMticE4Bool() == true)
	{
		if (cinematicBool == false)
		{
			_mainCamera->out_SetLinkTrans(player->getPlayerObject()->_transform);
			_mainCamera->out_SetRelativeCamPos(D3DXVECTOR3(0, 5, 5));
			cinematicBool = true;
		}
		else
		{
			_mainCamera->updateBase();
		}
	}

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
}

void stageFour::render()
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

	CINEMATICMANAGER->cinematicE4Render(_mainCamera);
}

void stageFour::shadowInit(void)
{
	//���� �⺻ �� �ʱ�ȭ
	sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight->_intensity = 1.0f;

	//�׸��ڸ� ���� ī�޶� �ڽ� ũ�� ������ ���� �ʱ�ȭ
	_shadowDistance = 100.0f;

	//�׸��� ī�޶��� ���� ��� ���� �� ���� / ���Ÿ� ũ�� ����
	_directionLightCamera->_isOrtho = true;	//��������
	_directionLightCamera->_camNear = 0.1f;	//�ٰŸ�
	_directionLightCamera->_camFar = _shadowDistance * 2.0f;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = _shadowDistance * 1.5f;	//����ũ��

																//�ؽ�ó �غ�
	_directionLightCamera->readyShadowTexture(4096);

	_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);

	sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);
}

void stageFour::shadowUpdate(void)
{
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
	this->readyShadowMap(&this->_renderObject, this->_terrainShadow);
}

void stageFour::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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
}
