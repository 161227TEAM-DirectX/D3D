#include "stdafx.h"
#include "cGameNodeTest.h"


cGameNodeTest::cGameNodeTest()
{
}


cGameNodeTest::~cGameNodeTest()
{
}

HRESULT cGameNodeTest::init()
{
	//����ī�޶� �ʱ�ȭ
	_mainCamera = new camera;

	//�⺻ ���� ����
	_sceneBaseDirectionLight = new lightDirection;

	//���⼺ ������ ī�޶� �� �����Ѵ�.
	_directionLightCamera = new camera;

	//�⺻ ��
	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;

	//�׸��� �Ÿ�
	_shadowDistance = 100.0f;

	//ī�޶��� ��������� �ٲ۴�...
	_directionLightCamera->_isOrtho = true;
	_directionLightCamera->_camNear = 0.1f;
	_directionLightCamera->_camFar = _shadowDistance * 2.0f;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = _shadowDistance * 1.5f;	//����ũ��� �׸���ũ���

																//���⼺���� ī�޶��� RenderToTexture �غ�
	_directionLightCamera->readyShadowTexture(4096);



	//���� Ŭ���� ������ �ʱ�ȭ
	_terrain = new terrain;
	_terrain->init(
		"Resources/Textures/MyHeight128.bmp",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/Splat.png",
		1.0f,
		200.0f,
		3,
		100);
	//�����׸��� Ŭ���� ������ �ʱ�ȭ
	_terrainShadow = new terrain();
	_terrainShadow->init(
		"Resources/Textures/MyHeight128.bmp",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/Splat.png",
		4.0f,
		200.0f,
		10,
		100);

	//���� �ִ� �Ž����� ������ ���� ��ķ� �������� 
	//��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.007f, 0.007f, 0.007f);
	D3DXMATRIXA16 matCorrection = matScale;

	//�ҳ��� �޽� �ε�
	xMeshStatic* mesh = RM_XMESH->getResource("Resources/Meshes/Tree/PineTree_01.X", &matCorrection);
	//���� �޽� �ε�
	xMeshStatic* Disc = RM_XMESH->getResource("Resources/Meshes/Disc/Disc.x");

	////������Ʈ ����
	//for (int i = 0; i < OBJECT_NUM; i++)
	//{
	//	for (int j = 0; j < OBJECT_NUM; j++)
	//	{
	//		baseObject* pNewObject = new baseObject;
	//		pNewObject->setMesh(mesh);
	//		pNewObject->setActive(true);

	//		//if( j % 2 == 0 )
	//		//pNewObject->IgnoreCreateShadow = true;	//�׸��� �ȱ׸�

	//		D3DXVECTOR3 pos(i * 10, 30.0f, j * 20);

	//		pos.y = this->_terrain->getHeight(pos.x, pos.z);

	//		//��ġ ����
	//		pNewObject->_transform->SetWorldPosition(pos);

	//		//���� ������Ʈ
	//		this->_renderObjects.push_back(pNewObject);
	//	}
	//}

	//��ũ �߰�
	//baseObject* pNewObject2 = new baseObject;
	//pNewObject2->setMesh( Disc );
	//pNewObject2->setActive( true );
	//pNewObject2->_transform->SetWorldPosition( 0, -10.0f, 0.0f );
	//pNewObject2->ignoreCreateShadow = true;		//�׸��� �ȱ׸���.
	//this->renderObjects.push_back( pNewObject2 );

	//�⺻����Ʈ ����
	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);

	D3DXMATRIXA16 matCorrection2;
	D3DXMatrixScaling(&matCorrection2, 1.0f, 1.0f, 1.0f);
	xMeshSkinned* pSkinned = RM_SKINNED->getResource("Resources/Meshes/Female/Femail.X", &matCorrection2);
	

	baseObject* pChar;
	pChar = new baseObject();
	pChar->setMesh(pSkinned);
	pChar->setActive(true);

	D3DXVECTOR3 pos2(-20, 0, 20);
	pos2.y = this->_terrain->getHeight(pos2.x, pos2.z);
	pChar->_transform->SetWorldPosition(pos2);

	_renderObjects.push_back(pChar);

	return S_OK;
}

void cGameNodeTest::release()
{
	//������Ʈ ����
	for (int i = 0; i < _renderObjects.size(); i++)
	{
		SAFE_DELETE(_renderObjects[i]);
	}
	
	SAFE_DELETE(_sceneBaseDirectionLight);
	SAFE_DELETE(_directionLightCamera);
	SAFE_DELETE(_terrain);
	SAFE_DELETE(_terrainShadow);
	SAFE_DELETE(_mainCamera);
}

void cGameNodeTest::update()
{
	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();
	_mainCamera->updateFrustum();

	//���� ��ġ
	D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();		//����ī�޶��� ��ġ
	D3DXVECTOR3 camFront = _mainCamera->GetForward();			//����ī�޶��� ����
	D3DXVECTOR3 lightDir = _sceneBaseDirectionLight->_transform->GetForward();	//���⼺ ������ ����

	D3DXVECTOR3 lightPos = camPos +
		(camFront * (_shadowDistance * 0.5f)) +
		(-lightDir * _shadowDistance);

	_directionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	_directionLightCamera->LookDirection(lightDir);

	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		_renderObjects[i]->update();
	}
	//������� �غ�
	this->readyShadowMap(&this->_renderObjects, this->_terrainShadow);
}

void cGameNodeTest::render()
{
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

	xMeshStatic::setCamera(_mainCamera);
	if (KEYMANAGER->isStayKeyDown('1'))
	{
		//������� ���� �׸����� ReciveShadow �� Technique ����
		xMeshStatic::setTechniqueName("CreateShadow");
	}
	else
	{
		//������� ���� �׸����� ReciveShadow �� Technique ����
		xMeshStatic::setTechniqueName("ReciveShadow");
	}

	xMeshStatic::setBaseLight(this->_sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resources/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
	}
	_terrain->render(_mainCamera, _sceneBaseDirectionLight, _directionLightCamera);
}

void cGameNodeTest::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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
		if (this->_directionLightCamera->_frustum.isInFrustum((*renderObjects)[i]))
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
		pTerrain->renderShadow(_directionLightCamera);
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
