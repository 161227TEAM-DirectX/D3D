#include "stdafx.h"
#include "kimsNewTest.h"


HRESULT kimsNewTest::init()
{
	SOUNDMANAGER->play("����1");
	_mainCamera = new camera;

	_directionLightCamera = new camera;

	_playerDirectionLightCamera = new camera;

	_sceneBaseDirectionLight = new lightDirection;

	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;

	_shadowDistance = 10.0f;

	//ī�޶��� ��������� �ٲ۴�...
	_directionLightCamera->_isOrtho = true;
	_directionLightCamera->_camNear = 0.1f;
	_directionLightCamera->_camFar = _shadowDistance *2.0;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = _shadowDistance * 1.5;	//����ũ��� �׸���ũ���
	_directionLightCamera->readyShadowTexture(4096);

	

	_playerDirectionLightCamera->_isOrtho = true;
	_playerDirectionLightCamera->_camNear = 0.1f;
	_playerDirectionLightCamera->_camFar = 15;
	_playerDirectionLightCamera->_aspect = 1;
	_playerDirectionLightCamera->_orthoSize = 15;	//����ũ��� �׸���ũ���
	_playerDirectionLightCamera->readyShadowTexture(4096);

	_terrain = new terrain;
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_3"));
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_1"));
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_2"));
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_3"));
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_4"));
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_1"));
	_terrain->setting();

	_terrainShadow = new terrain;
	_terrainShadow->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_3"));
	_terrainShadow->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_1"));
	_terrainShadow->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_2"));
	_terrainShadow->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_3"));
	_terrainShadow->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_4"));
	_terrainShadow->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_1"));
	_terrainShadow->setting();

//	_player = new xPlayer();
//	_player->init();

//	_hitPos = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIX mat;
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	mat = matRotate;

	_player = new xPlayer;
	_player->setlinkTerrain(*_terrain);
	_player->init();
	_player->getPlayerObject()->_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
	//	_player->getPlayerObject()->_transform->SetWorldPosition(20.0f, 0.0f, -20.0f);
	_player->getPlayerObject()->_transform->SetScale(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < _player->getRenderObject().size(); i++)
	{
	
		_renderObjects.push_back(_player->getRenderObject()[i]);
	}

	float tempY = _terrain->getHeight(0.0f, 0.0f);

	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);
	//	this->setEnvironment("Resource/TextureCUBE/SuperKanjiCube.dds");
	_env = new Environment;
	_env->init();
	_env->linkCamera(*_mainCamera);

	_mainCamera->SetWorldPosition(0.0f, 0.0f, 0.0f);
	_mainCamera->LookPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();
	_directionLightCamera->SetWorldPosition(camPos.x, camPos.y, camPos.z);
	/*lButtonState = SELECTFUNC::SELECT_NONE;

	sour = -1;
	dest = -1;*/


	return S_OK;
}

void kimsNewTest::release()
{

}

void kimsNewTest::update()
{
	_mainCamera->updateBase();
	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);


	//D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();		//����ī�޶��� ��ġ
	//D3DXVECTOR3 camFront = _mainCamera->GetForward();			//����ī�޶��� ����
	//D3DXVECTOR3 lightDir = _sceneBaseDirectionLight->_transform->GetForward();	//���⼺ ������ ����

	//D3DXVECTOR3 lightPos = camPos +
	//	(camFront * (_shadowDistance * 0.5f)) +
	//	(-lightDir * _shadowDistance);

	//D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();		//����ī�޶��� ��ġ

	D3DXVECTOR3 camPos = _player->getPlayerObject()->_transform->GetWorldPosition();	//����ī�޶��� ��ġ
	//D3DXVECTOR3 camFront = _mainCamera->GetForward();									//����ī�޶��� ����
	D3DXVECTOR3 lightDir = _sceneBaseDirectionLight->_transform->GetForward();			//���⼺ ������ ����

	_directionLightCamera->SetWorldPosition(camPos.x, 5, camPos.z);
	_directionLightCamera->LookDirection(lightDir);

	_player->update();

	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		_renderObjects[i]->update();
	}

	this->_cullObjects.clear();
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{

		//�������� �ȿ� �ִ�?
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{

			this->_cullObjects.push_back(_renderObjects[i]);
		}
	}

	//������� �غ�
	
}

void kimsNewTest::render()
{
	//ī�޶� �ø��ȰŸ�....
	

	_env->renderEnvironment(1);

	//if (KEYMANAGER->isStayKeyDown('0'))
	//{
	//	//������� ���� �׸����� ReciveShadow �� Technique ����
	//	xMeshStatic::setTechniqueName("CreateShadow");
	//}
	//else
	//{
	//	//������� ���� �׸����� ReciveShadow �� Technique ����
	//	
	//}

	xMeshStatic::setCamera(_mainCamera);
	//xMeshStatic::setTechniqueName("ReciveShadow");
	xMeshStatic::setTechniqueName("Toon");
	xMeshStatic::setBaseLight(this->_sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("CreateShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	_player->render();

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
		if (_cullObjects[i] == _player->getPlayerObject())
		{
			_player->itemUpdate();
		}
	}
	_terrain->render(_mainCamera, _sceneBaseDirectionLight, _directionLightCamera);
	
	
	this->readyShadowMap(&this->_cullObjects, this->_terrainShadow);


	_directionLightCamera->_frustum.renderGizmo();
	_mainCamera->_frustum.renderGizmo();
}


void kimsNewTest::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
{
	//���⼺������ ���� ī�޶��� Frustum ������Ʈ
	_directionLightCamera->updateMatrix();
	_directionLightCamera->updateFrustum();

	//���̷��Ƕ����� ī�޶� ������ �ֵ鸸 �׸���...
	//static vector<baseObject*>	shadowCullObject;
	//shadowCullObject.clear();

	//for (int i = 0; i < renderObjects->size(); i++)
	//{
		//�������� �ȿ� �ִ�?
	//	if (this->_mainCamera->_frustum.isInFrustum((*renderObjects)[i]))
	//	{
	//		shadowCullObject.push_back((*renderObjects)[i]);

	//	}
	//}

	//������ �� �׸���.
	_directionLightCamera->renderTextureBegin(0xffffffff);

	//�����޽� ����
	xMeshStatic::setCamera(this->_directionLightCamera);
	xMeshStatic::setTechniqueName("CreateShadow");
	//��Ų��޽� ����
	xMeshSkinned::setCamera(this->_directionLightCamera);
	xMeshSkinned::setTechniqueName("CreateShadow");

	for (int i = 0; i < (*renderObjects).size(); i++)
	{
		if ((*renderObjects)[i]->_ignoreCreateShadow == false)
		{
			(*renderObjects)[i]->render();
		}
	}

	//���� Terrain �� ������ ���� �׷����Ѵٸ�...
	if (pTerrain != NULL)
	{
		//pTerrain->renderShadow(_directionLightCamera);
	}

	_directionLightCamera->renderTextureEnd();


	//���� Terrain �� ������ ���� �����Ѵٸ�
	if (pTerrain != NULL)
	{
		pTerrain->_terrainEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
		pTerrain->_terrainEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
	}

	//������ �ؽ���
	xMeshStatic::_staticMeshEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
	//������ ���
	xMeshStatic::_staticMeshEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
	//������ �ؽ���
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
	//������ ���
	xMeshSkinned::_sSkinnedMeshEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
}