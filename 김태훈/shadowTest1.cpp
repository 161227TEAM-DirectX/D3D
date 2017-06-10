#include "stdafx.h"
#include "shadowTest1.h"

HRESULT shadowTest1::init(void)
{
	//���� �ִ� �Ž����� ������ ���� ��ķ� �������� 
	//��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale, matRotate;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//���� �޽� �ε�
	xMeshStatic* mesh = RM_XMESH->getResource("Resources/Meshes/GunShip/gunShip.X", &matCorrection);
	xMeshStatic* box = RM_XMESH->getResource("Resources/Meshes/Disc/Disc.x");

	//������Ʈ ����
	baseObject* newObject1 = new baseObject();
	newObject1->setMesh(mesh);
	newObject1->setActive(true);

	baseObject* newObject2 = new baseObject();
	newObject2->setMesh(mesh);
	newObject2->setActive(true);
	newObject2->_transform->SetWorldPosition(0, -5.0f, 0.0f);

	baseObject* newObject3 = new baseObject();
	newObject3->setMesh(box);
	newObject3->setActive(true);
	newObject3->_transform->SetWorldPosition(0, -10.0f, 0.0f);
	newObject3->_ignoreCreateShadow = true;	//�׸��� �ȱ׸���.

	//���� ������Ʈ Ǫ��
	_renderObjects.push_back(newObject1);
	_renderObjects.push_back(newObject2);
	_renderObjects.push_back(newObject3);

	//����Ʈ ��ġ
	this->_sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	this->_sceneBaseDirectionLight->_transform->SetRotateWorld(D3DXToRadian(90), 0, 0);

	return S_OK;
}

void shadowTest1::release(void)
{
	//������Ʈ ����
	for (int i = 0; i < _renderObjects.size(); i++)
	{
		SAFE_DELETE(_renderObjects[i]);
	}
}

void shadowTest1::update(void)
{
	this->_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	_mainCamera->updateFrustum();
	_cullObjects.clear();

	for (int i = 0; i < _renderObjects.size(); i++)
	{
		_renderObjects[i]->update();

		//�������� �ȿ� �ִ�?
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{
			_cullObjects.push_back(_renderObjects[i]);
		}
	}

	//������� �غ�
	//�������� ������Ʈ �����Ѵ� (�ݵ�� Render���� �������� ������Ʈ���� �ض�)
	this->readyShadowMap(&_renderObjects);
}

void shadowTest1::render(void)
{
	xMeshStatic::setCamera(_mainCamera);
	//������� ���� �׸����� ReciveShadow �� Technique ����
	xMeshStatic::setTechniqueName("ReciveShadow");		
	//���̽� ������ ����
	xMeshStatic::setBaseLight(_sceneBaseDirectionLight);
	
	for (int i = 0; i < _cullObjects.size(); i++)
	{
		_cullObjects[i]->render();
	}

	//�������� �׷�����
	_directionLightCamera->_frustum.renderGizmo();
	_sceneBaseDirectionLight->_transform->RenderGimozo();
}

void shadowTest1::renderSprite(void)
{
	//������ ���� �׷�����....
	RECT rcSour = { 0, 0, 4096, 4096 };
	RECT rcDest = { 0, 0, 300, 300 };

	SPRITEMANAGER->renderArea(_directionLightCamera->getRenderTexture(), &rcSour, &rcDest);
}
