#include "stdafx.h"
#include "shadowTest2.h"

HRESULT shadowTest2::init(void)
{
	//���� Ŭ���� ������ �ʱ�ȭ
	_terrain = new terrain;
	_terrain->init(
		"Resources/Textures/MyHeight512.bmp",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/terrain2.png",
		"Resources/Textures/terrain3.png",
		"Resources/Textures/terrain4.png",
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
		"Resources/Textures/terrain2.png",
		"Resources/Textures/terrain3.png",
		"Resources/Textures/terrain4.png",
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

	//������Ʈ ����
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		for (int j = 0; j < OBJECT_NUM; j++)
		{
			baseObject* pNewObject = new baseObject;
			pNewObject->setMesh(mesh);
			pNewObject->setActive(true);

			//if( j % 2 == 0 )
			//pNewObject->IgnoreCreateShadow = true;	//�׸��� �ȱ׸�

			D3DXVECTOR3 pos(i * 10, 30.0f, j * 20);

			pos.y = this->_terrain->getHeight(pos.x, pos.z);

			//��ġ ����
			pNewObject->_transform->SetWorldPosition(pos);

			//���� ������Ʈ
			//this->_renderObjects.push_back(pNewObject);
		}
	}

	//��ũ �߰�
	//baseObject* pNewObject2 = new baseObject;
	//pNewObject2->setMesh( Disc );
	//pNewObject2->setActive( true );
	//pNewObject2->_transform->SetWorldPosition( 0, -10.0f, 0.0f );
	//pNewObject2->ignoreCreateShadow = true;		//�׸��� �ȱ׸���.
	//this->renderObjects.push_back( pNewObject2 );

	//�⺻����Ʈ ����
	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);
	this->setEnvironment("Resources/TextureCUBE/SuperKanjiCube.dds");

	D3DXMATRIXA16 matCorrection2;
	D3DXMatrixScaling(&matCorrection2, 0.1f, 0.1f, 0.1f);
	xMeshSkinned* pSkinned = RM_SKINNED->getResource("Resources/Meshes/Female/Femail.X", &matCorrection2);

	baseObject* pChar;
	pChar = new baseObject();
	pChar->setMesh(pSkinned);
	pChar->setActive(true);

	D3DXVECTOR3 pos2(0, 0, 0);
	//pos2.y = this->_terrain->getHeight(pos2.x, pos2.z);
	pChar->_transform->SetWorldPosition(pos2);

	this->_renderObjects.push_back(pChar);

	return S_OK;
}

void shadowTest2::release(void)
{
	//������Ʈ ����
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}
	//������ �����׸��� ����
	SAFE_DELETE(this->_terrain);
	SAFE_DELETE(this->_terrainShadow);
}

void shadowTest2::update(void)
{
	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		_renderObjects[i]->update();
	}
	//������� �غ�
	this->readyShadowMap(&this->_renderObjects, this->_terrainShadow);
}

void shadowTest2::render(void)
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
	//_terrain->render(_mainCamera, _sceneBaseDirectionLight, _directionLightCamera);
}

void shadowTest2::renderSprite(void)
{

}
